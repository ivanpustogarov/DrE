//===-- Searcher.cpp ------------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Common.h"

#include "Searcher.h"

#include "CoreStats.h"
#include "Executor.h"
#include "PTree.h"
#include "StatsTracker.h"

#include "klee/ExecutionState.h"
#include "klee/Statistics.h"
#include "klee/Internal/Module/InstructionInfoTable.h"
#include "klee/Internal/Module/KInstruction.h"
#include "klee/Internal/Module/KModule.h"
#include "klee/Internal/ADT/DiscretePDF.h"
#include "klee/Internal/ADT/RNG.h"
#include "klee/Internal/Support/ModuleUtil.h"
#include "klee/Internal/System/Time.h"
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#else
#include "llvm/Constants.h"
#include "llvm/Instructions.h"
#include "llvm/Module.h"
#endif
#include "llvm/Support/CommandLine.h"

#if LLVM_VERSION_CODE < LLVM_VERSION(3, 5)
#include "llvm/Support/CallSite.h"
#else
#include "llvm/IR/CallSite.h"
#endif

#include <cassert>
#include <fstream>
#include <climits>

using namespace klee;
using namespace llvm;

namespace {
  cl::opt<bool>
  DebugLogMerge("debug-log-merge");
}

namespace klee {
  extern RNG theRNG;
}

Searcher::~Searcher() {
}

///

ExecutionState &DFSSearcher::selectState() {
  return *states.back();
}

void DFSSearcher::update(ExecutionState *current,
                         const std::set<ExecutionState*> &addedStates,
                         const std::set<ExecutionState*> &removedStates) {
  states.insert(states.end(),
                addedStates.begin(),
                addedStates.end());
  for (std::set<ExecutionState*>::const_iterator it = removedStates.begin(),
         ie = removedStates.end(); it != ie; ++it) {
    ExecutionState *es = *it;
    if (es == states.back()) {
      states.pop_back();
    } else {
      bool ok = false;

      for (std::vector<ExecutionState*>::iterator it = states.begin(),
             ie = states.end(); it != ie; ++it) {
        if (es==*it) {
          states.erase(it);
          ok = true;
          break;
        }
      }

      assert(ok && "invalid state removed");
    }
  }
}

///

/* FIXME: not yet implemented, the functionality is currently in ForwardExecutor */
ExecutionState &SummaryComplyingSearcher::selectState() {
  return *states.back();
}

void SummaryComplyingSearcher::update(ExecutionState *current,
                         const std::set<ExecutionState*> &addedStates,
                         const std::set<ExecutionState*> &removedStates) {
  states.insert(states.end(),
                addedStates.begin(),
                addedStates.end());
  for (std::set<ExecutionState*>::const_iterator it = removedStates.begin(),
         ie = removedStates.end(); it != ie; ++it) {
    ExecutionState *es = *it;
    if (es == states.back()) {
      states.pop_back();
    } else {
      bool ok = false;

      for (std::vector<ExecutionState*>::iterator it = states.begin(),
             ie = states.end(); it != ie; ++it) {
        if (es==*it) {
          states.erase(it);
          ok = true;
          break;
        }
      }

      assert(ok && "invalid state removed");
    }
  }
}

///


int get_num_of_prev_calls_in_curent_bb(llvm::Instruction *inst)
{
  BasicBlock *bb = inst->getParent();
  int num_call_inst = 0;
  for(llvm::BasicBlock::iterator it = bb->begin(); it != bb->end(); ++it)
  {
    llvm::Instruction *i = &(*it); 
    if(i == inst)
      break;
    CallInst* callInst = dyn_cast<CallInst>(i);
    if(callInst)
    {
      llvm::Function *callee = callInst->getCalledFunction();
      if(callee && !(callee->isDeclaration()))
        num_call_inst++;
    }
  }
  return num_call_inst;
}


int getPathIndex(ExecutionState *state, std::vector<std::pair<llvm::BasicBlock *, llvm::Instruction *> > &path)
{
  unsigned i = 0;
  BasicBlock *state_bb = state->pc->inst->getParent();
  Instruction *state_inst = state->pc->inst;

  int prevCallsInCurrentBB = get_num_of_prev_calls_in_curent_bb(state_inst);
  //llvm::outs() << "DEBUG: prevCallsInCurrentBB = " << prevCallsInCurrentBB << "\n";

  bool look_at_call_history = true;
  unsigned call_history_size = state->callHistory.size();
  unsigned j = 0;
  int k = 0;
  if(call_history_size == 0)
    look_at_call_history = false;

  for(i=0;i<path.size();i++)
  {
    if(look_at_call_history)
    {
      Instruction *inst = (Instruction *)path[i].second;
      if(inst)
      {
        CallInst* callInst = dyn_cast<CallInst>((Instruction *)(inst));
        if (callInst && (inst == state->callHistory[j]))
          j++;
        if(j == call_history_size)
          look_at_call_history = false; // Looked through all state's call history 
      }
    } else
    {
      // We have a match for our callHistory => our block should come soon.
      // We can have multiple copies in our path due to call instructions (see path documentation in Executor.h).
      // So may need to skip some of our blocks
      BasicBlock *bb = path[i].first;
      if((state_bb == bb) && (k == prevCallsInCurrentBB))
        return i;
      else if(state_bb == bb)
        k++;
    };
  }
  return -1;
}

