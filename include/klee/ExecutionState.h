//===-- ExecutionState.h ----------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef KLEE_EXECUTIONSTATE_H
#define KLEE_EXECUTIONSTATE_H

#include "klee/Constraints.h"
#include "klee/Expr.h"
#include "klee/PathSummary.h"
#include "klee/Internal/ADT/TreeStream.h"

// FIXME: We do not want to be exposing these? :(
#include "../../lib/Core/AddressSpace.h"
#include "klee/Internal/Module/KInstIterator.h"

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#else
#include "llvm/Constants.h"
#include "llvm/Instructions.h"
#include "llvm/Module.h"
#endif
#include "llvm/ADT/StringExtras.h"

#include <map>
#include <set>
#include <vector>
#include <list>

namespace klee {
class Array;
class CallPathNode;
struct Cell;
struct KFunction;
struct KInstruction;
class MemoryObject;
class PTreeNode;
struct InstructionInfo;

llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const MemoryMap &mm);

//class PathSummary;
//typedef PathSummary path_summary_ty;
//typedef std::map<llvm::Value *, std::vector<const Array *> > global_symbolic_replacements_ty;


struct StackFrame {
  KInstIterator caller;
  KFunction *kf;
  CallPathNode *callPathNode;
  KInstIterator restorePC; // This points to the return instruction when the stack frame is for ISR,
                           // It is NULL otherwise
  unsigned incomingBBIndex;

  std::vector<const MemoryObject *> allocas;
  Cell *locals;

  /// IVAN ADDITIONS BEGIN

  /* While doing backward symbolic execution and building the current path summary,
   * we replaceed call instruction with new symbolics and saved them in the
   * <call_symbolic_replacements>. Then for each symbolics we later generated a good path
   * summary which satisfies conditions on ret value.
   * Now we do forward symbolic execution, and for each call, we need to use the right
   * path summary of the called function */
  unsigned cur_call_symbolics_seq_num;
  path_summary_ty *cur_fsummary; // Function summary along which we are going during the forward symbex
  std::set<path_summary_ty *> fitting_psummaries;
  unsigned num_of_constraints; // How many constraints we added in current function
  std::vector<llvm::Instruction* > path_instructions;

  /// IVAN ADDITIONS END

  /// Minimum distance to an uncovered instruction once the function
  /// returns. This is not a good place for this but is used to
  /// quickly compute the context sensitive minimum distance to an
  /// uncovered instruction. This value is updated by the StatsTracker
  /// periodically.
  unsigned minDistToUncoveredOnReturn;

  // For vararg functions: arguments not passed via parameter are
  // stored (packed tightly) in a local (alloca) memory object. This
  // is setup to match the way the front-end generates vaarg code (it
  // does not pass vaarg through as expected). VACopy is lowered inside
  // of intrinsic lowering.
  MemoryObject *varargs;

  StackFrame(KInstIterator caller, KFunction *kf);
  StackFrame(KInstIterator _caller, KInstIterator _restore, KFunction *_kf, unsigned incomingBBIndexn);
  StackFrame(const StackFrame &s);
  ~StackFrame();
};


/* *** Classes for state pruning begin *** */

typedef std::map<const llvm::Value *, ref<Expr> > ValMap;
typedef std::map<const int, ref<Expr> > RegMap;

/**
 *  Snapshot of a stack frame. We try to keep only those fields
 *  which we need to compare two SavedConfig's
 */ 
class SavedFrame
{
  public:
    RegMap locals; /* Copy of stack frame's locals */
    KInstIterator caller;
    KFunction * kf;
    SavedFrame(StackFrame & frame);
    SavedFrame(KInstIterator caller, KFunction * callee);
};

/**
 *  Memory (read: execution state) configuration snapshot.
 */
class SavedConfig
{
  public:
    int stackSize;
    ValMap objs; /* Copies of objects from state.AddressSpaces.objects */
    SavedFrame ** stack; /* list of stack frames copied from the state */
    //std::list<KInstruction*> path;
    std::vector<llvm::Instruction *> path_instructions; /* copied from the state on which
                                                           this configuration is based on */
    SavedConfig(int stackSizeIn, std::vector<llvm::Instruction *> pathIn);
    SavedConfig(ExecutionState & state);
};


/**
 *  TODO: ADD CLASS DESCRIPTION
 * ConfigList:
 *  — List of SavedConfig’s <diffs>
 *  — map from SavedConfigs to list of SavedConfigs <bases>
 *  — SavedConfig <basis>
 */
class ConfList
{
  public:
    std::list<SavedConfig *> diffs;
    std::map<SavedConfig *, std::list<SavedConfig *> > bases;
    SavedConfig * basis;
    //SavedConfig * diff(ExecutionState& state, int thresh, bool& prunable);
    SavedConfig * diff(ExecutionState& state, bool& prunable);
    SavedConfig * getBasis(ExecutionState& state, bool& found);
    bool distinct(SavedConfig * conflicts, SavedConfig * basis, ExecutionState& state, int thresh);
    
    ConfList(SavedConfig * saved)
    {
      basis = saved;
      bases[basis];
    }
    
    unsigned size()
    {
      unsigned result = 0;
      std::map<SavedConfig *, std::list<SavedConfig *> >::iterator itr = bases.begin();
      std::map<SavedConfig *, std::list<SavedConfig *> >::iterator end = bases.end();
      for ( ; itr != end ; ++itr)
      {
        //1 for the basis, plus each diff of the basis
        result += 1 + itr->second.size();
      }
      return result;
    }
};


typedef std::map<llvm::Instruction *, ConfList *> MemConfMap;

/* *** Classes for state pruning end *** */

