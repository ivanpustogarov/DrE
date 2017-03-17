//===-- PathManager.cpp ------------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Common.h"
#include "klee/PathManager.h"
#include "Context.h"
#include "CoreStats.h"
#include "ExternalDispatcher.h"
#include "ImpliedValue.h"

#include "../Solver/SolverStats.h"

#include "klee/TimerStatIncrementer.h"
#include "klee/CommandLine.h"
#include "klee/Common.h"
#include "klee/util/Assignment.h"
#include "klee/util/ExprPPrinter.h"
#include "klee/util/ExprSMTLIBPrinter.h"
#include "klee/util/ExprUtil.h"
#include "klee/util/GetElementPtrTypeIterator.h"
#include "klee/Config/Version.h"
#include "klee/Internal/ADT/KTest.h"
#include "klee/Internal/ADT/RNG.h"
#include "klee/Internal/Module/Cell.h"
#include "klee/Internal/Module/InstructionInfoTable.h"
#include "klee/Internal/Module/KInstruction.h"
#include "klee/Internal/Module/KModule.h"
#include "klee/Internal/Support/FloatEvaluation.h"
#include "klee/Internal/System/Time.h"
#include "klee/Internal/System/MemoryUsage.h"

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
#include "llvm/IR/Function.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/TypeBuilder.h"
#else
#include "llvm/Attributes.h"
#include "llvm/BasicBlock.h"
#include "llvm/Constants.h"
#include "llvm/Function.h"
#include "llvm/Instructions.h"
#include "llvm/IntrinsicInst.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#if LLVM_VERSION_CODE <= LLVM_VERSION(3, 1)
#include "llvm/Target/TargetData.h"
#else
#include "llvm/DataLayout.h"
#include "llvm/TypeBuilder.h"
#endif
#endif
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/raw_ostream.h"

#if LLVM_VERSION_CODE < LLVM_VERSION(3, 5)
#include "llvm/Support/CallSite.h"
#else
#include "llvm/IR/CallSite.h"
#endif

#include <cassert>
#include <algorithm>
#include <iomanip>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <sys/mman.h>

#include <errno.h>
#include <cxxabi.h>
#include <iostream>

using namespace llvm;
using namespace klee;


#ifdef SUPPORT_METASMT

#include <metaSMT/frontend/Array.hpp>
#include <metaSMT/backend/Z3_Backend.hpp>
#include <metaSMT/backend/Boolector.hpp>
#include <metaSMT/backend/MiniSAT.hpp>
#include <metaSMT/DirectSolver_Context.hpp>
#include <metaSMT/support/run_algorithm.hpp>
#include <metaSMT/API/Stack.hpp>
#include <metaSMT/API/Group.hpp>

#define Expr VCExpr
#define Type VCType
#define STP STP_Backend
#include <metaSMT/backend/STP.hpp>
#undef Expr
#undef Type
#undef STP

using namespace metaSMT;
using namespace metaSMT::solver;

#endif /* SUPPORT_METASMT */


PathManager::PathManager(std::string start_function_name, std::string target_function_name, KModule *_kmodule)
{
  kmodule = _kmodule;
  //call_graph.runOnModule(*(kmodule->module));
  path_main_routine(start_function_name, target_function_name);
}

PathManager::~PathManager() {
}

/***/


/* Combine function names into one string: "f1() -> f2() -> ..." */
std::string PathManager::fvector_to_string(PathManager::FVector fvector)
{
  std::string ret = fvector[0]->getName().str() + "()";
  int sz = fvector.size();
  int i;
  for(i=1;i<sz;i++)
    ret = ret + " -> " +  fvector[i]->getName().str() + "()";
  return ret;
}


std::vector<llvm::CallGraphNode *> get_shortest_path(std::set<std::vector<llvm::CallGraphNode *> > &B)
{
  unsigned min_size = UINT_MAX;
  std::vector<llvm::CallGraphNode *> shortest_path;
  assert(!B.empty());
  for(std::set<std::vector<llvm::CallGraphNode *> >::iterator it = B.begin(); it != B.end(); ++it)
  {
    if(it->size() < min_size)
    {
      min_size = it->size();
      shortest_path = *it;
    }
  }
  return shortest_path;
}



/* Find K shortest paths in the call graph from source <s> to target <t>
 * notations are the same as in
 * https://en.wikipedia.org/wiki/K_shortest_path_routing */