int getBestState(std::vector<int> indices, std::deque<ExecutionState*> *states)
{
  int max = -1;
  int best_ndx = -1;
  for(unsigned count = 0; count < indices.size(); count++)
  {
    int ndx = indices[count];
    //llvm::outs() << "DEBUG: getBestState(): looking at state " <<  (*states)[ndx] << " with lastPathIndex = " 
    //             << (*states)[ndx]->lastPathIndex << " and onPathInsts =  " << (*states)[ndx]->onPathInsts << "\n";
    if( (*states)[ndx]->lastPathIndex > max)
    {
      max = (*states)[ndx]->lastPathIndex;
      best_ndx = ndx;
    }
    else if( ((*states)[ndx]->lastPathIndex == max) && ((*states)[ndx]->onPathInsts > (*states)[best_ndx]->onPathInsts) )
      best_ndx = ndx;
  }
  assert(best_ndx >= 0);
  return best_ndx;
}

int getBestState(std::deque<ExecutionState*> *states)
{
  int max = -1;
  int best_ndx = -1;
  for(unsigned ndx = 0; ndx < states->size(); ndx++)
  {
    //llvm::outs() << "DEBUG: getBestState(): looking at state " <<  (*states)[ndx] << " with lastPathIndex = " 
    //             << (*states)[ndx]->lastPathIndex << " and onPathInsts =  " << (*states)[ndx]->onPathInsts << "\n";
    if( (*states)[ndx]->lastPathIndex > max)
    {
      max = (*states)[ndx]->lastPathIndex;
      best_ndx = ndx;
    }
    else if( ((*states)[ndx]->lastPathIndex == max) && ((*states)[ndx]->onPathInsts > (*states)[best_ndx]->onPathInsts) )
      best_ndx = ndx;
  }
  assert(best_ndx >= 0);
  return best_ndx;
}

int get_states_with_shortest_summary(std::deque<ExecutionState*> *states)
{
  unsigned min;
  if( (*states)[0]->cur_fsummary == NULL )
    min = 0;
  else
    min = (*states)[0]->cur_fsummary->path_instructions.size();

  int best_ndx = 0;
  for(unsigned ndx = 0; ndx < states->size(); ndx++)
  {
    if( (*states)[ndx]->cur_fsummary == NULL )
    {
      min = 0;
      best_ndx = ndx;
    }
    else if ((*states)[ndx]->cur_fsummary->path_instructions.size() < min)
    {
      min = (*states)[ndx]->cur_fsummary->path_instructions.size();
      best_ndx = ndx;
    }
  }
  assert(best_ndx >= 0);
  return best_ndx;

}

