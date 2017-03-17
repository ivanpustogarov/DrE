//===-- ForwardExecutor.cpp ------------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Common.h"
#include "klee/ForwardExecutor.h"
#include "Context.h"
#include "CoreStats.h"
#include "ExternalDispatcher.h"
#include "ImpliedValue.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "PTree.h"
#include "Searcher.h"
#include "SeedInfo.h"
#include "SpecialFunctionHandler.h"
#include "StatsTracker.h"
#include "TimingSolver.h"
#include "UserSearcher.h"
#include "klee/ExecutorCommandLineParameters.h"

#include "../Solver/SolverStats.h"

#include "klee/PathManager.h"
#include "klee/ExecutionState.h"
#include "klee/Expr.h"
#include "klee/Interpreter.h"
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

//RNG theRNG;
//unsigned getIntTypeWidth(llvm::Type *type);
//unsigned getPointerTypeElementWidth(llvm::Type *type);

void ForwardExecutor::setArch(Architecture * _arch)
{
  arch = _arch;
  assert(memory && "You need to initialize MemoryManager first");
  memory->arch = _arch;
}

void ForwardExecutor::setPathManager(PathManager *_path_manager)
{
  assert(!path_manager && "Changing path manager is not supported");
  llvm::outs() << "smmry_executor->replayPath = " << replayPath << "\n";
  path_manager = _path_manager;
}

ForwardExecutor::ForwardExecutor(const InterpreterOptions &opts, Solver *_coreSolver, KModule *_kmodule) :
  Executor(opts, _coreSolver, _kmodule)
{
  specialFunctionHandler = new SpecialFunctionHandler(*this);
  specialFunctionHandler->prepare();
  specialFunctionHandler->bind();
}



/* Create memory objects for flash segments, and periperal registers */
void ForwardExecutor::initializeSpecialGlobals(ExecutionState& state) 
{
  Module *m = kmodule->module;

  /* Allocate memory for the status register. Obviously status register is not a part of RAM,
   * but we need to have a memory object in order to keep per-state values */
  { // new block to limit the scope of the variables and reuse the same names later
    llvm::outs() << "ForwardExecutor::initializeSpecialGlobals(): initializing status register\n";
    MemoryObject *mo = memory->allocate(arch->pointer_size, false, true, NULL);
    if (!mo)
      llvm::report_fatal_error("out of memory");
    ObjectState *os = bindObjectInState(state, mo, false);
    //globalObjects.insert(std::make_pair(i, mo));
    //globalAddresses.insert(std::make_pair(i, mo->getBaseExpr()));
    /* Initialize with concrete zeros */
    os->initializeToZero();

    outs() << "ForwardExecutor::initializeSpecialGlobals(): About to set status register\n";
    ref<Expr> sr_base = mo->getBaseExpr();
    //arch->statusRegisterAddress = cast<ConstantExpr>(sr_base);
    state.statusRegisterAddress = cast<ConstantExpr>(sr_base);
    llvm::outs() << "done setting status register\n";
  }


  /* Create new memory object for each of the flash memory segments and bind it
   * the state. Flash memroy is presistent memory, so should be defined. */
  for (std::vector<FlashMemory *>::iterator flashItr = arch->flashSegs.begin();
            flashItr != arch->flashSegs.end(); ++flashItr) 
  {
    FlashMemory *mem = *flashItr;
    uint64_t size = mem->end - mem->begin + 1;
    outs() << "ForwardExecutor::initializeSpecialGlobals(): Allocating fixed flash memory region: [" << mem->begin << "-" << mem->end << "]\n";
    MemoryObject * mo = memory->allocateFixed(mem->begin, size, NULL);
    ObjectState *os = bindObjectInState(state, mo, false);
    os->initializeToZero();
  }

  /* Create new memory object for each of the periperal registers (e.g. ADC10MEM),
   * and initalize them with fresh symbolic values */
  for (std::map<std::string, SpecialMemory *>::iterator specLocItr = arch->namedAddresses.begin();
            specLocItr != arch->namedAddresses.end(); ++specLocItr) 
  {
    //std::string loc_name = specLocItr->second;
    const SpecialMemory *mem = specLocItr->second;
    //uint64_t size = mem->end - mem->begin + 1;
    outs() << "ForwardExecutor::initializeSpecialGlobals(): Allocating special regiter: " 
           << mem->name << "at [" << mem->base << "-" << mem->base+mem->size << "]\n";
    MemoryObject * mo = memory->allocateFixed(mem->base, mem->size, NULL, true);
    ObjectState *os = bindObjectInState(state, mo, false);

    /* Write fresh symbolics */
    uint64_t w = mem->size*8;
    const Array * array = Array::CreateArray(mem->name + "_arr0", w);
    ref<Expr> fresh_value = Expr::createTempRead(array, w, true);
    ObjectState *wos = state.addressSpace.getWriteable(mo, os);
    wos->write(0, fresh_value);
 
    //os->initializeToZero();
  }



  return;
}


void ForwardExecutor::initializeGlobals(ExecutionState &state) 
{
  Module *m = kmodule->module;
  assert(memory && "MemoryManager is NULL");
  assert(arch && "Architecture is NULL");

  if (m->getModuleInlineAsm() != "")
    klee_warning("executable has module level assembly (ignoring)");
#if LLVM_VERSION_CODE < LLVM_VERSION(3, 3)
  assert(m->lib_begin() == m->lib_end() &&
         "XXX do not support dependent libraries");
#endif
  // represent function globals using the address of the actual llvm function
  // object. given that we use malloc to allocate memory in states this also
  // ensures that we won't conflict. we don't need to allocate a memory object
  // since reading/writing via a function pointer is unsupported anyway.
  outs() << "ForwardExecutor::initializeGlobals(): initializing function addresses\n";
  for (Module::iterator i = m->begin(), ie = m->end(); i != ie; ++i) {
    Function *f = i;
    ref<ConstantExpr> addr(0);

    outs() << "ForwardExecutor::initializeGlobals(): considering  function " << f->getName() << "\n";
    assert(externalDispatcher && "Execternal dispatcher is NULL!");
    // If the symbol has external weak linkage then it is implicitly
    // not defined in this module; if it isn't resolvable then it
    // should be null.
    if (f->hasExternalWeakLinkage() && 
        !externalDispatcher->resolveSymbol(f->getName())) {
      outs() << "ForwardExecutor::initializeGlobals(): creating NULL pointer\n";
      addr = Expr::createPointer(0);
    } else {

      /// IVAN ADDITIONS BEGIN
      MemoryObject *mo = memory->allocate(arch->pointer_size, false, true, i);
      //llvm::outs() << "here\n";
      ObjectState *os = bindObjectInState(state, mo, false);
      /// IVAN ADDITIONS END

      //addr = Expr::createPointer((unsigned long) (void*) f);
      addr = Expr::createPointer(mo->guest_address);
      legalFunctions.insert((uint64_t) (unsigned long) (void*) f);
    }
    
    globalAddresses.insert(std::make_pair(f, addr));
  }

  outs() << "ForwardExecutor::initializeGlobals(): function addresses initialized\n";

  /// IVAN ADDITIONS BEGIN
  /* This allocated flash memory, and peripehral registers */
  outs() << "ForwardExecutor::initializeGlobals(): initializing special memory\n";
  initializeSpecialGlobals(state);
  outs() << "ForwardExecutor::initializeGlobals(): special memory initialized\n";
  /// IVAN ADDITIONS END

  // allocate and initialize globals, done in two passes since we may
  // need address of a global in order to initialize some other one.

  // allocate memory objects for all globals
  for (Module::const_global_iterator i = m->global_begin(), e = m->global_end(); i != e; ++i)
  {
    if (i->isDeclaration())
    {
      // FIXME: We have no general way of handling unknown external
      // symbols. If we really cared about making external stuff work
      // better we could support user definition, or use the EXE style
      // hack where we check the object file information.
  
      outs() << "ForwardExecutor::initializeGlobals(): Allocating stuff for function declaration\n";
      assert(0 && "Allocating memory for declarations is not supported");

      LLVM_TYPE_Q Type *ty = i->getType()->getElementType();
      uint64_t size = kmodule->targetData->getTypeStoreSize(ty);

      // XXX - DWD - hardcode some things until we decide how to fix.
#ifndef WINDOWS
      if (i->getName() == "_ZTVN10__cxxabiv117__class_type_infoE") {
        size = 0x2C;
      } else if (i->getName() == "_ZTVN10__cxxabiv120__si_class_type_infoE") {
        size = 0x2C;
      } else if (i->getName() == "_ZTVN10__cxxabiv121__vmi_class_type_infoE") {
        size = 0x2C;
      }
#endif

      if (size == 0) {
        llvm::errs() << "Unable to find size for global variable: " 
                     << i->getName() 
                     << " (use will result in out of bounds access)\n";
      }

      MemoryObject *mo = memory->allocate(size, false, true, i);
      ObjectState *os = bindObjectInState(state, mo, false);
      globalObjects.insert(std::make_pair(i, mo));
      globalAddresses.insert(std::make_pair(i, mo->getBaseExpr()));

      // Program already running = object already initialized.  Read
      // concrete value and write it to our copy.
      if (size) {
        void *addr;
#if 0
        if (i->getName() == "__dso_handle") 
        {
          addr = &__dso_handle; // wtf ?
        } else 
#endif
        {
          addr = externalDispatcher->resolveSymbol(i->getName());
        }
        if (!addr)
          klee_error("unable to load symbol(%s) while initializing globals.", 
                     i->getName().data());

        for (unsigned offset=0; offset<mo->size; offset++)
          os->write8(offset, ((unsigned char*)addr)[offset]);
      }
    } else 
    {
      LLVM_TYPE_Q Type *ty = i->getType()->getElementType();
      uint64_t size = kmodule->targetData->getTypeStoreSize(ty);

      outs() << "ForwardExecutor::initializeGlobals(): considering  global " << i->getName() << "\n";
      MemoryObject *mo = memory->allocate(size, false, true, &*i);
      if (!mo)
        llvm::report_fatal_error("out of memory");
      //llvm::outs() << "ForwardExecutor::initializeGlobals(): allocated memory for global " << i->getName() <<
      //                " and size = " << size << " at address " << mo->address << "\n";
      ObjectState *os = bindObjectInState(state, mo, false);
      globalObjects.insert(std::make_pair(i, mo));
      globalAddresses.insert(std::make_pair(i, mo->getBaseExpr()));

      if (!i->hasInitializer())
          os->initializeToRandom();
    }
  }
  
  // link aliases to their definitions (if bound)
  for (Module::alias_iterator i = m->alias_begin(), ie = m->alias_end(); 
       i != ie; ++i) {
    // Map the alias to its aliasee's address. This works because we have
    // addresses for everything, even undefined functions. 
    globalAddresses.insert(std::make_pair(i, evalConstant(i->getAliasee())));
  }

  // once all objects are allocated, do the actual initialization
  for (Module::const_global_iterator i = m->global_begin(),
         e = m->global_end();
       i != e; ++i) {
    if (i->hasInitializer()) {
      MemoryObject *mo = globalObjects.find(i)->second;
      const ObjectState *os = state.addressSpace.findObject(mo);
      assert(os);
      ObjectState *wos = state.addressSpace.getWriteable(mo, os);
      
      initializeGlobalObject(state, wos, i->getInitializer(), 0);
      // if(i->isConstant()) os->setReadOnly(true);
    }
  }
}


void ForwardExecutor::branch(ExecutionState &state, 
                      const std::vector< ref<Expr> > &conditions,
                      std::vector<ExecutionState*> &result) {
  TimerStatIncrementer timer(stats::forkTime);
  unsigned N = conditions.size();
  assert(N);

  if (MaxForks!=~0u && stats::forks >= MaxForks) {
    unsigned next = theRNG.getInt32() % N;
    for (unsigned i=0; i<N; ++i) {
      if (i == next) {
        result.push_back(&state);
      } else {
        result.push_back(NULL);
      }
    }
  } else {
    stats::forks += N-1;

    // XXX do proper balance or keep random?
    result.push_back(&state);
    for (unsigned i=1; i<N; ++i) {
      ExecutionState *es = result[theRNG.getInt32() % i];
      ExecutionState *ns = es->branch();
      addedStates.insert(ns);
      result.push_back(ns);
      es->ptreeNode->data = 0;
      std::pair<PTree::Node*,PTree::Node*> res = 
        processTree->split(es->ptreeNode, ns, es);
      ns->ptreeNode = res.first;
      es->ptreeNode = res.second;
    }
  }

  // If necessary redistribute seeds to match conditions, killing
  // states if necessary due to OnlyReplaySeeds (inefficient but
  // simple).
  
  std::map< ExecutionState*, std::vector<SeedInfo> >::iterator it = 
    seedMap.find(&state);
  if (it != seedMap.end()) {
    std::vector<SeedInfo> seeds = it->second;
    seedMap.erase(it);

    // Assume each seed only satisfies one condition (necessarily true
    // when conditions are mutually exclusive and their conjunction is
    // a tautology).
    for (std::vector<SeedInfo>::iterator siit = seeds.begin(), 
           siie = seeds.end(); siit != siie; ++siit) {
      unsigned i;
      for (i=0; i<N; ++i) {
        ref<ConstantExpr> res;
        bool success = 
          solver->getValue(state, siit->assignment.evaluate(conditions[i]), 
                           res);
        assert(success && "FIXME: Unhandled solver failure");
        (void) success;
        if (res->isTrue())
          break;
      }
      
      // If we didn't find a satisfying condition randomly pick one
      // (the seed will be patched).
      if (i==N)
        i = theRNG.getInt32() % N;

      // Extra check in case we're replaying seeds with a max-fork
      if (result[i])
        seedMap[result[i]].push_back(*siit);
    }

    if (OnlyReplaySeeds) {
      for (unsigned i=0; i<N; ++i) {
        if (result[i] && !seedMap.count(result[i])) {
          terminateState(*result[i]);
          result[i] = NULL;
        }
      } 
    }
  }

  for (unsigned i=0; i<N; ++i)
    if (result[i])
      addConstraint(*result[i], conditions[i]);
}

ForwardExecutor::StatePair 
ForwardExecutor::fork(ExecutionState &current, ref<Expr> condition, bool isInternal) {
  Solver::Validity res;
  std::map< ExecutionState*, std::vector<SeedInfo> >::iterator it = 
    seedMap.find(&current);
  bool isSeeding = it != seedMap.end();

//#if 0
  if (!isSeeding && !isa<ConstantExpr>(condition) && 
      (MaxStaticForkPct!=1. || MaxStaticSolvePct != 1. ||
       MaxStaticCPForkPct!=1. || MaxStaticCPSolvePct != 1.) &&
      statsTracker->elapsed() > 60.) {
    StatisticManager &sm = *theStatisticManager;
    CallPathNode *cpn = current.stack.back().callPathNode;
    if ((MaxStaticForkPct<1. &&
         sm.getIndexedValue(stats::forks, sm.getIndex()) > 
         stats::forks*MaxStaticForkPct) ||
        (MaxStaticCPForkPct<1. &&
         cpn && (cpn->statistics.getValue(stats::forks) > 
                 stats::forks*MaxStaticCPForkPct)) ||
        (MaxStaticSolvePct<1 &&
         sm.getIndexedValue(stats::solverTime, sm.getIndex()) > 
         stats::solverTime*MaxStaticSolvePct) ||
        (MaxStaticCPForkPct<1. &&
         cpn && (cpn->statistics.getValue(stats::solverTime) > 
                 stats::solverTime*MaxStaticCPSolvePct))) {
      ref<ConstantExpr> value; 
      outs() << "ForwardExecutor::fork(): Going to execute solver->getValue() at line " << __LINE__ << "\n";
      bool success = solver->getValue(current, condition, value);
      assert(success && "FIXME: Unhandled solver failure");
      (void) success;
      addConstraint(current, EqExpr::create(value, condition));
      condition = value;
    } else
        outs() << "ForwardExecutor::fork(): Not going to execute solver->getValue() at line " << 728 << "\n";
  } else
      outs() << "ForwardExecutor::fork(): Not going to execute solver->getValue() at line " << 728 << "\n";
//#endif

  double timeout = coreSolverTimeout;
  if (isSeeding)
    timeout *= it->second.size();
  solver->setTimeout(timeout);
  bool success = solver->evaluate(current, condition, res);
  solver->setTimeout(0);
  if (!success) {
    current.pc = current.prevPC;
    terminateStateEarly(current, "Query timed out (fork).");
    return StatePair(0, 0);
  }

  llvm::outs() << "ForwardExecutor::fork(): isSeeding = " << isSeeding << "\n";
  if (!isSeeding) {
    if (replayPath && !isInternal) {
      llvm::outs() << "ForwardExecutor::fork(): replaying, wtf?! replayPath = " << replayPath << "\n";
      assert(replayPosition<replayPath->size() &&
             "ran out of branches in replay path mode");
      bool branch = (*replayPath)[replayPosition++];
      
      if (res==Solver::True) {
        assert(branch && "hit invalid branch in replay path mode");
      } else if (res==Solver::False) {
        assert(!branch && "hit invalid branch in replay path mode");
      } else {
        // add constraints
        if(branch) {
          res = Solver::True;
          addConstraint(current, condition);
        } else  {
          res = Solver::False;
          addConstraint(current, Expr::createIsZero(condition));
        }
      }
    } else if (res==Solver::Unknown) {
      assert(!replayOut && "in replay mode, only one branch can be true.");
      
      if ((MaxMemoryInhibit && atMemoryLimit) || 
          current.forkDisabled ||
          inhibitForking || 
          (MaxForks!=~0u && stats::forks >= MaxForks)) {

	if (MaxMemoryInhibit && atMemoryLimit)
	  klee_warning_once(0, "skipping fork (memory cap exceeded)");
	else if (current.forkDisabled)
	  klee_warning_once(0, "skipping fork (fork disabled on current path)");
	else if (inhibitForking)
	  klee_warning_once(0, "skipping fork (fork disabled globally)");
	else 
	  klee_warning_once(0, "skipping fork (max-forks reached)");

        TimerStatIncrementer timer(stats::forkTime);
        if (theRNG.getBool()) {
          addConstraint(current, condition);
          res = Solver::True;        
        } else {
          addConstraint(current, Expr::createIsZero(condition));
          res = Solver::False;
        }
      }
    }
  }

  // Fix branch in only-replay-seed mode, if we don't have both true
  // and false seeds.
  if (isSeeding && 
      (current.forkDisabled || OnlyReplaySeeds) && 
      res == Solver::Unknown) {
    bool trueSeed=false, falseSeed=false;
    // Is seed extension still ok here?
    for (std::vector<SeedInfo>::iterator siit = it->second.begin(), 
           siie = it->second.end(); siit != siie; ++siit) {
      ref<ConstantExpr> res;
      bool success = 
        solver->getValue(current, siit->assignment.evaluate(condition), res);
      assert(success && "FIXME: Unhandled solver failure");
      (void) success;
      if (res->isTrue()) {
        trueSeed = true;
      } else {
        falseSeed = true;
      }
      if (trueSeed && falseSeed)
        break;
    }
    if (!(trueSeed && falseSeed)) {
      assert(trueSeed || falseSeed);
      
      res = trueSeed ? Solver::True : Solver::False;
      addConstraint(current, trueSeed ? condition : Expr::createIsZero(condition));
    }
  }


  // XXX - even if the constraint is provable one way or the other we
  // can probably benefit by adding this constraint and allowing it to
  // reduce the other constraints. For example, if we do a binary
  // search on a particular value, and then see a comparison against
  // the value it has been fixed at, we should take this as a nice
  // hint to just use the single constraint instead of all the binary
  // search ones. If that makes sense.
    ///IVAN ADDITIONS BEGIN
                  KInstruction *ki = current.prevPC;
                  Instruction *instr = ki->inst;
                  std::string instr_str;
                  raw_string_ostream str_stream(instr_str);                                 
                  str_stream << *instr;
    ///IVAN ADDITIONS END

  if (res==Solver::True) {
    if (!isInternal) {
      if (pathWriter) {
        current.pathOS << "1";
      }
    }

    current.path_choices.push_back(1);
                  //current.path_choices_debug.push_back(instr_str);
    return StatePair(&current, 0);
  } else if (res==Solver::False) {
    if (!isInternal) {
      if (pathWriter) {
        current.pathOS << "0";
      }
    }

    current.path_choices.push_back(0);
                  //current.path_choices_debug.push_back(instr_str);
    return StatePair(0, &current);
  } else {
    TimerStatIncrementer timer(stats::forkTime);
    ExecutionState *falseState, *trueState = &current;

    ++stats::forks;

    falseState = trueState->branch();
    addedStates.insert(falseState);

    if (RandomizeFork && theRNG.getBool())
      std::swap(trueState, falseState);

    if (it != seedMap.end()) {
      std::vector<SeedInfo> seeds = it->second;
      it->second.clear();
      std::vector<SeedInfo> &trueSeeds = seedMap[trueState];
      std::vector<SeedInfo> &falseSeeds = seedMap[falseState];
      for (std::vector<SeedInfo>::iterator siit = seeds.begin(), 
             siie = seeds.end(); siit != siie; ++siit) {
        ref<ConstantExpr> res;
        bool success = 
          solver->getValue(current, siit->assignment.evaluate(condition), res);
        assert(success && "FIXME: Unhandled solver failure");
        (void) success;
        if (res->isTrue()) {
          trueSeeds.push_back(*siit);
        } else {
          falseSeeds.push_back(*siit);
        }
      }
      
      bool swapInfo = false;
      if (trueSeeds.empty()) {
        if (&current == trueState) swapInfo = true;
        seedMap.erase(trueState);
      }
      if (falseSeeds.empty()) {
        if (&current == falseState) swapInfo = true;
        seedMap.erase(falseState);
      }
      if (swapInfo) {
        std::swap(trueState->coveredNew, falseState->coveredNew);
        std::swap(trueState->coveredLines, falseState->coveredLines);
      }
    }

    current.ptreeNode->data = 0;
    std::pair<PTree::Node*, PTree::Node*> res =
      processTree->split(current.ptreeNode, falseState, trueState);
    falseState->ptreeNode = res.first;
    trueState->ptreeNode = res.second;

    if (!isInternal) {
      if (pathWriter) {
        falseState->pathOS = pathWriter->open(current.pathOS);
        trueState->pathOS << "1";
        falseState->pathOS << "0";
      }      
      if (symPathWriter) {
        falseState->symPathOS = symPathWriter->open(current.symPathOS);
        trueState->symPathOS << "1";
        falseState->symPathOS << "0";
      }
    }

    ///IVAN ADDITIONS BEGIN
    trueState->path_choices.push_back(1);
    falseState->path_choices.push_back(0);
                  //trueState->path_choices_debug.push_back(instr_str);
                  //falseState->path_choices_debug.push_back(instr_str);
    ///IVAN ADDITIONS END
    
    addConstraint(*trueState, condition);
    addConstraint(*falseState, Expr::createIsZero(condition));

    // Kinda gross, do we even really still want this option?
    if (MaxDepth && MaxDepth<=trueState->depth) {
      terminateStateEarly(*trueState, "max-depth exceeded.");
      terminateStateEarly(*falseState, "max-depth exceeded.");
      return StatePair(0, 0);
    }

    return StatePair(trueState, falseState);
  }
}