/// @brief ExecutionState representing a path under exploration
class ExecutionState {
public:
  typedef std::vector<StackFrame> stack_ty;

private:
  // unsupported, use copy constructor
  ExecutionState &operator=(const ExecutionState &);

  std::map<std::string, std::string> fnAliases;

public:
  // Execution - Control Flow specific

  /// IVAN ADDITTIONS BEGIN
  llvm::Function * interruptFun; // Set to the interrupt hander this state is executing (or NULL if not inside interrupt)
	ref<ConstantExpr> statusRegisterAddress; /* We allocate a memory object for
                                                the status register, and keep its address
                                                in this variable */
  int interrupt_depth;
  bool isOnPath; // The current basic block is on path 
  int pathDeviationDepth; // 0 means that deviated control flow in the same functions as the path. This filed only increaes when we call function from a off-path block
  int debug1; // holds the number of time the following instr was executed: br i1 %cmp11, label %if.then13, label %if.end16 
  int debug2; // holds the number of time the following instr was executed:  br i1 %cmp6, label %for.body, label %for.end 
  llvm::BasicBlock *first_offroad_block; // This variable is set to the first basic block at which we deviated from the path
  std::map<llvm::BasicBlock *, std::pair<int, int> > path_arc_falures;
  int onPathInsts;
  std::vector<llvm::Instruction *> callHistory; // TODO: add documentation about his field. The size of this array equals the call depth.
  int lastPathIndex;
  llvm::Function *target_func; // stop execution when we reach a call to this function
  std::vector< ref<Expr> > *ret_value_constraints; // This is constraints on the return value of the current function
                                                   // We use it for backward symbolic execution
  std::map<llvm::Function *, call_symbolic_replacements_ty> call_symbolic_replacements;

  /* Fields for forward_symbex */
  path_summary_ty *cur_fsummary;
  path_summary_ty *next_fsummary;
  std::set<path_summary_ty *> fitting_psummaries;
  std::set<path_summary_ty *> blacklisted_psummaries;

  /* Field for backward symbex */
  InnerCall *cur_inner_call; // For backward symbex we need to execute inner calls.
                             // This field is set to the current inner
                             // call or to NULL if we execute a function
                             // on the path
  bool complies_with_cur_inner_call;

  UpperCall *cur_upper_call; 

  global_symbolic_replacements_ty global_symbolic_replacements;

  /* For backward symbex: record which branch we took along a function execution */
  std::vector<int> path_choices; 
  std::vector<llvm::Instruction *> path_instructions; 
  std::vector<std::string> path_choices_debug; 

  std::vector<ref<Expr> > get_call_symbolics(ref<Expr> complex_expr);

  //int callsInCurrentBB; // How many times this block executed a call instruction (excluding cases when a called function has a declaration only)
  
  /// IVAN ADDITTIONS END

  /// @brief Pointer to instruction to be executed after the current
  /// instruction
  KInstIterator pc;

  /// @brief Pointer to instruction which is currently executed
  KInstIterator prevPC;

  /// @brief Stack representing the current instruction stream
  stack_ty stack;

  /// @brief Remember from which Basic Block control flow arrived
  /// (i.e. to select the right phi values)
  unsigned incomingBBIndex;

  // Overall state of the state - Data specific

  /// @brief Address space used by this state (e.g. Global and Heap)
  AddressSpace addressSpace;

  /// @brief Constraints collected so far
  ConstraintManager constraints;

  /// Statistics and information

  /// @brief Costs for all queries issued for this state, in seconds
  mutable double queryCost;

  /// @brief Weight assigned for importance of this state.  Can be
  /// used for searchers to decide what paths to explore
  double weight;

  /// @brief Exploration depth, i.e., number of times KLEE branched for this state
  unsigned depth;

  /// @brief History of complete path: represents branches taken to
  /// reach/create this state (both concrete and symbolic)
  TreeOStream pathOS;

  /// @brief History of symbolic path: represents symbolic branches
  /// taken to reach/create this state
  TreeOStream symPathOS;

  /// @brief Counts how many instructions were executed since the last new
  /// instruction was covered.
  unsigned instsSinceCovNew;

  /// @brief Whether a new instruction was covered in this state
  bool coveredNew;

  /// @brief Disables forking for this state. Set by user code
  bool forkDisabled;

  /// @brief Set containing which lines in which files are covered by this state
  std::map<const std::string *, std::set<unsigned> > coveredLines;

  /// @brief Pointer to the process tree of the current state
  PTreeNode *ptreeNode;

  /// @brief Ordered list of symbolics: used to generate test cases.
  //
  // FIXME: Move to a shared list structure (not critical).
  std::vector<std::pair<const MemoryObject *, const Array *> > symbolics;

  /// @brief Set of used array names for this state.  Used to avoid collisions.
  std::set<std::string> arrayNames;

  std::string getFnAlias(std::string fn);
  void addFnAlias(std::string old_fn, std::string new_fn);
  void removeFnAlias(std::string fn);

private:
  ExecutionState() : ptreeNode(0) {}

public:
  ExecutionState(KFunction *kf);

  // XXX total hack, just used to make a state so solver can
  // use on structure
  ExecutionState(const std::vector<ref<Expr> > &assumptions);

  ExecutionState(const ExecutionState &state);

  ~ExecutionState();

  ExecutionState *branch();

  void pushFrame(KInstIterator caller, KFunction *kf);
  void pushFrame(KInstIterator caller, KInstIterator restore, KFunction *kf);
  void popFrame();

  void addSymbolic(const MemoryObject *mo, const Array *array);
  void addConstraint(ref<Expr> e) { constraints.addConstraint(e); }

  bool merge(const ExecutionState &b);
  void dumpStack(llvm::raw_ostream &out) const;
};
}

#endif