// IVAN ADDIDITONS START (See above for original function (commented))
#if 0 // Leave this code for later.
ExecutionState &ClosestToPathSearcher::selectState() {
  std::vector<int> first_in_row_states; // States which are on path
  std::vector<int> second_in_row_states; // States which are one-block-deviated from path

  llvm::outs() << "\n == Starting state search. Number of states = " << states.size() << "\n";

  //if(path_functions.size() == 0)
	assert((path_manager->path_functions.size() != 0) && "path_functions.size() = 0");

  // Go through all states and find states which are on-path and states which one-block-deviated from path
  int sz = states.size();
  for (int i = 0; i<sz ;i++) // Go through all states BEGIN
  {
    ExecutionState *cur_state = states[i];
    llvm::Instruction *state_inst = cur_state->pc->inst;
    llvm::BasicBlock *parent_bb = state_inst->getParent();
    llvm::Function *parent_f = parent_bb->getParent();

    // We are in a function which belongs to the path AND we in a basic block which belongs to the path
    if( (std::find(path_manager->path_functions.begin(), path_manager->path_functions.end(), parent_f) != path_manager->path_functions.end())
         && (std::find(path_manager->cfg_paths[parent_f].begin(), path_manager->cfg_paths[parent_f].end(), parent_bb) != path_manager->cfg_paths[parent_f].end()) )
    {
        int path_index = getPathIndex(cur_state, path_manager->path); // will return -1, if we returned from the target function (note that we still will be at the on-path block).
        if ((cur_state->pathDeviationDepth > 0) || (path_index < 0))
        {
          //llvm::outs() << " ====> We have a match in function " << parent_f->getName() <<"().\n";
          //llvm::outs() << "State's instruction: " << *state_inst << "\n";
          //llvm::outs() << "    -----> deviations is too high for this state: " << cur_state->pathDeviationDepth << ".\n";
          cur_state->isOnPath = false;
          continue;
        }
        //llvm::outs() << " ====> We have a match! returning this state for function " << parent_f->getName() <<"().\n";
        //llvm::outs() << " ====> We have a good match (deviationDepth = 0) in function " << parent_f->getName() <<"().\n";
        //llvm::outs() << "State's instruction: " << *state_inst << "\n";
        cur_state->isOnPath = true;   
        cur_state->lastPathIndex = path_index;//getPathIndex(cur_state, path);
        first_in_row_states.push_back(i);
    }
    else // We are not in on-path BB, but maybe we just deviated
    {
      if (cur_state->isOnPath == true) // This means that the state just jumped off path
        cur_state->first_offroad_block = parent_bb;

      if ( (parent_bb == cur_state->first_offroad_block) && // If we are still in the block in which we first deviated from the path
           (cur_state->pathDeviationDepth == 0))            // AND we are still at the same call level
        second_in_row_states.push_back(i);

      cur_state->isOnPath = false;
    }
  }                      // Go through all states END

  // Now try no choose state: first choose from on-path states if there are some
  //                          second try states which are one-block-deviated
  //                          if nothing worked choose a random state.
  int state_ndx = 0;
  do_random_search++;
//#define RAND_SEARCH_FREQ 20 // 3 means every 3rd iteration
  if( (first_in_row_states.size() != 0) && (do_random_search < rand_search_freq) ) 
  {
    //state_ndx = first_in_row_states[theRNG.getInt32()%first_in_row_states.size()]; 
    llvm::outs() << "Searching among on-path states. Num of on-path states = " << first_in_row_states.size() << "\n";
    state_ndx = getBestState(first_in_row_states, &states);
    states[state_ndx]->onPathInsts++;
    llvm::outs() << "We have " <<  first_in_row_states.size()
                 << " on-path state. Choosing the one with lastPathIndex = " 
                 << states[state_ndx]->lastPathIndex << ".\n";
  }
  //else if((second_in_row_states.size() != 0) && false) 
  //{
  //  state_ndx = getBestState(second_in_row_states, &states);
  //  llvm::outs() << "No on-path states. We have " <<  second_in_row_states.size()
  //               << " one-block-deviated states. Choosing the one with lastPathIndex = " 
  //               << states[state_ndx]->lastPathIndex << ".\n";
  //}
  else if (do_random_search < rand_search_freq)
  {
    //state_ndx = theRNG.getInt32()%states.size();
    //llvm::outs() << " ====> No on-path, no just-deviated states. Using random choice.\n";
    state_ndx = getBestState(&states);
    llvm::outs() << "No on-path states. Choosing among all states. Choosing the one with lastPathIndex = " 
                 << states[state_ndx]->lastPathIndex << ".\n";
  } else
  {
    if(prefer_short_summaries)
    {
      state_ndx = get_states_with_shortest_summary(&states);
    } 
    else
    {
      state_ndx = theRNG.getInt32()%states.size();
      llvm::outs() << "Time to do random search. Choosing among all states. Choosing the one with lastPathIndex = " 
                   << states[state_ndx]->lastPathIndex << ".\n";
    }
    do_random_search = 0;

  }

  llvm::Instruction *state_inst = states[state_ndx]->pc->inst;
  llvm::outs() << " ====> State is in function " << state_inst->getParent()->getParent()->getName() << "()\n";
  llvm::outs() << "State's instruction: " << *state_inst << "\n";
  int path_index = getPathIndex(states[state_ndx], path_manager->path);
  llvm::outs() << "States pathIndex: " <<  path_index << "\n";
  //llvm::outs() << "States callsInCurrentBB: " << states[state_ndx]->callsInCurrentBB << "\n";
  llvm::outs() << "States callHistory:\n";
  for(unsigned long i = 0; i < states[state_ndx]->callHistory.size(); i++)
    llvm::outs() << *states[state_ndx]->callHistory[i] << "\n";
  //states[state_ndx]->isOnPath = false;
  //llvm::outs() << "State's isOnPath =  " <<  (states[state_ndx]->isOnPath ? "true" : "false") << "\n";
  
  // If we are of-path and calling a function: increase the deviationDepth
  // If we are of-path and returning from a function: decrease the deviationDepth
#if 0 // We don't need this code for Summary executors. Enable this code if we go non-Summary
  if(states[state_ndx]->isOnPath == false) 
  {
    CallInst* callInst = dyn_cast<CallInst>(state_inst);
    if (callInst)
    {
      outs() << "This is a callInst from a non-path basic block. " 
             << "Increasing pathDeviationDepth for this state: " << states[state_ndx]->pathDeviationDepth  << " -> " 
             << states[state_ndx]->pathDeviationDepth+1 << "\n";
      states[state_ndx]->pathDeviationDepth++;
    }
    ReturnInst* retInst = dyn_cast<ReturnInst>(state_inst);
    if (retInst)
    {
      outs() << "This is a returnInst back to a non-path basic block. " 
             << "Decreasing pathDeviationDepth for this state: " << states[state_ndx]->pathDeviationDepth  << " -> " 
             << states[state_ndx]->pathDeviationDepth-1 << "\n";
      states[state_ndx]->pathDeviationDepth--;
    }
  }
#endif
  if (states[state_ndx]->pathDeviationDepth < 0)
  {
    states[state_ndx]->pathDeviationDepth = 0;
    llvm::outs() << "WARNING: pathDeviation for the state just became less then zero, restoring.\n";
  }
      

 // if (states[state_ndx]->stack.size() > 1) 
 //   assert(states[state_ndx]->pathDeviationDepth >= 0 && "states[state_ndx]->pathDeviationDepth  < 0");
 // else
 // if (states[state_ndx]->stack.size() <= 1) // if this is the top-most function
 //   assert(states[state_ndx]->pathDeviationDepth >= -1 && "states[state_ndx]->pathDeviationDepth  < 0");
  return *states[state_ndx];
  // If *state_inst == callInst => even the functions belong to the path, we are still off-path
}
#endif
// IVAN ADDIDITONS END