void ForwardExecutor::addConstraint(ExecutionState &state, ref<Expr> condition) {
  if (ConstantExpr *CE = dyn_cast<ConstantExpr>(condition)) {
    if (!CE->isTrue())
      llvm::report_fatal_error("attempt to add invalid constraint");
    return;
  }

  // Check to see if this constraint violates seeds.
  std::map< ExecutionState*, std::vector<SeedInfo> >::iterator it = 
    seedMap.find(&state);
  if (it != seedMap.end()) {
    bool warn = false;
    for (std::vector<SeedInfo>::iterator siit = it->second.begin(), 
           siie = it->second.end(); siit != siie; ++siit) {
      bool res;
      bool success = 
        solver->mustBeFalse(state, siit->assignment.evaluate(condition), res);
      assert(success && "FIXME: Unhandled solver failure");
      (void) success;
      if (res) {
        siit->patchSeed(state, condition, solver);
        warn = true;
      }
    }
    if (warn)
      klee_warning("seeds patched for violating constraint"); 
  }

  state.addConstraint(condition);
  /// IVAN ADDITIONS BEGIN
  StackFrame &sf = state.stack.back();
  sf.num_of_constraints++;
  /// IVAN ADDITIONS END
#if 0 /* IVAN: not used anyways (always false */
  if (ivcEnabled)
    doImpliedValueConcretization(state, condition, 
                                 ConstantExpr::alloc(1, Expr::Bool));
#endif
}

ref<klee::ConstantExpr> ForwardExecutor::evalConstant(const Constant *c) {
  if (const llvm::ConstantExpr *ce = dyn_cast<llvm::ConstantExpr>(c)) {
    return evalConstantExpr(ce);
  } else {
    if (const ConstantInt *ci = dyn_cast<ConstantInt>(c)) {
      return ConstantExpr::alloc(ci->getValue());
    } else if (const ConstantFP *cf = dyn_cast<ConstantFP>(c)) {      
      return ConstantExpr::alloc(cf->getValueAPF().bitcastToAPInt());
    } else if (const GlobalValue *gv = dyn_cast<GlobalValue>(c)) {
      return globalAddresses.find(gv)->second;
    } else if (isa<ConstantPointerNull>(c)) {
      return Expr::createPointer(0);
    } else if (isa<UndefValue>(c) || isa<ConstantAggregateZero>(c)) {
      return ConstantExpr::create(0, getWidthForLLVMType(c->getType()));
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 1)
    } else if (const ConstantDataSequential *cds =
                 dyn_cast<ConstantDataSequential>(c)) {
      std::vector<ref<Expr> > kids;
      for (unsigned i = 0, e = cds->getNumElements(); i != e; ++i) {
        ref<Expr> kid = evalConstant(cds->getElementAsConstant(i));
        kids.push_back(kid);
      }
      ref<Expr> res = ConcatExpr::createN(kids.size(), kids.data());
      return cast<ConstantExpr>(res);
#endif
    } else if (const ConstantStruct *cs = dyn_cast<ConstantStruct>(c)) {
      const StructLayout *sl = kmodule->targetData->getStructLayout(cs->getType());
      llvm::SmallVector<ref<Expr>, 4> kids;
      for (unsigned i = cs->getNumOperands(); i != 0; --i) {
        unsigned op = i-1;
        ref<Expr> kid = evalConstant(cs->getOperand(op));

        uint64_t thisOffset = sl->getElementOffsetInBits(op),
                 nextOffset = (op == cs->getNumOperands() - 1)
                              ? sl->getSizeInBits()
                              : sl->getElementOffsetInBits(op+1);
        if (nextOffset-thisOffset > kid->getWidth()) {
          uint64_t paddingWidth = nextOffset-thisOffset-kid->getWidth();
          kids.push_back(ConstantExpr::create(0, paddingWidth));
        }

        kids.push_back(kid);
      }
      ref<Expr> res = ConcatExpr::createN(kids.size(), kids.data());
      return cast<ConstantExpr>(res);
    } else if (const ConstantArray *ca = dyn_cast<ConstantArray>(c)){
      llvm::SmallVector<ref<Expr>, 4> kids;
      for (unsigned i = ca->getNumOperands(); i != 0; --i) {
        unsigned op = i-1;
        ref<Expr> kid = evalConstant(ca->getOperand(op));
        kids.push_back(kid);
      }
      ref<Expr> res = ConcatExpr::createN(kids.size(), kids.data());
      return cast<ConstantExpr>(res);
    } else {
      // Constant{Vector}
      llvm::report_fatal_error("invalid argument to evalConstant()");
    }
  }
}

const Cell& ForwardExecutor::eval(KInstruction *ki, unsigned index, 
                           ExecutionState &state) const {
  assert(index < ki->inst->getNumOperands());
  int vnumber = ki->operands[index];

  assert(vnumber != -1 &&
         "Invalid operand to eval(), not a value or constant!");

  // Determine if this is a constant or not.
  if (vnumber < 0) {
    unsigned index = -vnumber - 2;
    return kmodule->constantTable[index];
  } else {
    unsigned index = vnumber;
    StackFrame &sf = state.stack.back();
    //llvm::outs() << "ForwardExecutor::eval() : returning from sf.locals\n";
    return sf.locals[index];
  }
}

void ForwardExecutor::bindLocal(KInstruction *target, ExecutionState &state, 
                         ref<Expr> value) {
  getDestCell(state, target).value = value;
}

void ForwardExecutor::bindArgument(KFunction *kf, unsigned index, 
                            ExecutionState &state, ref<Expr> value) {
  getArgumentCell(state, kf, index).value = value;
}

ref<Expr> ForwardExecutor::toUnique(const ExecutionState &state, 
                             ref<Expr> &e) {
  ref<Expr> result = e;

  if (!isa<ConstantExpr>(e)) {
    ref<ConstantExpr> value;
    bool isTrue = false;

    solver->setTimeout(coreSolverTimeout);      
    if (solver->getValue(state, e, value) &&
        solver->mustBeTrue(state, EqExpr::create(e, value), isTrue) &&
        isTrue)
      result = value;
    solver->setTimeout(0);
  }
  
  return result;
}


/* Concretize the given expression, and return a possible constant value. 
   'reason' is just a documentation string stating the reason for concretization. */
ref<klee::ConstantExpr> 
ForwardExecutor::toConstant(ExecutionState &state, 
                     ref<Expr> e,
                     const char *reason) {
  e = state.constraints.simplifyExpr(e);
  if (ConstantExpr *CE = dyn_cast<ConstantExpr>(e))
    return CE;

  ref<ConstantExpr> value;
  bool success = solver->getValue(state, e, value);
  assert(success && "FIXME: Unhandled solver failure");
  (void) success;

  std::string str;
  llvm::raw_string_ostream os(str);
  os << "silently concretizing (reason: " << reason << ") expression " << e
     << " to value " << value << " (" << (*(state.pc)).info->file << ":"
     << (*(state.pc)).info->line << ")";

  if (AllExternalWarnings)
    klee_warning(reason, os.str().c_str());
  else
    klee_warning_once(reason, "%s", os.str().c_str());

  addConstraint(state, EqExpr::create(e, value));
    
  return value;
}

void ForwardExecutor::executeGetValue(ExecutionState &state,
                               ref<Expr> e,
                               KInstruction *target) {
  e = state.constraints.simplifyExpr(e);
  std::map< ExecutionState*, std::vector<SeedInfo> >::iterator it = 
    seedMap.find(&state);
  if (it==seedMap.end() || isa<ConstantExpr>(e)) {
    ref<ConstantExpr> value;
    bool success = solver->getValue(state, e, value);
    assert(success && "FIXME: Unhandled solver failure");
    (void) success;
    bindLocal(target, state, value);
  } else {
    std::set< ref<Expr> > values;
    for (std::vector<SeedInfo>::iterator siit = it->second.begin(), 
           siie = it->second.end(); siit != siie; ++siit) {
      ref<ConstantExpr> value;
      bool success = 
        solver->getValue(state, siit->assignment.evaluate(e), value);
      assert(success && "FIXME: Unhandled solver failure");
      (void) success;
      values.insert(value);
    }
    
    std::vector< ref<Expr> > conditions;
    for (std::set< ref<Expr> >::iterator vit = values.begin(), 
           vie = values.end(); vit != vie; ++vit)
      conditions.push_back(EqExpr::create(e, *vit));

    std::vector<ExecutionState*> branches;
    branch(state, conditions, branches);
    
    std::vector<ExecutionState*>::iterator bit = branches.begin();
    for (std::set< ref<Expr> >::iterator vit = values.begin(), 
           vie = values.end(); vit != vie; ++vit) {
      ExecutionState *es = *bit;
      if (es)
        bindLocal(target, *es, *vit);
      ++bit;
    }
  }
}

void ForwardExecutor::stepInstruction(ExecutionState &state) {
  if (DebugPrintInstructions) {
    printFileLine(state, state.pc);
    llvm::errs().indent(10) << stats::instructions << " ";
    llvm::errs() << *(state.pc->inst) << '\n';
  }

  if (statsTracker)
    statsTracker->stepInstruction(state);

  ++stats::instructions;
  state.prevPC = state.pc;
  ++state.pc;

  if (stats::instructions==StopAfterNInstructions)
    haltExecution = true;
}

void ForwardExecutor::executeCall(ExecutionState &state, 
                           KInstruction *ki,
                           Function *f,
                           std::vector< ref<Expr> > &arguments) {
  Instruction *i = ki->inst;
  if (f && f->isDeclaration()) {
    //llvm::outs() << "DEBUG: function call to declaration\n";
    switch(f->getIntrinsicID()) {
    case Intrinsic::not_intrinsic:
      //llvm::outs() << "DEBUG: function is not intrinsic\n";
      // state may be destroyed by this call, cannot touch
      callExternalFunction(state, ki, f, arguments);
      break;
        
      // va_arg is handled by caller and intrinsic lowering, see comment for
      // ExecutionState::varargs
    case Intrinsic::vastart:  {
      StackFrame &sf = state.stack.back();
      assert(sf.varargs && 
             "vastart called in function with no vararg object");

      // FIXME: This is really specific to the architecture, not the pointer
      // size. This happens to work fir x86-32 and x86-64, however.
      Expr::Width WordSize = Context::get().getPointerWidth();
      if (WordSize == Expr::Int32) {
        executeMemoryOperation(state, true, arguments[0], 
                               sf.varargs->getBaseExpr(), 0);
      } else {
        assert(WordSize == Expr::Int64 && "Unknown word size!");

        // X86-64 has quite complicated calling convention. However,
        // instead of implementing it, we can do a simple hack: just
        // make a function believe that all varargs are on stack.
        executeMemoryOperation(state, true, arguments[0],
                               ConstantExpr::create(48, 32), 0); // gp_offset
        executeMemoryOperation(state, true,
                               AddExpr::create(arguments[0], 
                                               ConstantExpr::create(4, 64)),
                               ConstantExpr::create(304, 32), 0); // fp_offset
        executeMemoryOperation(state, true,
                               AddExpr::create(arguments[0], 
                                               ConstantExpr::create(8, 64)),
                               sf.varargs->getBaseExpr(), 0); // overflow_arg_area
        executeMemoryOperation(state, true,
                               AddExpr::create(arguments[0], 
                                               ConstantExpr::create(16, 64)),
                               ConstantExpr::create(0, 64), 0); // reg_save_area
      }
      break;
    }
    case Intrinsic::vaend:
      // va_end is a noop for the interpreter.
      //
      // FIXME: We should validate that the target didn't do something bad
      // with vaeend, however (like call it twice).
      break;
        
    case Intrinsic::vacopy:
      // va_copy should have been lowered.
      //
      // FIXME: It would be nice to check for errors in the usage of this as
      // well.
    default:
      klee_error("unknown intrinsic: %s", f->getName().data());
    }

    if (InvokeInst *ii = dyn_cast<InvokeInst>(i))
      transferToBasicBlock(ii->getNormalDest(), i->getParent(), state);
  } else {
    // FIXME: I'm not really happy about this reliance on prevPC but it is ok, I
    // guess. This just done to avoid having to pass KInstIterator everywhere
    // instead of the actual instruction, since we can't make a KInstIterator
    // from just an instruction (unlike LLVM).
    KFunction *kf = kmodule->functionMap[f];
    state.pushFrame(state.prevPC, kf);
    /// IVAN ADDITIONS BEGIN
    state.stack.back().cur_fsummary = state.cur_fsummary; // this will set the summary of the function which we are going to invoke
    /// IVAN ADDITIONS END
    state.pc = kf->instructions;
        
    if (statsTracker)
      statsTracker->framePushed(state, &state.stack[state.stack.size()-2]);
 
     // TODO: support "byval" parameter attribute
     // TODO: support zeroext, signext, sret attributes
        
    unsigned callingArgs = arguments.size();
    unsigned funcArgs = f->arg_size();
    if (!f->isVarArg()) {
      if (callingArgs > funcArgs) {
        klee_warning_once(f, "calling %s with extra arguments.", 
                          f->getName().data());
      } else if (callingArgs < funcArgs) {
        terminateStateOnError(state, "calling function with too few arguments", 
                              "user.err");
        return;
      }
    } else {
      Expr::Width WordSize = Context::get().getPointerWidth();

      if (callingArgs < funcArgs) {
        terminateStateOnError(state, "calling function with too few arguments", 
                              "user.err");
        return;
      }
            
      StackFrame &sf = state.stack.back();
      unsigned size = 0;
      for (unsigned i = funcArgs; i < callingArgs; i++) {
        // FIXME: This is really specific to the architecture, not the pointer
        // size. This happens to work fir x86-32 and x86-64, however.
        if (WordSize == Expr::Int32) {
          size += Expr::getMinBytesForWidth(arguments[i]->getWidth());
        } else {
          Expr::Width argWidth = arguments[i]->getWidth();
          // AMD64-ABI 3.5.7p5: Step 7. Align l->overflow_arg_area upwards to a 16
          // byte boundary if alignment needed by type exceeds 8 byte boundary.
          //
          // Alignment requirements for scalar types is the same as their size
          if (argWidth > Expr::Int64) {
             size = llvm::RoundUpToAlignment(size, 16);
          }
          size += llvm::RoundUpToAlignment(argWidth, WordSize) / 8;
        }
      }

      MemoryObject *mo = sf.varargs = memory->allocate(size, true, false, 
                                                       state.prevPC->inst);
      if (!mo) {
        terminateStateOnExecError(state, "out of memory (varargs)");
        return;
      }

      if ((WordSize == Expr::Int64) && (mo->guest_address & 15)) {
        // Both 64bit Linux/Glibc and 64bit MacOSX should align to 16 bytes.
        klee_warning_once(0, "While allocating varargs: malloc did not align to 16 bytes.");
      }

      ObjectState *os = bindObjectInState(state, mo, true);
      unsigned offset = 0;
      for (unsigned i = funcArgs; i < callingArgs; i++) {
        // FIXME: This is really specific to the architecture, not the pointer
        // size. This happens to work fir x86-32 and x86-64, however.
        if (WordSize == Expr::Int32) {
          os->write(offset, arguments[i]);
          offset += Expr::getMinBytesForWidth(arguments[i]->getWidth());
        } else {
          assert(WordSize == Expr::Int64 && "Unknown word size!");

          Expr::Width argWidth = arguments[i]->getWidth();
          if (argWidth > Expr::Int64) {
             offset = llvm::RoundUpToAlignment(offset, 16);
          }
          os->write(offset, arguments[i]);
          offset += llvm::RoundUpToAlignment(argWidth, WordSize) / 8;
        }
      }
    }

    unsigned numFormals = f->arg_size();
    for (unsigned i=0; i<numFormals; ++i) 
      bindArgument(kf, i, state, arguments[i]);
  }
}

void ForwardExecutor::transferToBasicBlock(BasicBlock *dst, BasicBlock *src, 
                                    ExecutionState &state) {
  // Note that in general phi nodes can reuse phi values from the same
  // block but the incoming value is the eval() result *before* the
  // execution of any phi nodes. this is pathological and doesn't
  // really seem to occur, but just in case we run the PhiCleanerPass
  // which makes sure this cannot happen and so it is safe to just
  // eval things in order. The PhiCleanerPass also makes sure that all
  // incoming blocks have the same order for each PHINode so we only
  // have to compute the index once.
  //
  // With that done we simply set an index in the state so that PHI
  // instructions know which argument to eval, set the pc, and continue.
  
  // XXX this lookup has to go ?
  KFunction *kf = state.stack.back().kf;
  unsigned entry = kf->basicBlockEntry[dst];
  state.pc = &kf->instructions[entry];
  if (state.pc->inst->getOpcode() == Instruction::PHI) {
    PHINode *first = static_cast<PHINode*>(state.pc->inst);
    state.incomingBBIndex = first->getBasicBlockIndex(src);
  }
}

void ForwardExecutor::printFileLine(ExecutionState &state, KInstruction *ki) {
  const InstructionInfo &ii = *ki->info;
  if (ii.file != "")
    llvm::errs() << "     " << ii.file << ":" << ii.line << ":";
  else
    llvm::errs() << "     [no debug info]:";
}

/// Compute the true target of a function call, resolving LLVM and KLEE aliases
/// and bitcasts.
Function* ForwardExecutor::getTargetFunction(Value *calledVal, ExecutionState &state) {
  SmallPtrSet<const GlobalValue*, 3> Visited;

  Constant *c = dyn_cast<Constant>(calledVal);
  if (!c)
    return 0;

  while (true) {
    if (GlobalValue *gv = dyn_cast<GlobalValue>(c)) {
      if (!Visited.insert(gv))
        return 0;

      std::string alias = state.getFnAlias(gv->getName());
      if (alias != "") {
        llvm::Module* currModule = kmodule->module;
        GlobalValue *old_gv = gv;
        gv = currModule->getNamedValue(alias);
        if (!gv) {
          llvm::errs() << "Function " << alias << "(), alias for " 
                       << old_gv->getName() << " not found!\n";
          assert(0 && "function alias not found");
        }
      }
     
      if (Function *f = dyn_cast<Function>(gv))
        return f;
      else if (GlobalAlias *ga = dyn_cast<GlobalAlias>(gv))
        c = ga->getAliasee();
      else
        return 0;
    } else if (llvm::ConstantExpr *ce = dyn_cast<llvm::ConstantExpr>(c)) {
      if (ce->getOpcode()==Instruction::BitCast)
        c = ce->getOperand(0);
      else
        return 0;
    } else
      return 0;
  }
}

/// TODO remove?
static bool isDebugIntrinsic(const Function *f, KModule *KM) {
  return false;
}

static inline const llvm::fltSemantics * fpWidthToSemantics(unsigned width) {
  switch(width) {
  case Expr::Int32:
    return &llvm::APFloat::IEEEsingle;
  case Expr::Int64:
    return &llvm::APFloat::IEEEdouble;
  case Expr::Fl80:
    return &llvm::APFloat::x87DoubleExtended;
  default:
    return 0;
  }
}


/* The current stack frame keeps the seq_number of the call symbolics */
/* The call symbolics are in the
 * current_state->cur_path_summary->call_symbolic_replacements */
InnerCall* ForwardExecutor::get_InnerCall_by_seqnum(path_summary_ty *smmry, unsigned seqnum)
{
  InnerCall *res = NULL;
  for(call_symbolic_replacements_ty::iterator it  = smmry->call_symbolic_replacements.begin();
                                              it != smmry->call_symbolic_replacements.end();
                                              ++it)
  {
    InnerCall *inner_call = it->second;
    llvm::outs() << "ForwardExecutor::get_InnerCall_by_seqnum(): Considering suppl call" << *(inner_call->call_inst) <<
                      " with seq num =  " << inner_call->seq_num << "\n";
    if(seqnum == inner_call->seq_num)
      return inner_call;
  }
  return NULL;
}



/* Copy <original> and adapt its inner calls according to <next_smmry>
 * Return the copy */
path_summary_ty* ForwardExecutor::duplicate_and_adapt_psummary(path_summary_ty *original, path_summary_ty *next_smmry)
{
    path_summary_ty *copy = new PathSummary(original);
    copy->clear_connected_summaries_for_inner_calls();
    
    if(next_smmry)
      copy->update_InnerCalls_with_constraints2(*next_smmry);

    int res = interpreter_manager->run_inner_calls(*copy); /* It will not recollect path summaries, but will re-use existing ones */
    assert(res && "no inner calls for already glued path summary: it's a b-b-b-b-u-u-u-u-ggggg!");
    return copy;
}