std::set<std::vector<llvm::CallGraphNode *> > PathManager::kshortest_call_graph(llvm::CallGraph &V, 
                  llvm::CallGraphNode *s, llvm::CallGraphNode *t)
{
  std::set<std::vector<llvm::CallGraphNode *> > P; // Set of shortest paths from <s> to <t>
  //std::set<std::vector<llvm::CallGraphNode *>,classcompB > B; // Working set of paths 
  std::set<std::vector<llvm::CallGraphNode *> > B; // Working set of paths 
  llvm::CallGraphNode *u = NULL; // u is the current node
  llvm::CallGraphNode *v = NULL; // v is used when we iterate
  std::vector<llvm::CallGraphNode *> P_u;
  std::vector<llvm::CallGraphNode *> P_v;
  int K = 4; // Number of of shortest paths
  std::vector<llvm::CallGraphNode *> P_s; // From <s> to <s>
  P_s.push_back(s);
  std::map<llvm::CallGraphNode *, unsigned> count;

  /* count[u] = 0, for all u in V */ 
  for (llvm::CallGraph::iterator u = V.begin(); u != V.end(); ++u)
    count[u->second] = 0;

  B.insert(P_s);
  std::set<llvm::Function *> seen;

  while(!B.empty() && (count[t] < K))
  {
    //llvm::outs() << "PathManager::kshortest_call_graph(): Next while iteration with B.size() = " << B.size() << "\n";
    P_u = get_shortest_path(B);
    //P_u = *(B.begin());
    u = P_u[P_u.size()-1];
    //llvm::outs() << "PathManager::kshortest_call_graph(): considering node " << u->getFunction()->getName() << "()\n";
    count[u]++;
    //B.erase(P_u);
    if(u == t) P.insert(P_u);
    if(count[u] <= K)
    {
      /* For each vertex v adjacent to u */
      //llvm::outs() << "PathManager::kshortest_call_graph(): looking for neighbours\n";
      seen.clear();
      for (llvm::CallGraphNode::iterator cr = u->begin(), cr_end = u->end(); cr != cr_end; ++cr)
      {
        v = cr->second;  // cr is a CallGraphNode::CallRecord, we need to extract CallGraphNode from it.
        if(!(v->getFunction()) || seen.count(v->getFunction())) continue;
        //llvm::outs() << "PathManager::kshortest_call_graph(): looking at " << v->getFunction()->getName() << "()\n";
        if(std::find(P_u.begin(),P_u.end(), v) == P_u.end())
        {
          P_v = P_u;
          P_v.push_back(v);
          //llvm::outs() << "PathManager::kshortest_call_graph(): adding P_v for " 
          //             << v->getFunction()->getName() << "(); path size = " << P_v.size()
          //             << "\n";
          //if(B.count(P_v))
          //  llvm::outs() << "Already exisits\n";
          B.insert(P_v);
        }
        seen.insert(v->getFunction());
      }
    }
    B.erase(P_u);
  }
  //llvm::outs() << "PathManager::kshortest_call_graph(): P.size() = " << P.size() << " and here are the paths:\n";
  //for(std::set<std::vector<llvm::CallGraphNode *> >::iterator it = P.begin(); it != P.end(); ++it)
  //{
  //  for(int i = 0;i < it->size(); i++)
  //    llvm::outs() << it->at(i)->getFunction()->getName() << "()" << ((i != (it->size()-1) ) ? " -> " : "");
  //  llvm::outs() << "\n";
  //}
  return P;
}

/* Dijkstra algorithm for finding shortets paths in the program's call
 * graph. Nodes are functions.
 *
 * @param call_graph Look for shortest paths in this graph
 * @param st The source vertex for Dijkstra algorithm
 * @param target_node We are interested in shortest path to this node 
 * @return Vector of functions representing the shortest call path from <st> to <target_node>
 */
PathManager::FVector PathManager::Dijkstra_call_graph(llvm::CallGraph &call_graph, llvm::CallGraphNode *st, llvm::CallGraphNode *target_node)
{
  PathManager::FVector ret;
  int count;
  int num_vertices = 0;
  unsigned int min_=UINT_MAX;
  unsigned int v_dist = UINT_MAX;
  std::string st_name = st->getFunction()->getName();
  llvm::CallGraphNode *u = NULL; // u is the current node with minumum distance to the source,
  llvm::CallGraphNode *v = NULL; // v is used when we iterate
  std::map<llvm::CallGraphNode *, unsigned int> distance;
  std::set<llvm::CallGraphNode *> visited;
  std::map<llvm::CallGraphNode *,PathManager::FVector>  path; // PathManager::FVector contains functions in between

  //std::map<llvm::CallGraphNode *, const llvm::Function *> nodeToFunc; /* We need this map since CllaGraphNode::CallRecord::getFunctio() returns NULL sometimes  */

  for (llvm::CallGraph::iterator it = call_graph.begin(); it != call_graph.end(); ++it)
  {
    v = it->second;  // v is a CallRecord, we need to extract CallGraphNode from it.
    //const llvm::Function *v_func = it->first;
    llvm::Function *v_func = v->getFunction();
    if (v_func == NULL)
      continue;
    //llvm::outs() << "PathManager::Dijkstra_call_graph(): adding node for function " << v_func->getName() << "().\n";
    llvm::outs() << "PathManager::Dijkstra_call_graph(): adding node for function " << 
                    v->getFunction()->getName() << "() @ " << v << ".\n";
    num_vertices++;
    //if (v != st)
    distance[v] = UINT_MAX;
    path[v].push_back(st->getFunction());
    //nodeToFunc[v] = v_func;
  }
  distance[st]=0;

  llvm::outs() << "PathManager::Dijkstra_call_graph(): number of vertices on the callgraph = " << num_vertices << ".\n";

  for (count=0; count<num_vertices-1; count++)
  {
    min_=UINT_MAX;

    /* Iterate through all nodes (including the source node) and find the node
     * with minumum distance to source. During the first outer loop
     * iteration it's going to be the source node.
     */
    llvm::outs() << "PathManager::Dijkstra_call_graph(): **** ; distance.size() = " << distance.size() << "\n";
    u = NULL;
    unsigned ind;
    ind = 0;
    for (std::map<llvm::CallGraphNode *,unsigned int>::iterator it=distance.begin(); it!=distance.end(); ++it)
    {
      v = it->first;
      v_dist = it->second;
      llvm::outs() << "PathManager::Dijkstra_call_graph(): distance[" << ind << "] = " << v_dist 
                   << " v = " << v << "(" << v->getFunction()->getName() << ").\n";
      if(visited.count(v))
        llvm::outs() << "PathManager::Dijkstra_call_graph(): skipping distance[" << ind << "] = " << v_dist << ".\n";
      if (!(visited.count(v)) && (v_dist < min_) )
      {
          min_ = v_dist;
          llvm::outs() << "PathManager::Dijkstra_call_graph(): min_ = " << v_dist << ".\n";
          llvm::outs() << "PathManager::Dijkstra_call_graph(): u changed to " << v->getFunction()->getName() << ".\n";
          u = v;
      }
      ind++;
    }
    if(!u)
    {
      if(path[target_node].size() == 1)
        klee_error("No call path to target function\n");
      return path[target_node];
    }

    visited.insert(u);
    if(u->getFunction())
      llvm::outs() << "PathManager::Dijkstra_call_graph(): we have new current node u: " << u->getFunction()->getName() <<
                   "; it has " << u->size() << " neighbours.\n";
    else
      llvm::outs() << "PathManager::Dijkstra_call_graph(): we have new current node u: NULL.\n";
    //llvm::outs() << "PathManager::Dijkstra_call_graph(): we have new current node: " << nodeToFunc[u]->getName() << ".\n";

    llvm::outs() << "PathManager::Dijkstra_call_graph(): ++++ ; distance.size() = " << distance.size() << "\n";
    /* Go through all unvisited neighbours of <u> and update their
     * distances to the source to DIST(u)+1 */
    for (llvm::CallGraphNode::iterator cr = u->begin(), cr_end = u->end(); cr != cr_end; ++cr)
    {
      v = cr->second;  // cr is a CallGraphNode::CallRecord, we need to extract CallGraphNode from it.
      if(!distance.count(v))
      {
        llvm::outs() << "PathManager::Dijkstra_call_graph(): Warning no distance information for neighbour v = " << v << " (skipping)!\n"; 
        continue;
      }
      //llvm::outs() << "                                 $$ ; neighbour = " << v->getFunction()->getName() <<
      llvm::outs() << "                                 $$ ;" <<
                                                        " u = " << u << "; v = " << v << 
                                                        "; distance.size() = " << distance.size() << "\n";
      if ( !visited.count(v)  && (distance[u] != UINT_MAX) &&  ((distance[u]+1) < distance[v]) )
      {
        distance[v] = distance[u]+1;
        llvm::outs() << "PathManager::Dijkstra_call_graph(): new distance for: " << v->getFunction()->getName()
                     << "() = " << distance[v] << ", v = " << v << "; u = " << u << ".\n";
        path[v].assign(path[u].begin(), path[u].end());
        path[v].push_back(v->getFunction());
      }
      llvm::outs() << "                                 $$2 ;" <<
                                                        " u = " << u << "; v = " << v << 
                                                        "; distance.size() = " << distance.size() << "\n";
    }
    llvm::outs() << "PathManager::Dijkstra_call_graph(): ---- ; distance.size() = " << distance.size() << "\n";
  }
  return path[target_node];
}