ExecutionState &BFSSearcher::selectState() {
  return *states.front();
}


void BFSSearcher::update(ExecutionState *current,
                         const std::set<ExecutionState*> &addedStates,
                         const std::set<ExecutionState*> &removedStates) {
  states.insert(states.end(),
                addedStates.begin(),
                addedStates.end());
  for (std::set<ExecutionState*>::const_iterator it = removedStates.begin(),
         ie = removedStates.end(); it != ie; ++it) {
    ExecutionState *es = *it;
    if (es == states.front()) {
      states.pop_front();
    } else {
      bool ok = false;

      for (std::deque<ExecutionState*>::iterator it = states.begin(),
             ie = states.end(); it != ie; ++it) {
        if (es==*it) {
          states.erase(it);
          ok = true;
          break;
        }
      }

      assert(ok && "invalid state removed");
    }
  }
}

/// SDSearcher 
SDSearcher::SDSearcher(Executor &_executor)
  : executor(_executor) {
}



ExecutionState &SDSearcher::selectState() {

  int state_ndx = 0;
  llvm::outs() << "\n == SDSearcher: Starting state search. Number of states = " << states.size() << "\n";
  assert(executor.path_manager);
  assert((executor.path_manager->path_functions.size() != 0) && "path_functions.size() = 0");

  unsigned min_dist = UINT_MAX;
  int sz = states.size();
  for (int i = 0; i<sz ;i++) // Go through all states BEGIN
  {
    ExecutionState *cur_state = states[i];
    llvm::Instruction *state_inst = cur_state->pc->inst;
    llvm::BasicBlock *parent_bb = state_inst->getParent();
    llvm::Function *parent_f = parent_bb->getParent();
    if(!(cur_state->complies_with_cur_inner_call))
      continue;

    /* If we are at inner call, function of which also belongs to the call path, then we need
     * to consider cfg_paths_aux (cif_paths_aux contains paths from entry to return) */
    llvm::BasicBlock *target_block = NULL;
    if(executor.path_manager->cfg_paths.count(parent_f))
    {
      if(cur_state->cur_inner_call && 
          (std::find(executor.path_manager->call_path.begin(), executor.path_manager->call_path.end(), parent_f) != executor.path_manager->call_path.end())
        )
        target_block = (llvm::BasicBlock *)executor.path_manager->cfg_paths_aux[parent_f].back();
      else
        target_block = (llvm::BasicBlock *)executor.path_manager->cfg_paths[parent_f].back();
    }
    /* If target_block stays NULL, then compute_distances will compute distance from
       parent_bb to return statement */
    unsigned distance = executor.path_manager->get_distance(parent_f, parent_bb,target_block);
    if(distance < min_dist)
    {
      min_dist = distance;
      state_ndx = i;
    }
  } // Go through all states END


  llvm::Instruction *state_inst = states[state_ndx]->pc->inst;
  llvm::outs() << " ====> State is in function " << state_inst->getParent()->getParent()->getName() << "()\n";
  llvm::outs() << "State's instruction: " << *state_inst << "\n";
  llvm::outs() << "States dist to target: " <<  min_dist << "\n";

  if(min_dist == UINT_MAX)
  {
    this->no_good_states = true;
    llvm::outs() << "No good states\n";
  }

  return *states[state_ndx];
}
// IVAN ADDIDITONS END

void SDSearcher::update(ExecutionState *current,
                         const std::set<ExecutionState*> &addedStates,
                         const std::set<ExecutionState*> &removedStates) {
  states.insert(states.end(),
                addedStates.begin(),
                addedStates.end());
  for (std::set<ExecutionState*>::const_iterator it = removedStates.begin(),
         ie = removedStates.end(); it != ie; ++it) {
    ExecutionState *es = *it;
    if (es == states.front()) {
      states.pop_front();
    } else {
      bool ok = false;

      for (std::deque<ExecutionState*>::iterator it = states.begin(),
             ie = states.end(); it != ie; ++it) {
        if (es==*it) {
          states.erase(it);
          ok = true;
          break;
        }
      }

      assert(ok && "invalid state removed");
    }
  }
}

///

ExecutionState &RandomSearcher::selectState() {
  return *states[theRNG.getInt32()%states.size()];
}

void RandomSearcher::update(ExecutionState *current,
                            const std::set<ExecutionState*> &addedStates,
                            const std::set<ExecutionState*> &removedStates) {
  states.insert(states.end(),
                addedStates.begin(),
                addedStates.end());
  for (std::set<ExecutionState*>::const_iterator it = removedStates.begin(),
         ie = removedStates.end(); it != ie; ++it) {
    ExecutionState *es = *it;
    bool ok = false;

    for (std::vector<ExecutionState*>::iterator it = states.begin(),
           ie = states.end(); it != ie; ++it) {
      if (es==*it) {
        states.erase(it);
        ok = true;
        break;
      }
    }
    
    assert(ok && "invalid state removed");
  }
}