void ForwardExecutor::executeInstruction(ExecutionState &state, KInstruction *ki) {
  Instruction *i = ki->inst;
  switch (i->getOpcode()) {
    // Control flow
  case Instruction::Ret: {
    ReturnInst *ri = cast<ReturnInst>(i);
    KInstIterator kcaller = state.stack.back().caller;
    Instruction *caller = kcaller ? kcaller->inst : 0;
    bool isVoidReturn = (ri->getNumOperands() == 0);
    ref<Expr> result = ConstantExpr::alloc(0, Expr::Bool);

    /* We are going one level up =>  remove the last *callInst from call
     * history */
    if(state.callHistory.size() != 0)
      state.callHistory.pop_back();
    /* *** */
    
    
    /* Check if we are returning from an ISR */
    bool interruptExit = false;
    if (state.interruptFun && (ki->inst->getParent()->getParent() == state.interruptFun))
    {
      interruptExit = true;
      state.interruptFun = NULL;
    }
    /* *** */
    
    if (!isVoidReturn) {
      result = eval(ki, 0, state).value;
      outs() << "ForwardExecutor::executeInstruction()::Ret: return vlaue = " << result << "\n";
    }

    /* It is top-level function: we have just one stack frame */
    if (state.stack.size() <= 1) {
      assert(!caller && "caller set on initial stack frame");
      terminateStateOnExit(state);
    } else {
      StackFrame &sf = state.stack.back();
	    KInstIterator restorePC = sf.restorePC;
      if (interruptExit)
      {
        //Restore BBIncomingIndex
	state.incomingBBIndex = state.stack.back().incomingBBIndex;
        state.interrupt_depth--;
      }
			
      state.popFrame();

      if (statsTracker)
        statsTracker->framePopped(state);

      if (InvokeInst *ii = dyn_cast<InvokeInst>(caller)) {
        transferToBasicBlock(ii->getNormalDest(), caller->getParent(), state);
      } else {
        /* If we return from an interrupt we need to use <restorePC>,
         * see the description of ExecutionState::pushFrame() for explanation */
        if (restorePC && interruptExit)
          state.pc = restorePC;
        else
        {
          state.pc = kcaller;
          ++state.pc;
        }
      }

      if (!isVoidReturn) {
        LLVM_TYPE_Q Type *t = caller->getType();
        if (t != Type::getVoidTy(getGlobalContext())) {
          // may need to do coercion due to bitcasts
          Expr::Width from = result->getWidth();
          Expr::Width to = getWidthForLLVMType(t);
            
          if (from != to) {
            CallSite cs = (isa<InvokeInst>(caller) ? CallSite(cast<InvokeInst>(caller)) : 
                           CallSite(cast<CallInst>(caller)));

            // XXX need to check other param attrs ?
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
      bool isSExt = cs.paramHasAttr(0, llvm::Attribute::SExt);
#elif LLVM_VERSION_CODE >= LLVM_VERSION(3, 2)
	    bool isSExt = cs.paramHasAttr(0, llvm::Attributes::SExt);
#else
	    bool isSExt = cs.paramHasAttr(0, llvm::Attribute::SExt);
#endif
            if (isSExt) {
              result = SExtExpr::create(result, to);
            } else {
              result = ZExtExpr::create(result, to);
            }
          }

          bindLocal(kcaller, state, result);
        }
      } else {
        // We check that the return value has no users instead of
        // checking the type, since C defaults to returning int for
        // undeclared functions.
	// ivan: the "caller" may indeed have uses completely unrelated to the 
	// "call", so we check on interrupts
        if (!interruptExit && !caller->use_empty()) {
          terminateStateOnExecError(state, "return void when caller expected a result");
        }
      }
    }      


    break;
  }
#if LLVM_VERSION_CODE < LLVM_VERSION(3, 1)
  case Instruction::Unwind: {
    for (;;) {
      KInstruction *kcaller = state.stack.back().caller;
      state.popFrame();

      if (statsTracker)
        statsTracker->framePopped(state);

      if (state.stack.empty()) {
        terminateStateOnExecError(state, "unwind from initial stack frame");
        break;
      } else {
        Instruction *caller = kcaller->inst;
        if (InvokeInst *ii = dyn_cast<InvokeInst>(caller)) {
          transferToBasicBlock(ii->getUnwindDest(), caller->getParent(), state);
          break;
        }
      }
    }
    break;
  }
#endif
  case Instruction::Br: {
    BranchInst *bi = cast<BranchInst>(i);
    if (bi->isUnconditional()) {
      transferToBasicBlock(bi->getSuccessor(0), bi->getParent(), state);
    } else {
      // FIXME: Find a way that we don't have this hidden dependency.
      assert(bi->getCondition() == bi->getOperand(0) &&
             "Wrong operand index!");
      ref<Expr> cond = eval(ki, 0, state).value;
      outs() << "ForwardExecutor::executeInstruction()::Br: cond = " << cond << "\n";
      ForwardExecutor::StatePair branches = fork(state, cond, false);
      outs() << "ForwardExecutor::executeInstruction()::Br: forked sucessfully\n";

      // NOTE: There is a hidden dependency here, markBranchVisited
      // requires that we still be in the context of the branch
      // instruction (it reuses its statistic id). Should be cleaned
      // up with convenient instruction specific data.
      if (statsTracker && state.stack.back().kf->trackCoverage)
        statsTracker->markBranchVisited(branches.first, branches.second);

      if (branches.first)
      {
        outs() << "ForwardExecutor::executeInstruction()::Br: branches.first is not NULL\n";
        transferToBasicBlock(bi->getSuccessor(0), bi->getParent(), *branches.first);
      }

      if (branches.second)
      {
        outs() << "ForwardExecutor::executeInstruction()::Br: branches.second is not NULL\n";
        transferToBasicBlock(bi->getSuccessor(1), bi->getParent(), *branches.second);
      }
    }
    break;
  }
  case Instruction::Switch: {
    SwitchInst *si = cast<SwitchInst>(i);
    ref<Expr> cond = eval(ki, 0, state).value;
    BasicBlock *bb = si->getParent();

    cond = toUnique(state, cond);
    if (ConstantExpr *CE = dyn_cast<ConstantExpr>(cond)) {
      // Somewhat gross to create these all the time, but fine till we
      // switch to an internal rep.
      LLVM_TYPE_Q llvm::IntegerType *Ty = 
        cast<IntegerType>(si->getCondition()->getType());
      ConstantInt *ci = ConstantInt::get(Ty, CE->getZExtValue());
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 1)
      unsigned index = si->findCaseValue(ci).getSuccessorIndex();
#else
      unsigned index = si->findCaseValue(ci);
#endif
      /// IVAN ADDITIONS START
      state.path_choices.push_back(index+2); // +2 is to differentiate from if-then-else conditions
      /// IVAN ADDITIONS END
      transferToBasicBlock(si->getSuccessor(index), si->getParent(), state);
    } else {
      std::map<BasicBlock*, ref<Expr> > targets;
      ref<Expr> isDefault = ConstantExpr::alloc(1, Expr::Bool);
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 1)      
      for (SwitchInst::CaseIt i = si->case_begin(), e = si->case_end();
           i != e; ++i) {
        ref<Expr> value = evalConstant(i.getCaseValue());
#else
      for (unsigned i=1, cases = si->getNumCases(); i<cases; ++i) {
        ref<Expr> value = evalConstant(si->getCaseValue(i));
#endif
        ref<Expr> match = EqExpr::create(cond, value);
        isDefault = AndExpr::create(isDefault, Expr::createIsZero(match));
        bool result;
        bool success = solver->mayBeTrue(state, match, result);
        assert(success && "FIXME: Unhandled solver failure");
        (void) success;
        if (result) {
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 1)
          BasicBlock *caseSuccessor = i.getCaseSuccessor();
#else
          BasicBlock *caseSuccessor = si->getSuccessor(i);
#endif
          std::map<BasicBlock*, ref<Expr> >::iterator it =
            targets.insert(std::make_pair(caseSuccessor,
                           ConstantExpr::alloc(0, Expr::Bool))).first;

          it->second = OrExpr::create(match, it->second);
        }
      }
      bool res;
      bool success = solver->mayBeTrue(state, isDefault, res);
      assert(success && "FIXME: Unhandled solver failure");
      (void) success;
      if (res)
        targets.insert(std::make_pair(si->getDefaultDest(), isDefault));
      
      std::vector< ref<Expr> > conditions;
      for (std::map<BasicBlock*, ref<Expr> >::iterator it = 
             targets.begin(), ie = targets.end();
           it != ie; ++it)
        conditions.push_back(it->second);
      
      std::vector<ExecutionState*> branches;
      branch(state, conditions, branches);
        
      std::vector<ExecutionState*>::iterator bit = branches.begin();
      /// IVAN ADDITIONS START
      int k = 0;
      /// IVAN ADDITIONS END
      for (std::map<BasicBlock*, ref<Expr> >::iterator it = 
             targets.begin(), ie = targets.end();
           it != ie; ++it) {
        ExecutionState *es = *bit;
        if (es)
        {
          /// IVAN ADDITIONS START
          es->path_choices.push_back(k); /* it's not really an index in switch expression; <k> rather depends on
                                            on the sorting order of <targets> which should be the same across the
                                            same run of klee */
          /// IVAN ADDITIONS END
          transferToBasicBlock(it->first, bb, *es);
        }
        ++bit;
        k++;
      }
    }
    break;
 }
  case Instruction::Unreachable:
    // Note that this is not necessarily an internal bug, llvm will
    // generate unreachable instructions in cases where it knows the
    // program will crash. So it is effectively a SEGV or internal
    // error.
    terminateStateOnExecError(state, "reached \"unreachable\" instruction");
    break;

  case Instruction::Invoke:
  case Instruction::Call: {
    CallSite cs(i);

    unsigned numArgs = cs.arg_size();
    Value *fp = cs.getCalledValue();
    Function *f = getTargetFunction(fp, state);


    // Skip debug intrinsics, we can't evaluate their metadata arguments.
    if (f && isDebugIntrinsic(f, kmodule))
      break;

    if (isa<InlineAsm>(fp)) {
      terminateStateOnExecError(state, "inline assembly is unsupported");
      break;
    }
    // evaluate arguments
    std::vector< ref<Expr> > arguments;
    arguments.reserve(numArgs);

    for (unsigned j=0; j<numArgs; ++j)
      arguments.push_back(eval(ki, j+1, state).value);

    if (f) 
    {
      if (f && !f->isDeclaration())
        state.callHistory.push_back((Instruction *)i); // add the *CallInst to the end of our call History

      /* When we were doing backward symbolic execution, and building the current path summary,
       * we replaced call instruction with new symbolics and saved them in the
       * <call_symbolic_replacements>. Then for each symbolics we later generated a good path
       * summary which satisfies conditiond on ret value.
       * Now we are do forward symbolic execution, and for each call, we need to use the right
       * path summary of the called function */

      if(state.cur_fsummary == NULL)
	      llvm::outs() << "ForwardExecutor::executeInstruction()::Call: cur_fsummry = NULL!\n";

      /* Found assert(), print constraints and exit KLEE */
      if(f->getName().str() == this->target_function_name) 
      {
        llvm::outs() << "BINGO! Here is are the constraints in KQUERY format:\n";
        print_state_constraints(&state);
        llvm::outs() << "And here is are the constraints in SMTLIB2 format:\n";
        std::string constraints;
        getConstraintLog(state, constraints, SMTLIB2);
        llvm::outs() << constraints << "\n";
        exit(0);
        return;
      }

      llvm::Function *cur_func = i->getParent()->getParent();
      /* Updating state->cur_fsummary. We'll use this value in
       * executeCall to update stack frame cur_fsummary. */ 
      SpecialFunctionHandler::handlers_ty::iterator it = specialFunctionHandler->handlers.find(f);
      /* If we call the next function in call graph; target_func is NULL for inner_calls */
      if(state.cur_fsummary &&  
         (state.stack.back().cur_call_symbolics_seq_num == state.cur_fsummary->call_symbolic_replacements.size()) &&
          (f == state.cur_fsummary->target_func)) 
      {
	      llvm::outs() << "ForwardExecutor::executeInstruction()::Call: calling next on call-path function "
                     <<  f->getName() << state.cur_fsummary << " " << state.next_fsummary << "; "
                     << "ki = " << *(ki->inst) << " prevPC =  " << *(state.prevPC->inst)  << "\n";
        state.cur_fsummary = state.next_fsummary;
        if((state.next_fsummary->fn != path_manager->call_path[path_manager->call_path.size()-2]))
        {
          /* The current implementation of backward symbex gives us only one
           * next path summary */
          state.next_fsummary = state.next_fsummary->next_path_summaries[0];
        }
        else 
          state.next_fsummary = NULL;


      }
      else if(state.cur_fsummary && !f->isDeclaration()
                                && (f->getName().str() != "klee_div_zero_check")
                                && (f->getName().str() != "memset")
                                && (f->getName().str() != "memcpy")
                                && (f->getName().str() != "klee_overshift_check"))/* else it is an inner call */
      {
        StackFrame &sf = state.stack.back();
        llvm::outs() << "ForwardExecutor::executeInstruction():: Call: searching suppl call for function " << cur_func->getName()
                     << " and seq_num = " << sf.cur_call_symbolics_seq_num << "\n";
        InnerCall *inner_call = get_InnerCall_by_seqnum(state.cur_fsummary, sf.cur_call_symbolics_seq_num);
        assert(inner_call && "could not find suppl call by seq_num");
        sf.cur_call_symbolics_seq_num++;

        /* If there are connected summaries, we run
         * executeCall for each of them and the break the switch
         * statement */
        unsigned N = inner_call->connected_summaries.size();
        if(N != 0)
        {
          //state.cur_fsummary = inner_call->connected_summaries[0];
          std::vector<ExecutionState*> branches;
          branch_connected_summaries(state, N, branches, true); // Add new states to addedStates
          for(unsigned k = 0; k < N; k++)
          {
            ExecutionState *es = branches[k];
            assert(es && "Execution state after branch_connected_summaries is NULL");
            es->cur_fsummary = inner_call->connected_summaries[k];
            //llvm::outs() << "Executor::executeInstruction():: Call: using the following summary"
            //                " for inner_call function " << cur_func->getName() << "\n";
            //print_function_summary(state.cur_fsummary);
            executeCall(*es, ki, f, arguments);
          }
          break; /* Break switch statement here */
        }
        /* Else set the cur_summary to NULL and proceed with usual flow */
        else
        {
          state.cur_fsummary = NULL;
          //llvm::outs() << "Executor::executeInstruction():: Call: using the following summary"
          //                " for inner_call function " << cur_func->getName() << "\n";
          //print_function_summary(state.cur_fsummary);
        }
      } 
	    else if( (f->isDeclaration()) && (f->getIntrinsicID() == Intrinsic::not_intrinsic) &&
         (it != specialFunctionHandler->handlers.end()) 
      )
	    {
	      /* Special function handler will be invoked in executeCall(),
	       * which does not set new stack frame, nor execute any llvm
	       * code => never check if it complies with any path summary;
	       * so just keep the current path summary (i.e. do nothing) */
	    }
	    else /* It's an inner call for which we dicided not to search for summaries */
      {
        assert((ForwardOnly || !is_part_of_callpath(f)) && "state.cur_fsummary is NULL and we are going to call on-call-path function");
        state.cur_fsummary = NULL;
        llvm::outs() << "Executor::executeInstruction():: Call: cur path summary is NULL or f is decl only ("
                     << (f->isDeclaration() ? "true" : "false") << ") or it's klee_div_zero_check() (" <<
                        ((f->getName().str() == "klee_div_zero_check") ? "true" : "false") << ") leaving cur summary as NULL\n";
      }
      
      const FunctionType *fType = 
        dyn_cast<FunctionType>(cast<PointerType>(f->getType())->getElementType());
      const FunctionType *fpType =
        dyn_cast<FunctionType>(cast<PointerType>(fp->getType())->getElementType());

      // special case the call with a bitcast case
      if (fType != fpType) {
        assert(fType && fpType && "unable to get function type");

        // XXX check result coercion

        // XXX this really needs thought and validation
        unsigned i=0;
        for (std::vector< ref<Expr> >::iterator
               ai = arguments.begin(), ie = arguments.end();
             ai != ie; ++ai) {
          Expr::Width to, from = (*ai)->getWidth();
            
          if (i<fType->getNumParams()) {
            to = getWidthForLLVMType(fType->getParamType(i));

            if (from != to) {
              // XXX need to check other param attrs ?
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
              bool isSExt = cs.paramHasAttr(i+1, llvm::Attribute::SExt);
#elif LLVM_VERSION_CODE >= LLVM_VERSION(3, 2)
	      bool isSExt = cs.paramHasAttr(i+1, llvm::Attributes::SExt);
#else
	      bool isSExt = cs.paramHasAttr(i+1, llvm::Attribute::SExt);
#endif
              if (isSExt) {
                arguments[i] = SExtExpr::create(arguments[i], to);
              } else {
                arguments[i] = ZExtExpr::create(arguments[i], to);
              }
            }
          }
            
          i++;
        }
      }

      executeCall(state, ki, f, arguments);
    } else {
      ref<Expr> v = eval(ki, 0, state).value;

      ExecutionState *free = &state;
      bool hasInvalid = false, first = true;

      /* XXX This is wasteful, no need to do a full evaluate since we
         have already got a value. But in the end the caches should
         handle it for us, albeit with some overhead. */
      do {
        ref<ConstantExpr> value;
        bool success = solver->getValue(*free, v, value);
        assert(success && "FIXME: Unhandled solver failure");
        (void) success;
        StatePair res = fork(*free, EqExpr::create(v, value), true);
        if (res.first) {
          uint64_t addr = value->getZExtValue();
          if (legalFunctions.count(addr)) {
            f = (Function*) addr;

            // Don't give warning on unique resolution
            if (res.second || !first)
              klee_warning_once((void*) (unsigned long) addr, 
                                "resolved symbolic function pointer to: %s",
                                f->getName().data());

            executeCall(*res.first, ki, f, arguments);
          } else {
            if (!hasInvalid) {
              terminateStateOnExecError(state, "invalid function pointer");
              hasInvalid = true;
            }
          }
        }

        first = false;
        free = res.second;
      } while (free);
    }
    break;
  }
  case Instruction::PHI: {
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 0)
    ref<Expr> result = eval(ki, state.incomingBBIndex, state).value;
#else
    ref<Expr> result = eval(ki, state.incomingBBIndex * 2, state).value;
