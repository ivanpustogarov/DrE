//===-- SummaryExecutor.h ----------------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Class to collect function summaries
//
//===----------------------------------------------------------------------===//

#ifndef KLEE_SUMMARYEXECUTOR_H
#define KLEE_SUMMARYEXECUTOR_H

#include "llvm/Support/CommandLine.h"
#include "../../lib/Core/Executor.h"

#include "klee/ExecutionState.h"
#include "klee/InterpreterManager.h"
#include "klee/Solver.h"
#include "klee/PathManager.h"
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

struct KTest;

namespace llvm {
  class BasicBlock;
  class BranchInst;
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
  struct Cell;
  class ExecutionState;
  class ExternalDispatcher;
  class Expr;
  class InstructionInfoTable;
  struct KFunction;
  struct KInstruction;
  class KInstIterator;
  class KModule;
  class MemoryManager;
  class MemoryObject;
  class ObjectState;
  class PTree;
  class Searcher;
  class SeedInfo;
  class SpecialFunctionHandler;
  struct StackFrame;
  class StatsTracker;
  class TimingSolver;
  class TreeStreamWriter;
  template<class T> class ref;
  class PathManager;
  class InterpreterManager;

  /// \todo Add a context object to keep track of data only live
  /// during an instruction step. Should contain addedStates,
  /// removedStates, and haltExecution, among others.

class SummaryExecutor : public Executor //public Interpreter
{

  friend class BumpMergingSearcher;
  friend class MergingSearcher;
  friend class RandomPathSearcher;
  friend class OwningSearcher;
  friend class WeightedRandomSearcher;
  friend class SpecialFunctionHandler;
  friend class StatsTracker;

  typedef std::pair<ExecutionState*,ExecutionState*> StatePair;

public:
  //SummaryExecutor(Solver *_coreSolver, KModule *_kmodule);
  SummaryExecutor(const InterpreterOptions &opts, Solver *_coreSolver, KModule *_kmodule);
  virtual ~SummaryExecutor();
  virtual void setArch(Architecture *_arch);
  virtual void setPathManager(PathManager *_path_manager);
  void setFunction(const llvm::Function *f);
  //void collectPathSummaries(const llvm::Function *target_func, InnerCall *inner_call = NULL);
  void collectPathSummaries(UpperCall *upper_call, InnerCall *inner_call);
  //int continue_run(const llvm::Function *target_func, InnerCall *inner_call);
  int continue_run(UpperCall *upper_call, InnerCall *inner_call);
  // XXX should just be moved out to utility module
  ref<klee::ConstantExpr> evalConstant(const llvm::Constant *c);
  Expr::Width getWidthForLLVMType(LLVM_TYPE_Q llvm::Type *type) const;
  void get_global_calling_context();
  bool state_complies_with_inner_call(ExecutionState *s);


public:
  /* The list of formal arguments of this summary executor's function */
  std::vector<ref<Expr> > fargs;
  std::vector<path_summary_ty *> path_summaries;
  const llvm::Function *func;
  InterpreterManager *interpreter_manager;
  /* Number of collected path summaries during interpreter manager round */
  unsigned num_new_summaries_during_round;
  /* Map of Function that are called from <this->func>, and their callees (recursively) */
  //std::set<llvm::Function *> callees;
  std::map<llvm::Function *, std::set<llvm::Function *> > callees;
  /* Function that call <func> */
  std::set<llvm::Function *> callers;
  /* Globales used in <func> */
  //std::map<const llvm::GlobalValue*, MemoryObject*> used_globals;
  std::set<const llvm::GlobalValue*> used_globals;
  /* Globales used in <func>, and used in at least one of the callers, but not in callees.
     This measn that we only need to initialize them as symbolic */
  std::set<const llvm::GlobalValue *> globals_to_init;
  /* Globales used in <func>, and used in at least one of the callers, but not in callees.
     This measn that we only need to initialize them as symbolic */
  std::map<const llvm::Function *, std::set<const llvm::GlobalValue*> > globals_to_refresh;

private:
  /* Fields */
  //PathManager *path_manager;

protected:

  /* FIXME: remove this field, even one summary should be enough if it
     satisfies condiitions. You should be able to return to
     collecting path summaries */
  unsigned min_num_of_summaries_to_collect = 5; 
  bool should_collect_more_summaries = true;
  /* We use this field for compostional symblolic execution;
     1) If we go along the call path, then we set it to 1
        when we reach the call to the next function in the path;
     2) If we execute a function which we replaced with a symbolics,
        then we set this field to 1, when we reach a return instruction
        and the constraints on the return value are satisfied. */
  int comp_symbex_target_reached; 
  std::set<llvm::Function *> mergeBlacklist;
  MemConfMap allSavedConfigs;

  /* *** */

  /* Methods */
  InnerCall* get_InnerCall_by_seqnum(path_summary_ty *smmry, unsigned seqnum);
  ref<Expr> comp_symbex_replace_for_retvalue(ref<Expr> expr, ref<Expr> &retvalue);
  bool conds_are_solvable(ref<Expr> x, std::vector< ref<Expr> > *conditions);
  bool check_formal_args_against_psummary(path_summary_ty &smmry, std::vector<std::vector< ref<Expr> > > &formal_args_conditions);
  void print_function_summaries(std::map<llvm::Function *, std::vector<path_summary_ty *> > ps);
  void print_state_constraints(ExecutionState *state);
  bool isStateMergeTime(KInstruction *ki);
  bool isDuplicateState(ExecutionState& state, KInstruction *ki);
  void initializeMergeBlackList();
  uint64_t get_free_memchunk_at_guest(unsigned size, ExecutionState *state);
  void init_globals_with_symbolic(ExecutionState *s, llvm::Function *f);
  std::vector<ref<Expr> > extract_constraints_for_symbolics(ConstraintManager &path_constraints, ref<Expr> &e);
  unsigned getPointerTypeElementWidth(llvm::Type *type);
  unsigned getIntTypeWidth(llvm::Type *type);
  void updateGlobalsDueToPossibleInterrupts(ExecutionState * state, KInstruction * inst);
  void setFreshSymbolicsToGlobals(ExecutionState *state, std::string reason, const llvm::Function *callee = NULL);
  void make_args_symbolic(ExecutionState *state,llvm::Function  *f1);
  /* *** */

  /// **** COPIED FROM EXECUTOR *****/

private:
  llvm::Function* getTargetFunction(llvm::Value *calledVal,
                                    ExecutionState &state);
  
  virtual void executeInstruction(ExecutionState &state, KInstruction *ki);

  void printFileLine(ExecutionState &state, KInstruction *ki);

  virtual void run(ExecutionState &initialState);

  // Given a concrete object in our [klee's] address space, add it to 
  // objects checked code can reference.
  //MemoryObject *addExternalObject(ExecutionState &state, void *addr, 
  //                                unsigned size, bool isReadOnly);

  void initializeGlobalObject(ExecutionState &state, ObjectState *os, 
			      const llvm::Constant *c,
			      unsigned offset);
  void initializeGlobals(ExecutionState &state);
  /// IVAN ADDITIONS BEGIN
  void initializeSpecialGlobals(ExecutionState &state);
  /// IVAN ADDITIONS END

  void stepInstruction(ExecutionState &state);
  void updateStates(ExecutionState *current);
  void transferToBasicBlock(llvm::BasicBlock *dst, 
			    llvm::BasicBlock *src,
			    ExecutionState &state);

  void callExternalFunction(ExecutionState &state,
                            KInstruction *target,
                            llvm::Function *function,
                            std::vector< ref<Expr> > &arguments);

  ObjectState *bindObjectInState(ExecutionState &state, const MemoryObject *mo,
                                 bool isLocal, const Array *array = 0);
  /// Resolve a pointer to the memory objects it could point to the
  /// start of, forking execution when necessary and generating errors
  /// for pointers to invalid locations (either out of bounds or
  /// address inside the middle of objects).
  ///
  /// \param results[out] A list of ((MemoryObject,ObjectState),
  /// state) pairs for each object the given address can point to the
  /// beginning of.
  typedef std::vector< std::pair<std::pair<const MemoryObject*, const ObjectState*>, 
                                 ExecutionState*> > ExactResolutionList;
  void resolveExact(ExecutionState &state,
                    ref<Expr> p,
                    ExactResolutionList &results,
                    const std::string &name);