///

WeightedRandomSearcher::WeightedRandomSearcher(WeightType _type)
  : states(new DiscretePDF<ExecutionState*>()),
    type(_type) {
  switch(type) {
  case Depth: 
    updateWeights = false;
    break;
  case InstCount:
  case CPInstCount:
  case QueryCost:
  case MinDistToUncovered:
  case CoveringNew:
    updateWeights = true;
    break;
  default:
    assert(0 && "invalid weight type");
  }
}

WeightedRandomSearcher::~WeightedRandomSearcher() {
  delete states;
}

ExecutionState &WeightedRandomSearcher::selectState() {
  return *states->choose(theRNG.getDoubleL());
}

double WeightedRandomSearcher::getWeight(ExecutionState *es) {
  switch(type) {
  default:
  case Depth: 
    return es->weight;
  case InstCount: {
    uint64_t count = theStatisticManager->getIndexedValue(stats::instructions,
                                                          es->pc->info->id);
    double inv = 1. / std::max((uint64_t) 1, count);
    return inv * inv;
  }
  case CPInstCount: {
    StackFrame &sf = es->stack.back();
    uint64_t count = sf.callPathNode->statistics.getValue(stats::instructions);
    double inv = 1. / std::max((uint64_t) 1, count);
    return inv;
  }
  case QueryCost:
    return (es->queryCost < .1) ? 1. : 1./es->queryCost;
  case CoveringNew:
  case MinDistToUncovered: {
    uint64_t md2u = computeMinDistToUncovered(es->pc,
                                              es->stack.back().minDistToUncoveredOnReturn);

    double invMD2U = 1. / (md2u ? md2u : 10000);
    if (type==CoveringNew) {
      double invCovNew = 0.;
      if (es->instsSinceCovNew)
        invCovNew = 1. / std::max(1, (int) es->instsSinceCovNew - 1000);
      return (invCovNew * invCovNew + invMD2U * invMD2U);
    } else {
      return invMD2U * invMD2U;
    }
  }
  }
}

void WeightedRandomSearcher::update(ExecutionState *current,
                                    const std::set<ExecutionState*> &addedStates,
                                    const std::set<ExecutionState*> &removedStates) {
  if (current && updateWeights && !removedStates.count(current))
    states->update(current, getWeight(current));
  
  for (std::set<ExecutionState*>::const_iterator it = addedStates.begin(),
         ie = addedStates.end(); it != ie; ++it) {
    ExecutionState *es = *it;
    states->insert(es, getWeight(es));
  }

  for (std::set<ExecutionState*>::const_iterator it = removedStates.begin(),
         ie = removedStates.end(); it != ie; ++it) {
    states->remove(*it);
  }
}

bool WeightedRandomSearcher::empty() { 
  return states->empty(); 
}

/// Directed Random Path Searcher 

DRandomPathSearcher::DRandomPathSearcher(Executor &_executor)
  : executor(_executor) {
}

DRandomPathSearcher::~DRandomPathSearcher() {
}

/* Check if current state's target (i.e. either next call graph function)
 * or return instruction for inner calls */
bool DRandomPathSearcher::is_target_reachable(ExecutionState *s)
{
  assert(s);
  llvm::Instruction *state_inst = s->pc->inst;
  llvm::BasicBlock *parent_bb = state_inst->getParent();
  llvm::Function *parent_f = parent_bb->getParent();
  assert(state_inst && parent_bb && parent_f);
  assert(executor.path_manager);

  /* If we are at inner call, function of which also belongs to the call path, then we need
   * to consider cfg_paths_aux (i.e. from entry to return) */
  llvm::BasicBlock *target_block = NULL;
  llvm::outs() << "DRandomPathSearcher::is_target_reachable(): setting the target block\n";
  //if(executor.path_manager->cfg_paths.count(parent_f) && executor.path_manager->cfg_paths[parent_f].size())
  if(executor.path_manager->cfg_paths.count(parent_f))
  {
    llvm::outs() << "DRandomPathSearcher::is_target_reachable(): current function is in cfg_paths\n";
    if(s->cur_inner_call && 
        (std::find(executor.path_manager->call_path.begin(), executor.path_manager->call_path.end(), parent_f) != executor.path_manager->call_path.end()))
    {
      llvm::outs() << "DRandomPathSearcher::is_target_reachable(): getting target block from cfg_paths_aux\n";
      target_block = (llvm::BasicBlock *)executor.path_manager->cfg_paths_aux[parent_f].back();
      llvm::outs() << "set\n";
    }
    else
    {
      llvm::outs() << "DRandomPathSearcher::is_target_reachable(): getting target block from cfg_paths\n";
      llvm::outs() << "DRandomPathSearcher::is_target_reachable(): executor.path_manager->cfg_paths.count(parent_f) = " << executor.path_manager->cfg_paths.count(parent_f) << "\n";
      llvm::outs() << "DRandomPathSearcher::is_target_reachable(): executor.path_manager->cfg_paths[parent_f].size() = " << executor.path_manager->cfg_paths[parent_f].size() << "\n";
      assert(executor.path_manager->cfg_paths.count(parent_f));
      target_block = (llvm::BasicBlock *)executor.path_manager->cfg_paths[parent_f].back();
      llvm::outs() << "set\n";
    }
  } else
    llvm::outs() << "DRandomPathSearcher::is_target_reachable(): current function is not in cfg_paths, leaving target block with NULL\n";
  /* If target_block stays NULL, then compute_distances will compute distance from
     parent_bb to return statement */
  llvm::outs() << "DRandomPathSearcher::is_target_reachable(): going inside get_distance\n";
  unsigned distance = executor.path_manager->get_distance(parent_f, parent_bb,target_block);
 
  //llvm::outs() <<  "DRandomPathSearcher::is_target_reachable(): distance = " << distance << "\n";
  if(distance == UINT_MAX)
    return false;
  return true;
}