#endif
    bindLocal(ki, state, result);
    break;
  }

    // Special instructions
  case Instruction::Select: {
    ref<Expr> cond = eval(ki, 0, state).value;
    ref<Expr> tExpr = eval(ki, 1, state).value;
    ref<Expr> fExpr = eval(ki, 2, state).value;
    ref<Expr> result = SelectExpr::create(cond, tExpr, fExpr);
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::VAArg:
    terminateStateOnExecError(state, "unexpected VAArg instruction");
    break;

    // Arithmetic / logical

  case Instruction::Add: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    bindLocal(ki, state, AddExpr::create(left, right));
    break;
  }

  case Instruction::Sub: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    bindLocal(ki, state, SubExpr::create(left, right));
    break;
  }
 
  case Instruction::Mul: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    bindLocal(ki, state, MulExpr::create(left, right));
    break;
  }

  case Instruction::UDiv: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = UDivExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::SDiv: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = SDivExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::URem: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = URemExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }
 
  case Instruction::SRem: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = SRemExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::And: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = AndExpr::create(left, right);
    llvm::outs() << "ForwardExecutor::executeInstruction(): And: " << result << "\n";
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::Or: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = OrExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::Xor: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = XorExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::Shl: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = ShlExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::LShr: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = LShrExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::AShr: {
    ref<Expr> left = eval(ki, 0, state).value;
    ref<Expr> right = eval(ki, 1, state).value;
    ref<Expr> result = AShrExpr::create(left, right);
    bindLocal(ki, state, result);
    break;
  }

    // Compare

  case Instruction::ICmp: {
    CmpInst *ci = cast<CmpInst>(i);
    ICmpInst *ii = cast<ICmpInst>(ci);
 
    switch(ii->getPredicate()) {
    case ICmpInst::ICMP_EQ: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = EqExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    case ICmpInst::ICMP_NE: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = NeExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    case ICmpInst::ICMP_UGT: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = UgtExpr::create(left, right);
      bindLocal(ki, state,result);
      break;
    }

    case ICmpInst::ICMP_UGE: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = UgeExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    case ICmpInst::ICMP_ULT: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = UltExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    case ICmpInst::ICMP_ULE: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = UleExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    case ICmpInst::ICMP_SGT: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = SgtExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    case ICmpInst::ICMP_SGE: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = SgeExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    case ICmpInst::ICMP_SLT: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = SltExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    case ICmpInst::ICMP_SLE: {
      ref<Expr> left = eval(ki, 0, state).value;
      ref<Expr> right = eval(ki, 1, state).value;
      ref<Expr> result = SleExpr::create(left, right);
      bindLocal(ki, state, result);
      break;
    }

    default:
      terminateStateOnExecError(state, "invalid ICmp predicate");
    }
    break;
  }
 
    // Memory instructions...
  case Instruction::Alloca: {
    AllocaInst *ai = cast<AllocaInst>(i);
    unsigned elementSize = 
      kmodule->targetData->getTypeStoreSize(ai->getAllocatedType());
    ref<Expr> size = Expr::createPointer(elementSize);
    if (ai->isArrayAllocation()) {
      ref<Expr> count = eval(ki, 0, state).value;
      count = Expr::createZExtToPointerWidth(count);
      size = MulExpr::create(size, count);
    }
    bool isLocal = i->getOpcode()==Instruction::Alloca;
    executeAlloc(state, size, isLocal, ki);
    break;
  }

  case Instruction::Load: {
    ref<Expr> base = eval(ki, 0, state).value;
    //llvm::outs() << "We have a load instruction with the fowollwing base expression: " << base << "\n";
    llvm::outs() << "ForwardExecutor::executeInstruction(): Load: base = " << base << "\n";
    executeMemoryOperation(state, false, base, 0, ki);
    break;
  }
  case Instruction::Store: {
    llvm::outs() << "Executing Store instruction\n";
    ref<Expr> base = eval(ki, 1, state).value;
    ref<Expr> value = eval(ki, 0, state).value;
    //llvm::outs() << "MAKAKA\n";
    //llvm::outs() << "Going inside executeMemoryOperation(), value.get() = " << value.get() << "\n";
    //llvm::outs() << "Going inside executeMemoryOperation(), base = " << base << "; value = " << value << "\n";
    //llvm::outs() << "Going inside executeMemoryOperation(), base = " << base << "\n";
    //llvm::outs() << "AKAFDEFF\n";
    llvm::outs() << "ForwardExecutor::executeInstruction(): Store: base = " << base << "\n";
    executeMemoryOperation(state, true, base, value, 0);
    llvm::outs() << "Returned from executeMemoryOperation()\n";
    break;
  }

  case Instruction::GetElementPtr: {
    KGEPInstruction *kgepi = static_cast<KGEPInstruction*>(ki);
    ref<Expr> base = eval(ki, 0, state).value;
    llvm::outs() << "ForwardExecutor::executeInstruction(): GetElemetPtr: base = " << base << "\n";

    for (std::vector< std::pair<unsigned, uint64_t> >::iterator 
           it = kgepi->indices.begin(), ie = kgepi->indices.end(); 
         it != ie; ++it) {
      uint64_t elementSize = it->second;
      ref<Expr> index = eval(ki, it->first, state).value;
      llvm::outs() << "ForwardExecutor::executeInstruction(): GetElemetPtr: considering index " 
                   << index << " with size " << elementSize << "\n";
      base = AddExpr::create(base,
                             MulExpr::create(Expr::createSExtToPointerWidth(index),
                                             Expr::createPointer(elementSize)));
      llvm::outs() << "ForwardExecutor::executeInstruction(): GetElemetPtr: new base = " << base << "\n";
    }
    if (kgepi->offset)
    {
      base = AddExpr::create(base,
                             Expr::createPointer(kgepi->offset));
      llvm::outs() << "ForwardExecutor::executeInstruction(): GetElemetPtr:  base after adding offset = " << base << "\n";
    }
    llvm::outs() << "ForwardExecutor::executeInstruction(): GetElemetPtr:  base to go to bind local = " << base << "\n";
    bindLocal(ki, state, base);
    break;
  }

    // Conversion
  case Instruction::Trunc: {
    CastInst *ci = cast<CastInst>(i);
    ref<Expr> result = ExtractExpr::create(eval(ki, 0, state).value,
                                           0,
                                           getWidthForLLVMType(ci->getType()));
    bindLocal(ki, state, result);
    break;
  }
  case Instruction::ZExt: {
    CastInst *ci = cast<CastInst>(i);
    ref<Expr> result = ZExtExpr::create(eval(ki, 0, state).value,
                                        getWidthForLLVMType(ci->getType()));
    llvm::outs() << "ForwardExecutor::executeInstruction(): ZExt: " << result << "\n";
    bindLocal(ki, state, result);
    break;
  }
  case Instruction::SExt: {
    CastInst *ci = cast<CastInst>(i);
    ref<Expr> result = SExtExpr::create(eval(ki, 0, state).value,
                                        getWidthForLLVMType(ci->getType()));
    bindLocal(ki, state, result);
    break;
  }

  case Instruction::IntToPtr: {
    CastInst *ci = cast<CastInst>(i);
    Expr::Width pType = getWidthForLLVMType(ci->getType());
    ref<Expr> arg = eval(ki, 0, state).value;
    bindLocal(ki, state, ZExtExpr::create(arg, pType));
    break;
  } 
  case Instruction::PtrToInt: {
    CastInst *ci = cast<CastInst>(i);
    Expr::Width iType = getWidthForLLVMType(ci->getType());
    ref<Expr> arg = eval(ki, 0, state).value;
    bindLocal(ki, state, ZExtExpr::create(arg, iType));
    break;
  }

  case Instruction::BitCast: {
    ref<Expr> result = eval(ki, 0, state).value;
    bindLocal(ki, state, result);
    break;
  }

    // Floating point instructions

  case Instruction::FAdd: {
    ref<ConstantExpr> left = toConstant(state, eval(ki, 0, state).value,
                                        "floating point");
    ref<ConstantExpr> right = toConstant(state, eval(ki, 1, state).value,
                                         "floating point");
    if (!fpWidthToSemantics(left->getWidth()) ||
        !fpWidthToSemantics(right->getWidth()))
      return terminateStateOnExecError(state, "Unsupported FAdd operation");

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Res(*fpWidthToSemantics(left->getWidth()), left->getAPValue());
    Res.add(APFloat(*fpWidthToSemantics(right->getWidth()),right->getAPValue()), APFloat::rmNearestTiesToEven);
#else
    llvm::APFloat Res(left->getAPValue());
    Res.add(APFloat(right->getAPValue()), APFloat::rmNearestTiesToEven);
#endif
    bindLocal(ki, state, ConstantExpr::alloc(Res.bitcastToAPInt()));
    break;
  }

  case Instruction::FSub: {
    ref<ConstantExpr> left = toConstant(state, eval(ki, 0, state).value,
                                        "floating point");
    ref<ConstantExpr> right = toConstant(state, eval(ki, 1, state).value,
                                         "floating point");
    if (!fpWidthToSemantics(left->getWidth()) ||
        !fpWidthToSemantics(right->getWidth()))
      return terminateStateOnExecError(state, "Unsupported FSub operation");
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Res(*fpWidthToSemantics(left->getWidth()), left->getAPValue());
    Res.subtract(APFloat(*fpWidthToSemantics(right->getWidth()), right->getAPValue()), APFloat::rmNearestTiesToEven);
#else
    llvm::APFloat Res(left->getAPValue());
    Res.subtract(APFloat(right->getAPValue()), APFloat::rmNearestTiesToEven);
#endif
    bindLocal(ki, state, ConstantExpr::alloc(Res.bitcastToAPInt()));
    break;
  }
 
  case Instruction::FMul: {
    ref<ConstantExpr> left = toConstant(state, eval(ki, 0, state).value,
                                        "floating point");
    ref<ConstantExpr> right = toConstant(state, eval(ki, 1, state).value,
                                         "floating point");
    if (!fpWidthToSemantics(left->getWidth()) ||
        !fpWidthToSemantics(right->getWidth()))
      return terminateStateOnExecError(state, "Unsupported FMul operation");

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Res(*fpWidthToSemantics(left->getWidth()), left->getAPValue());
    Res.multiply(APFloat(*fpWidthToSemantics(right->getWidth()), right->getAPValue()), APFloat::rmNearestTiesToEven);
#else
    llvm::APFloat Res(left->getAPValue());
    Res.multiply(APFloat(right->getAPValue()), APFloat::rmNearestTiesToEven);
#endif
    bindLocal(ki, state, ConstantExpr::alloc(Res.bitcastToAPInt()));
    break;
  }

  case Instruction::FDiv: {
    ref<ConstantExpr> left = toConstant(state, eval(ki, 0, state).value,
                                        "floating point");
    ref<ConstantExpr> right = toConstant(state, eval(ki, 1, state).value,
                                         "floating point");
    if (!fpWidthToSemantics(left->getWidth()) ||
        !fpWidthToSemantics(right->getWidth()))
      return terminateStateOnExecError(state, "Unsupported FDiv operation");

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Res(*fpWidthToSemantics(left->getWidth()), left->getAPValue());
    Res.divide(APFloat(*fpWidthToSemantics(right->getWidth()), right->getAPValue()), APFloat::rmNearestTiesToEven);
#else
    llvm::APFloat Res(left->getAPValue());
    Res.divide(APFloat(right->getAPValue()), APFloat::rmNearestTiesToEven);
#endif
    bindLocal(ki, state, ConstantExpr::alloc(Res.bitcastToAPInt()));
    break;
  }

  case Instruction::FRem: {
    ref<ConstantExpr> left = toConstant(state, eval(ki, 0, state).value,
                                        "floating point");
    ref<ConstantExpr> right = toConstant(state, eval(ki, 1, state).value,
                                         "floating point");
    if (!fpWidthToSemantics(left->getWidth()) ||
        !fpWidthToSemantics(right->getWidth()))
      return terminateStateOnExecError(state, "Unsupported FRem operation");
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Res(*fpWidthToSemantics(left->getWidth()), left->getAPValue());
    Res.mod(APFloat(*fpWidthToSemantics(right->getWidth()),right->getAPValue()),
            APFloat::rmNearestTiesToEven);
#else
    llvm::APFloat Res(left->getAPValue());
    Res.mod(APFloat(right->getAPValue()), APFloat::rmNearestTiesToEven);
#endif
    bindLocal(ki, state, ConstantExpr::alloc(Res.bitcastToAPInt()));
    break;
  }

  case Instruction::FPTrunc: {
    FPTruncInst *fi = cast<FPTruncInst>(i);
    Expr::Width resultType = getWidthForLLVMType(fi->getType());
    ref<ConstantExpr> arg = toConstant(state, eval(ki, 0, state).value,
                                       "floating point");
    if (!fpWidthToSemantics(arg->getWidth()) || resultType > arg->getWidth())
      return terminateStateOnExecError(state, "Unsupported FPTrunc operation");

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Res(*fpWidthToSemantics(arg->getWidth()), arg->getAPValue());
#else
    llvm::APFloat Res(arg->getAPValue());
#endif
    bool losesInfo = false;
    Res.convert(*fpWidthToSemantics(resultType),
                llvm::APFloat::rmNearestTiesToEven,
                &losesInfo);
    bindLocal(ki, state, ConstantExpr::alloc(Res));
    break;
  }

  case Instruction::FPExt: {
    FPExtInst *fi = cast<FPExtInst>(i);
    Expr::Width resultType = getWidthForLLVMType(fi->getType());
    ref<ConstantExpr> arg = toConstant(state, eval(ki, 0, state).value,
                                        "floating point");
    if (!fpWidthToSemantics(arg->getWidth()) || arg->getWidth() > resultType)
      return terminateStateOnExecError(state, "Unsupported FPExt operation");
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Res(*fpWidthToSemantics(arg->getWidth()), arg->getAPValue());
#else
    llvm::APFloat Res(arg->getAPValue());
#endif
    bool losesInfo = false;
    Res.convert(*fpWidthToSemantics(resultType),
                llvm::APFloat::rmNearestTiesToEven,
                &losesInfo);
    bindLocal(ki, state, ConstantExpr::alloc(Res));
    break;
  }

  case Instruction::FPToUI: {
    FPToUIInst *fi = cast<FPToUIInst>(i);
    Expr::Width resultType = getWidthForLLVMType(fi->getType());
    ref<ConstantExpr> arg = toConstant(state, eval(ki, 0, state).value,
                                       "floating point");
    if (!fpWidthToSemantics(arg->getWidth()) || resultType > 64)
      return terminateStateOnExecError(state, "Unsupported FPToUI operation");

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Arg(*fpWidthToSemantics(arg->getWidth()), arg->getAPValue());
#else
    llvm::APFloat Arg(arg->getAPValue());
#endif
    uint64_t value = 0;
    bool isExact = true;
    Arg.convertToInteger(&value, resultType, false,
                         llvm::APFloat::rmTowardZero, &isExact);
    bindLocal(ki, state, ConstantExpr::alloc(value, resultType));
    break;
  }

  case Instruction::FPToSI: {
    FPToSIInst *fi = cast<FPToSIInst>(i);
    Expr::Width resultType = getWidthForLLVMType(fi->getType());
    ref<ConstantExpr> arg = toConstant(state, eval(ki, 0, state).value,
                                       "floating point");
    if (!fpWidthToSemantics(arg->getWidth()) || resultType > 64)
      return terminateStateOnExecError(state, "Unsupported FPToSI operation");
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    llvm::APFloat Arg(*fpWidthToSemantics(arg->getWidth()), arg->getAPValue());
#else
    llvm::APFloat Arg(arg->getAPValue());

#endif
    uint64_t value = 0;
    bool isExact = true;
    Arg.convertToInteger(&value, resultType, true,
                         llvm::APFloat::rmTowardZero, &isExact);
    bindLocal(ki, state, ConstantExpr::alloc(value, resultType));
    break;
  }

  case Instruction::UIToFP: {
    UIToFPInst *fi = cast<UIToFPInst>(i);
    Expr::Width resultType = getWidthForLLVMType(fi->getType());
    ref<ConstantExpr> arg = toConstant(state, eval(ki, 0, state).value,
                                       "floating point");
    const llvm::fltSemantics *semantics = fpWidthToSemantics(resultType);
    if (!semantics)
      return terminateStateOnExecError(state, "Unsupported UIToFP operation");
    llvm::APFloat f(*semantics, 0);
    f.convertFromAPInt(arg->getAPValue(), false,
                       llvm::APFloat::rmNearestTiesToEven);

    bindLocal(ki, state, ConstantExpr::alloc(f));
    break;
  }

  case Instruction::SIToFP: {
    SIToFPInst *fi = cast<SIToFPInst>(i);
    Expr::Width resultType = getWidthForLLVMType(fi->getType());
    ref<ConstantExpr> arg = toConstant(state, eval(ki, 0, state).value,
                                       "floating point");
    const llvm::fltSemantics *semantics = fpWidthToSemantics(resultType);
    if (!semantics)
      return terminateStateOnExecError(state, "Unsupported SIToFP operation");
    llvm::APFloat f(*semantics, 0);
    f.convertFromAPInt(arg->getAPValue(), true,
                       llvm::APFloat::rmNearestTiesToEven);

    bindLocal(ki, state, ConstantExpr::alloc(f));
    break;
  }

  case Instruction::FCmp: {
    FCmpInst *fi = cast<FCmpInst>(i);
    ref<ConstantExpr> left = toConstant(state, eval(ki, 0, state).value,
                                        "floating point");
    ref<ConstantExpr> right = toConstant(state, eval(ki, 1, state).value,
                                         "floating point");
    if (!fpWidthToSemantics(left->getWidth()) ||
        !fpWidthToSemantics(right->getWidth()))
      return terminateStateOnExecError(state, "Unsupported FCmp operation");

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
    APFloat LHS(*fpWidthToSemantics(left->getWidth()),left->getAPValue());
    APFloat RHS(*fpWidthToSemantics(right->getWidth()),right->getAPValue());
#else
    APFloat LHS(left->getAPValue());
    APFloat RHS(right->getAPValue());
#endif
    APFloat::cmpResult CmpRes = LHS.compare(RHS);

    bool Result = false;
    switch( fi->getPredicate() ) {
      // Predicates which only care about whether or not the operands are NaNs.
    case FCmpInst::FCMP_ORD:
      Result = CmpRes != APFloat::cmpUnordered;
      break;

    case FCmpInst::FCMP_UNO:
      Result = CmpRes == APFloat::cmpUnordered;
      break;

      // Ordered comparisons return false if either operand is NaN.  Unordered
      // comparisons return true if either operand is NaN.
    case FCmpInst::FCMP_UEQ:
      if (CmpRes == APFloat::cmpUnordered) {
        Result = true;
        break;
      }
    case FCmpInst::FCMP_OEQ:
      Result = CmpRes == APFloat::cmpEqual;
      break;

    case FCmpInst::FCMP_UGT:
      if (CmpRes == APFloat::cmpUnordered) {
        Result = true;
        break;
      }
    case FCmpInst::FCMP_OGT:
      Result = CmpRes == APFloat::cmpGreaterThan;
      break;

    case FCmpInst::FCMP_UGE:
      if (CmpRes == APFloat::cmpUnordered) {
        Result = true;
        break;
      }
    case FCmpInst::FCMP_OGE:
      Result = CmpRes == APFloat::cmpGreaterThan || CmpRes == APFloat::cmpEqual;
      break;

    case FCmpInst::FCMP_ULT:
      if (CmpRes == APFloat::cmpUnordered) {
        Result = true;
        break;
      }
    case FCmpInst::FCMP_OLT:
      Result = CmpRes == APFloat::cmpLessThan;
      break;

    case FCmpInst::FCMP_ULE:
      if (CmpRes == APFloat::cmpUnordered) {
        Result = true;
        break;
      }
    case FCmpInst::FCMP_OLE:
      Result = CmpRes == APFloat::cmpLessThan || CmpRes == APFloat::cmpEqual;
      break;

    case FCmpInst::FCMP_UNE:
      Result = CmpRes == APFloat::cmpUnordered || CmpRes != APFloat::cmpEqual;
      break;
    case FCmpInst::FCMP_ONE:
      Result = CmpRes != APFloat::cmpUnordered && CmpRes != APFloat::cmpEqual;
      break;

    default:
      assert(0 && "Invalid FCMP predicate!");
    case FCmpInst::FCMP_FALSE:
      Result = false;
      break;
    case FCmpInst::FCMP_TRUE:
      Result = true;
      break;
    }

    bindLocal(ki, state, ConstantExpr::alloc(Result, Expr::Bool));
    break;
  }
  case Instruction::InsertValue: {
    KGEPInstruction *kgepi = static_cast<KGEPInstruction*>(ki);

    ref<Expr> agg = eval(ki, 0, state).value;
    ref<Expr> val = eval(ki, 1, state).value;

    ref<Expr> l = NULL, r = NULL;
    unsigned lOffset = kgepi->offset*8, rOffset = kgepi->offset*8 + val->getWidth();

    if (lOffset > 0)
      l = ExtractExpr::create(agg, 0, lOffset);
    if (rOffset < agg->getWidth())
      r = ExtractExpr::create(agg, rOffset, agg->getWidth() - rOffset);

    ref<Expr> result;
    if (!l.isNull() && !r.isNull())
      result = ConcatExpr::create(r, ConcatExpr::create(val, l));
    else if (!l.isNull())
      result = ConcatExpr::create(val, l);
    else if (!r.isNull())
      result = ConcatExpr::create(r, val);
    else
      result = val;

    bindLocal(ki, state, result);
    break;
  }
  case Instruction::ExtractValue: {
    KGEPInstruction *kgepi = static_cast<KGEPInstruction*>(ki);

    ref<Expr> agg = eval(ki, 0, state).value;

    ref<Expr> result = ExtractExpr::create(agg, kgepi->offset*8, getWidthForLLVMType(i->getType()));

    bindLocal(ki, state, result);
    break;
  }
 
    // Other instructions...
    // Unhandled
  case Instruction::ExtractElement:
  case Instruction::InsertElement:
  case Instruction::ShuffleVector:
    terminateStateOnError(state, "XXX vector instructions unhandled",
                          "xxx.err");
    break;
 
  default:
    terminateStateOnExecError(state, "illegal instruction");
    break;
  }
}

/// IVAN ADDITIONS START




void ForwardExecutor::updateStates(ExecutionState *current) {
  if (searcher) {
    searcher->update(current, addedStates, removedStates);
  }
  
  states.insert(addedStates.begin(), addedStates.end());
  addedStates.clear();
  
  for (std::set<ExecutionState*>::iterator
         it = removedStates.begin(), ie = removedStates.end();
       it != ie; ++it) {
    ExecutionState *es = *it;
    std::set<ExecutionState*>::iterator it2 = states.find(es);
    assert(it2!=states.end());
    states.erase(it2);
    std::map<ExecutionState*, std::vector<SeedInfo> >::iterator it3 = 
      seedMap.find(es);
    if (it3 != seedMap.end())
      seedMap.erase(it3);
    processTree->remove(es->ptreeNode);
    delete es;
  }
  removedStates.clear();
}

/// IVAN ADDITIONS BEGIN
template <typename TypeIt>
void ForwardExecutor::clearOffsets(KGEPInstruction *kgepi, TypeIt ib, TypeIt ie) {
  uint64_t index = 1;
  for (TypeIt ii = ib; ii != ie; ++ii) {
    if (LLVM_TYPE_Q StructType *st = dyn_cast<StructType>(*ii)) {
         // PASS
    } else {
      Value *operand = ii.getOperand();
      if (Constant *c = dyn_cast<Constant>(operand)) {
        // PASS
      } else {
        kgepi->indices.clear();
      }
    }
    index++;
  }
  kgepi->offset = 0;
}
/// IVAN ADDITIONS END

template <typename TypeIt>
void ForwardExecutor::computeOffsets(KGEPInstruction *kgepi, TypeIt ib, TypeIt ie) {
  ref<ConstantExpr> constantOffset =
    ConstantExpr::alloc(0, Context::get().getPointerWidth());
  uint64_t index = 1;
  for (TypeIt ii = ib; ii != ie; ++ii) {
    if (LLVM_TYPE_Q StructType *st = dyn_cast<StructType>(*ii)) {
      const StructLayout *sl = kmodule->targetData->getStructLayout(st);
      const ConstantInt *ci = cast<ConstantInt>(ii.getOperand());
      uint64_t addend = sl->getElementOffset((unsigned) ci->getZExtValue());
      constantOffset = constantOffset->Add(ConstantExpr::alloc(addend,
                                                               Context::get().getPointerWidth()));
    } else {
      const SequentialType *set = cast<SequentialType>(*ii);
      uint64_t elementSize = 
        kmodule->targetData->getTypeStoreSize(set->getElementType());
      Value *operand = ii.getOperand();
      if (Constant *c = dyn_cast<Constant>(operand)) {
        ref<ConstantExpr> index = 
          evalConstant(c)->SExt(Context::get().getPointerWidth());
        ref<ConstantExpr> addend = 
          index->Mul(ConstantExpr::alloc(elementSize,
                                         Context::get().getPointerWidth()));
        constantOffset = constantOffset->Add(addend);
      } else {
        kgepi->indices.push_back(std::make_pair(index, elementSize));
      }
    }
    index++;
  }
  kgepi->offset = constantOffset->getZExtValue();
}

void ForwardExecutor::bindInstructionConstants(KInstruction *KI) {
  KGEPInstruction *kgepi = static_cast<KGEPInstruction*>(KI);

  if (GetElementPtrInst *gepi = dyn_cast<GetElementPtrInst>(KI->inst)) {
    ///IVAN ADDITIONS BEGIN
    clearOffsets(kgepi, gep_type_begin(gepi), gep_type_end(gepi));
    ///IVAN ADDITIONS END
    computeOffsets(kgepi, gep_type_begin(gepi), gep_type_end(gepi));
  } else if (InsertValueInst *ivi = dyn_cast<InsertValueInst>(KI->inst)) {
    computeOffsets(kgepi, iv_type_begin(ivi), iv_type_end(ivi));
    assert(kgepi->indices.empty() && "InsertValue constant offset expected");
  } else if (ExtractValueInst *evi = dyn_cast<ExtractValueInst>(KI->inst)) {
    computeOffsets(kgepi, ev_type_begin(evi), ev_type_end(evi));
    assert(kgepi->indices.empty() && "ExtractValue constant offset expected");
  }
}

void ForwardExecutor::bindModuleConstants() {
  for (std::vector<KFunction*>::iterator it = kmodule->functions.begin(), 
         ie = kmodule->functions.end(); it != ie; ++it) {
    KFunction *kf = *it;
    for (unsigned i=0; i<kf->numInstructions; ++i)
      bindInstructionConstants(kf->instructions[i]);
  }

  kmodule->constantTable = new Cell[kmodule->constants.size()];
  for (unsigned i=0; i<kmodule->constants.size(); ++i) {
    Cell &c = kmodule->constantTable[i];
    c.value = evalConstant(kmodule->constants[i]);
  }
}


bool state_complies_with_inner_call_summary(ExecutionState *state, 
                   path_summary_ty *psmmry, unsigned stack_frame_ndx)
{
  StackFrame &sf = state->stack[stack_frame_ndx];
  unsigned next_inner_call_seq_num = 0;
  CallInst* last_callInst;
  /* Check if stack's and path summry's instructions match */
  for(unsigned j = 0; j < sf.path_instructions.size(); j++)
  {
    llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): comparing (state):" << *(sf.path_instructions[j]) <<
                    "\n                                                                   (summary):" << *(psmmry->path_instructions[j]) << "\n";
    llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): this is instruction " << j << " out of " <<
                     sf.path_instructions.size()-1 << "\n";
    if(sf.path_instructions[j] != psmmry->path_instructions[j])
    {
      llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): insts are different, returning false\n";
      //llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): " << sf.path_instructions[j] << " != " << \n";
      return false;
    }
    llvm::Instruction *cur_inst = sf.path_instructions[j];

    /* If we are at call instruction which is an inner call*/
    last_callInst = dyn_cast<CallInst>((llvm::Instruction *)(cur_inst));
    if(last_callInst)
    {
      llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): I see a call instruction, let's check if it is an inner call ... ";
      InnerCall *inner_call = psmmry->get_InnerCall_by_seqnum(next_inner_call_seq_num);
      /* This call instruction is an inner call that we recorded */
      if(inner_call->call_inst == last_callInst)
      {
        llvm::outs() << " yes\n";
        next_inner_call_seq_num++;
      } else
        llvm::outs() << " nope\n";
    }

  }
  /* All insts are good and this is the last stack frame */
  if(stack_frame_ndx == (state->stack.size()-1))
  {
    llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): returning true\n";
    return true;
  }

  /* Each stack frame should end by a call instruction */
  assert(last_callInst && "Last instruction of a stack frame is not a call");

  unsigned cur_inner_call_seq_num = 0;
  if(next_inner_call_seq_num)
    cur_inner_call_seq_num = next_inner_call_seq_num-1;
  assert(cur_inner_call_seq_num < psmmry->call_symbolic_replacements.size());
  llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): the last"
               << " instruction was call instruction (possibly to inner call with seq_num =  " << cur_inner_call_seq_num << "\n";


  InnerCall *inner_call = psmmry->get_InnerCall_by_seqnum(cur_inner_call_seq_num);
  /* This call instruction is an inner call that we recorded */
  if(inner_call->call_inst != last_callInst)
  {
    llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): the last instruction is not an inner call, i.e."
                 << " we are going inside something linke memset, returning true\n";
    return true;
  }

  llvm::outs() << "ForwardExecutor::state_complies_with_inner_call_summary(): inner call indeed\n";
  bool success = false;
  /* In summary executor we intentionally left some inner calls without
   * connected summaries: either such calls had no arguments and return value,
   * or they called blacklisted funcitons (as memset, etc.). */
  if(!inner_call->connected_summaries.size()) 
    success = true;
  for(unsigned k = 0; k < inner_call->connected_summaries.size(); k++)
  {
    success = state_complies_with_inner_call_summary(state, inner_call->connected_summaries[k], stack_frame_ndx+1);
    if(success)
      break;
  }
  return success;
}