/* Check if basic block <b> contains a retrun instruction */
bool ICFGPath::contains_ret_instr(llvm::BasicBlock *b)
{
    outs() << "--\n";
    for (llvm::BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; ++i)
    {
      ReturnInst* retInst = dyn_cast<ReturnInst>(&*i);
      outs() << *i << "\n";
      if (retInst)
      {
	      return true;
      }
    }
    return false;
}

/* Dijkstra algorithm for finding shortets paths between two basic
 * blocks in a function's control flow graph. Nodes are basic blocks.
 *
 * Note: target_bb can be NULL, in this case we are interested in the
 * shortest path to a basic block with a return instruction.
 *
 * @param parent_f Consider CFG of this function
 * @param entry_bb The source vertex for Dijkstra algorithm
 * @param target_bb We are interested in shortest path to this node (can be NULL, see the note above)
 * @param exclude_arcs Exclude these arc from CFG when considering shortest paths
 * @return Vector of functions representing the shortest call path from <st> to <target_node>
 */
ICFGPath::BBVector ICFGPath::Dijkstra_cfg(llvm::Function *parent_f,
                                          llvm::BasicBlock *entry_bb,
                                          llvm::BasicBlock *target_bb,
                                          std::vector<std::pair<llvm::BasicBlock *, llvm::BasicBlock *> > *exclude_arcs)
{
  assert(parent_f && "Start function cannot be NULL");
  assert(entry_bb && "Start node (basic block) cannot be NULL");
  PathManager::BBVector ret;
  int count;
  int num_vertices = 0;
  int min_=INT_MAX;
  //string st_name = st->getFunction()->getName();
  llvm::BasicBlock *u; // u is the current node with minumum distance to the source,
  llvm::BasicBlock *v; // v is used when we iterate
  std::map<llvm::BasicBlock *,int> distance;
  std::set<llvm::BasicBlock *> visited;
  std::map<llvm::BasicBlock *, PathManager::BBVector> path; // PathManager::BBVector contains blocks between entry_bb and another basicblock

  // Initialization: find number of vertices, set distance to infinity, set the first node in the path as entry_bb
  for (llvm::Function::iterator v = parent_f->begin(); v != parent_f->end(); ++v) // v is BasicBlock iterator
  {
    num_vertices++;
    distance[(&*v)] = INT_MAX;
    path[(&*v)].push_back(entry_bb); // Beginning of each path is entry basic block
    // If taget_bb == NULL, the the caller of this function asked us to make a path from entry to RET instruction
    if(!target_bb && contains_ret_instr(&*v))
    {
      outs() << "Contains ret\n";
      target_bb = &*v;
      //#define IVAN
      #ifdef IVAN
      const llvm::TerminatorInst *t_inst = target_bb->getTerminator();
      outs() <<  "Function " << parent_f->getName() 
	     << ": basic block has ret instruction:\n      " 
	     << *t_inst << "\n";
      #endif
      #undef IVAN
    }
  }
  /* If there's no return instruction (prob) infinite loop, then we
   * return empty path */
  if(!target_bb)
  {
    PathManager::BBVector v;
    return v;
  }
  distance[entry_bb]=0;

  for (count=0; count<num_vertices-1; count++)
  {
    min_=INT_MAX;
    // Find the node with minumum distance to source
    for (std::map<llvm::BasicBlock *,int>::iterator it=distance.begin(); it!=distance.end(); ++it)
    {
      v = it->first;
      int v_dist = it->second;
      if (!visited.count(v) && v_dist <= min_)
        {min_=v_dist; u=v;}
    }
    // Mark node as visited: we will parse all its neightbours below
    visited.insert(u);
    // Go through all neightbours of the the minimum-distance node
    const llvm::TerminatorInst *TInst = u->getTerminator();
    //for (CallGraphNode::iterator cr = u->begin(), cr_end = u->end(); cr != cr_end; ++cr)
    for (unsigned i = 0, NSucc = TInst->getNumSuccessors(); i < NSucc; ++i) 
    {
      llvm::BasicBlock *v = TInst->getSuccessor(i);
      // Skip neighbours for which we exluded arcs to them
      if(exclude_arcs && (std::find(exclude_arcs->begin(), exclude_arcs->end(), std::make_pair(u,v)) != exclude_arcs->end()))
        continue;
      if ( !visited.count(v)  && distance[u]!=INT_MAX &&  distance[u]+1 < distance[v])
      {
        distance[v]=distance[u]+1;
        path[v].assign(path[u].begin(), path[u].end());
        path[v].push_back(v);
      }
    }
  }
  //assert( (*(path[target_bb].end()-1) == target_bb) && "Path to target_bb does not end at target_bb");
  /* If there is no path from entry_bb to target_bb, return emtpy vector */
  assert(target_bb);
  if(*(path[target_bb].end()-1) != target_bb)
  {
    PathManager::BBVector v;
    return v;
  }
  return path[target_bb];
}