  /// Allocate and bind a new object in a particular state. NOTE: This
  /// function may fork.
  ///
  /// \param isLocal Flag to indicate if the object should be
  /// automatically deallocated on function return (this also makes it
  /// illegal to free directly).
  ///
  /// \param target Value at which to bind the base address of the new
  /// object.
  ///
  /// \param reallocFrom If non-zero and the allocation succeeds,
  /// initialize the new object from the given one and unbind it when
  /// done (realloc semantics). The initialized bytes will be the
  /// minimum of the size of the old and new objects, with remaining
  /// bytes initialized as specified by zeroMemory.
  void executeAlloc(ExecutionState &state,
                    ref<Expr> size,
                    bool isLocal,
                    KInstruction *target,
                    bool zeroMemory=false,
                    const ObjectState *reallocFrom=0);

  /// Free the given address with checking for errors. If target is
  /// given it will be bound to 0 in the resulting states (this is a
  /// convenience for realloc). Note that this function can cause the
  /// state to fork and that \ref state cannot be safely accessed
  /// afterwards.
  void executeFree(ExecutionState &state,
                   ref<Expr> address,
                   KInstruction *target = 0);
  
  void executeCall(ExecutionState &state, 
                   KInstruction *ki,
                   llvm::Function *f,
                   std::vector< ref<Expr> > &arguments);
                   
  // do address resolution / object binding / out of bounds checking
  // and perform the operation
  void executeMemoryOperation(ExecutionState &state,
                              bool isWrite,
                              ref<Expr> address,
                              ref<Expr> value /* undef if read */,
                              KInstruction *target /* undef if write */);

  void executeMakeSymbolic(ExecutionState &state, const MemoryObject *mo,
                           const std::string &name);

  /// Create a new state where each input condition has been added as
  /// a constraint and return the results. The input state is included
  /// as one of the results. Note that the output vector may included
  /// NULL pointers for states which were unable to be created.
  void branch(ExecutionState &state, 
              const std::vector< ref<Expr> > &conditions,
              std::vector<ExecutionState*> &result);

  // Fork current and return states in which condition holds / does
  // not hold, respectively. One of the states is necessarily the
  // current state, and one of the states may be null.
  StatePair fork(ExecutionState &current, ref<Expr> condition, bool isInternal);

  /// Add the given (boolean) condition as a constraint on state. This
  /// function is a wrapper around the state's addConstraint function
  /// which also manages propagation of implied values,
  /// validity checks, and seed patching.
  void addConstraint(ExecutionState &state, ref<Expr> condition);

  // Called on [for now] concrete reads, replaces constant with a symbolic
  // Used for testing.
  ref<Expr> replaceReadWithSymbolic(ExecutionState &state, ref<Expr> e);

  const Cell& eval(KInstruction *ki, unsigned index, 
                   ExecutionState &state) const;

  Cell& getArgumentCell(ExecutionState &state,
                        KFunction *kf,
                        unsigned index) {
    return state.stack.back().locals[kf->getArgRegister(index)];
  }

  Cell& getDestCell(ExecutionState &state,
                    KInstruction *target) {
    return state.stack.back().locals[target->dest];
  }

  void bindLocal(KInstruction *target, 
                 ExecutionState &state, 
                 ref<Expr> value);
  void bindArgument(KFunction *kf, 
                    unsigned index,
                    ExecutionState &state,
                    ref<Expr> value);

  ref<klee::ConstantExpr> evalConstantExpr(const llvm::ConstantExpr *ce);

  /// Return a unique constant value for the given expression in the
  /// given state, if it has one (i.e. it provably only has a single
  /// value). Otherwise return the original expression.
  ref<Expr> toUnique(const ExecutionState &state, ref<Expr> &e);

  /// Return a constant value for the given expression, forcing it to
  /// be constant in the given state by adding a constraint if
  /// necessary. Note that this function breaks completeness and
  /// should generally be avoided.
  ///
  /// \param purpose An identify string to printed in case of concretization.
  ref<klee::ConstantExpr> toConstant(ExecutionState &state, ref<Expr> e, 
                                     const char *purpose);

  /// Bind a constant value for e to the given target. NOTE: This
  /// function may fork state if the state has multiple seeds.
  void executeGetValue(ExecutionState &state, ref<Expr> e, KInstruction *target);