/* Candidate path is a linked list of path summaries, it starts from main() */
bool ForwardExecutor::state_complies_with_path_candidate(ExecutionState *state, path_summary_ty *candidate_path)
{
  llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): inside for candidate_path " 
               << candidate_path << "\n";

  if(state->interruptFun)
    return true;

  if(state->blacklisted_psummaries.count(candidate_path))
    return false;

  llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): candidate not blacklisted\n";

  /* Go from the upper level stack frame */
  unsigned next_inner_call_seq_num = 0;
  unsigned stack_sz = state->stack.size();
  llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): stack size = " << stack_sz << "\n";
  path_summary_ty *cur_psmmry = candidate_path;
  for(unsigned stack_frame_ndx = 0; stack_frame_ndx < stack_sz; stack_frame_ndx++)
  {
    StackFrame &sf = state->stack[stack_frame_ndx];
    CallInst* last_callInst;
    bool last_was_inner_call = false;

    /* Check if stack's and path summry's instructions match */
    next_inner_call_seq_num = 0;
    for(unsigned j = 0; j < sf.path_instructions.size(); j++)
    {
      llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): comparing (state):" << *(sf.path_instructions[j]) <<
                      "\n                                                               (summary):" << *(cur_psmmry->path_instructions[j]) << "\n";
      llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): this is instruction " << j << " out of " <<
                       sf.path_instructions.size()-1 << "\n";
      if(sf.path_instructions[j] != cur_psmmry->path_instructions[j])
      {
        state->blacklisted_psummaries.insert(candidate_path);
        llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): returning false\n";
        return false;
      }
      llvm::Instruction *cur_inst = sf.path_instructions[j];
      /* If we are at call instruction which is an inner call*/
      last_callInst = dyn_cast<CallInst>((llvm::Instruction *)(cur_inst));
      if(last_callInst)
      {
        llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): I see a call instruction, let's check if it is an inner call ... \n";
        InnerCall *inner_call = cur_psmmry->get_InnerCall_by_seqnum(next_inner_call_seq_num);
	/* This call instruction is an inner call that we recorded */
	if(inner_call && (inner_call->call_inst == last_callInst))
	{
          llvm::outs() << " yes\n";
          next_inner_call_seq_num++;
	  last_was_inner_call = true;
	} else
	{
          llvm::outs() << " nope.\n";
	  last_was_inner_call = false;
	}
      }
    }
    /* All insts are good for all frames => return true */
    if(stack_frame_ndx == (stack_sz-1))
    {
      llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): returning true\n";
      return true;
    }

    /* Each stack frame should end by a call instruction */
    assert(last_callInst && "Last instruction of a stack frame is not a call");
    /* Not it's time to find the next summary, it is either an inner call or
     * next function in the call path */
     /* if the last inst was not inner call and we already considered all inner calls*/
    //if(!(last_was_inner_call) && (next_inner_call_seq_num >= cur_psmmry->call_symbolic_replacements.size()))
    if(sf.path_instructions.size() == cur_psmmry->path_instructions.size())
    {
      assert(next_inner_call_seq_num == cur_psmmry->call_symbolic_replacements.size());
      /* The current implementation of backward symbex gives us only one
       * next path summary */
      assert(cur_psmmry->next_path_summaries.size() == 1);
      llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): the last"
                   << " instruction was call instruction to the next call path functions\n";
      cur_psmmry = cur_psmmry->next_path_summaries[0];
    } else /* we (probably (e.g. if not memset)) go inside inner call */
    {
      unsigned cur_inner_call_seq_num = 0;
      if(next_inner_call_seq_num)
        cur_inner_call_seq_num = next_inner_call_seq_num-1;
      llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): the last"
                   << " instruction was call instruction (possibly to inner call with seq_num =  " << cur_inner_call_seq_num << ")\n";


      InnerCall *inner_call = cur_psmmry->get_InnerCall_by_seqnum(cur_inner_call_seq_num);
      /* This call instruction is an inner call that we recorded */
      if(!(inner_call) || inner_call->call_inst != last_callInst)
      {
        llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): the last instruction is not an inner call, i.e."
	             << " we are going inside something linke memset, returning true\n";
        return true;
      }

      llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): inner call indeed\n";
      bool success = false;
      /* In summary executor we intentionally left some inner calls without
       * connected summaries: either such calls had no arguments and return value,
       * or they called blacklisted funcitons (as memset, etc.). */
      if(!inner_call->connected_summaries.size()) 
        success = true;
      llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): inner call has connected summaryes, going to check if we comply with at least one of them\n";
      for(unsigned k = 0; k < inner_call->connected_summaries.size(); k++)
      {
        success = state_complies_with_inner_call_summary(state, inner_call->connected_summaries[k], stack_frame_ndx+1);
	if(success)
	  break;
      }
      llvm::outs() << "ForwardExecutor::state_complies_with_path_candidate(): returning " << (success ? "true" : "false") << "\n";
      return success;
    }
  }
  assert(0 && "This code should be unreachable, you found a bug");
  return true;
}


bool ForwardExecutor::state_complies_with_fsummary(ExecutionState *state)
{
  StackFrame &sf = state->stack.back();
  path_summary_ty *cur_fsummary = sf.cur_fsummary;
  /* The only case when a suppl call's connected fsummary is NULL is
   * when we deliberately decided not to explore it. In this case we
   * do all forking stuff for this function */
  if(!cur_fsummary)
  {
    llvm::outs() << "ForwardExecutor::state_complies_with_fsummary(): cur_fsummary is NULL => returning true\n";
    return true; 
  }
  unsigned index = sf.path_instructions.size() - 1;
  llvm::outs() << "ForwardExecutor::state_complies_with_fsummary(): comparing " << *(sf.path_instructions[index]) <<
                  " and " << *(cur_fsummary->path_instructions[index]) << "\n";
  llvm::outs() << "ForwardExecutor::state_complies_with_fsummary(): this is instruction " << index+1 << " out of " <<
                  cur_fsummary->path_instructions.size() << "\n";
  if(sf.path_instructions[index] == cur_fsummary->path_instructions[index])
  {
    llvm::outs() << "ForwardExecutor::state_complies_with_fsummary(): returning true\n";
    return true;
  }
    llvm::outs() << "ForwardExecutor::state_complies_with_fsummary(): returning false\n";
  return false;
}


/* *** State pruning routines start *** */

/* Check if it is time to do state pruning.
 *
 * First check if the current function is not blacklisted for pruning.
 * Second, check if we are at the start of a basic block in case of BB
 * pruning frequency.
 *
 * @param state Current instruction
 * @return true if it is time to check the current state for duplicates.
 *         false otherwise */
bool ForwardExecutor::isStateMergeTime(KInstruction *ki)
{
	Function * fun = ki->inst->getParent()->getParent();

  /* If the current function is blacklisted, don't do pruning */
	if (mergeBlacklist.find(fun) != mergeBlacklist.end())
  {
		std::string error = "in Blacklisted fun " + fun->getName().str();
		return false;
	}
  
	if (MergeFrequency == InstructionFreq)
		return true;

  /* Get the first instruction of the current basic block */
  llvm::Instruction * instr = ki->inst->getParent()->getFirstNonPHI();
	if ( (MergeFrequency == BBLFreq) && (instr == ki->inst))
  {
    //llvm::outs() << "ForwardExecutor:::isStateMergeTime(): MergeFreq = BBL; we are at the head; returning true\n";
    return true;
  }

  /* IP: do we really need this check? */
	/*if (MergeFrequency =! NeverFreq)
  {
		outs() << "Instruction freq\n";
		klee_error("ERROR");
	}*/

  return false;
}

/* Hardcode some function for which we don't want to do state pruning 
 *
 * Currently we blacklist 'memset()' and 'memcpy()'
 * IP: don't know why, ask Drew Davidson. */
void ForwardExecutor::initializeMergeBlackList()
{
  Module::iterator fEnd = kmodule->module->end();
  for (Module::iterator fItr = kmodule->module->begin(); fItr != fEnd ; ++fItr)
  {
    Function * fun = fItr;
    if (fun->getName() == "memset")
      mergeBlacklist.insert(fun);
    if (fun->getName() == "memcpy")
      mergeBlacklist.insert(fun);
  }
}

/* Check if <state>'s memory configuration conincides with a prevously saved
 * configuration.
 *
 * @param state Check this Execution state
 * @param ki    State's current instruction (TODO: we can extract it from the state)
 * @return True if equivalent memory config is found
 *         False otherwise
 */
bool ForwardExecutor::isDuplicateState(ExecutionState& state, KInstruction *ki)
{
  assert(state.pc && "Instruction pointer cannot be NULL for a state.");
  Instruction * inst = ki->inst;

#if 0
  std::string srcFile = ki->info->file;
  if (srcFile.length() > 42){
  	srcFile = srcFile.substr(42);
  }
  llvm::outs() << "checking duplicates just-before " << *inst << " " 
               << inst->getParent()->getParent()->getName() << "\n"
               << "\t(assembly line: " << ki->info->assemblyLine << ")\n"
               << "\t(source line: " << ki->info->line << " of " 
               << srcFile << ")\n"
               << "\t(id: " << ki->info->id << ")\n";
#endif

	// state.path.push_back(ki);  ---> we will use state.path_instructions

  /*llvm::outs() << "ForwardExecutor::isDuplicateState(): enter checkDuplicateState\n";
  llvm::outs() << "ForwardExecutor::isDuplicateState(): There are " << allSavedConfigs.size() << " indices\n";*/
  
  //state.printRegs();
 
  /* Do we have any saved memory configuration for the current instruction? */
  if (allSavedConfigs.find(inst) == allSavedConfigs.end())
  {
    SavedConfig * savedConfig = new SavedConfig(state);
    ConfList * confList = new ConfList(savedConfig);
    allSavedConfigs[inst] = (confList);
    //llvm::outs() << "ForwardExecutor::isDuplicateState(): No memory config for the current instruction. Adding new memory config.\n";
    return false;
  }

  /* We have saved memory configuration for the current instruction, let's check it
     more detail */
  //llvm::outs() << "ForwardExecutor::isDuplicateState(): Not adding new memory config\n";
  ConfList * confList = allSavedConfigs[inst];
  unsigned points = confList->size();
  //llvm::outs() << "ForwardExecutor::isDuplicateState(): points = " << points << "\n";
  //outs() << "THERE ARE " << points << " states at this idx\n";
  bool prunable;
  //SavedConfig * diff = confList->diff(state, smudge, prunable);
  SavedConfig * diff = confList->diff(state, prunable);

  /* We have matching configuration => we can try to get rid of this state */
  if (prunable)
  {
    llvm::outs() << "actual MERGE SUCCESSFUL\n";
    stats::prunes += 1;

#if 0 /* TODO: Why do we ever need this code below? Just delete it! */
    int count = 0;
    for (std::set<ExecutionState*>::iterator it = states.begin(), ie = states.end(); it != ie; ++it) 
    {
      count++;
    }
    llvm::outs() << "there are (were)" << count << " states\n";
    
    //lineStats[ki]->mergeCount++;
    
    //state.causeOfTermination = "merge";
    
    bool isBBLhead = false;
    llvm::Instruction * instr = ki->inst->getParent()->getFirstNonPHI();
    if (instr == ki->inst){
    	isBBLhead = true;
    }
    
    std::string outStreamBacker;
    raw_string_ostream outStream(outStreamBacker);
    
    outStream << "merge at " << *inst << " " 
    			 << inst->getParent()->getParent()->getName() << "\n"
    			 << "\t(assembly line: " << ki->info->assemblyLine << ")\n"
    			 << "\t(source line: " << ki->info->line << " of " 
    			 << ki->info->file << ")\n"
    			 << "\t(id: " << ki->info->id << ")\n"
    			 << "\tisBBLhead" << isBBLhead << "\n";
    std::string outStreamResult = outStream.str();
    interpreterHandler->getInfoStream() << outStreamResult;
 #endif 
    
    return true;
  }
  //llvm::outs() << "MERGE FAILED\n";
  return false;
} 
/* *** State pruning routines end *** */


/* *** Interrupts routines start *** */

/* Create a new execution state which will start executing interrupt
 * handler <iFun>.
 *
 * Create a new execution state based on <state> which will start
 * executing interrupt handler <iFun> and then return to <state>'s
 * current instruction. 
 *
 * @param state Original state
 * @param iFun Interrupt handler
 * @param ki original state's current instruction
 * @return new execution state which executes iFun
 */
ExecutionState* ForwardExecutor::interruptFork(ExecutionState *state, const Function *iFun, KInstruction *ki)
{
  Function * interruptFun = (Function *)iFun;
  
  //Spawn the new state
  ExecutionState * interruptState = state->branch();
  interruptState->cur_fsummary = NULL;
  //interruptState->parent_id = state->string_id;
  //interruptState->string_id = ++maxId;
  //errs() << "Executor::interruptFork(): State " << state->string_id << " produced fork state ==> " << interruptState->string_id << "\n";
  llvm::outs() << "Executor::interruptFork(): original state " << state << " ==> " << interruptState << " (fork)\n";
  //interruptState->causeOfExistance = std::string("ISR ") + interruptFun->getName().str();
  interruptState->interrupt_depth++;
  assert(interruptState != NULL);
  
  //TODO: fixme and propagate constness throughout
  interruptState->interruptFun = (Function *)interruptFun;
  addedStates.insert(interruptState);
  
  state->ptreeNode->data = 0;
  //std::string split_reason = "interrupt " + interruptFun->getName().str();
  //std::pair<PTree::Node*, PTree::Node*> res =
  //	processTree->split(state->ptreeNode, interruptState, state, split_reason);
  std::pair<PTree::Node*, PTree::Node*> res =
  	processTree->split(state->ptreeNode, interruptState, state);
  interruptState->ptreeNode = res.first;
  state->ptreeNode = res.second;
  
  llvm::outs() << "Spawn interrupt " << interruptFun->getName() << "\n";
  
  /* The use of prevPC actually causes a problem for ESE. If the instruction just
   * executed is a call from A to B, then the end of the interrupt should return to 
   * the beginning of B. However, the interrupt will actually return to the
   * callsite in A, then advance the PC forward so it will work as if the call to
   * B never happened. */
  llvm::outs() << "Function on executeCall " << *ki->inst << "\n";
  KFunction *kf = kmodule->functionMap[interruptFun];
  llvm::outs() << "PC is at\n";
  llvm::outs() << "\t" << *interruptState->pc->inst << "\n";
  llvm::outs() << "\t" << " of function " << interruptState->pc->inst->getParent()->getParent()->getName() << "\n";
  llvm::outs() << "\t" << "prevPC is at\n";
  llvm::outs() << "\t" << *interruptState->prevPC->inst << "\n";
  llvm::outs() << "\t" << "   of function " << interruptState->prevPC->inst->getParent()->getParent()->getName() << "\n";
  
  bool prevOpcode = interruptState->prevPC->inst->getOpcode();
 
  /* Push the correct new stack frame */
  KInstIterator restorePC;
  int blah;
  switch (prevOpcode)
  {
    case Instruction::Call:	
    case Instruction::Ret:	
    case Instruction::Br:
      restorePC = interruptState->pc;
      interruptState->pushFrame(interruptState->prevPC, interruptState->pc, kf);
      break;
    default:
      outs() << "will not restore to special pc\n";
      restorePC = interruptState->prevPC;
      ++restorePC;
      interruptState->pushFrame(interruptState->prevPC, restorePC, kf);
      break;
  }

  /* Set the (NULL) summary for the newly pushed stack frame */
  interruptState->stack.back().cur_fsummary = interruptState->cur_fsummary;
	
  //interruptState->pushFrame(interruptState->prevPC, ++interruptState->prevPC, kf);
  interruptState->pc = kf->instructions;
  llvm::outs() << "setting pc to the isntrs of " << kf->function->getName() << "\n";
  llvm::outs() << "PC is " << *interruptState->pc->inst << "\n";
  return interruptState;
}



/* Try to execute each interrupt handler found in the user's code (e.g.
 * ADC10_ISR)
 *
 * This function iterates over interrupt handlers found in the analyzed
 * program. If interrupt handler's gate function returns true, the
 * state forks and the new state start executing the ISR.
 *
 * @param state Current execution state
 * @param inst State's current instruction
 * @return void
 */ 
void ForwardExecutor::executeInterrupts(ExecutionState * state, KInstruction * inst)
{
  llvm::outs() << "ForwardExecutor::executeInterrupts(): Check Interrupts\n";

  if (state->interruptFun == NULL)
    llvm::outs() << "ForwardExecutor::executeInterrupts(): not currently in interrupt\n";
  else 
  {
    llvm::outs() << "ForwardExecutor::executeInterrupts(): interrupt fun addr "  << state->interruptFun << "\n";
    llvm::outs() << "ForwardExecutor::executeInterrupts(): interrupt fun is " << state->interruptFun->getName() << "\n";
  }

  bool someInterruptOccured = false;
  std::string interruptsFired = "";
  /* Iterate over all interruption handerls found in the user's code.
   * (this list is built in the arch's constructor) */
  InterruptVector::iterator seek = arch->interruptVector.begin();
  InterruptVector::iterator end = arch->interruptVector.end();
  for ( ; seek != end ; ++seek)
  {
    InterruptHandler * handler = *seek;
    llvm::outs() << "ForwardExecutor::executeInterrupts(): check interrupt " << handler->fun->getName() << "\n";
		//if (interruptCondition == NULL)
    if (handler->gate == NULL)
      klee_error("Absentee interrupt condition (probably a bug in the memory layout file)\n");
    assert(handler->fun);
    bool same_interrupt = (handler->fun == state->interruptFun); /* We do not suport nested
                                                                    interrupts of the same kind (e.g. ADC10_ISR from ADC10_ISR)*/
    if(!same_interrupt && (handler->gate(arch, state, solver)) ) /* This checks status register and periph registers
                                                            flags (e.g. GIE flag, ADC10IE flag, etc) */
    {
      someInterruptOccured = true;
      //const Function *isr = handler->fun;
      //interruptsFired += std::string(llvm::utostr(maxId + 1)) + " : " + isr->getName().str() + "\n";
      ExecutionState *interrupt_state = interruptFork(state, handler->fun, inst);
      int max_interrupt_depth = 17; /* I love magic numbers */
      if(interrupt_state->interrupt_depth >= max_interrupt_depth)
      {
        llvm::outs() << "ForwardExecutor::executeInterrupts(): Killing "
                     << "the interrupt_state: too many interrupts: "
                     << interrupt_state->interrupt_depth << "\n";
        terminateStateEarly(*interrupt_state, "Max interrupt depth reached.");
      }
      //++stats::firedInterruptions;
    }
  }
  if (someInterruptOccured)
  {
    //std::string reason = std::string("ISR\n") + interruptsFired;
    //state->treeDump(*mergeTree, reason);
    state->path_instructions.clear();
    //state->parent_id = state->string_id;
    //state->string_id = ++maxId;
    //state->causeOfExistance = "no ISR";
    llvm::outs() << "IVAN: State " << state << " produced an interruptFork and will be terminated\n";
    //llvm::outs() << "STATE: ~" << state->string_id << " (no fork)\n";
    //errs() << "IVAN: State " << state->string_id << " gave life to an interrupt and will be terminated\n";
    terminateStateEarly(*state, "Produced interrupt.");
    //errs() << "stats::forks = " << stats::forks << "\n";
    //errs() << "depth" << state->depth << "\n";
    //errs() << " ** There are " << states.size() << " states remaining\n";
  }
  //errs() << "end Check Interrupt\n";
}


/* *** Interrupts routines end *** */


/* dev_note: remember that <cs> is still in the previous state
 * at the call instruction, so we need to run executeCall() on it before
 * adding to addedStates */
void ForwardExecutor::prepare_crossroad_state(ExecutionState &state)
{
    /* This is copied from executionInstruction(): Call */
    KInstruction *ki = state.prevPC;
    Instruction *i = ki->inst;
    CallSite cs(i);

    unsigned numArgs = cs.arg_size();
    Value *fp = cs.getCalledValue();
    Function *f = getTargetFunction(fp, state);

    // evaluate arguments
    std::vector< ref<Expr> > arguments;
    arguments.reserve(numArgs);

    for (unsigned j=0; j<numArgs; ++j)
      arguments.push_back(eval(ki, j+1, state).value);

    llvm::outs() << "ForwardExecutor::prepare_crossroad_state(): running executeCall on " << &state << "\n";
    executeCall(state, ki, f, arguments);
}

/* Take the last added crossrad state, update it's current summary
 * with constraints, with the next state, update its inner calls; add
 * it to <addedStates>; dev_note: remember that <cs> is still in the previous state
 * at the call instruction */
ExecutionState* ForwardExecutor::get_next_crossroad_state()
{
  //llvm::outs() << "ForwardExecutor::get_next_crossroad_state(): inside; returning NULL\n";
  //return NULL;
  if(crossroad_states.empty())
  {
    llvm::outs() << "ForwardExecutor::get_next_crossroad_state(): inside; no states\n";
    return NULL;
  }

  ExecutionState *cs = crossroad_states.back();
  crossroad_states.pop_back();
  llvm::outs() << "ForwardExecutor::get_next_crossroad_state(): retring cs = " << cs << " (" 
               << crossroad_states.size() << " left)\n";
  return cs;

#if 0
  llvm::outs() << "ForwardExecutor::get_next_crossroad_state(): inside; cs = " << cs << "\n";

  ExecutionState *ns = cs->branch();

    std::pair<PTree::Node*,PTree::Node*> res = 
      processTree->split(cs->ptreeNode, ns, cs);
    ns->ptreeNode = res.first;
    cs->ptreeNode = res.second;


  ns->cur_fsummary->clear_connected_summaries_for_inner_calls();
  ns->cur_fsummary->update_InnerCalls_with_constraints2(*(cs->next_fsummary));
  int is_inner_calls_connected = interpreter_manager->run_inner_calls(*(ns->cur_fsummary)); /* It will not recollect path summaries, but will re-use existing ones */
  assert(is_inner_calls_connected && "no inner calls for already glued path summary: it's a bug!");

  /* Advance next path summary for the crossroad states; or delete it if
   * there are not more next path summaries */
  std::vector<path_summary_ty *>::iterator it;
  it = std::find(cs->cur_fsummary->next_path_summaries.begin(),
                 cs->cur_fsummary->next_path_summaries.end(), cs->next_fsummary);
  assert(it != cs->cur_fsummary->next_path_summaries.end());
  unsigned idx = std::distance(cs->cur_fsummary->next_path_summaries.begin(), it);
  unsigned N = cs->cur_fsummary->next_path_summaries.size();
  if((idx+1) < N)
  {
    llvm::outs() << "ForwardExecutor::get_next_crossroad_state(): advancing " << cs << "\n";
    cs->next_fsummary = cs->cur_fsummary->next_path_summaries[idx+1];
  }
  else
  {
    llvm::outs() << "ForwardExecutor::get_next_crossroad_state(): deleting " << cs << "\n";
    crossroad_states.pop_back();
  }

  llvm::outs() << "ForwardExecutor::get_next_crossroad_state(): current index for next summary is " 
               << idx << "\n";
  llvm::outs() << "ForwardExecutor::get_next_crossroad_state(): cur_fsummary is for " 
               << cs->cur_fsummary->fn->getName() << " next_fsummar is for "
               << cs->next_fsummary->fn->getName() << "\n";

  return ns;
#endif
}