/* A wrapper function over Dijkstra_call_graph(): create call_graph on the
 * curren llvm module and call Dijkstra_call_graph() */
PathManager::FVector PathManager::get_call_graph_path(llvm::Function *entry_func, llvm::Function *target_func)
{
  if(target_func == NULL)
    klee_error("Could not find target function in the code: %s()\n",target_func->getName().str().c_str());
  if(entry_func == NULL)
    klee_error("Could not find entry function in the code: %s()\n",entry_func->getName().str().c_str());

  llvm::outs() << "Creating call graph: " << entry_func->getName() << " -- " << target_func->getName() << ".\n";

  llvm::CallGraph call_graph;
  //call_graph.runOnModule(*Mod);
  call_graph.runOnModule(*(kmodule->module));
  llvm::outs() << "Call graph is created.\n";
  llvm::CallGraphNode *entry_node  = call_graph[entry_func];
  llvm::CallGraphNode *target_node = call_graph[target_func];
  PathManager::FVector path_to_target = Dijkstra_call_graph(call_graph, entry_node, target_node);
  llvm::outs() << "Path to target node: " << entry_func->getName() << "() > " << target_func->getName() << 
               "(): " << fvector_to_string(path_to_target) << "\n";
  return path_to_target;
}


/* Find out if function f1() calls function f2(). Return the
 * corresponding call instruction. If there is no such instruction,
 * return the last (most probably RET) instruction of function f1().
 *
 * @param f1 Function in which search for the call instruction
 * @param f2 Funcition which should be argument of the call instruction
 * @return Call f2 instruction, if it is found. Last instruction of f1 otherwise.
 */
Instruction *ICFGPath::get_call_inst(Function *f1, Function *f2)
{
  Instruction *target_inst = NULL;
  for (Function::iterator b = f1->begin(), be = f1->end(); b != be; ++b)
    for (BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; ++i)
    {
        CallInst* callInst = dyn_cast<CallInst>(&*i);
        if (callInst && (callInst->getCalledFunction() == f2))
        {
          outs() << "Found call to " << f2->getName() << "() from " << f1->getName() << "(). Building path from the function entry to the call instruction.\n";
          //target_func = (&*f);
          target_inst = (&*i);
          return target_inst;
        }

    }
  return target_inst;
}


// Get path from f1's entry to call f2
/* Wrapper over Dijkstra_cfg() function: get "call f2()" instruction
 * inside f1() and call Dijkstra_cfg()
 *
 * @param f1 Function for which to build the path.
 * @param f2 Function which is called from f1.
 * @return BBVector of f1's basic blocks which lead to Call f2 instruction
 *         If there is no such call, the path is between f1's entry and return
 *         instruction.
 */
//PathManager::BBVector PathManager::get_cfg_path(Function *f1, Function *f2)
ICFGPath::BBVector ICFGPath::get_cfg_path(Function *f1, Function *f2)
{  
  Instruction *target_inst = NULL;
  BasicBlock *target_bb = NULL;
  BasicBlock *entry_bb = NULL;
 
  entry_bb = &f1->getEntryBlock();
  target_inst = get_call_inst(f1, f2);
  assert(target_inst && "target inst should not be NULL here");
  target_bb = target_inst->getParent();

  //outs() << *target_inst << "\n";
  // Now find shortest path (in terms of basic blocks between entry_bb and target_bb)
  ICFGPath::BBVector path_to_target =  Dijkstra_cfg(f1, entry_bb, target_bb, NULL);

  //#define IVAN
  #ifdef IVAN
  int sz = path_to_target.size();
  int i;
  outs() << "Path in " << f1->getName() << "() to " << f2->getName() << "()\n";
  for(i=0;i<sz;i++)
  {
    const Instruction* first_inst = path_to_target[i]->getFirstNonPHIOrDbg();
    outs() << " - First inst of block " << i << ": " << *first_inst << "\n";
  }
  #endif
  #undef IVAN

  return path_to_target;
}

/* Given a path in f1()'s control flow graph, look for call instructions
 * along this path. For each such call instruction "Call f2()", find the
 * shortest path from f2's entry to return.
 *
 * While expanding call instructions, we add corresponding calees and
 * their CFG shortest paths to cfg_paths and path_functions.
 * 
 * @param cfg_paths [out] Map of functions and shortest paths in their control flow graphs.
 * @param path_functions [out] Contains keys for cfg_paths.
 * @return always 0
 */