  /// Get textual information regarding a memory address.
  std::string getAddressInfo(ExecutionState &state, ref<Expr> address) const;

  // Determines the \param lastInstruction of the \param state which is not KLEE
  // internal and returns its InstructionInfo
  const InstructionInfo & getLastNonKleeInternalInstruction(const ExecutionState &state,
      llvm::Instruction** lastInstruction);

  // remove state from queue and delete
  void terminateState(ExecutionState &state);
  // call exit handler and terminate state
  void terminateStateEarly(ExecutionState &state, const llvm::Twine &message);
  // call exit handler and terminate state
  void terminateStateOnExit(ExecutionState &state);
  // call error handler and terminate state
  void terminateStateOnError(ExecutionState &state, 
                             const llvm::Twine &message,
                             const char *suffix,
                             const llvm::Twine &longMessage="");

  // call error handler and terminate state, for execution errors
  // (things that should not be possible, like illegal instruction or
  // unlowered instrinsic, or are unsupported, like inline assembly)
  void terminateStateOnExecError(ExecutionState &state, 
                                 const llvm::Twine &message,
                                 const llvm::Twine &info="") {
    terminateStateOnError(state, message, "exec.err", info);
  }

  /// bindModuleConstants - Initialize the module constant table.
  void bindModuleConstants();

  template <typename TypeIt>
  void computeOffsets(KGEPInstruction *kgepi, TypeIt ib, TypeIt ie);
  /* This function is used to keep the right number of indices for getElementPtr
   * instruction. It should be invoked before each computeOffsets() function.
   * We need this function becuase we run Executor::run() (and hence computeOffsets()
   * many times */
  template <typename TypeIt>
  void clearOffsets(KGEPInstruction *kgepi, TypeIt ib, TypeIt ie);

  /// bindInstructionConstants - Initialize any necessary per instruction
  /// constant values.
  void bindInstructionConstants(KInstruction *KI);

  void handlePointsToObj(ExecutionState &state, 
                         KInstruction *target, 
                         const std::vector<ref<Expr> > &arguments);

  void doImpliedValueConcretization(ExecutionState &state,
                                    ref<Expr> e,
                                    ref<ConstantExpr> value);


  //void initTimers();
  void processTimers(ExecutionState *current,
                     double maxInstTime);

public:
  virtual const llvm::Module * setModule(llvm::Module *module, const ModuleOptions &opts) 
  {}
  virtual void setPathWriter(TreeStreamWriter *tsw) {
    pathWriter = tsw;
  }
  virtual void setSymbolicPathWriter(TreeStreamWriter *tsw) {
    symPathWriter = tsw;
  }      
  virtual void setReplayOut(const struct KTest *out) {
    assert(!replayPath && "cannot replay both buffer and path");
    replayOut = out;
    replayPosition = 0;
  }

  virtual void setReplayPath(const std::vector<bool> *path) {
    assert(!replayOut && "cannot replay both buffer and path");
    replayPath = path;
    replayPosition = 0;
  }
  virtual void useSeeds(const std::vector<struct KTest *> *seeds) { 
    usingSeeds = seeds;
  }

  virtual void runFunctionAsMain(llvm::Function *f,
                                 int argc,
                                 char **argv,
                                 char **envp) 
  {}

  virtual void setHaltExecution(bool value) {
    haltExecution = value;
  }

  virtual void setInhibitForking(bool value) {
    inhibitForking = value;
  }


  virtual unsigned getPathStreamID(const ExecutionState &state) {}

  virtual unsigned getSymbolicPathStreamID(const ExecutionState &state) {}

  //virtual void getConstraintLog(const ExecutionState &state,
  //                              std::string &res,
  //                              Interpreter::LogType logFormat = Interpreter::STP) {}

  virtual bool getSymbolicSolution(const ExecutionState &state, 
                                   std::vector< 
                                   std::pair<std::string,
                                   std::vector<unsigned char> > >
                                   &res) {}

  virtual void getCoveredLines(const ExecutionState &state,
                               std::map<const std::string*, std::set<unsigned> > &res) {}


  virtual void getConstraintLog(const ExecutionState &state, std::string &res, Interpreter::LogType logFormat = Interpreter::STP);

};
} // End klee namespace

#endif