void ForwardExecutor::run(ExecutionState &initialState) {
  bindModuleConstants();

  // Delay init till now so that ticks don't accrue during
  // optimization and such.
  //initTimers();

  llvm::Function *start_func = initialState.pc->inst->getParent()->getParent();
  assert(states.empty() && "states should be empty at this point, did you execute this function for the second time while not finishgin the first run?");
  states.insert(&initialState);
  path_summary_ty *candidate_path = initialState.cur_fsummary;

#if 0 /* FIXME: We switch off seeds for now, should switch them back in the next versions */
  if (usingSeeds) {
    std::vector<SeedInfo> &v = seedMap[&initialState];
    
    for (std::vector<KTest*>::const_iterator it = usingSeeds->begin(), 
           ie = usingSeeds->end(); it != ie; ++it)
      v.push_back(SeedInfo(*it));

    int lastNumSeeds = usingSeeds->size()+10;
    double lastTime, startTime = lastTime = util::getWallTime();
    ExecutionState *lastState = 0;
    while (!seedMap.empty()) {
      if (haltExecution) goto dump;

      std::map<ExecutionState*, std::vector<SeedInfo> >::iterator it = 
        seedMap.upper_bound(lastState);
      if (it == seedMap.end())
        it = seedMap.begin();
      lastState = it->first;
      unsigned numSeeds = it->second.size();
      ExecutionState &state = *lastState;
      KInstruction *ki = state.pc;
      stepInstruction(state);

      executeInstruction(state, ki);
      processTimers(&state, MaxInstructionTime * numSeeds);
      updateStates(&state);

      if ((stats::instructions % 1000) == 0) {
        int numSeeds = 0, numStates = 0;
        for (std::map<ExecutionState*, std::vector<SeedInfo> >::iterator
               it = seedMap.begin(), ie = seedMap.end();
             it != ie; ++it) {
          numSeeds += it->second.size();
          numStates++;
        }
        double time = util::getWallTime();
        if (SeedTime>0. && time > startTime + SeedTime) {
          klee_warning("seed time expired, %d seeds remain over %d states",
                       numSeeds, numStates);
          break;
        } else if (numSeeds<=lastNumSeeds-10 ||
                   time >= lastTime+10) {
          lastTime = time;
          lastNumSeeds = numSeeds;          
          klee_message("%d seeds remaining over: %d states", 
                       numSeeds, numStates);
        }
      }
    }

    klee_message("seeding done (%d states remain)", (int) states.size());

    // XXX total hack, just because I like non uniform better but want
    // seed results to be equally weighted.
    for (std::set<ExecutionState*>::iterator
           it = states.begin(), ie = states.end();
         it != ie; ++it) {
      (*it)->weight = 1.;
    }

    if (OnlySeed)
      goto dump;
  }
#endif

  llvm::outs() << "ForwardExecutor::run(): constructing searcher...\n";
  searcher = constructUserSearcher(*this);
  llvm::outs() << "ForwardExecutor::run(): searcher constructed...\n";
  searcher->update(0, states, std::set<ExecutionState*>());
  searcher->no_good_states = false; 
  //searcher->setPathManager(path_manager);
  //searcher->slave_search_freq = 0.00;// 0% (i.e. never do slave (random path) search) //rand_search_freq; 
  //searcher->prefer_short_summaries = true;

  haltExecution = 0;
  while (!states.empty() && !haltExecution) {
    ExecutionState &state = searcher->selectState();
    //llvm::outs() << "Selected state " << &state << " (pathDeviationDepth = " << state.pathDeviationDepth << ")\n\n";

    //llvm::outs() << "ForwardExecutor::run(): inside main loop\n";
    llvm::outs() << "\n\n == Selected state " << &state << "(in function " 
                 << state.pc->inst->getParent()->getParent()->getName() 
		 << "() ); number of states = " << states.size() << "\n";
    llvm::outs() << " == instsruction " << *state.pc->inst << "\n";
#if 0
    std::string constraints;
    getConstraintLog(state, constraints, KQUERY);
    llvm::outs() << "                           constraints for the state: \n" << constraints;
#endif

    KInstruction *ki = state.pc;

    /// IVAN ADDITIONS BEGIN
    Instruction *instr = ki->inst;
    std::string instr_str;
    raw_string_ostream str_stream(instr_str);                                 
    str_stream << *instr;
    state.path_choices_debug.push_back(instr_str);
    state.path_instructions.push_back(instr);
    state.stack.back().path_instructions.push_back(instr);

    if (false && isStateMergeTime(ki) && isDuplicateState(state, ki))
    {
      terminateState(state);
      llvm::outs() << "ForwardExecutor::run(): terminate STATE\n"; 
    } 
    

    if(state.cur_fsummary == NULL)
       llvm::outs() << "ForwardExecutor::run(): cur_fsummry = NULL!\n";

    //bool complies1 = state_complies_with_path_candidate(&state, candidate_path);
    bool complies2 = state_complies_with_fsummary(&state);
    //if(complies1 != complies2)
    //  exit(0);

    //if(!state_complies_with_fsummary(&state))
    if(!complies2)
    {
      llvm::outs() << "ForwardExecutor::run(): state does now comply with the current fsummary during"
                      " the forward symbex!\n";
      terminateStateEarly(state, "does not comply with fsummary.");
      updateStates(&state);
      continue;
    }
     
    stepInstruction(state);
    executeInstruction(state, ki);

    executeInterrupts(&state, ki);

    //processTimers(&state, MaxInstructionTime);

    if (MaxMemory) {
      if ((stats::instructions & 0xFFFF) == 0) {
        // We need to avoid calling GetMallocUsage() often because it
        // is O(elts on freelist). This is really bad since we start
        // to pummel the freelist once we hit the memory cap.
        unsigned mbs = util::GetTotalMallocUsage() >> 20;
        if (mbs > MaxMemory) {
          if (mbs > MaxMemory + 100) {
            // just guess at how many to kill
            unsigned numStates = states.size();
            unsigned toKill = std::max(1U, numStates - numStates*MaxMemory/mbs);

            klee_warning("killing %d states (over memory cap)", toKill);

            std::vector<ExecutionState*> arr(states.begin(), states.end());
            for (unsigned i=0,N=arr.size(); N && i<toKill; ++i,--N) {
              unsigned idx = rand() % N;

              // Make two pulls to try and not hit a state that
              // covered new code.
              if (arr[idx]->coveredNew)
                idx = rand() % N;

              std::swap(arr[idx], arr[N-1]);
              terminateStateEarly(*arr[N-1], "Memory limit exceeded.");
            }
          }
          atMemoryLimit = true;
        } else {
          atMemoryLimit = false;
        }
      }
    }

    updateStates(&state);
    /* If states are empty, add crossroad saved states */
  }
  if(states.empty())
    llvm::outs() << "ForwardExecutor::run(): states are empty, finishing\n";
  //if(states.empty())
  //  should_collect_more_summaries = false;
  delete searcher;
  searcher = 0;
  
 dump:
  if (DumpStatesOnHalt && !states.empty()) {
    llvm::errs() << "KLEE: halting execution, dumping remaining states\n";
    for (std::set<ExecutionState*>::iterator
           it = states.begin(), ie = states.end();
         it != ie; ++it) {
      ExecutionState &state = **it;
      stepInstruction(state); // keep stats rolling
      terminateStateEarly(state, "Execution halting.");
    }
    updateStates(0);
  }
}

std::string ForwardExecutor::getAddressInfo(ExecutionState &state, 
                                     ref<Expr> address) const{
  std::string Str;
  llvm::raw_string_ostream info(Str);
  info << "\taddress: " << address << "\n";
  uint64_t example;
  if (ConstantExpr *CE = dyn_cast<ConstantExpr>(address)) {
    example = CE->getZExtValue();
  } else {
    ref<ConstantExpr> value;
    bool success = solver->getValue(state, address, value);
    assert(success && "FIXME: Unhandled solver failure");
    (void) success;
    example = value->getZExtValue();
    info << "\texample: " << example << "\n";
    std::pair< ref<Expr>, ref<Expr> > res = solver->getRange(state, address);
    info << "\trange: [" << res.first << ", " << res.second <<"]\n";
  }
  
  MemoryObject hack((unsigned) example);    
  MemoryMap::iterator lower = state.addressSpace.objects.upper_bound(&hack);
  info << "\tnext: ";
  if (lower==state.addressSpace.objects.end()) {
    info << "none\n";
  } else {
    const MemoryObject *mo = lower->first;
    std::string alloc_info;
    mo->getAllocInfo(alloc_info);
    info << "object at " << mo->guest_address
         << " of size " << mo->size << "\n"
         << "\t\t" << alloc_info << "\n";
  }
  if (lower!=state.addressSpace.objects.begin()) {
    --lower;
    info << "\tprev: ";
    if (lower==state.addressSpace.objects.end()) {
      info << "none\n";
    } else {
      const MemoryObject *mo = lower->first;
      std::string alloc_info;
      mo->getAllocInfo(alloc_info);
      info << "object at " << mo->guest_address 
           << " of size " << mo->size << "\n"
           << "\t\t" << alloc_info << "\n";
    }
  }

  return info.str();
}

void ForwardExecutor::terminateState(ExecutionState &state) {
  if (replayOut && replayPosition!=replayOut->numObjects) {
    klee_warning_once(replayOut, 
                      "replay did not consume all objects in test input.");
  }

  //interpreterHandler->incPathsExplored();

  std::set<ExecutionState*>::iterator it = addedStates.find(&state);
  if (it==addedStates.end()) {
    state.pc = state.prevPC;

    removedStates.insert(&state);
  } else {
    // never reached searcher, just delete immediately
    std::map< ExecutionState*, std::vector<SeedInfo> >::iterator it3 = 
      seedMap.find(&state);
    if (it3 != seedMap.end())
      seedMap.erase(it3);
    addedStates.erase(it);
    processTree->remove(state.ptreeNode);
    delete &state;
  }
}

void ForwardExecutor::terminateStateEarly(ExecutionState &state, 
                                   const Twine &message) {
#if 0 /* We don't have interpreter handler in Summary Executor */
  if (!OnlyOutputStatesCoveringNew || state.coveredNew ||
      (AlwaysOutputSeeds && seedMap.count(&state)))
    interpreterHandler->processTestCase(state, (message + "\n").str().c_str(),
                                        "early");
#endif
  terminateState(state);
}

void ForwardExecutor::terminateStateOnExit(ExecutionState &state) {
  //llvm::outs() << "terminateStateOnExit(): interpreterHandler = " << interpreterHandler << "\n";
  if (!OnlyOutputStatesCoveringNew || state.coveredNew || 
      (AlwaysOutputSeeds && seedMap.count(&state)))
  {
    llvm::outs() << "terminateStateOnExit(): going inside  interpreterHandler->processTestCase()\n";
    //interpreterHandler->processTestCase(state, 0, 0);
  }
  llvm::outs() << "terminateStateOnExit(): going inside terminateState()\n";
  terminateState(state);
}

const InstructionInfo & ForwardExecutor::getLastNonKleeInternalInstruction(const ExecutionState &state,
    Instruction ** lastInstruction) {
  // unroll the stack of the applications state and find
  // the last instruction which is not inside a KLEE internal function
  ExecutionState::stack_ty::const_reverse_iterator it = state.stack.rbegin(),
      itE = state.stack.rend();

  // don't check beyond the outermost function (i.e. main())
  itE--;

  const InstructionInfo * ii = 0;
  if (kmodule->internalFunctions.count(it->kf->function) == 0){
    ii =  state.prevPC->info;
    *lastInstruction = state.prevPC->inst;
    //  Cannot return yet because even though
    //  it->function is not an internal function it might of
    //  been called from an internal function.
  }

  // Wind up the stack and check if we are in a KLEE internal function.
  // We visit the entire stack because we want to return a CallInstruction
  // that was not reached via any KLEE internal functions.
  for (;it != itE; ++it) {
    // check calling instruction and if it is contained in a KLEE internal function
    const Function * f = (*it->caller).inst->getParent()->getParent();
    if (kmodule->internalFunctions.count(f)){
      ii = 0;
      continue;
    }
    if (!ii){
      ii = (*it->caller).info;
      *lastInstruction = (*it->caller).inst;
    }
  }

  if (!ii) {
    // something went wrong, play safe and return the current instruction info
    *lastInstruction = state.prevPC->inst;
    return *state.prevPC->info;
  }
  return *ii;
}
void ForwardExecutor::terminateStateOnError(ExecutionState &state,
                                     const llvm::Twine &messaget,
                                     const char *suffix,
                                     const llvm::Twine &info) {
  std::string message = messaget.str();
  static std::set< std::pair<Instruction*, std::string> > emittedErrors;
  Instruction * lastInst;
  const InstructionInfo &ii = getLastNonKleeInternalInstruction(state, &lastInst);
  
  if (EmitAllErrors ||
      emittedErrors.insert(std::make_pair(lastInst, message)).second) {
    if (ii.file != "") {
      klee_message("ERROR: %s:%d: %s", ii.file.c_str(), ii.line, message.c_str());
    } else {
      klee_message("ERROR: (location information missing) %s", message.c_str());
    }
    if (!EmitAllErrors)
      klee_message("NOTE: now ignoring this error at this location");

    std::string MsgString;
    llvm::raw_string_ostream msg(MsgString);
    msg << "Error: " << message << "\n";
    if (ii.file != "") {
      msg << "File: " << ii.file << "\n";
      msg << "Line: " << ii.line << "\n";
      msg << "assembly.ll line: " << ii.assemblyLine << "\n";
    }
    msg << "Stack: \n";
    state.dumpStack(msg);

    std::string info_str = info.str();
    if (info_str != "")
      msg << "Info: \n" << info_str;

    //interpreterHandler->processTestCase(state, msg.str().c_str(), suffix);
  }
    
  terminateState(state);
}

// XXX shoot me
static const char *okExternalsList[] = { "printf", 
                                         "fprintf", 
                                         "puts",
                                         "getpid" };
static std::set<std::string> okExternals(okExternalsList,
                                         okExternalsList + 
                                         (sizeof(okExternalsList)/sizeof(okExternalsList[0])));

void ForwardExecutor::callExternalFunction(ExecutionState &state,
                                    KInstruction *target,
                                    Function *function,
                                    std::vector< ref<Expr> > &arguments) {
  // check if specialFunctionHandler wants it
  if (specialFunctionHandler->handle(state, function, target, arguments))
    return;
  llvm::outs() << "DEBUG: passed over special function handler\n";
  
  if (NoExternals && !okExternals.count(function->getName())) {
    llvm::errs() << "KLEE:ERROR: Calling not-OK external function : "
                 << function->getName().str() << "\n";
    terminateStateOnError(state, "externals disallowed", "user.err");
    return;
  }

  // normal external function handling path
  // allocate 128 bits for each argument (+return value) to support fp80's;
  // we could iterate through all the arguments first and determine the exact
  // size we need, but this is faster, and the memory usage isn't significant.
  uint64_t *args = (uint64_t*) alloca(2*sizeof(*args) * (arguments.size() + 1));
  memset(args, 0, 2 * sizeof(*args) * (arguments.size() + 1));
  unsigned wordIndex = 2;
  for (std::vector<ref<Expr> >::iterator ai = arguments.begin(), 
       ae = arguments.end(); ai!=ae; ++ai) {
    if (AllowExternalSymCalls) { // don't bother checking uniqueness
      ref<ConstantExpr> ce;
      bool success = solver->getValue(state, *ai, ce);
      assert(success && "FIXME: Unhandled solver failure");
      (void) success;
      ce->toMemory(&args[wordIndex]);
      wordIndex += (ce->getWidth()+63)/64;
    } else {
      ref<Expr> arg = toUnique(state, *ai);
      if (ConstantExpr *ce = dyn_cast<ConstantExpr>(arg)) {
        // XXX kick toMemory functions from here
        ce->toMemory(&args[wordIndex]);
        wordIndex += (ce->getWidth()+63)/64;
      } else {
        terminateStateOnExecError(state, 
                                  "external call with symbolic argument: " + 
                                  function->getName());
        return;
      }
    }
  }

  state.addressSpace.copyOutConcretes();

  if (!SuppressExternalWarnings) {

    std::string TmpStr;
    llvm::raw_string_ostream os(TmpStr);
    os << "calling external: " << function->getName().str() << "(";
    for (unsigned i=0; i<arguments.size(); i++) {
      os << arguments[i];
      if (i != arguments.size()-1)
	os << ", ";
    }
    os << ")";
    
    if (AllExternalWarnings)
      klee_warning("%s", os.str().c_str());
    else
      klee_warning_once(function, "%s", os.str().c_str());
  }
  
  bool success = externalDispatcher->executeCall(function, target->inst, args);
  if (!success) {
    terminateStateOnError(state, "failed external call: " + function->getName(),
                          "external.err");
    return;
  }

  if (!state.addressSpace.copyInConcretes()) {
    terminateStateOnError(state, "external modified read-only object",
                          "external.err");
    return;
  }

  LLVM_TYPE_Q Type *resultType = target->inst->getType();
  if (resultType != Type::getVoidTy(getGlobalContext())) {
    ref<Expr> e = ConstantExpr::fromMemory((void*) args, 
                                           getWidthForLLVMType(resultType));
    bindLocal(target, state, e);
  }
}

/***/

ref<Expr> ForwardExecutor::replaceReadWithSymbolic(ExecutionState &state, 
                                            ref<Expr> e) 
{
  return e;
#if 0 /* IVAN: No supported yet */
  unsigned n = interpreterOpts.MakeConcreteSymbolic;
  if (!n || replayOut || replayPath)
    return e;

  // right now, we don't replace symbolics (is there any reason to?)
  if (!isa<ConstantExpr>(e))
    return e;

  if (n != 1 && random() % n)
    return e;

  // create a new fresh location, assert it is equal to concrete value in e
  // and return it.
  
  static unsigned id;
  const Array *array = Array::CreateArray("rrws_arr" + llvm::utostr(++id),
					  Expr::getMinBytesForWidth(e->getWidth()));
  ref<Expr> res = Expr::createTempRead(array, e->getWidth());
  ref<Expr> eq = NotOptimizedExpr::create(EqExpr::create(e, res));
  llvm::errs() << "Making symbolic: " << eq << "\n";
  state.addConstraint(eq);
  return res;
#endif
}



/* Allocate new memory with malloc. Find a free memory chunk of size
 * <size> in the state's address space and mark it reserved.
 *
 * We first use malloc() to allocate the memory on the host (this is the
 * where we will actually store the data). We then need to map this
 * memory on the guest: we iterate over state->addressSpace.objects
 * guest_addresses and try to find a free memory region of size bigger
 * then <size> We don't differentiate between the heap and the stack: we
 * put everything into one big chunk 
 *
 * @param size Size of the new memory to allcoate
 * @param state The state Address Space of which we consider
 *
 * @return pointer to the start of available memory address on the guest
 */
uint64_t ForwardExecutor::get_free_memchunk_at_guest(unsigned size, ExecutionState *state) 
{
  if (size>10*1024*1024)
  {
    klee_warning_once(0, "failing large alloc: %u bytes", (unsigned) size);
    return 0;
  }
  
  uint16_t heap_min = 0x8000;
  assert(state);

#if 0
  llvm::outs() << " working with state "  << state << "\n";
  llvm::outs() << " Allocation memory max is " << arch->memory_size - 1 << "\n";
  llvm::outs() << " Attempting allocation of " << size << "\n";
#endif

  /* Now we need to find a free memory chunk at the guest
   * Note that state->addressSpace.objects is a map of memory objects 
   * sorted by guest_address (see AddressSpace.h) */
  MemoryMap::iterator obj_begin = state->addressSpace.objects.begin();
  MemoryMap::iterator obj_end = state->addressSpace.objects.end();
  unsigned prev_begin = 0;
  unsigned cur_end = 0;
  //llvm::outs() << " Going to allocate" <<
  //  " space for a new object of size " << size << ". " <<
  //  "state->addressSpace.objects.size() = " <<
  //  state->addressSpace.objects.size() << "\n";
  uint64_t guest_address;
  bool first = false;

  /* If we don't have any objects yet, reserve space at the
   * highest memory address */
  if (obj_begin == obj_end) 
  {
    guest_address = arch->memory_size - 1 - size;
    //std::cout << " This is the first memory object. guest addr: "  << guest_address << "\n";
    //std::cout << " arch->memory_size =  "  << arch->memory_size << "\n";
    first = true;
  }
  /* Else iterate through objects from the end: i.e from highest to lowest memory address */
  else 
  {
    const MemoryObject *obj = NULL;
    --obj_end; // Now it points to the latest object (at highest memory location)
    obj = obj_end->first;
    prev_begin = obj->guest_address;
    //llvm::outs() << " We have object at [" << obj->guest_address << "-" << obj->guest_address + obj->size << "]\n";
    while (obj_begin != obj_end)
    {
      --obj_end; // Going from the end
      obj = obj_end->first;
      //const MemoryObject *obj = obj_end->first;
      cur_end = obj->guest_address + obj->size;

      //llvm::outs() << " We have object at [" << obj->guest_address << "-" << obj->guest_address + obj->size << "]\n";
      //llvm::outs() << " cur end " << cur_end << " prev begin " << prev_begin << "\n";

      if ( (prev_begin - size >= cur_end) && (cur_end + size < arch->memory_size) )
      {
        guest_address = prev_begin - size;
        //llvm::outs() << " There was an appropriate memory gap\n";
	  		//llvm::outs() << " updated address is " << guest_address << "\n";
        break;
      } 
      prev_begin = obj->guest_address;
    }
  }

  /* We reached the wilderness */
  if (!first && obj_begin == obj_end)
  {
    //llvm::outs() << " extending guest memory past the last object\n";
    guest_address = prev_begin - size;
  }

  llvm::outs() << " Found apporpriate memory chunk:  ++ [" << guest_address << " - " << guest_address+size << "]\n";

  if (guest_address < 1000)
    llvm::outs() << "MemoryManager::allocate_guest(): Guest address seems to be too low\n";

  return guest_address;
}

ObjectState *ForwardExecutor::bindObjectInState(ExecutionState &state, 
                                         const MemoryObject *mo,
                                         bool isLocal,
                                         const Array *array) {
  /// IVAN ADDITIONS BEGIN
  /* <guest_address> is set in case the memory object was allocated with allocateFixed(),
   * it is 0 otherwise */
  if(!(mo->guest_address))
    ((MemoryObject *)mo)->guest_address = get_free_memchunk_at_guest(mo->size, &state);
  /// IVAN ADDITIONS END
  
  ObjectState *os = array ? new ObjectState(mo, array) : new ObjectState(mo);
  state.addressSpace.bindObject(mo, os);

  // Its possible that multiple bindings of the same mo in the state
  // will put multiple copies on this list, but it doesn't really
  // matter because all we use this list for is to unbind the object
  // on function return.
  if (isLocal)
    state.stack.back().allocas.push_back(mo);

  return os;
}

void ForwardExecutor::executeAlloc(ExecutionState &state,
                            ref<Expr> size,
                            bool isLocal,
                            KInstruction *target,
                            bool zeroMemory,
                            const ObjectState *reallocFrom) {
  size = toUnique(state, size);
  if (ConstantExpr *CE = dyn_cast<ConstantExpr>(size)) {
    MemoryObject *mo = memory->allocate(CE->getZExtValue(), isLocal, false, 
                                        state.prevPC->inst);
    if (!mo) {
      bindLocal(target, state, 
                ConstantExpr::alloc(0, Context::get().getPointerWidth()));
    } else {
      ObjectState *os = bindObjectInState(state, mo, isLocal);
      if (zeroMemory) {
        os->initializeToZero();
      } else {
        os->initializeToRandom();
      }
      bindLocal(target, state, mo->getBaseExpr());
      
      if (reallocFrom) {
        unsigned count = std::min(reallocFrom->size, os->size);
        for (unsigned i=0; i<count; i++)
          os->write(i, reallocFrom->read8(i));
        state.addressSpace.unbindObject(reallocFrom->getObject());
      }
    }
  } else {
    // XXX For now we just pick a size. Ideally we would support
    // symbolic sizes fully but even if we don't it would be better to
    // "smartly" pick a value, for example we could fork and pick the
    // min and max values and perhaps some intermediate (reasonable
    // value).
    // 
    // It would also be nice to recognize the case when size has
    // exactly two values and just fork (but we need to get rid of
    // return argument first). This shows up in pcre when llvm
    // collapses the size expression with a select.

    ref<ConstantExpr> example;
    bool success = solver->getValue(state, size, example);
    assert(success && "FIXME: Unhandled solver failure");
    (void) success;
    
    // Try and start with a small example.
    Expr::Width W = example->getWidth();
    while (example->Ugt(ConstantExpr::alloc(128, W))->isTrue()) {
      ref<ConstantExpr> tmp = example->LShr(ConstantExpr::alloc(1, W));
      bool res;
      bool success = solver->mayBeTrue(state, EqExpr::create(tmp, size), res);
      assert(success && "FIXME: Unhandled solver failure");      
      (void) success;
      if (!res)
        break;
      example = tmp;
    }

    StatePair fixedSize = fork(state, EqExpr::create(example, size), true);
    
    if (fixedSize.second) { 
      // Check for exactly two values
      ref<ConstantExpr> tmp;
      bool success = solver->getValue(*fixedSize.second, size, tmp);
      assert(success && "FIXME: Unhandled solver failure");      
      (void) success;
      bool res;
      success = solver->mustBeTrue(*fixedSize.second, 
                                   EqExpr::create(tmp, size),
                                   res);
      assert(success && "FIXME: Unhandled solver failure");      
      (void) success;
      if (res) {
        executeAlloc(*fixedSize.second, tmp, isLocal,
                     target, zeroMemory, reallocFrom);
      } else {
        // See if a *really* big value is possible. If so assume
        // malloc will fail for it, so lets fork and return 0.
        StatePair hugeSize = 
          fork(*fixedSize.second, 
               UltExpr::create(ConstantExpr::alloc(1<<31, W), size), 
               true);
        if (hugeSize.first) {
          klee_message("NOTE: found huge malloc, returning 0");
          bindLocal(target, *hugeSize.first, 
                    ConstantExpr::alloc(0, Context::get().getPointerWidth()));
        }
        
        if (hugeSize.second) {

          std::string Str;
          llvm::raw_string_ostream info(Str);
          ExprPPrinter::printOne(info, "  size expr", size);
          info << "  concretization : " << example << "\n";
          info << "  unbound example: " << tmp << "\n";
          terminateStateOnError(*hugeSize.second, 
                                "concretized symbolic size", 
                                "model.err", 
                                info.str());
        }
      }
    }

    if (fixedSize.first) // can be zero when fork fails
      executeAlloc(*fixedSize.first, example, isLocal, 
                   target, zeroMemory, reallocFrom);
  }
}