int ICFGPath::expand_call_instructions(std::map<Function *, BBVector> &cfg_paths, FVector &path_functions)
{
  int num_funs = path_functions.size();
  //for(int k = 0; k<num_funs; k++)  // for each function in <path_functionss>
  llvm::outs() << "ICFGPath::expand_call_instructions(): path_functions = \n";
  for(int k = 0; k<path_functions.size(); k++)  // for each function in <path_functionss>
    llvm::outs() << path_functions[k]->getName() << "()@" << path_functions[k] << " ";
  llvm::outs() << "\n";

  for(int k = 0; k<path_functions.size(); k++)  // for each function in <path_functionss>
  {
    Function *f = (Function *)path_functions[k];
    BBVector bbvector = cfg_paths[f];
    int num_blocks = bbvector.size();
    for(int j = 0; j<num_blocks; j++) // for each basicblock <b> in <path_functions[k]>
    {
      BasicBlock *b = (BasicBlock *)bbvector[j];
      for(BasicBlock::const_iterator i = b->begin(); i != b->end(); ++i) // for each instruction <i> in block <b>
      {
        CallInst* callInst = dyn_cast<CallInst>((Instruction *)(&*i));
        if (callInst)
        {
          Function *callee = callInst->getCalledFunction();
	        // If: (callee is not NULL) AND (we don't have callee in our path_functions vector yet)
          if(callee && !callee->isDeclaration() && 
             (std::find(path_functions.begin(), path_functions.end(), callee) == path_functions.end()))
          {
            outs() << "Found a call to unexplored function " << callee->getName() << "()@" <<
                   callee << " among our path instructions. Building path from this function's entry to ret.\n";
	          BBVector path_through_callee = Dijkstra_cfg(callee, &callee->getEntryBlock(), NULL, NULL); // first NULL means we need a path to ret instruction

            path_functions.push_back(callee);
            cfg_paths[callee] = path_through_callee;
            #ifdef DEBUG
            int sz = path_through_callee.size();
            outs() << "Path through " << callee->getName() << "():\n";
            for(int i=0;i<sz;i++)
            {
              const Instruction* first_inst = path_through_callee[i]->getFirstNonPHIOrDbg();
              outs() << " - First inst of block " << i << ": " << *first_inst << "\n";
            }
            #endif
            num_funs++;
            //return 0;
            //outs() << "Found a call to unexplored function among our path instructions\n";
            //already_analyzed.push_back(callee);
          }
          else if(callee && !callee->isDeclaration() && (std::find(call_path.begin(), call_path.end(), callee) != path_functions.end()) && !(cfg_paths_aux.count(callee)))
          {
            outs() << "Building aux path from entry to return for " << callee->getName() << "()\n";
            callee->getEntryBlock();
	          BBVector path_through_callee = Dijkstra_cfg(callee, &callee->getEntryBlock(), NULL, NULL); // first NULL means we need a path to ret instruction
            this->cfg_paths_aux[callee] = path_through_callee;
            num_funs++;
          }
        }
      } // for each instruction
    } // for each basicblock
  } // for each function
  return 0;
}


/* Arc src->dst is unreachable in the call graph for function
 * src->getParent().  We need to find the second shortest path
 * Originally we made a path either (entry -> .. -> return) or (entry ->
 * .. -> call instruction to next function in call graph).*/
int PathManager::rebuildInfeasableCFGPath(BasicBlock *src, BasicBlock *dst)
{
  return 0;
#if 0
  Function *f = src->getParent(); // The function for which we rebuild the cfg path

  std::vector<std::pair<BasicBlock *,BasicBlock*> > v;
  v.push_back(std::make_pair(src,dst));

  BasicBlock *entry = (BasicBlock *) *(cfg_paths[f].begin()); // We need to make another path from the same entry 
  BasicBlock *target = (BasicBlock *) *(cfg_paths[f].end()-1); // to the same last block (eitherfunction call or RET instruction)

  PathManager::BBVector new_path =  Dijkstra_cfg(f, entry, target, &v);
  if(new_path.size() == 0)
  {
    outs() << "PathManager::rebuildInfeasableCFGPath(): could not build new path, the arc is in the cut set. Staying with old path\n";
    return 0;
  }

  cfg_paths[f] = new_path;
  expand_call_instructions(cfg_paths, path_functions); // Go through function which we need to go through and add correspnding shortest paths.
  path.clear(); // Clear interprocedural path. If we don't do that, then the new path will be appended to the old one.
  build_path(path_functions[0], true); // Build a new interprocedural path
  return 0;
  //BBVector f_old_path = std::find(cfg_paths[f]);
  //BBVector::iterator it = std::find(f_old_path.begin(), f_old_path.end(), src);
  //assert( it != f_old_path.end() && "src is not found in the original path");
#endif

}

/* Build interprocedural path using cfg_paths of individual functions.
 * TODO: should be fixed (see the problem in the description).
 *
 * Building the path starts from the start function (usually it is
 * "main" function). The key idea is that we go deeper into the calling
 * hierarchy and finally should arrive to our destination function.
 * TODO: The problem with this approach: this works if we have a
 * function call along our path: we go from the entry to the RET
 * instruction and all intermediate call should be indeed in our
 * path_function. However, consider the functions from our call_path.
 * They should not be covered completely but only until the call to the
 * next function in call_path is made. So we add additional unnecessary
 * blocks to the path. Another thing is that we can have multiple call
 * paths to the target function.
 *
 * @param f The entry function of our path toward the target.
 * @return Always 0.
 */