ExecutionState &DRandomPathSearcher::selectState() {
  unsigned flips=0, bits=0;
  PTree::Node *n = executor.processTree->root;

  llvm::outs() << "\n == DRandomPathSearcher: Starting state search.\n";
  while (!n->data) 
  {
    bool bad_left =  (!n->left  || blacklisted.count(n->left ));
    bool bad_right = (!n->right || blacklisted.count(n->right));
    /* If both 'left' and 'right' are blacklisted we blacklist the current
     * node and go one level up in the execution tree */
    if(bad_left && bad_right)
    {
      /* If cannot reach the target from the root, tell the executor that
       * there are not good states, and return */
      if(n == executor.processTree->root)
      {
        this->no_good_states = true;
        llvm::outs() << "No good states\n";
        return *(*executor.states.begin());
      }

      blacklisted.insert(n);
      n = n->parent;
      continue;
    }

    /* At least one child is good if we got here */
    if (bad_left) {
      n = n->right;
    } else if (bad_right) {
      n = n->left;
    } else {
      if (bits==0) {
        flips = theRNG.getInt32();
        bits = 32;
      }
      --bits;
      n = (flips&(1<<bits)) ? n->left : n->right;
    }

    /* If we are at the leaf, and we cannot reach the target from the
     * state's instruction, We blakclist the node and go one level up
     * in the process tree */
    if(n->data && !is_target_reachable(n->data))
    {
    /* Debug print */
            ExecutionState *leaf = n->data; 
            llvm::Instruction *state_inst = leaf->pc->inst;
            llvm::outs() << " ((((((((((((())))))))))))) State is in function " << state_inst->getParent()->getParent()->getName() << "()\n";
            llvm::outs() << "Unreacheable state's instruction: " << *state_inst << "\n";
    /* */
      blacklisted.insert(n);
      n = n->parent;
    }
  }

  ExecutionState *chosen = n->data; 
  llvm::Instruction *state_inst = chosen->pc->inst;
  llvm::outs() << " ====> State is in function " << state_inst->getParent()->getParent()->getName() << "()\n";
  llvm::outs() << "State's instruction: " << *state_inst << "\n";

  return *n->data;
}

void DRandomPathSearcher::update(ExecutionState *current,
                                const std::set<ExecutionState*> &addedStates,
                                const std::set<ExecutionState*> &removedStates) {
}

bool DRandomPathSearcher::empty() { 
  return executor.states.empty(); 
}

///

///

RandomPathSearcher::RandomPathSearcher(Executor &_executor)
  : executor(_executor) {
}

RandomPathSearcher::~RandomPathSearcher() {
}

ExecutionState &RandomPathSearcher::selectState() {
  unsigned flips=0, bits=0;
  PTree::Node *n = executor.processTree->root;
  
  while (!n->data) {
    if (!n->left) {
      n = n->right;
    } else if (!n->right) {
      n = n->left;
    } else {
      if (bits==0) {
        flips = theRNG.getInt32();
        bits = 32;
      }
      --bits;
      n = (flips&(1<<bits)) ? n->left : n->right;
    }
  }

  return *n->data;
}

void RandomPathSearcher::update(ExecutionState *current,
                                const std::set<ExecutionState*> &addedStates,
                                const std::set<ExecutionState*> &removedStates) {
}

bool RandomPathSearcher::empty() { 
  return executor.states.empty(); 
}

///

BumpMergingSearcher::BumpMergingSearcher(Executor &_executor, Searcher *_baseSearcher) 
  : executor(_executor),
    baseSearcher(_baseSearcher),
    mergeFunction(executor.kmodule->kleeMergeFn) {
}

BumpMergingSearcher::~BumpMergingSearcher() {
  delete baseSearcher;
}

///

Instruction *BumpMergingSearcher::getMergePoint(ExecutionState &es) {  
  if (mergeFunction) {
    Instruction *i = es.pc->inst;

    if (i->getOpcode()==Instruction::Call) {
      CallSite cs(cast<CallInst>(i));
      if (mergeFunction==cs.getCalledFunction())
        return i;
    }
  }

  return 0;
}