void ForwardExecutor::executeFree(ExecutionState &state,
                           ref<Expr> address,
                           KInstruction *target) {
  StatePair zeroPointer = fork(state, Expr::createIsZero(address), true);
  if (zeroPointer.first) {
    if (target)
      bindLocal(target, *zeroPointer.first, Expr::createPointer(0));
  }
  if (zeroPointer.second) { // address != 0
    ExactResolutionList rl;
    resolveExact(*zeroPointer.second, address, rl, "free");
    
    for (ForwardExecutor::ExactResolutionList::iterator it = rl.begin(), 
           ie = rl.end(); it != ie; ++it) {
      const MemoryObject *mo = it->first.first;
      if (mo->isLocal) {
        terminateStateOnError(*it->second, 
                              "free of alloca", 
                              "free.err",
                              getAddressInfo(*it->second, address));
      } else if (mo->isGlobal) {
        terminateStateOnError(*it->second, 
                              "free of global", 
                              "free.err",
                              getAddressInfo(*it->second, address));
      } else {
        it->second->addressSpace.unbindObject(mo);
        if (target)
          bindLocal(target, *it->second, Expr::createPointer(0));
      }
    }
  }
}

void ForwardExecutor::resolveExact(ExecutionState &state,
                            ref<Expr> p,
                            ExactResolutionList &results, 
                            const std::string &name) {
  // XXX we may want to be capping this?
  ResolutionList rl;
  state.addressSpace.resolve(state, solver, p, rl);
  
  ExecutionState *unbound = &state;
  for (ResolutionList::iterator it = rl.begin(), ie = rl.end(); 
       it != ie; ++it) {
    ref<Expr> inBounds = EqExpr::create(p, it->first->getBaseExpr());
    
    StatePair branches = fork(*unbound, inBounds, true);
    
    if (branches.first)
      results.push_back(std::make_pair(*it, branches.first));

    unbound = branches.second;
    if (!unbound) // Fork failure
      break;
  }

  if (unbound) {
    terminateStateOnError(*unbound,
                          "memory error: invalid pointer: " + name,
                          "ptr.err",
                          getAddressInfo(*unbound, p));
  }
}

void ForwardExecutor::executeMemoryOperation(ExecutionState &state,
                                      bool isWrite,
                                      ref<Expr> address,
                                      ref<Expr> value /* undef if read */,
                                      KInstruction *target /* undef if write */) {
  llvm::outs() << "ForwardExecutor::executeMemoryOperation() :: inside\n";
  Expr::Width type = (isWrite ? value->getWidth() : 
                     getWidthForLLVMType(target->inst->getType()));
  unsigned bytes = Expr::getMinBytesForWidth(type);

  if (SimplifySymIndices) {
    if (!isa<ConstantExpr>(address))
      address = state.constraints.simplifyExpr(address);
    if (isWrite && !isa<ConstantExpr>(value))
      value = state.constraints.simplifyExpr(value);
  }

  // fast path: single in-bounds resolution
  ObjectPair op;
  bool success;
  solver->setTimeout(coreSolverTimeout);
  llvm::outs() << "ForwardExecutor::executeMemoryOperation() :: Going inside resolveOne()\n";
  if (!state.addressSpace.resolveOne(state, solver, address, op, success)) {
    address = toConstant(state, address, "resolveOne failure");
    success = state.addressSpace.resolveOne(cast<ConstantExpr>(address), op);
  }
  solver->setTimeout(0);
  llvm::outs() << "ForwardExecutor::executeMemoryOperation() :: returned from resolveOne()\n";

  if (success) {
    llvm::outs() << "ForwardExecutor::executeMemoryOperation() :: sucess = true\n";


    /// IVAN ADDITIONS BEGIN We replaced this code with more general Drew's code
    #if 0
    if(target)
    {
      LoadInst *load_inst = dyn_cast<LoadInst>(target->inst);
      if(load_inst)
      {
        llvm::Value *val = load_inst->getPointerOperand();
        llvm::outs() << "ForwardExecutor::executeMemoryOperation():: load operand = : " << val->getName() << "\n";
        if(val->getName().str() == "ADC10MEM0")
        {
          static unsigned id = 0;
          unsigned w = 16;
          //unsigned w = 10;
          const Array *array = Array::CreateArray(val->getName().str() + "_" + llvm::utostr(id), Expr::getMinBytesForWidth(w) );
          id++;
          ref<Expr> result = Expr::createTempRead(array, w);
          llvm::outs() << "ForwardExecutor::executeInstruction():Load: replacing 'ADC10MEM0' with a new symbolic variable.\n";
				  bindLocal(target, state, result); // LLVM always loads things into local registers
          
          /* FIXME: Hack, ADC10 is 10 bits, and we cannot create TempRead's with 10 bits, so just add
           * a constraint < 1024 */
          llvm::outs() << "ForwardExecutor::executeInstruction():Load: hack: adding constraint to the state ADC10MEM0 < 1024.\n";
          ref<Expr> const_1024 =  ConstantExpr::create(1024, Expr::Int16);
          ref<Expr> ult_1024 = UltExpr::create(result, const_1024);
          state.addConstraint(ult_1024);

				  return;
        }
      }
    }
    #endif
    /// IVAN ADDITIONS END. We replaced this code with more general Drew's code


    const MemoryObject *mo = op.first;


    /// DREW ADDITIONS BEGIN
    /* Drew's code below is responsible for handling read/writes to/from
     * special memory location: peripheral registers and flash memroy.
     * For each such location, the code invokes specel read/write
     * handlers which are defined by the Architecture class */
    ConstantExpr * ce = dyn_cast<ConstantExpr>(address);
    /* We don't support accessing special memory locations using
     * symbolic addresses yet */
    if (ce != NULL){
	    uint64_t addrVal = ce->getZExtValue();
	    if (addrVal < arch->memory_size){
		    uint8_t flags = arch->memory[addrVal];
		    if ((flags & MEMORY_SPECIAL) && isWrite){
			    if (flags & MEMORY_FLASH){
				    llvm::outs() << "IS FLASH write at " << addrVal << "\n";
				    return;
			    }

			    special_write_t writeFun = arch->writeMap[addrVal];
			    if (writeFun == NULL){
				    klee_error("Absentee writeFun at 0x%lx\n", addrVal);
			    }
			    bool validWrite = writeFun(&state, addrVal, value, false);
			    if (!validWrite){
				    terminateStateOnError(state,
						    "memory error: invalid peripheral write",
						    "write.err");
			    }
			    return;
		    } else if (flags & MEMORY_SPECIAL){
			    if (flags & MEMORY_FLASH){
				    llvm::outs() << "IS FLASH read at " << addrVal << "\n";
				    ref<Expr> result = arch->flashReader(&state, addrVal, type, false);
				    llvm::outs() << "flash READ" << result << "\n";
				    bindLocal(target, state, result);
				    return;
			    } else {
				    special_read_t readFun = arch->readMap[addrVal];
				    if (readFun == NULL){
					    //klee_error("Absentee readFun at 0x%lx (not flash)\n", addrVal);
					    terminateStateOnError(state,
							    "invalid read",
							    "read.err");
				    }
				    ref<Expr> result;
            //if(forward_symbex) // return previosly written value
            if(false) // return previosly written value
				      result = readFun(&state, addrVal, type, false);
            else // return fresh symbolics
				      result = readFun(&state, addrVal, type, true);
				    bindLocal(target, state, result);
				    return;
			    }
		    }
	    }
    }
    /// DREW ADDITIONS END

 
    if (MaxSymArraySize && mo->size>=MaxSymArraySize) {
      address = toConstant(state, address, "max-sym-array-size");
    }
    
    ref<Expr> offset = mo->getOffsetExpr(address);

    bool inBounds;
    solver->setTimeout(coreSolverTimeout);
    bool success = solver->mustBeTrue(state, 
                                      mo->getBoundsCheckOffset(offset, bytes),
                                      inBounds);
    solver->setTimeout(0);
    if (!success) {
      state.pc = state.prevPC;
      terminateStateEarly(state, "Query timed out (bounds check).");
      return;
    }

    if (inBounds) {
      const ObjectState *os = op.second;
      if (isWrite) {
        if (os->readOnly) {
          terminateStateOnError(state,
                                "memory error: object read only",
                                "readonly.err");
        } else {
          ObjectState *wos = state.addressSpace.getWriteable(mo, os);
          llvm::outs() << "ForwardExecutor::executeMemoryOperation() :: sucess (for write) = true; value = " << value << "\n";
          wos->write(offset, value);
        }          
      } else {
        ref<Expr> result = os->read(offset, type);
        
        llvm::outs() << "ForwardExecutor::executeMemoryOperation() :: sucess (for read) = true; result = " << result << "\n";
	#if 0 /* IVAN: we don't have interpreterOpts in ForwardExecutor */
        if (interpreterOpts.MakeConcreteSymbolic)
          result = replaceReadWithSymbolic(state, result);
	#endif

        
        bindLocal(target, state, result);
      }

      return;
    }
  } else
    llvm::outs() << "ForwardExecutor::executeMemoryOperation() :: sucess = false, going to exit(0)\n";
  
  // we are on an error path (no resolution, multiple resolution, one
  // resolution with out of bounds)
  
  ResolutionList rl;  
  solver->setTimeout(coreSolverTimeout);
  bool incomplete = state.addressSpace.resolve(state, solver, address, rl,
                                               0, coreSolverTimeout);
  solver->setTimeout(0);
  
  // XXX there is some query wasteage here. who cares?
  ExecutionState *unbound = &state;
  
  for (ResolutionList::iterator i = rl.begin(), ie = rl.end(); i != ie; ++i) {
    const MemoryObject *mo = i->first;
    const ObjectState *os = i->second;
    ref<Expr> inBounds = mo->getBoundsCheckPointer(address, bytes);
    
    StatePair branches = fork(*unbound, inBounds, true);
    ExecutionState *bound = branches.first;

    // bound can be 0 on failure or overlapped 
    if (bound) {
      if (isWrite) {
        if (os->readOnly) {
          terminateStateOnError(*bound,
                                "memory error: object read only",
                                "readonly.err");
        } else {
          ObjectState *wos = bound->addressSpace.getWriteable(mo, os);
          wos->write(mo->getOffsetExpr(address), value);
        }
      } else {
        ref<Expr> result = os->read(mo->getOffsetExpr(address), type);
        bindLocal(target, *bound, result);
      }
    }

    unbound = branches.second;
    if (!unbound)
      break;
  }
  
  // XXX should we distinguish out of bounds and overlapped cases?
  if (unbound) {
    if (incomplete) {
      terminateStateEarly(*unbound, "Query timed out (resolve).");
    } else {
      terminateStateOnError(*unbound,
                            "memory error: out of bound pointer",
                            "ptr.err",
                            getAddressInfo(*unbound, address));
    }
  }
}

void ForwardExecutor::executeMakeSymbolic(ExecutionState &state, 
                                   const MemoryObject *mo,
                                   const std::string &name) {
  llvm::outs() << "Inside ForwardExecutor::executeMakeSymbolic()\n";
  // Create a new object state for the memory object (instead of a copy).
  if (!replayOut) {
    llvm::outs() << "ForwardExecutor::executeMakeSymbolic(): replayOut is not NULL\n";
    // Find a unique name for this array.  First try the original name,
    // or if that fails try adding a unique identifier.
    unsigned id = 0;
    std::string uniqueName = name;
    while (!state.arrayNames.insert(uniqueName).second) {
      uniqueName = name + "_" + llvm::utostr(++id);
    }
    const Array *array = Array::CreateArray(uniqueName, mo->size);
    bindObjectInState(state, mo, false, array);
    state.addSymbolic(mo, array);
    
    std::map< ExecutionState*, std::vector<SeedInfo> >::iterator it = 
      seedMap.find(&state);
    if (it!=seedMap.end()) { // In seed mode we need to add this as a
                             // binding.
      llvm::outs() << "ForwardExecutor::executeMakeSymbolic(): in seed mode.\n";
      for (std::vector<SeedInfo>::iterator siit = it->second.begin(), 
             siie = it->second.end(); siit != siie; ++siit) {
        SeedInfo &si = *siit;
        KTestObject *obj = si.getNextInput(mo, NamedSeedMatching);

        if (!obj) {
          if (ZeroSeedExtension) {
            std::vector<unsigned char> &values = si.assignment.bindings[array];
            values = std::vector<unsigned char>(mo->size, '\0');
          } else if (!AllowSeedExtension) {
            terminateStateOnError(state, 
                                  "ran out of inputs during seeding",
                                  "user.err");
            break;
          }
        } else {
          if (obj->numBytes != mo->size &&
              ((!(AllowSeedExtension || ZeroSeedExtension)
                && obj->numBytes < mo->size) ||
               (!AllowSeedTruncation && obj->numBytes > mo->size))) {
	    std::stringstream msg;
	    msg << "replace size mismatch: "
		<< mo->name << "[" << mo->size << "]"
		<< " vs " << obj->name << "[" << obj->numBytes << "]"
		<< " in test\n";

            terminateStateOnError(state,
                                  msg.str(),
                                  "user.err");
            break;
          } else {
            std::vector<unsigned char> &values = si.assignment.bindings[array];
            values.insert(values.begin(), obj->bytes, 
                          obj->bytes + std::min(obj->numBytes, mo->size));
            if (ZeroSeedExtension) {
              for (unsigned i=obj->numBytes; i<mo->size; ++i)
                values.push_back('\0');
            }
          }
        }
      }
    }
  } else {
    llvm::outs() << "ForwardExecutor::executeMakeSymbolic(): replayOut is NULL\n";
    ObjectState *os = bindObjectInState(state, mo, false);
    if (replayPosition >= replayOut->numObjects) {
      terminateStateOnError(state, "replay count mismatch", "user.err");
    } else {
      KTestObject *obj = &replayOut->objects[replayPosition++];
      if (obj->numBytes != mo->size) {
        terminateStateOnError(state, "replay size mismatch", "user.err");
      } else {
        for (unsigned i=0; i<mo->size; i++)
          os->write8(i, obj->bytes[i]);
      }
    }
  }
}



void ForwardExecutor::runFunction(llvm::Function *f,
         path_summary_ty *start_summary,
				 int argc,
				 char **argv,
				 char **envp) 
{
  std::vector<ref<Expr> > arguments;
  llvm::outs() << "ForwardExecutor::runFunction(); Inside\n";
  // force deterministic initialization of memory objects
  srand(1);
  srandom(1);
  
  MemoryObject *argvMO = 0;

  // In order to make uclibc happy and be closer to what the system is
  // doing we lay out the environments at the end of the argv array
  // (both are terminated by a null). There is also a final terminating
  // null that uclibc seems to expect, possibly the ELF header?

  int envc;
  for (envc=0; envp[envc]; ++envc) ;

  unsigned NumPtrBytes = Context::get().getPointerWidth() / 8;
  KFunction *kf = kmodule->functionMap[f];
  assert(kf);
  Function::arg_iterator ai = f->arg_begin(), ae = f->arg_end();
  if (ai!=ae) {
    arguments.push_back(ConstantExpr::alloc(argc, Expr::Int32)); // This creates a new constant experession

    if (++ai!=ae) {
      fprintf(stderr, "IVAN: allocating memory for the main function\n");
      argvMO = memory->allocate((argc+1+envc+1+1) * NumPtrBytes, false, true,
                                f->begin()->begin());
      
      arguments.push_back(argvMO->getBaseExpr());

      if (++ai!=ae) {
        uint64_t envp_start = argvMO->guest_address + (argc+1)*NumPtrBytes;
        arguments.push_back(Expr::createPointer(envp_start));

        if (++ai!=ae)
          klee_error("invalid main function (expect 0-3 arguments)");
      }
    }
  }

  ExecutionState *state = new ExecutionState(kmodule->functionMap[f]);
  
  if (pathWriter) 
    state->pathOS = pathWriter->open();
  if (symPathWriter) 
    state->symPathOS = symPathWriter->open();


  if (statsTracker)
    statsTracker->framePushed(*state, 0);

  assert(arguments.size() == f->arg_size() && "wrong number of arguments");
  for (unsigned i = 0, e = f->arg_size(); i != e; ++i)
    bindArgument(kf, i, *state, arguments[i]);

  if (argvMO) {
    ObjectState *argvOS = bindObjectInState(*state, argvMO, false);

    for (int i=0; i<argc+1+envc+1+1; i++) {
      if (i==argc || i>=argc+1+envc) {
        // Write NULL pointer
        argvOS->write(i * NumPtrBytes, Expr::createPointer(0));
      } else {
        char *s = i<argc ? argv[i] : envp[i-(argc+1)];
        int j, len = strlen(s);
        
        MemoryObject *arg = memory->allocate(len+1, false, true, state->pc->inst);
        ObjectState *os = bindObjectInState(*state, arg, false);
        for (j=0; j<len+1; j++)
          os->write8(j, s[j]);

        // Write pointer to newly allocated and initialised argv/envp c-string
        argvOS->write(i * NumPtrBytes, arg->getBaseExpr());
      }
    }
  }
  
  llvm::outs() << "Going inside initializeGlobals().\n";
  initializeGlobals(*state);
  llvm::outs() << "Returned from initializeGlobals().\n";

  processTree = new PTree(state);
  state->ptreeNode = processTree->root;
  
  state->cur_fsummary = start_summary;
  /* If main() calls assert() directly, we don't have any next path summary */
  if( !(ForwardOnly) && (f != *(interpreter_manager->path_manager->call_path.end()-2)) )
  {
    assert(!start_summary->next_path_summaries.empty() && "next path summary cannot be NULL for non-final function");
    /* The current implementation of backward symbex gives us only one
     * next path summary */
    state->next_fsummary = start_summary->next_path_summaries[0]; 
  } else
    state->next_fsummary = NULL; 
  state->stack.back().cur_fsummary = state->cur_fsummary;

  run(*state);
  delete processTree;
  processTree = 0;

  // hack to clear memory objects
  delete memory;
  memory = new MemoryManager();
  memory->arch = this->arch;
  
  globalObjects.clear();
  globalAddresses.clear();

  if (statsTracker)
    statsTracker->done();
}


/***/

/* Functionality moved to PathSummary::print()
void ForwardExecutor::print_function_summary(path_summary_ty *smmry)
{
  if(!smmry)
  {
    llvm::outs() << "  NULL\n";
    return;
  }

  ref<Expr> fn_result = smmry->return_value;
  ConstraintManager fn_constraints = smmry->path_constraints;

  std::string Str;
  llvm::raw_string_ostream info(Str);
  ExprPPrinter::printConstraints(info, fn_constraints);
  llvm::outs() << "Res: " << fn_result  << "; constraints:\n" << info.str() << "\n";
  return;
} */

void ForwardExecutor::print_state_constraints(ExecutionState *state)
{
  //ref<Expr> fn_result = smmry->return_value;
  //ConstraintManager fn_constraints = smmry->path_constraints;

  std::string Str;
  llvm::raw_string_ostream info(Str);
  ExprPPrinter::printConstraints(info, state->constraints);
  llvm::outs() << "State: " << state  << "; constraints:\n" << info.str() << "\n";
  return;
}

/* This moved to ExprUtils 
void print_expressions(std::vector<ref<Expr> > vexpr)
{
  for(std::vector<ref<Expr> >::iterator it = vexpr.begin(); it != vexpr.end(); ++it)
    llvm::outs() << *it << "\n";
  return;
}
*/


///* We return 0 if for at least one suppl call, there are zero connected
// * summaries*/
//int ForwardExecutor::paint_summary_chains(path_summary_ty *path_smmry)
//{
//  llvm::outs() << "ForwardExecutor::print_summary_chains(): Considering path summary for function " << path_smmry->fn->getName() << "()\n";
//  print_function_summary(path_smmry);
//  int res = 1; // assume that summary is feasible
//  for(call_symbolic_replacements_ty::iterator it_1  = path_smmry->call_symbolic_replacements.begin();
//                                              it_1 != path_smmry->call_symbolic_replacements.end(); ++it_1)
//  {
//    InnerCall *inner_call = it_1->second;
//    llvm::Function *suppl_fn = inner_call->call_inst->getCalledFunction();
//    llvm::outs() << "ForwardExecutor::print_summary_chains(): Suppl call " << inner_call->seq_num 
//                 << " for " << path_smmry->fn->getName() << "() (function " << suppl_fn->getName() << "()) has " << inner_call->connected_summaries.size()
//                 << " connected summaries.\n";
//    for(unsigned i = 0; i<inner_call->connected_summaries.size(); i++)
//      print_summary_chains(inner_call->connected_summaries[i]);
//  }
//  return 0;
//}

/*
void ForwardExecutor::print_function_summaries(std::map<llvm::Function *, std::vector<path_summary_ty *> > ps)
{
  //llvm::outs() << "ForwardExecutor::runFunctionAsNonMain(): run() is finished, printing the collected summaries.\n";
  for (std::map<llvm::Function *, std::vector<path_summary_ty *> >::iterator it  = ps.begin();
                                                                           it != ps.end(); 
                                                                           ++it)
  {
    llvm::outs() << it->first->getName() << "\n"; // Function name
    std::vector<path_summary_ty *> fn_smmries = it->second; // vector of pairs of <function result, path constraints>.
    for (std::vector<path_summary_ty *>::iterator smmry  = fn_smmries.begin();
                                                smmry != fn_smmries.end(); ++smmry)
    {
      ref<Expr> fn_result = (*smmry)->return_value;
      ConstraintManager fn_constraints = (*smmry)->path_constraints;
      llvm::outs() << "ForwardExecutor::print_function_summaries(): fn_constraints.size() = " << fn_constraints.size() << "\n";

      // KQUERY format printing 
      std::string Str;
      llvm::raw_string_ostream info(Str);
      ExprPPrinter::printConstraints(info, fn_constraints);
      llvm::outs() << "Res: " << fn_result  << "; constraints:\n" << info.str() << "\n";

      //// STP format
      //Query query(fn_constraints, ConstantExpr::alloc(0, Expr::Bool));
      //char *log = solver->getConstraintLog(query);
      //std::string res = std::string(log);
      //llvm::outs() << "Res: " << fn_result  << "; constraints:\n" << res << "\n";
      //free(log);
    }
  }
  return;
} */