int ICFGPath::build_icfg_path(const Function *f, bool on_call_path)
{
  outs() << "ICFGPath::build_icfg_path(): inside for function " << f->getName() << "(), on_call_path = " << (on_call_path ? "true" : "false") << "\n";
  BBVector bbvector;
  /* If we are looking at inner calls, and the inner call is also
   * function which belongs to the call path, then we need to take the
   * cfg path from its entry to retun (instead of the one from entry to
   * target function )*/
  if(!on_call_path && (std::find(this->call_path.begin(), this->call_path.end(), (Function *)f) != this->call_path.end()))
    bbvector = this->cfg_paths_aux[(Function *)f];
  else
    bbvector = this->cfg_paths[(Function *)f];
  int num_blocks = bbvector.size();
  for(int j = 0; j<num_blocks; j++) 
  {
    BasicBlock *b = (BasicBlock *)bbvector[j];
    this->icfg_path.push_back(std::make_pair(b,(Instruction*)NULL));
    for(BasicBlock::const_iterator i = b->begin(); i != b->end(); ++i) // for each instruction <i> in block <b>
    {
      CallInst* callInst = dyn_cast<CallInst>((Instruction *)(&*i));
      if(callInst)
      {
        Function *callee = callInst->getCalledFunction();
        if(f == callee)
          llvm::outs() << "Recursion detected for function " << f->getName() << "\n";
        assert((f != callee) && "recursion is not supported yet");
        if(callee && !(callee->isDeclaration()))
        {
          this->icfg_path.push_back(std::make_pair((BasicBlock*)NULL,callInst));
          assert((std::find(path_functions.begin(), path_functions.end(), callee) != path_functions.end()) && "Function called from path is not in path ");
          /* If this function does not belong to the call path, we set on_call_path to false,
             so that we handle correctly calls to on-call-path functions as nested fucntions */
          if(std::find(this->call_path.begin(), this->call_path.end(), callee) == this->call_path.end())
            build_icfg_path(callee, false);
          else
            build_icfg_path(callee, on_call_path);
          if(on_call_path && (std::find(this->call_path.begin(), this->call_path.end(), callee) != this->call_path.end()))
          {
            outs() << "ICFGPath::build_icfg_path(): finishing for " << f->getName() << "() due to next on-call-path call\n";
            return 0;
          }
          this->icfg_path.push_back(std::make_pair(b,(Instruction*)NULL)); // We return to the same block, but path has advanced. To reflect we add another copy of the same block
        }
      } else
      {
        ReturnInst* retInst = dyn_cast<ReturnInst>((Instruction *)(&*i));
        if (retInst)
        {
          outs() << "ICFGPath::build_icfg_path(): found RET instruction for " << f->getName() << "()\n";
          this->icfg_path.push_back(std::make_pair((BasicBlock*)NULL,retInst));
        }
      }
    } // for each instruction
  } // for each basicblock
  return 0;
}

/* Single out call instructions from interprocedural control flow graph
 * (ICFG).
 * Note: our ICFG is a vector elements of which are either basic blocks
 * of call instructions. This function just singles out call
 * instructions and put them into a separte vector. */
std::vector<llvm::CallInst *> PathManager::extract_call_insts_from_path()
{
  std::vector<llvm::CallInst *> res;
  int path_len = path.size();
  for(int j = 0; j<path_len; j++) 
  {
    BasicBlock *block = path[j].first;
    Instruction *inst = path[j].second;
    assert( (block || inst) && "Both block and instruction in a path pair are NULL");
    if (inst)
    {
      CallInst* callInst = dyn_cast<CallInst>((Instruction *)(inst));
      if (callInst)
      {
        Function *callee = callInst->getCalledFunction();
        assert(callee);
        res.push_back(callInst);
      }
    }
  }
  return res;
}

/* Print ICFG path <PathManager::path> (from enty to target function) */
int ICFGPath::print_icfg_path()
{
  int INDENT = 2;
  BasicBlock *first_block = this->icfg_path[0].first;
  outs() << "Printing the shortest combined control-flow-path.\n";
  outs() << first_block->getParent()->getName() << ":\n";
  int level = 1;
  int path_len = this->icfg_path.size();
  for(int j = 0; j<path_len; j++) 
  {
    BasicBlock *block = this->icfg_path[j].first;
    Instruction *inst = this->icfg_path[j].second;
    assert( (block || inst) && "Both block and instruction in a path pair are NULL");

    if(block)
    {
      outs() << std::string(level*INDENT, ' ' ) << block->getParent()->getName() << ".bb_" << j << "\n";
    }
    else if (inst)
    {
      CallInst* callInst = dyn_cast<CallInst>((Instruction *)(inst));
      if (callInst)
      {
        Function *callee = callInst->getCalledFunction();
        assert(callee);
        outs() << std::string(level*INDENT,' ') << callee->getName() << ":\n";
        level++;
      }
      else // it should be return instrucion, as in path we only keep callInst and retInst
      {
        ReturnInst* retInst = dyn_cast<ReturnInst>((Instruction *)(inst));
        assert(retInst && "Path instruction is neither callInst nor retInst");
        outs() << std::string(level*INDENT,' ') << "RETN\n";
        level--;
      }
    }
  }
  return 0;
}

ICFGPath::ICFGPath(std::vector<llvm::CallGraphNode *> &_call_path)
{

  llvm::outs() << "ICFGPath::ICFGPath: constructing new obejct for call path:\n";
  for(int i = 0;i < _call_path.size(); i++)
    llvm::outs() << _call_path[i]->getFunction()->getName() << "()" << ((i != (_call_path.size()-1) ) ? " -> " : "");
  llvm::outs() << "\n";


  /* convert vector of CallGraphNode into vector of Functions */
  for(std::vector<llvm::CallGraphNode *>::iterator it = _call_path.begin(); it != _call_path.end(); ++it)
    this->call_path.push_back((*it)->getFunction());

  this->path_functions.assign(this->call_path.begin(), this->call_path.end());
  int sz = this->call_path.size();
  outs() << "Constructing cfg paths for each function in call graph, call path size = " << sz << "\n";
  for (int i=0;i<sz-1;i++)
  {
    llvm::Function *f1 = (Function *)this->call_path[i];
    llvm::Function *f2 = (Function *)this->call_path[i+1];
    this->cfg_paths[f1] = get_cfg_path(f1,f2);
  }  
  outs() << "CFG paths constructed, expanding call instructions.\n";

  /* cfg_paths and path_fucntions are passed as refrences and will be
   * modified in the next function */
  expand_call_instructions(this->cfg_paths, this->path_functions); // Go through function which we need to go through and add corresponding shortest paths.
  sz = path_functions.size();
  outs() << "Expanded, path goes through the following functions (" << sz << " functions):\n";
  for (int i=0;i<sz;i++)
    outs() << "path_funtions[" << i << "]->getName() = " << path_functions[i]->getName() << " @ " << path_functions[i] << "\n";
  outs() << "\n";
  build_icfg_path(this->path_functions[0], true);
  print_icfg_path();
}