ExecutionState &BumpMergingSearcher::selectState() {
entry:
  // out of base states, pick one to pop
  if (baseSearcher->empty()) {
    std::map<llvm::Instruction*, ExecutionState*>::iterator it = 
      statesAtMerge.begin();
    ExecutionState *es = it->second;
    statesAtMerge.erase(it);
    ++es->pc;

    baseSearcher->addState(es);
  }

  ExecutionState &es = baseSearcher->selectState();

  if (Instruction *mp = getMergePoint(es)) {
    std::map<llvm::Instruction*, ExecutionState*>::iterator it = 
      statesAtMerge.find(mp);

    baseSearcher->removeState(&es);

    if (it==statesAtMerge.end()) {
      statesAtMerge.insert(std::make_pair(mp, &es));
    } else {
      ExecutionState *mergeWith = it->second;
      if (mergeWith->merge(es)) {
        // hack, because we are terminating the state we need to let
        // the baseSearcher know about it again
        baseSearcher->addState(&es);
        executor.terminateState(es);
      } else {
        it->second = &es; // the bump
        ++mergeWith->pc;

        baseSearcher->addState(mergeWith);
      }
    }

    goto entry;
  } else {
    return es;
  }
}

void BumpMergingSearcher::update(ExecutionState *current,
                                 const std::set<ExecutionState*> &addedStates,
                                 const std::set<ExecutionState*> &removedStates) {
  baseSearcher->update(current, addedStates, removedStates);
}

///

MergingSearcher::MergingSearcher(Executor &_executor, Searcher *_baseSearcher) 
  : executor(_executor),
    baseSearcher(_baseSearcher),
    mergeFunction(executor.kmodule->kleeMergeFn) {
}

MergingSearcher::~MergingSearcher() {
  delete baseSearcher;
}

///

Instruction *MergingSearcher::getMergePoint(ExecutionState &es) {
  if (mergeFunction) {
    Instruction *i = es.pc->inst;

    if (i->getOpcode()==Instruction::Call) {
      CallSite cs(cast<CallInst>(i));
      if (mergeFunction==cs.getCalledFunction())
        return i;
    }
  }

  return 0;
}

ExecutionState &MergingSearcher::selectState() {
  while (!baseSearcher->empty()) {
    ExecutionState &es = baseSearcher->selectState();
    if (getMergePoint(es)) {
      baseSearcher->removeState(&es, &es);
      statesAtMerge.insert(&es);
    } else {
      return es;
    }
  }
  
  // build map of merge point -> state list
  std::map<Instruction*, std::vector<ExecutionState*> > merges;
  for (std::set<ExecutionState*>::const_iterator it = statesAtMerge.begin(),
         ie = statesAtMerge.end(); it != ie; ++it) {
    ExecutionState &state = **it;
    Instruction *mp = getMergePoint(state);
    
    merges[mp].push_back(&state);
  }
  
  if (DebugLogMerge)
    llvm::errs() << "-- all at merge --\n";
  for (std::map<Instruction*, std::vector<ExecutionState*> >::iterator
         it = merges.begin(), ie = merges.end(); it != ie; ++it) {
    if (DebugLogMerge) {
      llvm::errs() << "\tmerge: " << it->first << " [";
      for (std::vector<ExecutionState*>::iterator it2 = it->second.begin(),
             ie2 = it->second.end(); it2 != ie2; ++it2) {
        ExecutionState *state = *it2;
        llvm::errs() << state << ", ";
      }
      llvm::errs() << "]\n";
    }

    // merge states
    std::set<ExecutionState*> toMerge(it->second.begin(), it->second.end());
    while (!toMerge.empty()) {
      ExecutionState *base = *toMerge.begin();
      toMerge.erase(toMerge.begin());
      
      std::set<ExecutionState*> toErase;
      for (std::set<ExecutionState*>::iterator it = toMerge.begin(),
             ie = toMerge.end(); it != ie; ++it) {
        ExecutionState *mergeWith = *it;
        
        if (base->merge(*mergeWith)) {
          toErase.insert(mergeWith);
        }
      }
      if (DebugLogMerge && !toErase.empty()) {
        llvm::errs() << "\t\tmerged: " << base << " with [";
        for (std::set<ExecutionState*>::iterator it = toErase.begin(),
               ie = toErase.end(); it != ie; ++it) {
          if (it!=toErase.begin()) llvm::errs() << ", ";
          llvm::errs() << *it;
        }
        llvm::errs() << "]\n";
      }
      for (std::set<ExecutionState*>::iterator it = toErase.begin(),
             ie = toErase.end(); it != ie; ++it) {
        std::set<ExecutionState*>::iterator it2 = toMerge.find(*it);
        assert(it2!=toMerge.end());
        executor.terminateState(**it);
        toMerge.erase(it2);
      }

      // step past merge and toss base back in pool
      statesAtMerge.erase(statesAtMerge.find(base));
      ++base->pc;
      baseSearcher->addState(base);
    }  
  }
  
  if (DebugLogMerge)
    llvm::errs() << "-- merge complete, continuing --\n";
  
  return selectState();
}