/*
void ForwardExecutor::make_globals_symbolic(ExecutionState *s, std::vector<llvm::Value *> globals)
{
  for(std::vector<llvm::Value *>::iterator gv = globals.begin(); gv != globals.end(); ++gv)
  {
    llvm::outs() << "ForwardExecutor::make_globals_symbolic(): making '" << (*gv)->getName() << "' symbolic\n";

    MemoryObject* mo = globalObjects[(GlobalValue *)(*gv)];



          unsigned id = 0;
          std::string name = (*gv)->getName().str();
          std::string uniqueName = name;
          while (!s->arrayNames.insert(uniqueName).second) {
            uniqueName = name + "_" + llvm::utostr(++id);
          }
          const Array *new_array = Array::CreateArray(uniqueName, mo->size);
          bindObjectInState(*s, mo, false, new_array);
          s->global_symbolic_replacements[*gv].push_back(new_array);



    //llvm::outs() << "       @" << mo->address << "\n";
    //executeMakeSymbolic(*s, mo, (*gv)->getName().str()); // This one just put new pair (mo, array) to s->symbolics
    //s->global_symbolic_replacements[*gv].push_back(s->symbolics[s->symbolics.size()-1].second);
  }
  llvm::outs() << "ForwardExecutor::make_globals_symbolic(): state has the following symbolics now:\n";
  //for(std::vector<std::pair<const MemoryObject *, const Array *> >::iterator it = s->symbolics.begin();
  //                        it != s->symbolics.end(); ++it)
  //{
  //  llvm::outs() << "mo->name = " << it->first->name << "; array->name = " << it->second->getName() << 
  //               "@" << it->second << "\n"; 
  //}
  return;
}*/

std::vector<llvm::Value *> ForwardExecutor::get_global_calling_context(Function *f)
{
  std::vector<llvm::Value *>  res;

  llvm::outs() << "DEBUG: the following global variables are used in " << f->getName() << "@" << f << ":\n";
  //llvm::outs() << "DEBUG: globalObjects.size() =  " << globalObjects.size()  << "\n";
  for(std::map<const llvm::GlobalValue*, MemoryObject*>::iterator it = globalObjects.begin(); it != globalObjects.end(); ++it)
  {
    llvm::GlobalValue* gv = (llvm::GlobalValue *)it->first;
    //llvm::outs() << "get_global_calling_context(): Considering " << gv->getName() << "\n";
    MemoryObject* mo = it->second;
    for(llvm::Value::use_iterator u_it=gv->use_begin(); u_it != gv->use_end(); ++u_it)
    {
      if(Instruction *Inst = dyn_cast<Instruction>(*u_it))
      {
        //llvm::outs() << "     -- in " << *Inst << " -- " << Inst->getParent()->getParent()->getName() << 
        //             "@" << Inst->getParent()->getParent() << "\n";
        if(Inst->getParent()->getParent() == f)
        {
          //llvm::outs() << "     " << Inst->getParent()->getParent()->getName() << "\n";
          llvm::outs() << "     " << gv->getName() << "\n";
          res.push_back(gv);
          break; // we are interested in just one usage
        }
      }
    } // for each usage
  } // for each globalValue
  return res;
}

//std::vector<llvm::Value *> ForwardExecutor::get_global_calling_context(Function *f)
//{
//  std::vector<llvm::Value *>  res;
//  Module *m = kmodule->module;
//  llvm::outs() << "DEBUG: the following global variables are used in " << f->getName() << ":\n";
//  for(llvm::Module::global_iterator g_it=m->global_begin(); g_it != m->global_end(); ++g_it)
//    for(llvm::Value::use_iterator u_it=g_it->use_begin(); u_it != g_it->use_end(); ++u_it)
//      if (Instruction *Inst = dyn_cast<Instruction>(*u_it))
//        if(Inst->getParent()->getParent() == f)
//        {
//          //llvm::outs() << "     " << Inst->getParent()->getParent()->getName() << "\n";
//          llvm::outs() << "     " << g_it->getName() << "\n";
//          res.push_back(&(*g_it));
//          break; // we are interested in just one usage
//        }
//  return res;
//}




/*  Get call instruction which correspond to symbolic values which
 *  replaced them in function <f>.
 *
 *  Correspondence between symbolic values and call instructions are
 *  contained in map <ForwardExecutor::call_symbolic_replacements>.  We need
 *  only those call instructions whose symbolic values are in good_path_summaries
 *  for function <f>.
 *
 *  @param ps Path summary (i.e. function ret value, and path constraint) for function <f>
 *  @param f Function in which we had call instruction that were replaced by symbolics.
 *  @return vector with call instruction which we will need to execute
 *  
 */
//std::vector<llvm::CallInst *> ForwardExecutor::resolve_call_symbolics(path_summary_ty ps, llvm::Function *f)
// The return value is a map. Key is a function which we need to call, and the value is the 
// constraints on the return value of the called function (i.e. it is
// the subset of the corresponding path condition).
// TODO: add constraints on global values.
//std::map<llvm::CallInst *, std::vector< ref<Expr> > > ForwardExecutor::resolve_call_symbolics(llvm::Function *f, int ps_index_)
//std::map<llvm::CallInst *, std::vector< ref<Expr> > >
//      ForwardExecutor::resolve_call_symbolics(llvm::Function *f, constraints_ty conds)
//{
//  llvm::outs() << "ForwardExecutor::resolve_call_symbolic(): inside; for function " << f->getName() << "().\n";
//  std::map<llvm::CallInst *, std::vector< ref<Expr> > > calls;
//
//  call_symbolic_replacements_ty symb_replacements = call_symbolic_replacements[f];
//  //constraints_ty f_path_conditions = ps.second;
//
//  for(call_symbolic_replacements_ty::iterator it_1 = symb_replacements.begin(); it_1 != symb_replacements.end(); ++it_1)
//  {
//    ref<Expr> symb_replc = it_1->first; // Let's collect constraints for this symbolics
//    llvm::CallInst *call_inst = it_1->second; // Which replaced this call instruction
//
//    for(std::vector< ref<Expr> >::const_iterator it_2 = conds.begin(); it_2 != conds.end(); ++it_2)
//    {
//      const ref<Expr> e = *it_2;
//      std::vector<ref<Expr> > concats =  extract_concat_subexpressions(e);
//      for(std::vector<ref<Expr> >::iterator it_3 = concats.begin(); it_3 != concats.end(); ++it_3)
//      {
//        ref<Expr> concat = *it_3;
//        if(symb_replc == concat)
//        {
//          calls[call_inst].push_back(e);
//          break;
//        }
//      }
//    }
//  }
//  return calls;
//}

///* For each call instruction that was replaced by a symbolics, return the
// * the corresponding call instruction and conditions collected on those
// * symbolics along path summary <f1_smmry>*/
////std::map<llvm::CallInst *, std::vector< ref<Expr> > > 
//ForwardExecutor::resolve_call_symbolics1(path_summary_ty &f1_smmry)
//{
//  llvm::Function *f1 = f1_smmry.fn; 
//  llvm::outs() << "ForwardExecutor::resolve_call_symbolic1(): inside; for function " << f1->getName() << "().\n";
//  //std::map<llvm::CallInst *, std::vector< ref<Expr> > > calls;
//  call_symbolic_replacements_ty symb_replacements = f1_smmry.call_symbolic_replacements;
//
//  for(call_symbolic_replacements_ty::iterator it_1 = symb_replacements.begin(); 
//                                              it_1 != symb_replacements.end(); ++it_1)
//  {
//    ref<Expr> symb_replc = it_1->first; // symbolics
//    llvm::CallInst *call_inst = it_1->second; // which replaced this call instruction
//
//    /* First collect conditions along the f1's path summary. */
//    for(std::vector< ref<Expr> >::const_iterator it_2 = f1_smmry.path_constraints.begin();
//                                                 it_2 != f1_smmry.path_constraints.end(); ++it_2)
//    {
//      const ref<Expr> e = *it_2;
//      std::vector<ref<Expr> > concats =  extract_concat_subexpressions(e);
//      for(std::vector<ref<Expr> >::iterator it_3 = concats.begin(); it_3 != concats.end(); ++it_3)
//      {
//        ref<Expr> concat = *it_3;
//        if(symb_replc == concat)
//        {
//          calls[call_inst].push_back(e);
//          break;
//        }
//      }
//    }
//  }
//}
//    
////    std::vector<int> used_arg_indices;
////    /* Second check if the call symbolic replacement was used as f2's actual parameter */
////    std::vector<ref<Expr> > f2_actual_args = f1_smmry.target_func_actual_args;
////    for(unsigned i = 0; i < f2_actual_args.size(); i++)
////    {
////      if(symb_replc == f2_actual_args[i])
////      {
////        llvm::outs() << "call symbolics is a function arguments\n";
////        used_arg_indices.push_back(i);
////        exit(0);
////      }
////    }
////  }
////  return calls;
////}
//
//


#if 0
bool ForwardExecutor::check_formal_args_against_psummary(path_summary_ty &smmry, std::vector<std::vector< ref<Expr> > > &formal_args_conditions)
{
  std::vector<ref<Expr> > combined_constraints;
  std::vector<ref<Expr> > debug_constraints; // keeps conditions on formal arguments (already replaced)
  unsigned numFormals = smmry.fargs.size();
  llvm::outs() << "ForwardExecutor::check_formal_args_against_fsummary(): Creating combined (formal_args_conds + path_conds) contraints\n";
  for (unsigned i=0; i<numFormals; ++i) 
  {
    std::vector< ref<Expr> > arg_i_conditions = formal_args_conditions[i];
    for(std::vector< ref<Expr> >::iterator it = arg_i_conditions.begin(); it != arg_i_conditions.end(); ++it)
    {
      /*ref<Expr> cond = *it;
      comp_symbex_replace_for_retvalue(cond, smmry.fargs[i]);
      combined_constraints.push_back(cond);
      debug_constraints.push_back(cond);*/
      ref<Expr> cond = *it;
      ref<Expr> tmp = comp_symbex_replace_for_retvalue(cond, smmry.fargs[i]);
      combined_constraints.push_back(tmp);
      debug_constraints.push_back(tmp);
    }
  }
  combined_constraints.insert(combined_constraints.end(), smmry.path_constraints.begin(), smmry.path_constraints.end());

  llvm::outs() << "ForwardExecutor::check_formal_args_against_fsummary(): checking the following combined conditions:\n";
  for(std::vector<ref<Expr> >::iterator it = combined_constraints.begin(); it != combined_constraints.end(); ++it)
    llvm::outs() << *it << "\n";
  
  if(combined_constraints.size() == 0)
  {
    llvm::outs() << "ForwardExecutor::check_formal_args_against_fsummary(): Conditions are empty => result = 1 (true)\n";
    return true;
  }
  ConstraintManager cm(combined_constraints);
  bool solver_result;
  bool success = solver->solver->mayBeTrue(Query(cm, combined_constraints[0]), solver_result);

  // DEBUG STUFF BEGIN
  //ref<Expr> true_expr =  ConstantExpr::create(1, Expr::Bool);
  //ConstraintManager cm1(combined_constraints);
  //bool debug_result;
  Solver::Validity debug_result;
  bool success1;
  if((debug_constraints.size() != 0) && (smmry.path_constraints.size() != 0))
  {
    std::string res_str;
    //success1 = solver->solver->evaluate(Query(smmry.path_constraints, debug_constraints[0]), debug_result); 
    success1 = solver->solver->evaluate(Query(smmry.path_constraints, smmry.path_constraints.back()), debug_result); 
    if (debug_result == Solver::Unknown)
      res_str = "unknown";
    else if (debug_result == Solver::False)
      res_str = "0";
    else if (debug_result == Solver::True)
      res_str = "1";
    llvm::outs() << "ForwardExecutor::check_formal_args_against_fsummary(): debug_result = " << res_str << "\n";
  }
  else
    llvm::outs() << "ForwardExecutor::check_formal_args_against_fsummary(): no additional constraints on formals\n";
  // DEBUG STUFF END

  // DEBUG STUFF BEGIN
  //ref<Expr> true_expr =  ConstantExpr::create(1, Expr::Bool);
  //ConstraintManager cm1(combined_constraints);
  //bool debug_result;
  //bool success1 = solver->solver->mayBeTrue(Query(cm1, true_expr), debug_result);
  //llvm::outs() << "ForwardExecutor::check_formal_args_against_fsummary(): debug_result = " << debug_result << "\n";
  // DEBUG STUFF END

  assert(success && "FIXME: Unhandled solver failure");
  llvm::outs() << "ForwardExecutor::check_formal_args_against_fsummary(): result = " << solver_result << "\n";

  if(!solver_result)
    return false;

  return true;

}
#endif



/* Get bit width if type is an Interger type, 0 otherwise
 */
unsigned ForwardExecutor::getIntTypeWidth(llvm::Type *type)
{
  //if(isa<llvm::IntegerType>(type))
  assert(isa<llvm::IntegerType>(type));
  return (dyn_cast<llvm::IntegerType>(type))->getBitWidth();
  //return 0;
}

/* Get bit width of pointer subtype
 * Return 0 if type is not a PointerType
 */
unsigned ForwardExecutor::getPointerTypeElementWidth(llvm::Type *type)
{
  assert(isa<llvm::PointerType>(type));
  llvm::Type *element_type = (dyn_cast<llvm::PointerType>(type))->getElementType();
  return getIntTypeWidth(element_type);
}


void ForwardExecutor::getConstraintLog(const ExecutionState &state, std::string &res,
                                LogType logFormat) {

  std::ostringstream info;

  switch (logFormat) {
  case STP: {
    Query query(state.constraints, ConstantExpr::alloc(0, Expr::Bool));
    char *log = solver->getConstraintLog(query);
    res = std::string(log);
    free(log);
  } break;

  case KQUERY: {
    std::string Str;
    llvm::raw_string_ostream info(Str);
    ExprPPrinter::printConstraints(info, state.constraints);
    res = info.str();
  } break;

  case SMTLIB2: {
    std::string Str;
    llvm::raw_string_ostream info(Str);
    ExprSMTLIBPrinter printer;
    printer.setOutput(info);
    Query query(state.constraints, ConstantExpr::alloc(0, Expr::Bool));
    printer.setQuery(query);
    printer.generateOutput();
    res = info.str();
  } break;

  case CVS: {
    //std::ostringstream info;
    //ExprPPrinter::printConstraints(info, state.constraints);
    //res = info.str();    
  } break;

  default:
    klee_warning("ForwardExecutor::getConstraintLog() : Log format not supported!");
  }
}




Expr::Width ForwardExecutor::getWidthForLLVMType(LLVM_TYPE_Q llvm::Type *type) const {
  return kmodule->targetData->getTypeSizeInBits(type);
}

namespace klee {
ref<ConstantExpr> ForwardExecutor::evalConstantExpr(const llvm::ConstantExpr *ce) 
{
  LLVM_TYPE_Q llvm::Type *type = ce->getType();

  ref<ConstantExpr> op1(0), op2(0), op3(0);
  int numOperands = ce->getNumOperands();

  if (numOperands > 0) op1 = evalConstant(ce->getOperand(0));
  if (numOperands > 1) op2 = evalConstant(ce->getOperand(1));
  if (numOperands > 2) op3 = evalConstant(ce->getOperand(2));

  switch (ce->getOpcode()) {
  default :
    ce->dump();
    llvm::errs() << "error: unknown ConstantExpr type\n"
              << "opcode: " << ce->getOpcode() << "\n";
    abort();

  case Instruction::Trunc: 
    return op1->Extract(0, getWidthForLLVMType(type));
  case Instruction::ZExt:  return op1->ZExt(getWidthForLLVMType(type));
  case Instruction::SExt:  return op1->SExt(getWidthForLLVMType(type));
  case Instruction::Add:   return op1->Add(op2);
  case Instruction::Sub:   return op1->Sub(op2);
  case Instruction::Mul:   return op1->Mul(op2);
  case Instruction::SDiv:  return op1->SDiv(op2);
  case Instruction::UDiv:  return op1->UDiv(op2);
  case Instruction::SRem:  return op1->SRem(op2);
  case Instruction::URem:  return op1->URem(op2);
  case Instruction::And:   return op1->And(op2);
  case Instruction::Or:    return op1->Or(op2);
  case Instruction::Xor:   return op1->Xor(op2);
  case Instruction::Shl:   return op1->Shl(op2);
  case Instruction::LShr:  return op1->LShr(op2);
  case Instruction::AShr:  return op1->AShr(op2);
  case Instruction::BitCast:  return op1;

  case Instruction::IntToPtr:
    return op1->ZExt(getWidthForLLVMType(type));

  case Instruction::PtrToInt:
    return op1->ZExt(getWidthForLLVMType(type));

  case Instruction::GetElementPtr: {
    ref<ConstantExpr> base = op1->ZExt(Context::get().getPointerWidth());

    for (gep_type_iterator ii = gep_type_begin(ce), ie = gep_type_end(ce);
         ii != ie; ++ii) {
      ref<ConstantExpr> addend = 
        ConstantExpr::alloc(0, Context::get().getPointerWidth());

      if (LLVM_TYPE_Q StructType *st = dyn_cast<StructType>(*ii)) {
        const StructLayout *sl = kmodule->targetData->getStructLayout(st);
        const ConstantInt *ci = cast<ConstantInt>(ii.getOperand());

        addend = ConstantExpr::alloc(sl->getElementOffset((unsigned)
                                                          ci->getZExtValue()),
                                     Context::get().getPointerWidth());
      } else {
        const SequentialType *set = cast<SequentialType>(*ii);
        ref<ConstantExpr> index = 
          evalConstant(cast<Constant>(ii.getOperand()));
        unsigned elementSize = 
          kmodule->targetData->getTypeStoreSize(set->getElementType());

        index = index->ZExt(Context::get().getPointerWidth());
        addend = index->Mul(ConstantExpr::alloc(elementSize, 
                                                Context::get().getPointerWidth()));
      }

      base = base->Add(addend);
    }

    return base;
  }
    
  case Instruction::ICmp: {
    switch(ce->getPredicate()) {
    default: assert(0 && "unhandled ICmp predicate");
    case ICmpInst::ICMP_EQ:  return op1->Eq(op2);
    case ICmpInst::ICMP_NE:  return op1->Ne(op2);
    case ICmpInst::ICMP_UGT: return op1->Ugt(op2);
    case ICmpInst::ICMP_UGE: return op1->Uge(op2);
    case ICmpInst::ICMP_ULT: return op1->Ult(op2);
    case ICmpInst::ICMP_ULE: return op1->Ule(op2);
    case ICmpInst::ICMP_SGT: return op1->Sgt(op2);
    case ICmpInst::ICMP_SGE: return op1->Sge(op2);
    case ICmpInst::ICMP_SLT: return op1->Slt(op2);
    case ICmpInst::ICMP_SLE: return op1->Sle(op2);
    }
  }

  case Instruction::Select:
    return op1->isTrue() ? op2 : op3;

  case Instruction::FAdd:
  case Instruction::FSub:
  case Instruction::FMul:
  case Instruction::FDiv:
  case Instruction::FRem:
  case Instruction::FPTrunc:
  case Instruction::FPExt:
  case Instruction::UIToFP:
  case Instruction::SIToFP:
  case Instruction::FPToUI:
  case Instruction::FPToSI:
  case Instruction::FCmp:
    assert(0 && "floating point ConstantExprs unsupported");
  }
}
}

void ForwardExecutor::initializeGlobalObject(ExecutionState &state, ObjectState *os,
                                      const Constant *c, 
                                      unsigned offset) {
#if LLVM_VERSION_CODE <= LLVM_VERSION(3, 1)
  TargetData *targetData = kmodule->targetData;
#else
  DataLayout *targetData = kmodule->targetData;
#endif
  if (const ConstantVector *cp = dyn_cast<ConstantVector>(c)) {
    unsigned elementSize =
      targetData->getTypeStoreSize(cp->getType()->getElementType());
    for (unsigned i=0, e=cp->getNumOperands(); i != e; ++i)
      initializeGlobalObject(state, os, cp->getOperand(i), 
			     offset + i*elementSize);
  } else if (isa<ConstantAggregateZero>(c)) {
    unsigned i, size = targetData->getTypeStoreSize(c->getType());
    for (i=0; i<size; i++)
      os->write8(offset+i, (uint8_t) 0);
  } else if (const ConstantArray *ca = dyn_cast<ConstantArray>(c)) {
    unsigned elementSize =
      targetData->getTypeStoreSize(ca->getType()->getElementType());
    for (unsigned i=0, e=ca->getNumOperands(); i != e; ++i)
      initializeGlobalObject(state, os, ca->getOperand(i), 
			     offset + i*elementSize);
  } else if (const ConstantStruct *cs = dyn_cast<ConstantStruct>(c)) {
    const StructLayout *sl =
      targetData->getStructLayout(cast<StructType>(cs->getType()));
    for (unsigned i=0, e=cs->getNumOperands(); i != e; ++i)
      initializeGlobalObject(state, os, cs->getOperand(i), 
			     offset + sl->getElementOffset(i));
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 1)
  } else if (const ConstantDataSequential *cds =
               dyn_cast<ConstantDataSequential>(c)) {
    unsigned elementSize =
      targetData->getTypeStoreSize(cds->getElementType());
    for (unsigned i=0, e=cds->getNumElements(); i != e; ++i)
      initializeGlobalObject(state, os, cds->getElementAsConstant(i),
                             offset + i*elementSize);
#endif
  } else if (!isa<UndefValue>(c)) {
    unsigned StoreBits = targetData->getTypeStoreSizeInBits(c->getType());
    ref<ConstantExpr> C = evalConstant(c);

    // Extend the constant if necessary;
    assert(StoreBits >= C->getWidth() && "Invalid store size!");
    if (StoreBits > C->getWidth())
      C = C->ZExt(StoreBits);

    os->write(offset, C);
  }
}

ForwardExecutor::~ForwardExecutor() {
  delete memory;
  delete externalDispatcher;
  if (processTree)
    delete processTree;
  if (specialFunctionHandler)
    delete specialFunctionHandler;
  if (statsTracker)
    delete statsTracker;
  delete solver;
  delete kmodule;
}

void ForwardExecutor::branch_connected_summaries(ExecutionState &state,
                           unsigned N, std::vector<ExecutionState*> &result, bool add)
{
  TimerStatIncrementer timer(stats::forkTime);
  assert(N);

  stats::forks += N-1;

  // XXX do proper balance or keep random?
  result.push_back(&state);
  for (unsigned i=1; i<N; ++i)
  {
    ExecutionState *es = result[theRNG.getInt32() % i];
    ExecutionState *ns = es->branch();
    if(add)
      addedStates.insert(ns);
    result.push_back(ns);
    es->ptreeNode->data = 0;
    std::pair<PTree::Node*,PTree::Node*> res = 
      processTree->split(es->ptreeNode, ns, es);
    ns->ptreeNode = res.first;
    es->ptreeNode = res.second;
  }
  return;
}

bool ForwardExecutor::is_part_of_callpath(llvm::Function *f)
{
  PathManager::FVector::iterator it;
  it = find(path_manager->call_path.begin(), path_manager->call_path.end(), f);
  if (it != path_manager->call_path.end())
    return true;
  else
    return false;
}



//const llvm::Module *  setModule(llvm::Module *module,  const Interpreter::ModuleOptions &opts)
//{ 
//  return NULL;
//}


///