/* Given a path in the call graph from the entry to the target function,
 * construct ICFG path, using shortest cfg paths for each individual
 * function. This fills vector PathManager::icfg_paths.
 * @param P set of call paths */
void PathManager::construct_icfg_paths(std::set<std::vector<llvm::CallGraphNode *> > P)
{
  for(std::set<std::vector<llvm::CallGraphNode *> >::iterator it = P.begin(); it != P.end(); ++it) 
  {
    std::vector<llvm::CallGraphNode *> call_path = *it;
    ICFGPath *icfg_path = new ICFGPath(call_path);
    icfg_paths.push_back(icfg_path);
  }
}

/* Go through icfg_paths and find the shortest icfg path in terms of
 * basic blocks */
unsigned PathManager::get_next_shortest_icfg_ndx()
{
  unsigned min_size = UINT_MAX;
  unsigned min_p_ndx = 0;

  if(this->icfg_paths.size() <=  this->used_icfg_indices.size())
    this->used_icfg_indices.clear();

  for(unsigned i = 0; i < this->icfg_paths.size(); i++) 
  {
    ICFGPath *p = this->icfg_paths[i];
    bool used = (std::find(this->used_icfg_indices.begin(), this->used_icfg_indices.end(), i) != this->used_icfg_indices.end());
    if((p->size() < min_size) && !used)
    {
      min_size = p->size();
      min_p_ndx = i;
    }
  }
  assert(min_size < UINT_MAX);
  return min_p_ndx;
}

void PathManager::rotate_icfg()
{
  unsigned ndx = get_next_shortest_icfg_ndx();
  ICFGPath *p = this->icfg_paths[ndx];
  llvm::outs() << "Chose this path:\n";
  p->print_icfg_path();
  this->cur_icfg_ndx = ndx;
  this->path = p->icfg_path;
  this->call_path = p->call_path;
  this->cfg_paths = p->cfg_paths;
  this->cfg_paths_aux = p->cfg_paths_aux;
  this->path_functions = p->path_functions;
  this->used_icfg_indices.push_back(ndx);
  return;
}


/* Construct the shortest path from the program's start to the target
 * function in the interprocedural control flow graph
 * 
 *
 * Build: call_path, cfg_paths for each function on the path, and path
 * (which is a sequence of blocks and call and ret instructions).  If
 * start_function = target_function then path is constructed from entry
 * to return of this function.
 *
 * @param start_function Start symbolic execution from this function
 *                       (i.e. it is the parameter to runFunctionAsMain())
 * @param target_function Construct path towards call to this funtion
 */
int PathManager::path_main_routine(std::string start_function_name, std::string target_function_name)
{
  this->start_function_name = start_function_name;
  this->target_function_name = target_function_name;

  this->start_function = NULL;
  this->target_function = NULL;

  /*  Find start and target functions by their names */
  for (llvm::Module::iterator f = kmodule->module->begin(), fe = kmodule->module->end(); f != fe; ++f)
  {
    if( f && f->getName() == start_function_name)
      this->start_function = (&*f);
    if( f && f->getName() == target_function_name)
      this->target_function = (&*f);
  }
  if(!this->target_function)
    klee_error("Could not find target function '%s()' in the code\n",target_function_name.c_str());
  if(!this->start_function)
    klee_error("Could not find start function '%s()' in the code\n",start_function_name.c_str());


  /* Find 3 (three) shortest call paths */
  llvm::outs() << "Invoking k-shortest algo\n";
  llvm::CallGraph call_graph;
  call_graph.runOnModule(*(kmodule->module));
  llvm::CallGraphNode *entry_node  = call_graph[this->start_function];
  llvm::CallGraphNode *target_node = call_graph[this->target_function];
  std::set<std::vector<llvm::CallGraphNode *> > P = kshortest_call_graph(call_graph, entry_node, target_node);
  construct_icfg_paths(P);

  /* Take the shortest icfg and assign its fields to the corresponding
   * fields of the PathManager */
  unsigned ndx = get_next_shortest_icfg_ndx();
  ICFGPath *p = this->icfg_paths[ndx];
  llvm::outs() << "Chose this path:\n";
  p->print_icfg_path();
  this->cur_icfg_ndx = ndx;
  this->path = p->icfg_path;
  this->call_path = p->call_path;
  this->cfg_paths = p->cfg_paths;
  this->cfg_paths_aux = p->cfg_paths_aux;
  this->path_functions = p->path_functions;
  this->used_icfg_indices.push_back(ndx);
  
#if 0
  llvm::outs() << "Going inside get_call_graph_path().\n";
  call_path = get_call_graph_path(this->start_function, this->target_function);
  path_functions.assign(call_path.begin(), call_path.end());

  int sz = call_path.size();
  outs() << "Constructing cfg paths for each function in call graph, call path size = " << sz << "\n";

  assert((sz > 1) && "Call patht should be at least of length 2 (main -> assert)!");

  for (int i=0;i<sz-1;i++)
  {
    llvm::Function *f1 = (Function *)call_path[i];
    llvm::Function *f2 = (Function *)call_path[i+1];
    cfg_paths[f1] = get_cfg_path(f1,f2);
  }  

  outs() << "CFG paths constructed, expanding call instructions.\n";
  expand_call_instructions(cfg_paths, path_functions); // Go through function which we need to go through and add corresponding shortest paths.
  sz = path_functions.size();
  outs() << "Expanded, path goes through the following functions (" << sz << " functions):\n";
  for (int i=0;i<sz;i++)
    outs() << "path_funtions[" << i << "]->getName() = " << path_functions[i]->getName() << " @ " << path_functions[i] << "\n";
  outs() << "\n";
  build_path(path_functions[0], true);
  print_path();
#endif
  return 0;
}


