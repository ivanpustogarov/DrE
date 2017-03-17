//===-- PathManager.h ----------------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Class to manage/build interprocedural control flow graph paths.
//
//===----------------------------------------------------------------------===//

#ifndef KLEE_PATHMANAGER_H
#define KLEE_PATHMANAGER_H

#include "klee/ExecutionState.h"
#include "klee/Arch.h"
#include "klee/Interpreter.h"
#include "klee/Internal/Module/Cell.h"
#include "klee/Internal/Module/KInstruction.h"
#include "klee/Internal/Module/KModule.h"

#include "llvm/ADT/Twine.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"

#include <vector>
#include <string>
#include <map>
#include <set>

namespace llvm {
  class BasicBlock;
  class CallInst;
  class Constant;
  class ConstantExpr;
  class Function;
  class GlobalValue;
  class Instruction;
#if LLVM_VERSION_CODE <= LLVM_VERSION(3, 1)
  class TargetData;
#else
  class DataLayout;
#endif
  class Twine;
  class Value;
}

namespace klee {  
  class Array;
  class Expr;
  struct KFunction;
  struct KInstruction;
  class KInstIterator;
  class KModule;
  class TreeStreamWriter;
  template<class T> class ref;

/* Represents individual ICFG path from start to target function */
class ICFGPath
{
  typedef std::vector<const llvm::Function *>   FVector;
  typedef std::vector<const llvm::BasicBlock *> BBVector;

  public:
    /* icfg path consisting of basic blocks; this includes all nested functions */
    std::vector<std::pair<llvm::BasicBlock *, llvm::Instruction *> > icfg_path;
    llvm::Function *start_function;
    llvm::Function *target_function;

    FVector call_path; /* Path from main to assert in the call graph */
    FVector path_functions; /* This includes call_path + functions from call instructions along the path */
    std::map<llvm::Function *, BBVector> cfg_paths; /* For each function in path_functions, keep its cfg_path */
    std::map<llvm::Function *, BBVector> cfg_paths_aux; /* CFG paths from entry to return for functions in call path (as they can appear as inner calls) */

    /* In each block in each cfg path, find call instruction. Create cfg paths for these functions
     Upon return <path_functions>  contains functions for which we built a cfg path */
    int expand_call_instructions(std::map<llvm::Function *, BBVector> &cfg_paths, FVector &path_functions);
    int build_icfg_path(const llvm::Function *f, bool on_call_path); 
    ICFGPath(std::vector<llvm::CallGraphNode *> &call_path);

  /* Find shortest path (in terms of number of basic blocks) from entry_bb to tartget_bb in control flow graph */
  BBVector Dijkstra_cfg(llvm::Function *parent_f, 
                        llvm::BasicBlock *entry_bb,
                        llvm::BasicBlock *target_bb,
                        std::vector<std::pair<llvm::BasicBlock*,llvm::BasicBlock*> > *);
  /* Get the shortest path from f1's entry to the first call to f2. If f2 is null then, to the first return instruction. */
  BBVector get_cfg_path(llvm::Function *f1, llvm::Function *f2);
  bool contains_ret_instr(llvm::BasicBlock *b);
  /* Get the first call intruction "call f2" from function f1 */
  llvm::Instruction *get_call_inst(llvm::Function *f1, llvm::Function *f2);
  int print_icfg_path();
  unsigned size() {return icfg_path.size();}
};


class PathManager
{

public:

  PathManager(std::string start_function_name, std::string target_function_name, KModule *_kmodule);
  ~PathManager();

  /* The main function to build path. TODO: give more meaningful name to this function.
   * Probably even move this function to the constructor's code */
  int path_main_routine(std::string start_function_name, std::string target_function_name);
  /* Find the function to which <src> belongs, extract the first and the last blocks for the
     cfg path for this function, and rebuild this path assuming that there is no arc between src and dst */
  int rebuildInfeasableCFGPath(llvm::BasicBlock *src, llvm::BasicBlock *dst);

  typedef std::vector<const llvm::Function *>   FVector;
  typedef std::vector<const llvm::BasicBlock *> BBVector;

  //struct classcompB {
  //  bool operator() (const std::vector<llvm::CallGraphNode *>& lhs, const std::vector<llvm::CallGraphNode *>& rhs) const
  //  {return lhs.size()<rhs.size();}
  //};


  unsigned get_distance(llvm::Function *f, llvm::BasicBlock *s, llvm::BasicBlock *t);
  //FVector get_callees_r(const llvm::Function *f);
  std::set<llvm::Function *> get_callees_r(const llvm::Function *f);
  std::set<llvm::Function *> get_callers_r(const llvm::Function *f);
  std::map<llvm::Function *, std::set<llvm::Function *> > get_callees(const llvm::Function *f, Architecture *arch = NULL);

private:

  //std::set<llvm::Function *> mergeBlacklist;

  KModule *kmodule;

 /* *** Functions to work with call/control flow graphs */
  
  /* Shortest distances between blocks */
  std::map<llvm::BasicBlock *, std::map<llvm::BasicBlock *, unsigned> > cfg_distances;
  unsigned compute_cfg_distance(llvm::Function *f, llvm::BasicBlock *s, llvm::BasicBlock *t);

  /* Create a sequence of blocks representing a path to the target block.
     It goes inside each call instruction */
  //int build_path(const llvm::Function *f, bool on_call_path); 
  std::string fvector_to_string(FVector fvector);
  /* Find k shortest paths in the call graph from <s> to <t> */
  std::set<std::vector<llvm::CallGraphNode *> > kshortest_call_graph(llvm::CallGraph &call_graph,  llvm::CallGraphNode *s, llvm::CallGraphNode *t);
  /* Find shortest path (in terms of number of functions) from st to tartget_node in the call graph */
  FVector Dijkstra_call_graph(llvm::CallGraph &call_graph, llvm::CallGraphNode *st, llvm::CallGraphNode *target_node);
  /* Get one (shortest) call graph path from entry tor start function */
  FVector get_call_graph_path(llvm::Function *entry_func, llvm::Function *target_func);
  /* Check if basic block <b> contains a retrun instruction */
                                           
  std::vector<llvm::CallInst *> extract_call_insts_from_path();

 /* *** */


 /* *** Fileds to store information about path from entry function to target function */

  /* Function from which we start compositional sybmolic execution */
  std::string start_function_name;
  llvm::Function *start_function;
  /* Function to which we are trying to find a feasiable path*/
  std::string target_function_name;
  llvm::Function *target_function;

  llvm::CallGraph call_graph;

 /* *** */

public:
  /* Path is a sequence of basic blocks or call and ret instructions.
     Is is represented a vector of pairs. In each pair, only one element can be non-NULL.
     This is a hack to model a vector which accepts several elements' data types. */
  std::vector<std::pair<llvm::BasicBlock *, llvm::Instruction *> > path;
  FVector call_path; /* Path from main to assert in the call graph */
  FVector path_functions; /* This includes call_path + functions from call instructions along the path */
  std::map<llvm::Function *, BBVector> cfg_paths; /* For each function in path_functions, keep its cfg_path */
  std::map<llvm::Function *, BBVector> cfg_paths_aux; /* CFG paths from entry to return for functions in call path (as they can appear as inner calls) */

  std::vector<ICFGPath *> icfg_paths;
  void construct_icfg_paths(std::set<std::vector<llvm::CallGraphNode *> > P);
  void rotate_icfg();
  unsigned get_next_shortest_icfg_ndx();
  unsigned cur_icfg_ndx;
  std::vector<unsigned> used_icfg_indices;

};
  
} // End klee namespace

#endif