void MergingSearcher::update(ExecutionState *current,
                             const std::set<ExecutionState*> &addedStates,
                             const std::set<ExecutionState*> &removedStates) {
  if (!removedStates.empty()) {
    std::set<ExecutionState *> alt = removedStates;
    for (std::set<ExecutionState*>::const_iterator it = removedStates.begin(),
           ie = removedStates.end(); it != ie; ++it) {
      ExecutionState *es = *it;
      std::set<ExecutionState*>::const_iterator it2 = statesAtMerge.find(es);
      if (it2 != statesAtMerge.end()) {
        statesAtMerge.erase(it2);
        alt.erase(alt.find(es));
      }
    }    
    baseSearcher->update(current, addedStates, alt);
  } else {
    baseSearcher->update(current, addedStates, removedStates);
  }
}

///

BatchingSearcher::BatchingSearcher(Searcher *_baseSearcher,
                                   double _timeBudget,
                                   unsigned _instructionBudget) 
  : baseSearcher(_baseSearcher),
    timeBudget(_timeBudget),
    instructionBudget(_instructionBudget),
    lastState(0) {
  
}

BatchingSearcher::~BatchingSearcher() {
  delete baseSearcher;
}

ExecutionState &BatchingSearcher::selectState() {
  if (!lastState || 
      (util::getWallTime()-lastStartTime)>timeBudget ||
      (stats::instructions-lastStartInstructions)>instructionBudget) {
    if (lastState) {
      double delta = util::getWallTime()-lastStartTime;
      if (delta>timeBudget*1.1) {
        llvm::errs() << "KLEE: increased time budget from " << timeBudget
                     << " to " << delta << "\n";
        timeBudget = delta;
      }
    }
    lastState = &baseSearcher->selectState();
    lastStartTime = util::getWallTime();
    lastStartInstructions = stats::instructions;
    return *lastState;
  } else {
    return *lastState;
  }
}

void BatchingSearcher::update(ExecutionState *current,
                              const std::set<ExecutionState*> &addedStates,
                              const std::set<ExecutionState*> &removedStates) {
  if (removedStates.count(lastState))
    lastState = 0;
  baseSearcher->update(current, addedStates, removedStates);
}

/***/

IterativeDeepeningTimeSearcher::IterativeDeepeningTimeSearcher(Searcher *_baseSearcher)
  : baseSearcher(_baseSearcher),
    time(1.) {
}

IterativeDeepeningTimeSearcher::~IterativeDeepeningTimeSearcher() {
  delete baseSearcher;
}

ExecutionState &IterativeDeepeningTimeSearcher::selectState() {
  ExecutionState &res = baseSearcher->selectState();
  startTime = util::getWallTime();
  return res;
}

void IterativeDeepeningTimeSearcher::update(ExecutionState *current,
                                            const std::set<ExecutionState*> &addedStates,
                                            const std::set<ExecutionState*> &removedStates) {
  double elapsed = util::getWallTime() - startTime;

  if (!removedStates.empty()) {
    std::set<ExecutionState *> alt = removedStates;
    for (std::set<ExecutionState*>::const_iterator it = removedStates.begin(),
           ie = removedStates.end(); it != ie; ++it) {
      ExecutionState *es = *it;
      std::set<ExecutionState*>::const_iterator it2 = pausedStates.find(es);
      if (it2 != pausedStates.end()) {
        pausedStates.erase(it);
        alt.erase(alt.find(es));
      }
    }    
    baseSearcher->update(current, addedStates, alt);
  } else {
    baseSearcher->update(current, addedStates, removedStates);
  }

  if (current && !removedStates.count(current) && elapsed>time) {
    pausedStates.insert(current);
    baseSearcher->removeState(current);
  }

  if (baseSearcher->empty()) {
    time *= 2;
    llvm::errs() << "KLEE: increasing time budget to: " << time << "\n";
    baseSearcher->update(0, pausedStates, std::set<ExecutionState*>());
    pausedStates.clear();
  }
}

/***/

InterleavedSearcher::InterleavedSearcher(const std::vector<Searcher*> &_searchers, const std::vector<Searcher*> &_copies)
  : searchers(_searchers), copies(_copies),
    index(1) {
}

InterleavedSearcher::~InterleavedSearcher() {
  for (std::vector<Searcher*>::const_iterator it = searchers.begin(),
         ie = searchers.end(); it != ie; ++it)
    delete *it;
}

ExecutionState &InterleavedSearcher::selectState() {
  //Searcher *s = searchers[--index];
  //if (index==0) index = searchers.size();
  Searcher *s = copies[--index];
  if (index==0) index = copies.size();
  //return s->selectState();
  ExecutionState &state = s->selectState();
  this->no_good_states = s->no_good_states;
  return state;
}

void InterleavedSearcher::update(ExecutionState *current,
                                 const std::set<ExecutionState*> &addedStates,
                                 const std::set<ExecutionState*> &removedStates) {
  for (std::vector<Searcher*>::const_iterator it = searchers.begin(),
         ie = searchers.end(); it != ie; ++it)
    (*it)->update(current, addedStates, removedStates);
}