unsigned PathManager::compute_cfg_distance(llvm::Function *f, llvm::BasicBlock *s, llvm::BasicBlock *t)
{
  unsigned ndx = this->cur_icfg_ndx;
  ICFGPath *p = this->icfg_paths[ndx];
  // If there is no path from entry_bb to target_bb, Dijkstra_cfg returns emtpy vector
  BBVector tmp = p->Dijkstra_cfg(f, s, t, NULL);
  if(tmp.size() == 0)
    return UINT_MAX;
  return tmp.size();
}


unsigned PathManager::get_distance(llvm::Function *f, llvm::BasicBlock *s, llvm::BasicBlock *t)
{
  if(!cfg_distances.count(s) || !cfg_distances[s].count(t))
    cfg_distances[s][t] = compute_cfg_distance(f, s, t); 

  //llvm::outs() << "PathManager::get_distance(): f = " << f->getName() << "s = " << s  <<
  //                " t =  " << t << "; distance = " << cfg_distances[s][t] << "\n";
  return cfg_distances[s][t];
}


/* Get function which are called by <f> (r)ecursively */
std::set<llvm::Function *> PathManager::get_callees_r(const llvm::Function *f)
{
  //PathManager::FVector callees;
  std::set<llvm::Function *> callees;
  assert(f && "You need a non-fuctnion to find callees");
  llvm::CallGraph call_graph;
  call_graph.runOnModule(*(kmodule->module));
  //llvm::outs() << "PathManager::get_callees_r(): Call graph is created.\n";
  llvm::CallGraphNode *f_node = call_graph[f];

  llvm::CallGraphNode *n = NULL; // neigboru of <f> in the call graph
  /* Go through all unvisited neighbours of <f_node> */
  for (llvm::CallGraphNode::iterator cr = f_node->begin(), cr_end = f_node->end(); cr != cr_end; ++cr)
  {
    n = cr->second;  // cr is a CallGraphNode::CallRecord, we need to extract CallGraphNode <n> from it.
    if(n->getFunction())
    {
      callees.insert(n->getFunction());
      std::set<llvm::Function *> sub_callees = get_callees_r(n->getFunction());
      callees.insert(sub_callees.begin(), sub_callees.end());
    }
  }
  return callees;
}

/* Get function which are called by <f> */
std::map<llvm::Function *, std::set<llvm::Function *> > PathManager::get_callees(const llvm::Function *f, Architecture *arch)
{
  std::map<llvm::Function *, std::set<llvm::Function *> > callees;
  //assert(f && "You need a non-fuctnion to find callees");
  llvm::CallGraph call_graph;
  call_graph.runOnModule(*(kmodule->module));
  //llvm::outs() << "PathManager::get_callees_r(): Call graph is created.\n";
  llvm::CallGraphNode *f_node = call_graph[f];

  llvm::CallGraphNode *n = NULL; // neigbour of <f> in the call graph
  /* Go all neighbours (i.e. callees) of <f_node> */
  for (llvm::CallGraphNode::iterator cr = f_node->begin(), cr_end = f_node->end(); cr != cr_end; ++cr)
  {
    n = cr->second;  // cr is a CallGraphNode::CallRecord, we need to extract CallGraphNode <n> from it.
    llvm::Function *callee = n->getFunction();
    if(callee)
    {
      std::set<llvm::Function *> sub_callees = get_callees_r(callee);
      callees[callee].insert(sub_callees.begin(), sub_callees.end());
    }
  }

  /* Now collect interrupts, they are potential callees too */
  InterruptVector::iterator seek = arch->interruptVector.begin();
  InterruptVector::iterator end = arch->interruptVector.end();
  for ( ; seek != end ; ++seek)
  {
    InterruptHandler * handler = *seek;
    if (handler->gate == NULL)
      klee_error("Absentee interrupt condition (probably a bug in the memory layout file)\n");
    assert(handler->fun);
    llvm::Function *callee = (llvm::Function *)handler->fun;
    std::set<llvm::Function *> sub_callees = get_callees_r(callee);
    callees[callee].insert(sub_callees.begin(), sub_callees.end());
  }
  return callees;
}


/* TODO: add interrupts to the list of callers, as they can change gloabls too
 * before we come to the current function*/
std::set<llvm::Function *> PathManager::get_callers_r(const llvm::Function *f)
{
  std::set<llvm::Function *> callers;
  //llvm::outs() << "DEBUG: MAKAKA\n";
  llvm::GlobalValue* gv = (llvm::GlobalValue *)f;
  for(llvm::Value::use_iterator u_it=gv->use_begin(); u_it != gv->use_end(); ++u_it)
  {
    if(Instruction *Inst = dyn_cast<Instruction>(*u_it))
    {
      llvm::Function *caller = Inst->getParent()->getParent();
      if(caller)
      {
        callers.insert(caller);
        std::set<llvm::Function *> super_callers = get_callers_r(caller);
        callers.insert(super_callers.begin(), super_callers.end());
      }
    }
  } // for each usage
  return callers;
}
