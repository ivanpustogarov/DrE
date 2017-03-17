//===-- SummaryExecutor.cpp ------------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Common.h"
#include "klee/SummaryExecutor.h"
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


//extern cl::opt<unsigned> MaxForks;
//extern cl::opt<bool> OnlyReplaySeeds;
//extern cl::opt<bool> OnlyReplaySeeds;
//namespace klee
//{
//  unsigned MaxForks = 0;
//  bool OnlyReplaySeeds = false;
//}

#endif /* SUPPORT_METASMT */

//namespace klee {
//  RNG theRNG;
//}

bool forward_symbex = false;
//void print_expressions(std::vector<ref<Expr> > vexpr);

//unsigned getIntTypeWidth(llvm::Type *type);
//unsigned getPointerTypeElementWidth(llvm::Type *type);

void SummaryExecutor::setArch(Architecture * _arch)
{
  arch = _arch;
  assert(memory && "You need to initialize MemoryManager first");
  memory->arch = _arch;
}

void SummaryExecutor::setFunction(const llvm::Function *f)
{
  assert(!func && "Changing function is not supported");
  func = f;
}

void SummaryExecutor::setPathManager(PathManager *_path_manager)
{
  assert(!path_manager && "Changing path manager is not supported");
  llvm::outs() << "smmry_executor->replayPath = " << replayPath << "\n";
  path_manager = _path_manager;
}

SummaryExecutor::SummaryExecutor(const InterpreterOptions &opts, Solver *_coreSolver, KModule *_kmodule) :
  Executor(opts, _coreSolver, _kmodule),
  func(NULL),
  //path_manager(NULL),
  num_new_summaries_during_round(0)
{
  specialFunctionHandler = new SpecialFunctionHandler(*this);
  specialFunctionHandler->prepare();
  specialFunctionHandler->bind();
  initializeMergeBlackList();
}



/* Create memory objects for flash segments, and periperal registers */
#define GIE                    (0x0008)
void SummaryExecutor::initializeSpecialGlobals(ExecutionState& state) 
{
  Module *m = kmodule->module;

  /* Allocate memory for the status register. Obviously status register is not a part of RAM,
   * but we need to have a memory object in order to keep per-state values */
  { // new block to limit the scope of the variables and reuse the same names later
    llvm::outs() << "SummaryExecutor::initializeSpecialGlobals(): initializing status register\n";
    //MemoryObject *mo = memory->allocate(arch->pointer_size, false, true, NULL);
    MemoryObject *mo = memory->allocate(Context::get().getPointerWidth(), false, true, NULL);
    if (!mo)
      llvm::report_fatal_error("out of memory");
    ObjectState *os = bindObjectInState(state, mo, false);
    //globalObjects.insert(std::make_pair(i, mo));
    //globalAddresses.insert(std::make_pair(i, mo->getBaseExpr()));
    //os->initializeToZero();

    /* Initialize with (symbolic zero || GIE) to enable interrupts */
    ref<ConstantExpr> zero_expr = ConstantExpr::create(0x0000,Expr::Int16);
    ref<ConstantExpr> gie_expr = ConstantExpr::create(GIE,Expr::Int16);
    ref<Expr> or_expr = OrExpr::create(zero_expr, gie_expr);

    ObjectState *wos = state.addressSpace.getWriteable(mo, os);
    //wos->write(0, zero_expr);
    wos->write(0, or_expr);

    outs() << "SummaryExecutor::initializeSpecialGlobals(): About to set status register\n";
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
    outs() << "SummaryExecutor::initializeSpecialGlobals(): Allocating fixed flash memory region: [" << mem->begin << "-" << mem->end << "]\n";
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
    outs() << "SummaryExecutor::initializeSpecialGlobals(): Allocating special regiter: " 
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


void SummaryExecutor::initializeGlobals(ExecutionState &state) 
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
  outs() << "SummaryExecutor::initializeGlobals(): initializing function addresses\n";
  for (Module::iterator i = m->begin(), ie = m->end(); i != ie; ++i) {
    Function *f = i;
    ref<ConstantExpr> addr(0);

    outs() << "SummaryExecutor::initializeGlobals(): considering  function " << f->getName() << "\n";
    assert(externalDispatcher && "Execternal dispatcher is NULL!");
    // If the symbol has external weak linkage then it is implicitly
    // not defined in this module; if it isn't resolvable then it
    // should be null.
    if (f->hasExternalWeakLinkage() && 
        !externalDispatcher->resolveSymbol(f->getName())) {
      outs() << "SummaryExecutor::initializeGlobals(): creating NULL pointer\n";
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

  outs() << "SummaryExecutor::initializeGlobals(): function addresses initialized\n";

  /// IVAN ADDITIONS BEGIN
  /* This allocated flash memory, and peripehral registers */
  outs() << "SummaryExecutor::initializeGlobals(): initializing special memory\n";
  initializeSpecialGlobals(state);
  outs() << "SummaryExecutor::initializeGlobals(): special memory initialized\n";
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
  
      outs() << "SummaryExecutor::initializeGlobals(): Allocating stuff for function declaration\n";
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

      outs() << "SummaryExecutor::initializeGlobals(): considering  global " << i->getName() << "\n";
      MemoryObject *mo = memory->allocate(size, false, true, &*i);
      if (!mo)
        llvm::report_fatal_error("out of memory");
      //llvm::outs() << "SummaryExecutor::initializeGlobals(): allocated memory for global " << i->getName() <<
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



/* Run function and collect path summaries
 * 
 * Make this SummaryExecutor's function <func> arguments and global variables
 * symbolic, and run the function.  We are interested in path summaries: 1)
 * which satisfy <ret_conds> on the return value; 2) which end up calling <target_func>
 * if it is not NULL.  We put such summaries in <good_path_summaries> vector.
 */
//void SummaryExecutor::collectPathSummaries(const Function *target_func, InnerCall *inner_call) 
void SummaryExecutor::collectPathSummaries(UpperCall *upper_call, InnerCall *inner_call) 
{
  assert((!upper_call || !inner_call) && "upper_call and inner_call are mutually exclusive");
  assert((upper_call || inner_call) && "upper_call and inner_call cannot be both NULL");

  std::vector<ref<Expr> > arguments;
  std::vector<llvm::Value *> globals;
  llvm::Function *target_func = NULL;
  if(upper_call)
    target_func = upper_call->fn;

  llvm::Function *f1 = (llvm::Function *)this->func;
  llvm::Function *f2 = (llvm::Function *)target_func;
  llvm::outs() << "\n\n [NEW SYMBEX] collectPathSummaries(): f1->getName() = " << f1->getName() << "\n";
  // force deterministic initialization of memory objects
  srand(1);
  srandom(1);
  
  MemoryObject *argvMO = 0;

  unsigned NumPtrBytes = Context::get().getPointerWidth() / 8;
  KFunction *kf = kmodule->functionMap[f1];
  assert(kf && "BUG: kf is NULL (kmodule was not initialized properly?)");

  //llvm::outs() << "SummaryExecutor::runFunctionAsNonMain(): allocating memory for function arguments (arg_size() = " 
  //             << f->arg_size() << ")\n";
  ExecutionState *state = new ExecutionState(kf);

  /// IVAN ADDITIONS BEGIN
  //Setting the target function for the state, i.e. once we reach a call instruction
  //  for this function, we should terminate the state.
  state->target_func = f2;

  /* Initialize retu conditions to an empty vector */
  //std::vector<ref<Expr> > ret_conds;
  /* If we are collecting good summaries for an inner  call, set the return conditions */
  //if(inner_call)
  //{
  //  ret_conds = inner_call->retval_conditions;
  //  ret_conds.insert(ret_conds.end(), inner_call->retval_conditions2.begin(), inner_call->retval_conditions2.end());
  //}


  //state->ret_value_constraints = &ret_conds;
  state->cur_inner_call = inner_call;
  state->cur_upper_call = upper_call;
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): set the target function for the initial state to '"
               << (state->target_func ? state->target_func->getName() : "NULL") << "'\n";
  /// IVAN ADDITIONS END

  
  //if (pathWriter) 
  //  state->pathOS = pathWriter->open();
  //if (symPathWriter) 
  //  state->symPathOS = symPathWriter->open();


  //if (statsTracker)
  //  statsTracker->framePushed(*state, 0);

  llvm::outs() << "SummaryExecutor::collectPathSummaries(): Going inside initializeGlobals().\n";
  initializeGlobals(*state);
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): Returned from initializeGlobals().\n";

  processTree = new PTree(state);
  state->ptreeNode = processTree->root;


  // IVAN ADDITIONS BEGIN
  // Making function arguments symbolic
  
  //globals = get_global_calling_context(f); // get the list of global variables which are read and written in the function

  //llvm::outs() << "DEBUG: Making function arguments symbolic\n";
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): Making function '" << f1->getName() << "()' arguments symbolic\n";
  fargs.clear();

  make_args_symbolic(state, f1);
#if 0 // Replaced by the funtion above
  unsigned numFormals = f1->arg_size();
  unsigned id = 0;
  llvm::Function::arg_iterator arg_it = f1->arg_begin();
  for (unsigned i=0; i<numFormals; ++i) 
  {
    //llvm::Argument arg = *arg_it;
    llvm::Value *arg = arg_it;
    llvm::Type *arg_type = arg->getType();
    unsigned bit_width = 0;
    Expr::Width w = 0;
    if(isa<llvm::PointerType>(arg_type))
    {
      llvm::outs() << "SummaryExecutor::collectPathSummaries(): fun arg is a pointer\n";
      //w = Context::get().getPointerWidth() / 8;
      w = Context::get().getPointerWidth();
    }
    else
      w = getWidthForLLVMType(arg_type);
    assert(w && "Formal arg width cannot be zero");


    //llvm::outs() << "DEBUG: symbolic's name : " << "arg_" + f->getName().str() + "_" + llvm::utostr(idi) << "\n";
    //llvm::outs() << "SummaryExecutor::runFunctionAsNonMain(): making symbolic the following arg:" << getArgumentCell(*state, kf, i).value << "\n";
    llvm::outs() << "SummaryExecutor::collectPathSummaries(): creating new symbolic array with size " << w << "\n";
    const Array *array = Array::CreateArray("arg_" + f1->getName().str() + "_" + llvm::utostr(id), Expr::getMinBytesForWidth(w) );
    ref<Expr> res = Expr::createTempRead(array, w);
    bindArgument(kf, i, *state, res);
    fargs.push_back(res);
    id++;
    ++arg_it;
  }
#endif

  // Making globals which are used in the function symbolic

  //make_globals_symbolic(state, f1); 


  comp_symbex_target_reached = 0; // This is set to one when either we reach a ret, satisfying conditions or
                                  // a call to the next function in the call path

  /* Get callers and callees of the current function */
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): here are the callees of current func (" << this->func->getName() << "()):\n";
  callees = this->path_manager->get_callees(this->func, this->arch);
  for (std::map<llvm::Function *, std::set<llvm::Function *> >::iterator it=callees.begin(); it!=callees.end(); ++it)
  {
    llvm::Function *immediate_callee = it->first;
    std::set<llvm::Function *> sub_callees = it->second;
    llvm::outs() << "  [ " << immediate_callee->getName() << "\n";
    for (std::set<llvm::Function *>::iterator it1=sub_callees.begin(); it1!=sub_callees.end(); ++it1)
      llvm::outs() << "     - " << (*it1)->getName() << "\n";
  }
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): here are the callers of current func (" << this->func->getName() << "()):\n";
  callers = this->path_manager->get_callers_r(this->func);
  for (std::set<llvm::Function *>::iterator it=callers.begin(); it!=callers.end(); ++it)
    llvm::outs() << "     " << (*it)->getName() << "\n";

  get_global_calling_context();
  llvm::outs() << "globals to init size = " << this->globals_to_init.size() << "\n";
  llvm::outs() << "globals to refresh size = " << this->globals_to_refresh.size() << "\n";

  /* Now when we identified globals which should be initialized to fresh symbolics, let's initialize them */
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): Making globals symbolic\n";
  init_globals_with_symbolic(state, f1); 
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): number of global symbolic replacements = " << 
                  state->global_symbolic_replacements.size() << "\n";

  // IVAN ADDITIONS END

  //build_fsummary_start_timer = time(NULL);
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): going inside run()\n";
  if(target_func)
     llvm::outs() << "SummaryExecutor::collectPathSummaries(): summary_interpreters.count(target_func) = " 
                  << interpreter_manager->summary_interpreters.count((llvm::Function *)target_func) 
                  << "; target_func =  " << target_func->getName() << "()\n";
  this->num_new_summaries_during_round = 0;
  run(*state);

#if 0 // We might come back to collecting summaries, so don't destroy anything yet
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
#endif
  
  llvm::outs() << "SummaryExecutor::collectPathSummaries(): finished collecting summaries for f1->getName() = " << f1->getName() << "\n";
}



void SummaryExecutor::branch(ExecutionState &state, 
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

SummaryExecutor::StatePair 
SummaryExecutor::fork(ExecutionState &current, ref<Expr> condition, bool isInternal) {
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
      outs() << "SummaryExecutor::fork(): Going to execute solver->getValue() at line " << __LINE__ << "\n";
      bool success = solver->getValue(current, condition, value);
      assert(success && "FIXME: Unhandled solver failure");
      (void) success;
      addConstraint(current, EqExpr::create(value, condition));
      condition = value;
    } else
        outs() << "SummaryExecutor::fork(): Not going to execute solver->getValue() at line " << 728 << "\n";
  } else
      outs() << "SummaryExecutor::fork(): Not going to execute solver->getValue() at line " << 728 << "\n";
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

  llvm::outs() << "SummaryExecutor::fork(): isSeeding = " << isSeeding << "\n";
  if (!isSeeding) {
    if (replayPath && !isInternal) {
      llvm::outs() << "SummaryExecutor::fork(): replaying, wtf?! replayPath = " << replayPath << "\n";
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
        //llvm::outs() << "MAKAAAAAKKKA\n";
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

void SummaryExecutor::addConstraint(ExecutionState &state, ref<Expr> condition) {
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

ref<klee::ConstantExpr> SummaryExecutor::evalConstant(const Constant *c) {
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

const Cell& SummaryExecutor::eval(KInstruction *ki, unsigned index, 
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
    //llvm::outs() << "SummaryExecutor::eval() : returning from sf.locals\n";
    return sf.locals[index];
  }
}

void SummaryExecutor::bindLocal(KInstruction *target, ExecutionState &state, 
                         ref<Expr> value) {
  getDestCell(state, target).value = value;
}

void SummaryExecutor::bindArgument(KFunction *kf, unsigned index, 
                            ExecutionState &state, ref<Expr> value) {
  getArgumentCell(state, kf, index).value = value;
}

ref<Expr> SummaryExecutor::toUnique(const ExecutionState &state, 
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
SummaryExecutor::toConstant(ExecutionState &state, 
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

void SummaryExecutor::executeGetValue(ExecutionState &state,
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

void SummaryExecutor::stepInstruction(ExecutionState &state) {
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

void SummaryExecutor::executeCall(ExecutionState &state, 
                           KInstruction *ki,
                           Function *f,
                           std::vector< ref<Expr> > &arguments) {
  llvm::outs() << "SummaryExecutor::executeCall(): inside\n";
  Instruction *i = ki->inst;
  if (f && f->isDeclaration()) {
    //llvm::outs() << "DEBUG: function call to declaration\n";
    switch(f->getIntrinsicID()) {
    case Intrinsic::not_intrinsic:
      //llvm::outs() << "DEBUG: function is not intrinsic\n";
      // state may be destroyed by this call, cannot touch
      llvm::outs() << "SummaryExecutor::executeCall(): going to call external function\n";
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

void SummaryExecutor::transferToBasicBlock(BasicBlock *dst, BasicBlock *src, 
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

void SummaryExecutor::printFileLine(ExecutionState &state, KInstruction *ki) {
  const InstructionInfo &ii = *ki->info;
  if (ii.file != "")
    llvm::errs() << "     " << ii.file << ":" << ii.line << ":";
  else
    llvm::errs() << "     [no debug info]:";
}

/// Compute the true target of a function call, resolving LLVM and KLEE aliases
/// and bitcasts.
Function* SummaryExecutor::getTargetFunction(Value *calledVal, ExecutionState &state) {
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

//void SummaryExecutor::scan2_backup(const ref<Expr> &e) {
//  const ConstantExpr *ce = dyn_cast<ConstantExpr>(e);
//  if (!ce)
//  {
//    Expr *ep = e.get();
//    llvm::outs() << "Considering kids of " << *ep << " (type = " << e->getKind() << ", @" << ep << ")\n";
//    for (unsigned i=0; i<ep->getNumKids(); i++)
//      scan2(ep->getKid(i));
//    llvm::outs() << "End of kids\n";
//
//    if (const ReadExpr *re = dyn_cast<ReadExpr>(e)) {
//      llvm::outs() << "Found a Read expression: " << *re << " (type = " << e->getKind() << ", @" << re << ")\n";
//      llvm::outs() << "The corresponding array: " << re->updates.root->getName() << ", @" <<  re->updates.root << "\n";
//    } else
//    if (const ConcatExpr *ce = dyn_cast<ConcatExpr>(e)) 
//    {
//      llvm::outs() << "Found a Concat expression: " << *ep << " (type = " << e->getKind() << ", @" << ep << ")\n";
//      llvm::outs() << call_symbolic_replacements.count(ep) << "\n";
//    } else
//      llvm::outs() << "Found another expression: " << *ep << " (type = " << e->getKind() << ", @" << ep << ")\n";
//
//  } else 
//  {
//    llvm::outs() << "Found a Constant expression: " << *ce << " (type = " << e->getKind() << ", @" << ce << ")\n";
//  }
//}


/* Extract all ConcatExpr which are concatenations of two reads from e.
 *
 * Recursivealy consider all kids of e, returning a kid if it is a concat 
 * exprssion of two reads.
 *
 * @param e Exprssion to extract concats from
 * @return Vector of all found concat expressions
 */
//std::vector<const ConcatExpr *> SummaryExecutor::extract_concat_subexpressions(ref<Expr> e)
//std::vector<ref<Expr> > SummaryExecutor::extract_concat_subexpressions(ref<Expr> e)
//{
//  std::vector<ref<Expr> > res;
//
//  const ConstantExpr *ce = dyn_cast<ConstantExpr>(e);
//  if (!ce)
//  {
//    Expr *ep = e.get();
//
//    if (const ConcatExpr *ce = dyn_cast<ConcatExpr>(e)) 
//    {
//      //llvm::outs() << "SummaryExecutor::extract_concat_subexpressions(): Found a concat expression: " << *ce << "\n";
//      res.push_back(e);
//    }
//
//    for (unsigned i=0; i<ep->getNumKids(); i++)
//    {
//      std::vector<ref<Expr> > sub_res;
//      sub_res = extract_concat_subexpressions(ep->getKid(i));
//      res.insert(res.end(), sub_res.begin(), sub_res.end());
//    }
//  }
//  return res;
//}

#if 0 // Moved to ExprUtil.cpp
std::vector<ref<Expr> > SummaryExecutor::extract_concat_subexpressions(ref<Expr> e)
{
  std::vector<ref<Expr> > res;

  const klee::ConstantExpr *ce = dyn_cast<klee::ConstantExpr>(e);
  if (!ce)
  {
    Expr *ep = e.get();

    if (const klee::ConcatExpr *ce = dyn_cast<klee::ConcatExpr>(e)) 
    {
      //llvm::outs() << "SummaryExecutor::extract_concat_subexpressions(): Found a concat expression: " << *ce << "\n";
      res.push_back(e);
    }

    for (unsigned i=0; i<ep->getNumKids(); i++)
    {
      std::vector<ref<Expr> > sub_res;
      sub_res = extract_concat_subexpressions(ep->getKid(i));
      res.insert(res.end(), sub_res.begin(), sub_res.end());
    }
  }
  return res;
}
#endif



/* The current stack frame keeps the seq_number of the call symbolics */
/* The call symbolics are in the
 * current_state->cur_path_summary->call_symbolic_replacements */
InnerCall* SummaryExecutor::get_InnerCall_by_seqnum(path_summary_ty *smmry, unsigned seqnum)
{
  InnerCall *res = NULL;
  for(call_symbolic_replacements_ty::iterator it  = smmry->call_symbolic_replacements.begin();
                                              it != smmry->call_symbolic_replacements.end();
                                              ++it)
  {
    InnerCall *inner_call = it->second;
    llvm::outs() << "SummaryExecutor::get_InnerCall_by_seqnum(): Considering suppl call" << *(inner_call->call_inst) <<
                      " with seq num =  " << inner_call->seq_num << "\n";
    if(seqnum == inner_call->seq_num)
      return inner_call;
  }
  return NULL;
}



/* Replace all concat expressions in <conditions> with <retvalue> */
ref<Expr> SummaryExecutor::comp_symbex_replace_for_retvalue(ref<Expr> expr, ref<Expr> &retvalue)
{
  if (isa<ConstantExpr>(expr))
    return expr;

  /* If it is something like [Eq false (Eq 2 (ReadLSB w32 0 arg_printGesture_1))] */
  if (BinaryExpr *be = dyn_cast<BinaryExpr>(expr)) 
  {

    ref<Expr> arr[2];
    /* if child is a concat, replace with revalue */
    if(isa<ConcatExpr>(be->left))
      arr[0] = retvalue;
    else
      arr[0] = comp_symbex_replace_for_retvalue(be->left, retvalue);

    if(isa<ConcatExpr>(be->right))
      arr[1] = retvalue;
    else
      arr[1] = comp_symbex_replace_for_retvalue(be->right, retvalue);

    ref<Expr> tmp = be->rebuild(arr);

    return tmp;

  }

  /* If it is something like [Select w32 (Eq 4 (ReadLSB w32 0 arg_printGesture_1)) 9 4] */
  else if (SelectExpr *se = dyn_cast<SelectExpr>(expr)) 
  {
    //llvm::outs() << "SummaryExecutor::comp_symbex_replace_for_retvalue():  considerting select:\n" << *se << "\n";
    ref<Expr> arr[3];
    if(isa<ConcatExpr>(se->cond))
      arr[0] = retvalue;
    else
      arr[0] = comp_symbex_replace_for_retvalue(se->cond, retvalue);

    if(isa<ConcatExpr>(se->trueExpr))
      arr[1] = retvalue;
    else
      arr[1] = comp_symbex_replace_for_retvalue(se->trueExpr, retvalue);

    if(isa<ConcatExpr>(se->falseExpr))
      arr[2] = retvalue;
    else
      arr[2] = comp_symbex_replace_for_retvalue(se->falseExpr, retvalue);

    ref<Expr> tmp = se->rebuild(arr);

    return tmp;

  }
  else /* Everything else with one or two kids */
  {
    llvm::outs() << "SummaryExecutor::comp_symbex_replace_for_retvalue(): general case\n";
    unsigned numkids = expr->getNumKids();
    assert(numkids && "zero numkids for non costant expression, wtf!?");
    if(numkids == 1)
    {
      llvm::outs() << "SummaryExecutor::comp_symbex_replace_for_retvalue(): general case, 1 kid\n";
      ref<Expr> arr[1];
      if(isa<ConcatExpr>(expr->getKid(0)))
        arr[0] = retvalue;
      else
        arr[0] = comp_symbex_replace_for_retvalue(expr->getKid(0), retvalue);
      ref<Expr> tmp = expr->rebuild(arr);
      return tmp;
    }
    else if(numkids == 2)
    {
      llvm::outs() << "SummaryExecutor::comp_symbex_replace_for_retvalue(): general case, 2 kids\n";
      ref<Expr> arr[2];
      if(isa<ConcatExpr>(expr->getKid(0)))
        arr[0] = retvalue;
      else
        arr[0] = comp_symbex_replace_for_retvalue(expr->getKid(0), retvalue);

      if(isa<ConcatExpr>(expr->getKid(1)))
        arr[1] = retvalue;
      else
        arr[1] = comp_symbex_replace_for_retvalue(expr->getKid(1), retvalue);

      ref<Expr> tmp = expr->rebuild(arr);
      return tmp;
    }
    else
    {
      llvm::outs() << "SummaryExecutor::comp_symbex_replace_for_retvalue(): general case, " << numkids << " kids\n";
      assert(0 && "number of kids is not supported");
    }
  }
  assert(0 && "expression type is not supported yet");
}

#if 0
/* Extract call symbolic replacements from <retvalue>
 *
 * We need this funcntion to understand how many symbolic replacements
 * are a part of the return value. We use it to decide if we need to pass
 * some constraints to a supplimentray function.
 *
 * @param state Execution state from which we check symbolic replacements
 * @param retvalue The return value of the function that the <state> is executing
 * @return vector of symbolic replacements which are a part of retvalue
 */
std::vector<ref<Expr> > SummaryExecutor::extract_call_symbolics_from_expression(ExecutionState *state, ref<Expr> retvalue)
{
  llvm::Function *cur_func = state->prevPC->inst->getParent()->getParent();
  std::vector<ref<Expr> > res;
  for(call_symbolic_replacements_ty::iterator it_1  = state->call_symbolic_replacements[cur_func].begin();
                                              it_1 != state->call_symbolic_replacements[cur_func].end(); ++it_1)
  {
    ref<Expr> symbolics = it_1->first;
    std::vector<ref<Expr> > concats = extract_concat_subexpressions(retvalue);
    for(std::vector<ref<Expr> >::iterator it_2 = concats.begin(); it_2 != concats.end(); ++it_2) 
    { 
      ref<Expr> concat = *it_2;
      if( symbolics == concat) 
      {
        res.push_back(symbolics);
        break;
      }
    }
  }
  return res;
}

std::vector<ref<Expr> > SummaryExecutor::extract_call_symbolics_from_expression(PathSummary *smmry, ref<Expr> retvalue)
{
  std::vector<ref<Expr> > res;
  for(call_symbolic_replacements_ty::iterator it_1  = smmry->call_symbolic_replacements.begin();
                                              it_1 != smmry->call_symbolic_replacements.end(); ++it_1)
  {
    ref<Expr> symbolics = it_1->first;
    std::vector<ref<Expr> > concats = extract_concat_subexpressions(retvalue);
    for(std::vector<ref<Expr> >::iterator it_2 = concats.begin(); it_2 != concats.end(); ++it_2) 
    { 
      ref<Expr> concat = *it_2;
      if( symbolics == concat) 
      {
        res.push_back(symbolics);
        break;
      }
    }
  }
  return res;
}
#endif

std::vector<ref<Expr> > SummaryExecutor::extract_constraints_for_symbolics(ConstraintManager &path_constraints, ref<Expr> &e)
{
  std::vector<ref<Expr> > res;
  for(std::vector< ref<Expr> >::const_iterator it_1  = path_constraints.begin(); 
                                               it_1 != path_constraints.end(); ++it_1) //For each condition in the summary
  {
    const ref<Expr> cond = *it_1;
    std::vector<ref<Expr> > concats = extract_concat_subexpressions(cond);
    for(std::vector<ref<Expr> >::iterator it_2 = concats.begin(); it_2 != concats.end(); ++it_2) 
    { 
      ref<Expr> concat = *it_2;
      if(e == concat) 
      {
        res.push_back(cond);
        break;
      }
    }
  }
  return res;
}


void SummaryExecutor::executeInstruction(ExecutionState &state, KInstruction *ki) {
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
     * history. ivan: when collecting summaries, we don't use go inside
     * calls, so TODO: remove the next two lines.*/
    if(false && state.callHistory.size() != 0)
      state.callHistory.pop_back();
    /* *** */
    
    
#if 0 // We don't have interrupts in Summary Executor
    /* Check if we are returning from an ISR */
    bool interruptExit = false;
    if (state.interruptFun && (ki->inst->getParent()->getParent() == state.interruptFun))
    {
      interruptExit = true;
      state.interruptFun = NULL;
    }
    /* *** */
#endif
    
    if (!isVoidReturn) {
      result = eval(ki, 0, state).value;
    }

    assert((state.stack.size() <= 1) && "Stack size should be 1 in Summary Executor");

    llvm::outs() << "SummaryExecutor::executeInstruction():Ret : Terminating state on exit, result = " <<  result << "\n";
    llvm::Function *cur_func = ri->getParent()->getParent();

#if 0
    ConstantExpr *ce = dyn_cast<ConstantExpr>(result);
    /* If return value is a call symbolics, we need to pass
     * current retavlue conditions to the corresponding inner call*/
    if (!ce) 
    {
      llvm::outs() << "SummaryExecutor::executeInstruction():Ret: result is not a constant! " << result << "\n";
      //std::vector<ref<Expr> > symbs = extract_call_symbolics_from_expression(&state, result);
      std::vector<ref<Expr> > symbs = state.get_call_symbolics(result);
      llvm::outs() << "SummaryExecutor::executeInstruction():Ret: result contains " << symbs.size() << " call symbolics.\n";
      // So our return value is symbolic => return constraints will always be satisfied.
      // We need to pass constraints on this symbolics to the corresponding suppl call.
      assert( (symbs.size() <= 1) && "Complex symbolic return values are not supported yet");
      
      if(symbs.size() == 1)
      {
        llvm::outs() << "SummaryExecutor::executeInstruction(): Ret: adding the current state's retval_conditions to suppl call:\n";
        print_expressions(*state.ret_value_constraints);
        InnerCall *inner_call = state.call_symbolic_replacements[cur_func][symbs[0]];
        inner_call->retval_conditions.insert(inner_call->retval_conditions.end(),
                     state.ret_value_constraints->begin(), state.ret_value_constraints->end());
      }
    }
#endif

    /* Create new path summary of type RET_SUMMARY_TYPE */
    llvm::outs() << "SummaryExecutor::executeInstruction():Ret: creating new path summary with the following path constraints:\n";
    std::string constraints;
    getConstraintLog(state, constraints, KQUERY);
    llvm::outs() << "                           constraints for the state: \n" << constraints;
    llvm::outs() << "SummaryExecutor::executeInstruction():Ret: Adding new path summary for function " << cur_func->getName() 
                 << "(); ret value = " << result << "\n";
    path_summary_ty *smmry = new PathSummary(cur_func, result, state.constraints);
    llvm::outs() << "SummaryExecutor::executeInstruction():Ret: Summary created\n";
    smmry->call_symbolic_replacements = state.call_symbolic_replacements[cur_func];
    smmry->fargs = this->fargs;
    //llvm::outs() << "SummaryExecutor::executeInstruction():Ret: extracting constraints on globals for the summary\n";
    //smmry->extract_constraints_on_globals();
    smmry->path_choices = state.path_choices;
    smmry->path_choices_debug = state.path_choices_debug;
    //smmry->path_instructions = state.path_instructions;
    smmry->path_instructions = state.stack.back().path_instructions;
          smmry->type = PathSummary::RET_SUMMARY_TYPE;
    path_summaries.push_back(smmry);
    this->num_new_summaries_during_round++;
    llvm::outs() << "SummaryExecutor::executeInstruction():Ret: Summary added\n";
    
    /* If we are interested in a good path summary for an inner call:
     * check if the function args and return value satisifeid inner call
     * conditions */
    if(state.cur_inner_call != NULL)
    {
      if( BreakOnFirstFit && (interpreter_manager->comp_symbex_can_glue2(smmry, state.cur_inner_call)) ) 
      {
        comp_symbex_target_reached = 1;
        state.cur_inner_call->path_summary_found = true;
        //llvm::outs() << "DEBUG: the return value is good!\n";
        //llvm::outs() << "Adding new path good summary for function " << cur_func->getName()  << " and terminating the state\n";
      }
    }
    if((interpreter_manager->smmries_per_run) && (interpreter_manager->smmries_per_run <= this->num_new_summaries_during_round))
      comp_symbex_target_reached = 1;
    ///IVAN ADDITIONS END
    /* Finally terminate the state (summary executor we don't have anywhere to return)
     * and break from switch case */
    print_state_constraints(&state);
    llvm::outs() << "SummaryExecutor::executeInstruction():Ret: Done with all checks, terminating the state\n";
    terminateStateOnExit(state);
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
      outs() << "SummaryExecutor::executeInstruction()::Br: cond = " << cond << "\n";
      SummaryExecutor::StatePair branches = fork(state, cond, false);
      outs() << "SummaryExecutor::executeInstruction()::Br: forked sucessfully\n";

      // NOTE: There is a hidden dependency here, markBranchVisited
      // requires that we still be in the context of the branch
      // instruction (it reuses its statistic id). Should be cleaned
      // up with convenient instruction specific data.
      if (statsTracker && state.stack.back().kf->trackCoverage)
        statsTracker->markBranchVisited(branches.first, branches.second);

      if (branches.first)
      {
        outs() << "SummaryExecutor::executeInstruction()::Br: branches.first is not NULL\n";
        transferToBasicBlock(bi->getSuccessor(0), bi->getParent(), *branches.first);
      }
      // IVAN ADDITIONS BEGIN
#if 0 // buggy code follows (you don't check if <f> is in cfg_paths => you can create an empty element
      else 
      {
        BasicBlock *trueBlock = bi->getSuccessor(0);
        Function *f = bi->getParent()->getParent();
        /* If the infeasable true branch is on the path, we might want to rebuild the path */
        if(std::find(path_manager->cfg_paths[f].begin(),
	             path_manager->cfg_paths[f].end(),trueBlock) != path_manager->cfg_paths[f].end())
        {
          state.path_arc_falures[bi->getParent()].first++;
          outs() << "DEBUG: Path goes through True branch, but this branch is infeasable (number of failures = " 
                 << state.path_arc_falures[bi->getParent()].first << ").\n";
          if(state.path_arc_falures[bi->getParent()].first >= 1)
          {
            outs() << "DEBUG: Rebuildig infeasable True arc.\n";
            path_manager->rebuildInfeasableCFGPath(bi->getParent(), bi->getSuccessor(0));
          }
        }
      }
#endif
      // IVAN ADDITIONS END

      if (branches.second)
      {
        outs() << "SummaryExecutor::executeInstruction()::Br: branches.second is not NULL\n";
        transferToBasicBlock(bi->getSuccessor(1), bi->getParent(), *branches.second);
      }
      // IVAN ADDITIONS BEGIN
#if 0 // buggy code follows (you don't check if <f> is in cfg_paths => you can create an empty element
      else 
      {
        BasicBlock *falseBlock = bi->getSuccessor(1);
        Function *f = bi->getParent()->getParent();
        // If false branch is on the path
        //if(state.isOnPath == true)
        if(std::find(path_manager->cfg_paths[f].begin(),
	             path_manager->cfg_paths[f].end(),falseBlock) != path_manager->cfg_paths[f].end())
        {
          state.path_arc_falures[bi->getParent()].second++;
          outs() << "DEBUG: Path goes through False branch, but this branch is infeasable (number of failures = " 
                 << state.path_arc_falures[bi->getParent()].second << ").\n";
          if(state.path_arc_falures[bi->getParent()].second >= 1)
          {
            outs() << "DEBUG: Rebuildig infeasable False arc.\n";
            // Path between on-path blocks looks to be infeasable (bi->geParent() -- bi->getSuccessor(1))
            // We will try to find another path
            path_manager->rebuildInfeasableCFGPath(bi->getParent(), bi->getSuccessor(1));
          }
        }
      }
#endif
      // IVAN ADDITIONS END
    }
    break;
  }
  case Instruction::Switch: {
    SwitchInst *si = cast<SwitchInst>(i);
    ref<Expr> cond = eval(ki, 0, state).value;
    BasicBlock *bb = si->getParent();
    //exit(0);

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

    if (f) {

      /// IVAN ADDITIONS BEGIN
      
      /* If we reached a call to a function from 
       * path_manager->path_function: add new path summary */
      //if(f && std::find(path_manager->path_functions.begin(),
	    //         path_manager->path_functions.end(),f) != path_manager->path_functions.end())
      if(f && std::find(path_manager->call_path.begin(),
	             path_manager->call_path.end(),f) != path_manager->call_path.end())
      {
        llvm::outs() << "SummaryExecutor::executeInstruction(): Call:: Calling a call-graph function: " 
                     << f->getName() << "\n";
        std::string constraints;
        getConstraintLog(state, constraints, KQUERY);
        llvm::outs() << "                           constraints for the state: \n" << constraints;
        llvm::Function *cur_func = i->getParent()->getParent();

        path_summary_ty *new_smmry = new PathSummary(cur_func,
                      ConstantExpr::alloc(0, Expr::Int16), state.constraints, f, arguments);
        new_smmry->call_symbolic_replacements = state.call_symbolic_replacements[cur_func];
        new_smmry->fargs = this->fargs;
        //new_smmry->extract_constraints_on_globals();
        new_smmry->path_choices = state.path_choices;
        new_smmry->path_choices_debug = state.path_choices_debug;
        //new_smmry->path_instructions = state.path_instructions;
        new_smmry->path_instructions = state.stack.back().path_instructions;
        llvm::outs() << "SummaryExecutor::executeInstruction()::Call: number of call symbolics in path summary = " << 
                        new_smmry->call_symbolic_replacements.size() << "\n";
        llvm::outs() << "SummaryExecutor::executeInstruction()::Call: number of call symbolics in state = " << 
                        state.call_symbolic_replacements[cur_func].size() << "\n";
        llvm::outs() << "SummaryExecutor::executeInstruction()::Call: new_smmry.target_func_actual_args.size() = " << 
                        new_smmry->target_func_actual_args.size() << "\n";
        llvm::outs() << "SummaryExecutor::executeInstruction()::Call: arguments.size() = " << 
                        arguments.size() << "\n";
        llvm::outs() << "SummaryExecutor::executeInstruction()::Call: numArgs= " << 
                        numArgs << "\n";
	new_smmry->type = PathSummary::TARGET_FUNC_SUMMARY_TYPE;
        new_smmry->end_function = f;
        path_summaries.push_back(new_smmry);
	this->num_new_summaries_during_round++;
        
        //terminateStateOnExit(state);

        /* If the called function is also the target funtion for the
         * state, then we are done with summaries */
        if (BreakOnFirstFit && (f == state.target_func))
        {
          if(state.target_func != path_manager->call_path[path_manager->call_path.size()-1]) // If this is not the final target function (i.e. assert())
          {
            llvm::outs() << "SummaryExecutor::executeInstruction()::Call: state.target_func  = " << state.target_func->getName() << "\n";  
            //if(interpreter_manager->comp_symbex_can_glue(cur_func, state, arguments)) // This will check if we can glue summaries of the current and the next functions; We can finish if we can really glue with some summary
            if(interpreter_manager->comp_symbex_can_glue2(new_smmry, state.cur_upper_call)) 
            {
              llvm::outs() << "SummaryExecutor::executeInstruction()::Call: the current state can be glued with"  
                              " one of the next on-path summaries\n";
              comp_symbex_target_reached = 1;
              //good_path_summaries.push_back(new_smmry);
            }
          } else 
          {
            comp_symbex_target_reached = 1;
            //good_path_summaries.push_back(new_smmry);
          }
        }
        //break; // We are done with the call instruction
      }
      if((interpreter_manager->smmries_per_run) && (interpreter_manager->smmries_per_run <= this->num_new_summaries_during_round))
        comp_symbex_target_reached = 1;
      
      /* replacing function call with a symbolic value
       *   <f> is a called function
       *   <ki>, <i> is the current instruction
       *   
       * In case of backward symbex: If it is not a declaration 
       * we don't call the function, but
       * just make the return result symbolic and break the switch
       * statement .*/
      //if (!forward_symbex && !f->isDeclaration() && (f != state.target_func))
      /* If if is not klee_make_symbolic, memset, etc */
      if (!f->isDeclaration())
      {

        /* Ivan: The following check is redundant (and wrong) I guess */
        if((f->getName().str() == "klee_div_zero_check") || (f->getName().str() == "memset") ||
            (f->getName().str() == "memcpy") || (f->getName().str() == "klee_overshift_check"))
        {
          //llvm::outs() << "SummaryExecutor::explore_inner_call(): skipping klee_div_zero_check.\n";
          break;
        }

        //if(f->getName().str() == "abs_")
        //{
        //  llvm::outs() << "SummaryExecutor::explore_inner_call(): skipping abs_.\n";
        //  break;
        //}

        //if(f->getName().str() == "avg")
        //{
        //  llvm::outs() << "SummaryExecutor::explore_inner_call(): skipping avg.\n";
        //  break;
        //}


        llvm::outs() << "SummaryExecutor::executeInstruction():Call: replacing call instruction '" << *(ki->inst) << "' with symbolic variable.\n";
        ref<Expr> result = ConstantExpr::alloc(0, Expr::Bool);
        static unsigned id = 0;

        llvm::Type *return_type = f->getReturnType();
        llvm::outs() << "SummaryExecutor::executeInstruction(): return type: " << *return_type << "\n";
        unsigned w = 0;

        if(!return_type->isVoidTy())
          w = getWidthForLLVMType(return_type);
        else
          w = Context::get().getPointerWidth(); /* Dummy for void type */
        assert(w && "Return width cannot be zero");

        /* If ret value is a pointer, then we allocate some symbolic memory for it */
        if(isa<llvm::PointerType>(return_type))
        {
          llvm::outs() << "SummaryExecutor::executeInstruction(): fun return type is a pointer\n";
          llvm::Type *element_type = (dyn_cast<llvm::PointerType>(return_type))->getElementType();
          Expr::Width w = getWidthForLLVMType(element_type);
          uint64_t size = w*64;
          MemoryObject *mo = memory->allocate(size, false, true, f->begin()->begin());
          if (!mo)
            llvm::report_fatal_error("out of memory");
          ObjectState *os = bindObjectInState(state, mo, false);
          std::string name;
          name = "res_" + f->getName().str() + "_" + llvm::utostr(id);
          executeMakeSymbolic(state, mo, name);
          result = mo->getBaseExpr();
        }
        else
	      {
          const Array *array = Array::CreateArray("res_" + f->getName().str() + "_" + llvm::utostr(id), Expr::getMinBytesForWidth(w) );
          result = Expr::createTempRead(array, w);
        }

        id++;
        //llvm::outs() << "SummaryExecutor::executeInstruction(): creating new symbolic array with size " << w << "\n";
        llvm::outs() << "SummaryExecutor::executeInstruction(): result =  " << result << "\n";
        llvm::outs() << "SummaryExecutor::executeInstruction(): result->hash() =  " << result->hash() << "\n";
        bindLocal(ki, state, result);
        CallInst *ci = dyn_cast<CallInst>(i);
        llvm::Function *cur_func = i->getParent()->getParent();

        /* Create a new call symbolic replacement and add it to to the list of symbolics
         * for the current state. */
        //state.call_symbolic_replacements[cur_func][result] = InnerCall(result, ci); // result is a symbolic expression
        InnerCall *new_inner_call = new InnerCall(result, ci, state.constraints); // result is a symbolic expression
        unsigned seq_num = state.call_symbolic_replacements[cur_func].size(); // We start seq_num's from 0
        new_inner_call->seq_num = seq_num;
        //state.call_symbolic_replacements[cur_func][result].seq_num = seq_num;

        /* Extract constraints on actual arguments (we will use them as constraints of formal arguments when
         * we execute the inner call */
        //new_inner_call->update_formal_args_conds(state.constraints, arguments);
        new_inner_call->actual_args = arguments;
        llvm::outs() << "SummaryExecutor::executeInstruction():Call: arguments.size() = " << arguments.size() << "\n";
        new_inner_call->fargs = this->fargs;

        //llvm::outs() << "SummaryExecutor::executeInstruction():Call: updating constrains on globals for Suppl call "
        //             << "for " << *ci << "\n";
        llvm::outs() << "SummaryExecutor::executeInstruction():Call: we have the following path constraints so far:\n";
        print_state_constraints(&state);
        //new_inner_call->update_constraints_on_globals(state.global_symbolic_replacements, state.constraints);
        state.call_symbolic_replacements[cur_func][result] = new_inner_call;

        llvm::outs() << "DEBUG:SummaryExecutor::executeInstruction()::Call: As we have a function call => we should assume that global variables have changed\n";


        setFreshSymbolicsToGlobals(&state, "Inner call", f);
 #if 0 // The code below is replaced by the function above
        // This should assign a new symbolic value to global values
        std::vector<llvm::Value *> globals = get_global_calling_context(cur_func); // get the list of global variables which are read and written in the function
        for(std::vector<llvm::Value *>::iterator it = globals.begin(); it != globals.end(); ++it)
        {
          MemoryObject* mo = globalObjects[(GlobalValue *)(*it)];
          unsigned id = 0;
          std::string name = (*it)->getName().str();
          std::string uniqueName = name;
          while (!state.arrayNames.insert(uniqueName).second) {
            uniqueName = name + "_" + llvm::utostr(++id);
          }
          const Array *new_array = Array::CreateArray(uniqueName, mo->size);
          bindObjectInState(state, mo, false, new_array);
          state.global_symbolic_replacements[*it].push_back(new_array);
        }
#endif

        //std::vector<llvm::Value *> globals = get_global_calling_context(cur_func); // get the list of global variables which are read and written in the function
        //make_globals_symbolic(&state, globals); // This will assign new arrays (with new names) to the globals
      }
      /* Pass only klee special functions */ 
      SpecialFunctionHandler::handlers_ty::iterator it = specialFunctionHandler->handlers.find(f);
	    if( (f->isDeclaration()) && (f->getIntrinsicID() == Intrinsic::not_intrinsic) &&
           (it != specialFunctionHandler->handlers.end()) 
      )
      {
        llvm::outs() << "SummaryExecutor::executeInstruction():Call: will execute function (looks like special functio handler)\n";
        /* Special function handler will be invoked in executeCall(),
         * which does not set new stack frame, nor execute any llvm
         * code (but might set e.g. symbolic values, or assign new
         * values to MSP430 status register */
      } else
      {
        llvm::outs() << "SummaryExecutor::executeInstruction():Call: finishing with call instruction\n";
        break;
      }
      ///* Let pass only some klee internal functions */
      //if((f->getName().str() != "klee_make_symbolic"))
      //{
      //  break;  /* We are done with Call instruction. */
      //}


      if (false && f && !f->isDeclaration())
        state.callHistory.push_back((Instruction *)i); // add the *CallInst to the end of our call History

      /// IVAN ADDITIONS END
      
      
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
    llvm::outs() << "SummaryExecutor::executeInstruction(): And: " << result << "\n";
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
    llvm::outs() << "SummaryExecutor::executeInstruction(): Load: base = " << base << "\n";
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
    llvm::outs() << "SummaryExecutor::executeInstruction(): Store: base = " << base << "\n";
    executeMemoryOperation(state, true, base, value, 0);
    llvm::outs() << "Returned from executeMemoryOperation()\n";
    break;
  }

  case Instruction::GetElementPtr: {
    KGEPInstruction *kgepi = static_cast<KGEPInstruction*>(ki);
    ref<Expr> base = eval(ki, 0, state).value;
    llvm::outs() << "SummaryExecutor::executeInstruction(): GetElemetPtr: base = " << base << "\n";

    for (std::vector< std::pair<unsigned, uint64_t> >::iterator 
           it = kgepi->indices.begin(), ie = kgepi->indices.end(); 
         it != ie; ++it) {
      uint64_t elementSize = it->second;
      ref<Expr> index = eval(ki, it->first, state).value;
      llvm::outs() << "SummaryExecutor::executeInstruction(): GetElemetPtr: considering index " 
                   << index << " with size " << elementSize << "\n";
      base = AddExpr::create(base,
                             MulExpr::create(Expr::createSExtToPointerWidth(index),
                                             Expr::createPointer(elementSize)));
      llvm::outs() << "SummaryExecutor::executeInstruction(): GetElemetPtr: new base = " << base << "\n";
    }
    if (kgepi->offset)
    {
      base = AddExpr::create(base,
                             Expr::createPointer(kgepi->offset));
      llvm::outs() << "SummaryExecutor::executeInstruction(): GetElemetPtr:  base after adding offset = " << base << "\n";
    }
    llvm::outs() << "SummaryExecutor::executeInstruction(): GetElemetPtr:  base to go to bind local = " << base << "\n";
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
    llvm::outs() << "SummaryExecutor::executeInstruction(): ZExt: " << result << "\n";
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




void SummaryExecutor::updateStates(ExecutionState *current) {
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
void SummaryExecutor::clearOffsets(KGEPInstruction *kgepi, TypeIt ib, TypeIt ie) {
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
void SummaryExecutor::computeOffsets(KGEPInstruction *kgepi, TypeIt ib, TypeIt ie) {
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

void SummaryExecutor::bindInstructionConstants(KInstruction *KI) {
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

void SummaryExecutor::bindModuleConstants() {
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



#if 0 /* We needed this funtion for forward symbex. We don't use forward symbex in this class,
         so don't need this function either */
bool SummaryExecutor::state_complies_with_fsummary1(ExecutionState *state)
{
  StackFrame &sf = state->stack.back();
  path_summary_ty *cur_fsummary = sf.cur_fsummary;
  //assert(cur_fsummary && "DEBUG ASSERT: replace for returning true");
  /* The only case when a suppl call's connected fsummary is NULL is
   * when we deliberately decided not to explore it. In this case we
   * do all forking stuff for this function */
  if(!cur_fsummary)
  {
    llvm::outs() << "SummaryExecutor::state_complies_with_fsummary1(): cur_fsummary is NULL => returning true\n";
    return true; 
  }
  unsigned index = sf.path_instructions.size() - 1;
  llvm::outs() << "SummaryExecutor::state_complies_with_fsummary1(): comparing " << *(sf.path_instructions[index]) <<
                  " and " << *(cur_fsummary->path_instructions[index]) << "\n";
  llvm::outs() << "SummaryExecutor::state_complies_with_fsummary1(): this is instruction " << index+1 << " out of " <<
                  cur_fsummary->path_instructions.size() << "\n";
  if(sf.path_instructions[index] == cur_fsummary->path_instructions[index])
  {
    llvm::outs() << "SummaryExecutor::state_complies_with_fsummary1(): returning true\n";
    return true;
  }
    llvm::outs() << "SummaryExecutor::state_complies_with_fsummary1(): returning false\n";
  return false;
}
#endif


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
bool SummaryExecutor::isStateMergeTime(KInstruction *ki)
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
    //llvm::outs() << "SummaryExecutor:::isStateMergeTime(): MergeFreq = BBL; we are at the head; returning true\n";
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
void SummaryExecutor::initializeMergeBlackList()
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
bool SummaryExecutor::isDuplicateState(ExecutionState& state, KInstruction *ki)
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

  /*llvm::outs() << "SummaryExecutor::isDuplicateState(): enter checkDuplicateState\n";
  llvm::outs() << "SummaryExecutor::isDuplicateState(): There are " << allSavedConfigs.size() << " indices\n";*/
  
  //state.printRegs();
 
  /* Do we have any saved memory configuration for the current instruction? */
  if (allSavedConfigs.find(inst) == allSavedConfigs.end())
  {
    SavedConfig * savedConfig = new SavedConfig(state);
    ConfList * confList = new ConfList(savedConfig);
    allSavedConfigs[inst] = (confList);
    //llvm::outs() << "SummaryExecutor::isDuplicateState(): No memory config for the current instruction. Adding new memory config.\n";
    return false;
  }

  /* We have saved memory configuration for the current instruction, let's check it
     in more detail */
  //llvm::outs() << "SummaryExecutor::isDuplicateState(): Not adding new memory config\n";
  ConfList * confList = allSavedConfigs[inst];
  unsigned points = confList->size();
  //llvm::outs() << "SummaryExecutor::isDuplicateState(): points = " << points << "\n";
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
/* *** Interrupts routines end *** */

//int SummaryExecutor::continue_run(const Function *target_func, InnerCall *inner_call) 
int SummaryExecutor::continue_run(UpperCall *upper_call, InnerCall *inner_call) 
{
  //bindModuleConstants();
  //states.insert(&initialState);
  assert((!upper_call || !inner_call) && "upper_call and inner_call are mutually exclusive");
  assert((upper_call || inner_call) && "upper_call and inner_call cannot be both NULL");


  llvm::outs() << "SummaryExecutor::continue_run(): constructing searcher...\n";
  delete searcher;
  searcher = constructUserSearcher(*this);
  llvm::outs() << "SummaryExecutor::continue_run(): searcher constructed...\n";

  llvm::Function *target_func = NULL;
  if(upper_call)
    target_func = upper_call->fn;

  for (std::set<ExecutionState*>::iterator it = states.begin(), ie = states.end(); it != ie; ++it) 
  {
    ExecutionState *s = *it;
    s->target_func = target_func;
    s->cur_inner_call = inner_call;
    s->cur_upper_call = upper_call;
    s->complies_with_cur_inner_call = true;
  }

  searcher->update(0, states, std::set<ExecutionState*>());
  //searcher->setPathManager(path_manager);
  //searcher->slave_search_freq = interpreter_manager->slave_search_freq;
  //searcher->prefer_short_summaries = true;
  searcher->no_good_states = false; 

  comp_symbex_target_reached = 0;
  haltExecution = 0;
  llvm::outs() << "SummaryExecutor::continue_run(): states.size() = " << states.size() << "\n";
  int start_time = time(NULL);
  int cur_time = time(NULL);
  this->num_new_summaries_during_round = 0;
  while (!states.empty() && 
         !haltExecution && 
         !searcher->no_good_states && 
	       !comp_symbex_target_reached &&
	       ((cur_time - start_time) < interpreter_manager->collect_timeout)) {
    cur_time = time(NULL);
    if(((cur_time - start_time) >= interpreter_manager->collect_timeout))
      llvm::outs() << "SummaryExecutor::continue_run(): Finishing by timeout (last iteration)\n";
    llvm::outs() << "SummaryExecutor::continue_run(): inside main loop\n";
    ExecutionState &state = searcher->selectState();
    //if(!state.complies_with_cur_inner_call)
    if(!state_complies_with_inner_call(&state))
      continue;
    llvm::outs() << "\n\n == Selected state " << &state << "(in function " 
                 << state.pc->inst->getParent()->getParent()->getName() 
		 << "() ); number of states = " << states.size() << "\n";
    llvm::outs() << " == instsruction " << *state.pc->inst << "\n";

    KInstruction *ki = state.pc;

    Instruction *instr = ki->inst;
    std::string instr_str;
    raw_string_ostream str_stream(instr_str);                                 
    str_stream << *instr;
    state.path_choices_debug.push_back(instr_str);
    state.path_instructions.push_back(instr);
    state.stack.back().path_instructions.push_back(instr);

    if (isStateMergeTime(ki) && isDuplicateState(state, ki))
    {
      terminateState(state);
      llvm::outs() << "SummaryExecutor::continue_run(): terminate STATE\n"; 
    } 
    
    stepInstruction(state);
    executeInstruction(state, ki);
    updateGlobalsDueToPossibleInterrupts(&state, ki);

    if (MaxMemory) {
      //fprintf(stderr, "IVAN: inside MaxMemory0\n");
      if ((stats::instructions & 0xFFFF) == 0) {
        //fprintf(stderr, "IVAN: inside MaxMemory1\n");
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
  }
  if(states.empty())
    should_collect_more_summaries = false;
  delete searcher;
  searcher = 0;
  
 dump:
  if (false && DumpStatesOnHalt && !states.empty()) {
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

void SummaryExecutor::run(ExecutionState &initialState) {
  //fprintf(stderr, "IVAN: Inside SummaryExecutor::run\n");
  bindModuleConstants();

  // Delay init till now so that ticks don't accrue during
  // optimization and such.
  //initTimers();

  //llvm::Function *start_func = initialState.pc->inst->getParent()->getParent();
  states.insert(&initialState);

#if 0 /* No seeds in backward symbex */
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

  /* Searcher init */
  llvm::outs() << "SummaryExecutor::run(): constructing searcher...\n";
  searcher = constructUserSearcher(*this);
  llvm::outs() << "SummaryExecutor::run(): searcher constructed...\n";
  searcher->update(0, states, std::set<ExecutionState*>());
  //searcher->setPathManager(path_manager);
  //searcher->slave_search_freq = interpreter_manager->slave_search_freq;
  //searcher->prefer_short_summaries = true;
  searcher->no_good_states = false;
  /** */

  comp_symbex_target_reached = 0;
  haltExecution = 0;
  int start_time = time(NULL);
  int cur_time = time(NULL);
  while (!states.empty() && 
         !haltExecution && 
         !searcher->no_good_states && 
	       !comp_symbex_target_reached && 
	       ((cur_time - start_time) < interpreter_manager->collect_timeout)) {
    cur_time = time(NULL);
    if(((cur_time - start_time) >= interpreter_manager->collect_timeout))
      llvm::outs() << "SummaryExecutor::run(): Finishing by timeout (last iteration)\n";
    llvm::outs() << "SummaryExecutor::run(): inside main loop\n";
    ExecutionState &state = searcher->selectState();
    //if(!state.complies_with_cur_inner_call)
    if(!state_complies_with_inner_call(&state))
      continue;
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

    if (isStateMergeTime(ki) && isDuplicateState(state, ki))
    {
      terminateState(state);
      llvm::outs() << "SummaryExecutor::run(): terminate STATE\n"; 
    } 
     
    stepInstruction(state);
    executeInstruction(state, ki);

    updateGlobalsDueToPossibleInterrupts(&state, ki);

#if 0 // We don't support timers in SummaryExecutor
    processTimers(&state, MaxInstructionTime);
#endif

    if (MaxMemory) {
      //fprintf(stderr, "IVAN: inside MaxMemory0\n");
      if ((stats::instructions & 0xFFFF) == 0) {
        //fprintf(stderr, "IVAN: inside MaxMemory1\n");
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
  }
  if(states.empty())
    should_collect_more_summaries = false;
  delete searcher;
  searcher = 0;
  
 dump:
  if (false && DumpStatesOnHalt && !states.empty()) {
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

std::string SummaryExecutor::getAddressInfo(ExecutionState &state, 
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

void SummaryExecutor::terminateState(ExecutionState &state) {
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

void SummaryExecutor::terminateStateEarly(ExecutionState &state, 
                                   const Twine &message) {
#if 0 /* We don't have interpreter handler in Summary Executor */
  if (!OnlyOutputStatesCoveringNew || state.coveredNew ||
      (AlwaysOutputSeeds && seedMap.count(&state)))
    interpreterHandler->processTestCase(state, (message + "\n").str().c_str(),
                                        "early");
#endif
  terminateState(state);
}

void SummaryExecutor::terminateStateOnExit(ExecutionState &state) {
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

const InstructionInfo & SummaryExecutor::getLastNonKleeInternalInstruction(const ExecutionState &state,
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
void SummaryExecutor::terminateStateOnError(ExecutionState &state,
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

void SummaryExecutor::callExternalFunction(ExecutionState &state,
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

ref<Expr> SummaryExecutor::replaceReadWithSymbolic(ExecutionState &state, 
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
uint64_t SummaryExecutor::get_free_memchunk_at_guest(unsigned size, ExecutionState *state) 
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

ObjectState *SummaryExecutor::bindObjectInState(ExecutionState &state, 
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

void SummaryExecutor::executeAlloc(ExecutionState &state,
                            ref<Expr> size,
                            bool isLocal,
                            KInstruction *target,
                            bool zeroMemory,
                            const ObjectState *reallocFrom) {


  llvm::outs() << "SummaryExecutor::executeAlloc(): inside\n";
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
    assert(0 && "Symbolic sizes to malloc unsupported!");
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

void SummaryExecutor::executeFree(ExecutionState &state,
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
    
    for (SummaryExecutor::ExactResolutionList::iterator it = rl.begin(), 
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

void SummaryExecutor::resolveExact(ExecutionState &state,
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

void SummaryExecutor::executeMemoryOperation(ExecutionState &state,
                                      bool isWrite,
                                      ref<Expr> address,
                                      ref<Expr> value /* undef if read */,
                                      KInstruction *target /* undef if write */) {
  llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: inside\n";
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
  llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: Going inside resolveOne()\n";
  if (!state.addressSpace.resolveOne(state, solver, address, op, success)) {
    address = toConstant(state, address, "resolveOne failure");
    success = state.addressSpace.resolveOne(cast<ConstantExpr>(address), op);
  }
  solver->setTimeout(0);
  llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: returned from resolveOne()\n";

  if (success) {
    llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: sucess = true\n";


    const MemoryObject *mo = op.first;


    /// DREW ADDITIONS BEGIN
    /* Drew's code below is responsible for handling read/writes to/from
     * special memory location: peripheral registers and flash memory.
     * For each such location, the code invokes special read/write
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

    llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: passed over solver->mustBeTrue()\n";

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
          llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: sucess (for write) = true; value = " << value << "\n";
          wos->write(offset, value);
        }          
      } else {
        ref<Expr> result = os->read(offset, type);
        
        llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: sucess (for read) = true; result = " << result << "\n";
	#if 0 /* IVAN: we don't have interpreterOpts in SummaryExecutor */
        if (interpreterOpts.MakeConcreteSymbolic)
          result = replaceReadWithSymbolic(state, result);
	#endif

        
        bindLocal(target, state, result);
      }

      return;
    }
  } else
    llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: sucess = false, going to exit(0)\n";
  
  //exit(0);
  // we are on an error path (no resolution, multiple resolution, one
  // resolution with out of bounds)
  llvm::outs() << "SummaryExecutor::executeMemoryOperation() :: we are on an error path (no resolution, multiple resolution, oneresolution with out of bounds)\n";
  
  ResolutionList rl;  
  solver->setTimeout(coreSolverTimeout);
  bool incomplete = state.addressSpace.resolve(state, solver, address, rl,
                                               0, coreSolverTimeout);
  solver->setTimeout(0);
  llvm::outs() << "SummaryExecutor::executeMemoryOperation():: rl.size() = " << rl.size() << "\n";
  
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

void SummaryExecutor::executeMakeSymbolic(ExecutionState &state, 
                                   const MemoryObject *mo,
                                   const std::string &name) {
  llvm::outs() << "Inside SummaryExecutor::executeMakeSymbolic()\n";
  // Create a new object state for the memory object (instead of a copy).
  if (!replayOut) {
    llvm::outs() << "SummaryExecutor::executeMakeSymbolic(): replayOut is not NULL\n";
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
      llvm::outs() << "SummaryExecutor::executeMakeSymbolic(): in seed mode.\n";
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
    llvm::outs() << "SummaryExecutor::executeMakeSymbolic(): replayOut is NULL\n";
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

/***/

/* Functionality moved to PathSummary::print()
void SummaryExecutor::print_function_summary(path_summary_ty *smmry)
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

void SummaryExecutor::print_state_constraints(ExecutionState *state)
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
//int SummaryExecutor::paint_summary_chains(path_summary_ty *path_smmry)
//{
//  llvm::outs() << "SummaryExecutor::print_summary_chains(): Considering path summary for function " << path_smmry->fn->getName() << "()\n";
//  print_function_summary(path_smmry);
//  int res = 1; // assume that summary is feasible
//  for(call_symbolic_replacements_ty::iterator it_1  = path_smmry->call_symbolic_replacements.begin();
//                                              it_1 != path_smmry->call_symbolic_replacements.end(); ++it_1)
//  {
//    InnerCall *inner_call = it_1->second;
//    llvm::Function *suppl_fn = inner_call->call_inst->getCalledFunction();
//    llvm::outs() << "SummaryExecutor::print_summary_chains(): Suppl call " << inner_call->seq_num 
//                 << " for " << path_smmry->fn->getName() << "() (function " << suppl_fn->getName() << "()) has " << inner_call->connected_summaries.size()
//                 << " connected summaries.\n";
//    for(unsigned i = 0; i<inner_call->connected_summaries.size(); i++)
//      print_summary_chains(inner_call->connected_summaries[i]);
//  }
//  return 0;
//}

/*
void SummaryExecutor::print_function_summaries(std::map<llvm::Function *, std::vector<path_summary_ty *> > ps)
{
  //llvm::outs() << "SummaryExecutor::runFunctionAsNonMain(): run() is finished, printing the collected summaries.\n";
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
      llvm::outs() << "SummaryExecutor::print_function_summaries(): fn_constraints.size() = " << fn_constraints.size() << "\n";

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

//void SummaryExecutor::make_globals_symbolic(ExecutionState *s, llvm::Function *f)
/* Initialize globals which are used in the current function to fresh symbolic
   This is done only for globals which might have changed in one of the callers
   of this function. */
void SummaryExecutor::init_globals_with_symbolic(ExecutionState *s, llvm::Function *f)
{
  //std::vector<llvm::Value *> globals = get_global_calling_context(f); // get the list of global variables which are read and written in the function
  //for(std::vector<llvm::Value *>::iterator gv = globals.begin(); gv != globals.end(); ++gv)
  //for(std::map<const llvm::GlobalValue*, MemoryObject*>::iterator it = globalObjects.begin(); it != globalObjects.end(); ++it)
  for(std::set<const llvm::GlobalValue *>::iterator it  = this->globals_to_init.begin(); 
                                                    it != this->globals_to_init.end(); ++it)
  {
    //llvm::GlobalValue* gv = (llvm::GlobalValue *)it->first;
    llvm::GlobalValue *gv = (llvm::GlobalValue *)(*it);


    GlobalVariable *glob_var = dyn_cast<GlobalVariable>(gv);
    assert(glob_var);
    if(glob_var->isConstant())
    {
      llvm::outs() << "SummaryExecutor::make_globals_symbolic(): global '" << gv->getName() << "' is a constant\n";
      continue;
    }


    llvm::Type *gv_pointer_type = gv->getType();
    MemoryObject* mo = globalObjects[(GlobalValue *)(gv)];
    llvm::outs() << "SummaryExecutor::make_globals_symbolic(): making '" << gv->getName() << "' of size " 
                 << mo->size <<  " symbolic\n";

    /* Note that all llvm globals have pointer types, so what we
     * actually need to check to the type of the element */
    /* If the global ojbect is a pointer, then we allocate some symbolic
     * memory for it */
    assert(isa<llvm::PointerType>(gv_pointer_type) && "Global is not a pointer (bug in llvm?)");
    llvm::Type *gv_type = (dyn_cast<llvm::PointerType>(gv_pointer_type))->getElementType();
    if(isa<llvm::PointerType>(gv_type))
    {
      llvm::outs() << "SummaryExecutor::make_globals_symbolic(): global '" << gv->getName() << "' is a pointer(" << *gv_type << ")\n";
      //llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): element type is '" << *element_type << "'\n";
      //exit(0);
      llvm::Type *element_type = (dyn_cast<llvm::PointerType>(gv_type))->getElementType();
      Expr::Width w = getWidthForLLVMType(element_type);
      uint64_t size = w*64;
      MemoryObject *mo_data = memory->allocate(size, false, true, f->begin()->begin());
      if (!mo_data)
        llvm::report_fatal_error("out of memory");
      ObjectState *os_data = bindObjectInState(*s, mo_data, false);
      std::string name;
      name = gv->getName().str() + "data_ver0";
      executeMakeSymbolic(*s, mo_data, name);

      ObjectPair op;
      bool success;
      //success = state.addressSpace.resolveOne(cast<ConstantExpr>(mo->getBaseExpr()), op);
      s->addressSpace.resolveOne(*s, solver, mo->getBaseExpr(), op, success);
      const MemoryObject *mo_base = op.first;
      const ObjectState *os_base = op.second;
      ObjectState *wos = s->addressSpace.getWriteable(mo_base, os_base);
      wos->write(0, mo_data->getBaseExpr());
      //w = Context::get().getPointerWidth();
      llvm::outs() << "SummaryExecutor::make_globals_symbolic(): " << gv->getName() 
                   << " is now points to symbolic data chunk @" << mo_data->getBaseExpr() << "\n";
    } else
    {
      unsigned id = 0;
      std::string name = gv->getName().str();
      std::string uniqueName = name;
      while (!s->arrayNames.insert(uniqueName).second) {
        uniqueName = name + "_" + llvm::utostr(++id);
      }
      const Array *new_array = Array::CreateArray(uniqueName, mo->size);
      bindObjectInState(*s, mo, false, new_array);
      s->global_symbolic_replacements[gv].push_back(new_array);
    }

    //llvm::outs() << "       @" << mo->address << "\n";
    //executeMakeSymbolic(*s, mo, (*gv)->getName().str()); // This one just put new pair (mo, array) to s->symbolics
    //s->global_symbolic_replacements[*gv].push_back(s->symbolics[s->symbolics.size()-1].second);
  }
  //llvm::outs() << "SummaryExecutor::make_globals_symbolic(): state has the following symbolics now:\n";
  //for(std::vector<std::pair<const MemoryObject *, const Array *> >::iterator it = s->symbolics.begin();
  //                        it != s->symbolics.end(); ++it)
  //{
  //  llvm::outs() << "mo->name = " << it->first->name << "; array->name = " << it->second->getName() << 
  //               "@" << it->second << "\n"; 
  //}
  return;
}


//std::vector<llvm::Value *> SummaryExecutor::get_global_calling_context(const Function *f)
/* Take globals that are used in this->func from globalObjects*/
void SummaryExecutor::get_global_calling_context()
{
  /* Find globals which are used in the current function */
  llvm::outs() << "SummaryExecutor::get_global_calling_context(): globalObjects.size() = " << globalObjects.size() << "\n";
  for(std::map<const llvm::GlobalValue*, MemoryObject*>::iterator it = globalObjects.begin(); it != globalObjects.end(); ++it)
  {
    llvm::GlobalValue* gv = (llvm::GlobalValue *)it->first;

    /* Skip constants */
    GlobalVariable *glob_var = dyn_cast<GlobalVariable>(gv);
    assert(glob_var);
    if(glob_var->isConstant())
    {
      llvm::outs() << "SummaryExecutor:::get_global_calling_context(): global '" << gv->getName() << "' is a constant\n";
      continue;
    }

    MemoryObject* mo = it->second;
    llvm::outs() << "SummaryExecutor::get_global_calling_context(): considering " << gv->getName() << "\n";
    for(llvm::Value::use_iterator u_it=gv->use_begin(); u_it != gv->use_end(); ++u_it)
    {
      Instruction *Inst = dyn_cast<Instruction>(*u_it);
      if(!Inst)
      {
        Inst = dyn_cast<Instruction>(*(u_it->use_begin()));
      }
      //llvm::outs() << "     place = " << *(*u_it) << "\n";
      //if(Instruction *Inst = dyn_cast<Instruction>(*u_it))
      if(Inst)
      {
        llvm::Function *user = Inst->getParent()->getParent();
        //llvm::outs() << "     user = " << user->getName() << "\n";
        if( (user == this->func) )
        {
          llvm::outs() << "     " << gv->getName() << " is used immediately\n";
          used_globals.insert(gv);
        }
      } else
      {
        llvm::outs() << " Warning: no instruction for " << gv->getName() << "\n";
      }
    } // for each usage
  } // for each globalValue

  /* Indentify globals that are used in this function that needs to be symbolically initialized or refreshed upon calees calls */
  for(std::set<const llvm::GlobalValue*>::iterator it = used_globals.begin(); it != used_globals.end(); ++it)
  {
    llvm::GlobalValue* gv = (llvm::GlobalValue*)(*it);
    for(llvm::Value::use_iterator u_it=gv->use_begin(); u_it != gv->use_end(); ++u_it)
    {

      Instruction *Inst = dyn_cast<Instruction>(*u_it);
      if(!Inst)
      {
        Inst = dyn_cast<Instruction>(*(u_it->use_begin()));
      }

      //if(Instruction *Inst = dyn_cast<Instruction>(*u_it))
      if(Inst)
      {
        llvm::Function *user = Inst->getParent()->getParent();
        /* This global might have been used in a caller => 
	   we don't know its value => we need to init it with a new symbolic */
        if(this->callers.count(user))
	{
          llvm::outs() << "     " << gv->getName() << " is used in a caller " << user->getName() << "() \n";
          globals_to_init.insert(gv);
	}
        
        /* This global might be used in a callee => 
	   when we invoke this callee we need to refresh the globals */
        if(this->callees.count(user) )
          globals_to_refresh[user].insert(gv);
        else
        {
          for(std::map<llvm::Function *, std::set<llvm::Function *> >::iterator it_1 = this->callees.begin();
                      it_1 != this->callees.end(); ++it_1) 
          {
            llvm::Function *immediate_callee = it_1->first; 
            std::set<llvm::Function *> sub_callees = it_1->second; 
            if(sub_callees.count(user))
            {
              llvm::outs() << "     " << gv->getName() << " is used in callee " << immediate_callee->getName() << " (or its subcallees)\n";
              globals_to_refresh[immediate_callee].insert(gv);
              break;
            }
          }
        }
      } else
      {
        llvm::outs() << " Warning: no instruction for " << gv->getName() << "\n";
      }

    } /* end of users loop */ 
  } /* end of  used_globals loop*/
}

//std::vector<llvm::Value *> SummaryExecutor::get_global_calling_context(Function *f)
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
 *  contained in map <SummaryExecutor::call_symbolic_replacements>.  We need
 *  only those call instructions whose symbolic values are in good_path_summaries
 *  for function <f>.
 *
 *  @param ps Path summary (i.e. function ret value, and path constraint) for function <f>
 *  @param f Function in which we had call instruction that were replaced by symbolics.
 *  @return vector with call instruction which we will need to execute
 *  
 */
//std::vector<llvm::CallInst *> SummaryExecutor::resolve_call_symbolics(path_summary_ty ps, llvm::Function *f)
// The return value is a map. Key is a function which we need to call, and the value is the 
// constraints on the return value of the called function (i.e. it is
// the subset of the corresponding path condition).
// TODO: add constraints on global values.
//std::map<llvm::CallInst *, std::vector< ref<Expr> > > SummaryExecutor::resolve_call_symbolics(llvm::Function *f, int ps_index_)
//std::map<llvm::CallInst *, std::vector< ref<Expr> > >
//      SummaryExecutor::resolve_call_symbolics(llvm::Function *f, constraints_ty conds)
//{
//  llvm::outs() << "SummaryExecutor::resolve_call_symbolic(): inside; for function " << f->getName() << "().\n";
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
//SummaryExecutor::resolve_call_symbolics1(path_summary_ty &f1_smmry)
//{
//  llvm::Function *f1 = f1_smmry.fn; 
//  llvm::outs() << "SummaryExecutor::resolve_call_symbolic1(): inside; for function " << f1->getName() << "().\n";
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


bool SummaryExecutor::check_formal_args_against_psummary(path_summary_ty &smmry, std::vector<std::vector< ref<Expr> > > &formal_args_conditions)
{
  std::vector<ref<Expr> > combined_constraints;
  std::vector<ref<Expr> > debug_constraints; // keeps conditions on formal arguments (already replaced)
  unsigned numFormals = smmry.fargs.size();
  llvm::outs() << "SummaryExecutor::check_formal_args_against_fsummary(): Creating combined (formal_args_conds + path_conds) contraints\n";
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

  llvm::outs() << "SummaryExecutor::check_formal_args_against_fsummary(): checking the following combined conditions:\n";
  for(std::vector<ref<Expr> >::iterator it = combined_constraints.begin(); it != combined_constraints.end(); ++it)
    llvm::outs() << *it << "\n";
  
  if(combined_constraints.size() == 0)
  {
    llvm::outs() << "SummaryExecutor::check_formal_args_against_fsummary(): Conditions are empty => result = 1 (true)\n";
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
    llvm::outs() << "SummaryExecutor::check_formal_args_against_fsummary(): debug_result = " << res_str << "\n";
  }
  else
    llvm::outs() << "SummaryExecutor::check_formal_args_against_fsummary(): no additional constraints on formals\n";
  // DEBUG STUFF END

  // DEBUG STUFF BEGIN
  //ref<Expr> true_expr =  ConstantExpr::create(1, Expr::Bool);
  //ConstraintManager cm1(combined_constraints);
  //bool debug_result;
  //bool success1 = solver->solver->mayBeTrue(Query(cm1, true_expr), debug_result);
  //llvm::outs() << "SummaryExecutor::check_formal_args_against_fsummary(): debug_result = " << debug_result << "\n";
  // DEBUG STUFF END

  assert(success && "FIXME: Unhandled solver failure");
  llvm::outs() << "SummaryExecutor::check_formal_args_against_fsummary(): result = " << solver_result << "\n";

  if(!solver_result)
    return false;

  return true;

}

#if 0
/* Replace all concat expressions in <conditions> with <x> and check
 * the system can be solved.*
 */
bool SummaryExecutor::conds_are_solvable(ref<Expr> x, std::vector< ref<Expr> > *conditions)
{
  if(conditions->size() == 0)
    return true;

  bool solver_result = true;
  /* Replace concat expressions in each condition with <x>. */
  std::vector<ref<Expr> > vexpr;
  for(std::vector< ref<Expr> >::iterator it_expr = conditions->begin();
                                         it_expr != conditions->end(); ++it_expr)
  {
    ref<Expr> e = *it_expr;
    BinaryExpr *be = dyn_cast<BinaryExpr>(e);

    /*
    // Create a temporary copy
    ref<Expr> arr[2];
    arr[0] = be->left;
    arr[1] = be->right;
    ref<Expr> tmp = e->rebuild(arr);
    //llvm::outs() << "SummaryExecutor::conds_are_solvable(): replacing concats in\n" << tmp << "\n"
    //                "with " << x << "\n";
    //comp_symbex_replace_for_retvalue(tmp, x);


    //llvm::outs() << "SummaryExecutor::conds_are_solvable(): the updated constraint:\n" << tmp << "\n";
    */ 

    ref<Expr> tmp = comp_symbex_replace_for_retvalue(e, x);

    vexpr.push_back(tmp);
  }

  llvm::outs() << "SummaryExecutor::conds_are_solvable(): checking the following constraints:\n";
  print_expressions(vexpr);

  ref<Expr> true_expr =  ConstantExpr::create(1, Expr::Bool);
  ConstraintManager cm(vexpr);
  //bool success = solver->solver->mayBeTrue(Query(cm, true_expr), solver_result);
  //bool success = solver->solver->mayBeTrue(Query(cm, vexpr.back()), solver_result);
  for(std::vector< ref<Expr> >::iterator it = vexpr.begin(); it != vexpr.end(); ++it)
  {
    bool success = solver->solver->mayBeTrue(Query(cm, *it), solver_result);
    assert(success && "FIXME: Unhandled solver failure");
    if(!solver_result)
      break;
  }
  llvm::outs() << "SummaryExecutor::conds_are_solvable(): result = " << solver_result << "\n";

  if(!solver_result)
    return false;

  return true;
}
#endif




/* **** ++++ MOVED TO INTERPRETER MANAGER BEGIN */
#if 0
/* f1 is being symbolically executed (backwards pass);
 * it calls f2 and wants to know if they can glue
 * together given the current f1's state conditions.
 *
 * The main idea is the following: previously when we were executing
 * function f2 we made its formal arguments symbolic and saved them
 * for the future reference in map <fargs>. f2's good_summaries set
 * conditions on the formal arguments.
 *
 * On the other hand, f1's state <f1_state> just reached a call to f2. This state
 * has constraints on the actual arguments of the call <f2_actual_args>.
 * So we combine both constraints and check if they do not contradict.
 * We do this for each f2's summary. If for at least one summary there
 * is no contradiction, we decide that we can glue two functions.
 *
 * @param f1             Function for which we were doing backward symbex, and which 
 *                       called <f2>
 * @param f1_state       Exectuion state of function f1 at the moment when it
 *                       called f2
 * @param f2_actual_args These are arguments (expressions) with which <f1> called <f2>
 */
bool SummaryExecutor::comp_symbex_can_glue(llvm::Function *f1, ExecutionState &f1_state, std::vector< ref<Expr> > f2_actual_args)
{
  llvm::Function *f2 = f1_state.target_func;
  llvm::outs() << "SummaryExecutor::comp_symbex_can_glue(): Checking if function " << 
                   f1->getName() << "() with " << f2_actual_args.size() << " arguments can be glued with " << 
                   "on-path function " << f2->getName() << "()\n";
  if(f2_actual_args.size() == 0)
    return true;

  bool can_glue = false;
  std::vector<std::vector<ref<Expr> > > f2_actual_arg_conds; // We keep conditions (for f2's actual arguments) from f1's state.constraints
  std::vector<std::vector<ref<Expr> > > f2_formal_arg_conds;  // Stores conditions on f2_formal_arg, which are extracted from a summary
  std::vector<ref<Expr> > aggregated_conds;
  //std::vector<ref<Expr> > f2_formal_args = fargs[f2];
  //std::vector<ref<Expr> > f2_formal_args = f2_smmry.fargs;
  
  /* Initialize: f2_actual_args and f2_formal_arg_conds are vectors of vectors. We
   * need to initialize the first vecotor (which is contains vectors) */
  for(unsigned i=0; i<f2_actual_args.size(); i++)
  {
    std::vector<ref<Expr> > v1;
    f2_actual_arg_conds.push_back(v1);
    std::vector<ref<Expr> > v2;
    f2_formal_arg_conds.push_back(v2);
  }

  /*  Collect constraints for each actual argument from the current state. */
  llvm::outs() << "Extracting constraints for actual arguments from f1_state.constraints.\n";
  for(std::vector< ref<Expr> >::const_iterator it_1  = f1_state.constraints.begin(); 
                                               it_1 != f1_state.constraints.end(); ++it_1) //For each condition in the summary
  {
    const ref<Expr> cond = *it_1;
    std::vector<ref<Expr> > concats = extract_concat_subexpressions(cond);
    for(unsigned i=0; i<f2_actual_args.size(); i++)
    {
      assert(isa<ConcatExpr>(f2_actual_args[i]) && "f2_actual_arg is not a ConcatExpr");
      for(std::vector<ref<Expr> >::iterator it_2 = concats.begin(); it_2 != concats.end(); ++it_2) 
      { 
        ref<Expr> concat = *it_2;

        if(f2_actual_args[i] == concat) 
        {
          f2_actual_arg_conds[i].push_back(cond);
          break;
        }
      }
    }
  }


  std::vector<path_summary_ty *> f2_summaries = good_path_summaries;
  for(std::vector<path_summary_ty *>::iterator it_1 = f2_summaries.begin(); it_1 != f2_summaries.end(); ++it_1) // For each f2's summary
  {
    llvm::outs() << "SummaryExecutor::comp_symbex_can_glue(): considering the following function summary:\n";
    print_function_summary(*it_1); // Function summaries which go along the call path
    constraints_ty &f2_summary_conds = (*it_1)->path_constraints;
    std::vector<ref<Expr> > f2_formal_args = (*it_1)->fargs;
    //f2_formal_arg_conds.clear();
    for(unsigned i=0; i<f2_actual_args.size(); i++)
      f2_formal_arg_conds[i].clear();

    /*  Collect constraints for each formal argument. */
    llvm::outs() << "Extracting constraints for formal arguments from the summary.\n";
    for(std::vector< ref<Expr> >::const_iterator it_2 = f2_summary_conds.begin(); it_2 != f2_summary_conds.end(); ++it_2) //For each condition in the summary
    {
      const ref<Expr> cond = *it_2;
      std::vector<ref<Expr> > concats = extract_concat_subexpressions(cond);
      for(unsigned i=0; i<f2_formal_args.size(); i++)
      {
        assert(isa<ConcatExpr>(f2_formal_args[i]) && "f2_formal_arg is not a ConcatExpr");
        for(std::vector<ref<Expr> >::iterator it_3 = concats.begin(); it_3 != concats.end(); ++it_3) 
        { 
          ref<Expr> concat = *it_3;
          if(f2_formal_args[i] == concat) 
          {
            f2_formal_arg_conds[i].push_back(cond);
            break;
          }
        } 
      }
    }

    bool solver_result = false;
    aggregated_conds.clear();

    /* For each pair of actual and formal arguments */
    for(unsigned i=0; i<f2_actual_args.size(); i++)
    {
      /* Combine constraints for acutal and formal arguments, and check if
       * they contradict */
      aggregated_conds.clear();
      aggregated_conds.insert(aggregated_conds.end(), f2_actual_arg_conds[i].begin(), f2_actual_arg_conds[i].end());
      aggregated_conds.insert(aggregated_conds.end(), f2_formal_arg_conds[i].begin(), f2_formal_arg_conds[i].end());
      llvm::outs() << "SummaryExecutor::comp_symbex_can_glue(): We collected constraints both for formal and"
                          " actual parameters for arg " << i 
                          << ". Checking if they are compatible (aggregated_conds.size() = " 
                          << aggregated_conds.size() << "):\n";
      for(std::vector<ref<Expr> >::iterator it_2 = aggregated_conds.begin(); it_2 != aggregated_conds.end(); ++it_2)
        llvm::outs() << *it_2 << "\n";

      if(aggregated_conds.size() == 0)
        solver_result = true;
      else
        solver_result = conds_are_solvable(f2_formal_args[i], &aggregated_conds);
      llvm::outs() << "SummaryExecutor::comp_symbex_can_glue(): solver's results = " << solver_result << "\n";

      if(!solver_result)
        break;

    } 

    if(solver_result)
    {
      llvm::outs() << "SummaryExecutor::comp_symbex_can_glue(): can glue with this summary\n";
      can_glue = true;
    }
    else
    {
      llvm::outs() << "SummaryExecutor::comp_symbex_can_glue(): cannot glue with this summary\n";
    }
  }
  return can_glue;
}
#endif
/* **** ++++ MOVED TO INTERPRETER MANAGER END */



#if 0
void SummaryExecutor::merge_dublicated_good_summaries(llvm::Function *f)
{
  std::vector<path_summary_ty *> good_summaries = good_path_summaries;
  std::vector<path_summary_ty *> unique;
  unsigned i,j;
  bool should_add;

  for(i=0;i<good_summaries.size();i++)
  {
    path_summary_ty *s1 = good_summaries[i];

    should_add = true;
    for(j=0;j<unique.size();j++)
    {
      path_summary_ty *s2 = unique[j];
      if(s1->has_the_same_path_instructions(s2))
      {
        should_add = false;
        break;
      }
    }

    if(should_add)
      unique.push_back(s1);
  }

  good_path_summaries = unique;
  return;
}
#endif


/* */


/* Get bit width if type is an Interger type, 0 otherwise
 */
unsigned SummaryExecutor::getIntTypeWidth(llvm::Type *type)
{
  //if(isa<llvm::IntegerType>(type))
  assert(isa<llvm::IntegerType>(type));
  return (dyn_cast<llvm::IntegerType>(type))->getBitWidth();
  //return 0;
}

/* Get bit width of pointer subtype
 * Return 0 if type is not a PointerType
 */
unsigned SummaryExecutor::getPointerTypeElementWidth(llvm::Type *type)
{
  assert(isa<llvm::PointerType>(type));
  llvm::Type *element_type = (dyn_cast<llvm::PointerType>(type))->getElementType();
  return getIntTypeWidth(element_type);
}


void SummaryExecutor::getConstraintLog(const ExecutionState &state, std::string &res,
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
    klee_warning("SummaryExecutor::getConstraintLog() : Log format not supported!");
  }
}




Expr::Width SummaryExecutor::getWidthForLLVMType(LLVM_TYPE_Q llvm::Type *type) const {
  return kmodule->targetData->getTypeSizeInBits(type);
}

namespace klee {
ref<ConstantExpr> SummaryExecutor::evalConstantExpr(const llvm::ConstantExpr *ce) 
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

void SummaryExecutor::initializeGlobalObject(ExecutionState &state, ObjectState *os,
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

SummaryExecutor::~SummaryExecutor() {
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

/* 
 */ 
void SummaryExecutor::updateGlobalsDueToPossibleInterrupts(ExecutionState * state, KInstruction * inst)
{
  llvm::outs() << "SummaryExecutor::updateGlobalsDueToPossibleInterrupts(): Check Interrupts\n";
  KInstruction * pcInst = state->prevPC;
  if(!WithInterrupts)
      return;
  //not a basic block head, disable this check for now
  /* this is already checked in the interrupt gate */
  //if (false && pcInst && pcInst->inst && (pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst))
  //{
  //  llvm::outs() << "SummaryExecutor::updateGlobalsDueToPossibleInterrupts(): Not a BBL Head, not updating globals\n";
  //  return;
  //}
  //llvm::outs() << "SummaryExecutor::updateGlobalsDueToPossibleInterrupts(): BBL head => will update globals\n";
  //setFreshSymbolicsToGlobals(state, "Possbile interrupt");
  //return;

  // The code below invokes gate function for each interrupt
  bool someInterruptOccured = false;
  std::string interruptsFired = "";
  /* Iterate over all interruption handerls found in the user's code.
   * (this list is built in the arch's constructor) */
  InterruptVector::iterator seek = arch->interruptVector.begin();
  InterruptVector::iterator end = arch->interruptVector.end();
  for ( ; seek != end ; ++seek)
  {
    InterruptHandler * handler = *seek;
    llvm::outs() << "SummaryExecutor::updateGlobalsDueToPossibleInterrupts(): check interrupt " << handler->fun->getName() << "\n";
		//if (interruptCondition == NULL)
    if (handler->gate == NULL)
      klee_error("Absentee interrupt condition (probably a bug in the memory layout file)\n");
    assert(handler->fun);
    /* This checks status register and periph registers
     * flags (e.g. GIE flag, ADC10IE flag, etc) */
    if(handler->gate(arch, state, solver))
    {
      //someInterruptOccured = true;
      setFreshSymbolicsToGlobals(state, "Possbile interrupt", handler->fun);
      //break;
    }
  }
  //if (someInterruptOccured)
    //setFreshSymbolicsToGlobals(state, "Possbile interrupt");
}

/* <callee> is not NULL only if we refresh globals due to inner call */
void SummaryExecutor::setFreshSymbolicsToGlobals(ExecutionState *state, std::string reason, const llvm::Function *callee)
{
  llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): reason: " << reason << "\n";
  llvm::Function *cur_func = (llvm::Function *)this->func;
  assert(callee && "Refreshing global requires the guilt caller");
  if(callee && !(this->globals_to_refresh.count(callee)))
  {
    llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): no globals to refresh due to call to " 
                 << callee->getName() << "()\n";
    return;
  }

  // This should assign a new symbolic value to global values
  //for(std::map<const llvm::GlobalValue*, MemoryObject*>::iterator it = globalObjects.begin(); it != globalObjects.end(); ++it)
  for(std::set<const llvm::GlobalValue*>::iterator it  = this->globals_to_refresh[callee].begin(); 
                                                   it != this->globals_to_refresh[callee].end(); ++it)
  {

    //llvm::GlobalValue* gv = (llvm::GlobalValue *)it->first;
    llvm::GlobalValue* gv = (llvm::GlobalValue *)(*it);


    GlobalVariable *glob_var = dyn_cast<GlobalVariable>(gv);
    assert(glob_var);
    if(glob_var->isConstant())
    {
      llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): global '" << gv->getName() << "' is a constant\n";
      continue;
    }

    llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): refreshing '" << gv->getName() << "\n";

    llvm::Type *gv_pointer_type = gv->getType();
    assert(isa<llvm::PointerType>(gv_pointer_type) && "Global is not a pointer (bug in llvm?)");
    MemoryObject* mo = globalObjects[(GlobalValue *)(gv)];

    llvm::Type *gv_type = (dyn_cast<llvm::PointerType>(gv_pointer_type))->getElementType();
    if(isa<llvm::PointerType>(gv_type))
    {
      llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): global '" << gv->getName() << "' is a pointer(" << gv_type << ")\n";
      llvm::Type *element_type = (dyn_cast<llvm::PointerType>(gv_type))->getElementType();
      Expr::Width w = getWidthForLLVMType(element_type);
      uint64_t size = w*64;

      unsigned id = 0;
      std::string name = gv->getName().str();
      std::string uniqueName = name;
      while (!state->arrayNames.insert(uniqueName).second) {
        uniqueName = name + "_data_ver_" + llvm::utostr(++id);
      }

      //executeMakeSymbolic(*s, mo_data, unique_name);

      ObjectPair op;
      bool success;
      //success = state.addressSpace.resolveOne(cast<ConstantExpr>(mo->getBaseExpr()), op);
      state->addressSpace.resolveOne(*state, solver, mo->getBaseExpr(), op, success);
      if(success)
      {
        const MemoryObject *mo_base = op.first;
        const ObjectState *os_base = op.second;
        ref<Expr> data_addr = os_base->read(0, Context::get().getPointerWidth());
        llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): data_addr =  " << data_addr << "\n";

        ObjectPair op1;
        bool success1;
        state->addressSpace.resolveOne(*state, solver, data_addr, op1, success1);
        if(success1)
        {
          const MemoryObject *mo_data = op1.first;
          const ObjectState *os_data = op1.second;

          const Array *new_array = Array::CreateArray(uniqueName, size);
          bindObjectInState(*state, mo_data, false, new_array);
          /* Note that the global value already points to the array */
          llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): created new symbolic array for pointer " << gv->getName() << " @" << mo_data->getBaseExpr() << "\n";
        } else llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): could not resolve global's symbolic data chunk for " << gv->getName() << "\n";
      } else llvm::outs() << "SummaryExecutor::setFreshSymbolicsToGlobals(): could not resolve global " << gv->getName() << "\n";
    } else
    {
      unsigned id = 0;
      std::string name = gv->getName().str();
      std::string uniqueName = name;
      while (!state->arrayNames.insert(uniqueName).second) {
        uniqueName = name + "_" + llvm::utostr(++id);
      }
      const Array *new_array = Array::CreateArray(uniqueName, mo->size);
      bindObjectInState(*state, mo, false, new_array);
      state->global_symbolic_replacements[gv].push_back(new_array);
    }
  }
}

void SummaryExecutor::make_args_symbolic(ExecutionState *state,llvm::Function  *f1)
{
  KFunction *kf = kmodule->functionMap[f1];
  unsigned numFormals = f1->arg_size();
  unsigned id = 0;
  llvm::Function::arg_iterator arg_it = f1->arg_begin();
  for (unsigned i=0; i<numFormals; ++i) 
  {
    //llvm::Argument arg = *arg_it;
    llvm::Value *arg = arg_it;
    llvm::Type *arg_type = arg->getType();
    unsigned bit_width = 0;
    Expr::Width w = 0;
    if(isa<llvm::PointerType>(arg_type))
    {
      llvm::outs() << "SummaryExecutor::collectPathSummaries(): fun arg is a pointer\n";
      //w = Context::get().getPointerWidth() / 8;
      w = Context::get().getPointerWidth();
    }
    else
      w = getWidthForLLVMType(arg_type);
    assert(w && "Formal arg width cannot be zero");


    ref<Expr> res;
    /* If arg is a pointer, then we allocate some symbolic memory for it */
    if(isa<llvm::PointerType>(arg_type))
    {
      llvm::Type *element_type = (dyn_cast<llvm::PointerType>(arg_type))->getElementType();
      Expr::Width w = getWidthForLLVMType(element_type);
      uint64_t size = w*64;
      MemoryObject *mo = memory->allocate(size, false, true, f1->begin()->begin());
      if (!mo)
        llvm::report_fatal_error("out of memory");
      ObjectState *os = bindObjectInState(*state, mo, false);
      std::string name;
      //name = "unnamed_synth";
      name = "arg_" + f1->getName().str() + "_" + llvm::utostr(id);
      executeMakeSymbolic(*state, mo, name);
      res = mo->getBaseExpr();
    } else
    {
      //llvm::outs() << "DEBUG: symbolic's name : " << "arg_" + f->getName().str() + "_" + llvm::utostr(idi) << "\n";
      //llvm::outs() << "SummaryExecutor::runFunctionAsNonMain(): making symbolic the following arg:" << getArgumentCell(*state, kf, i).value << "\n";
      llvm::outs() << "SummaryExecutor::collectPathSummaries(): creating new symbolic array with size " << w << "\n";
      const Array *array = Array::CreateArray("arg_" + f1->getName().str() + "_" + llvm::utostr(id), Expr::getMinBytesForWidth(w) );
      res = Expr::createTempRead(array, w);
    }

    bindArgument(kf, i, *state, res);
    fargs.push_back(res);
    id++;
    ++arg_it;
  }
}


//const llvm::Module *  setModule(llvm::Module *module,  const Interpreter::ModuleOptions &opts)
//{ 
//  return NULL;
//}


///


/* If inner call for state <s> is not NULL, check if the state's
 * constratins do not contradict with inner call's constraint */
//bool SummaryExecutor::state_complies_with_inner_call(ExecutionState *s, InnerCall *inner_call)
bool SummaryExecutor::state_complies_with_inner_call(ExecutionState *s)
{
  /* No inner call => we condier as complying */
  if(!s->cur_inner_call)
  {
    assert(s->complies_with_cur_inner_call);
    return true;
  }

  /* If we already marked this state as not complying */
  if(!(s->complies_with_cur_inner_call))
    return false;

  /* If the inner call's function does not have formal args, we consider the state as complying */
  llvm::Function *cur_fn = s->cur_inner_call->call_inst->getCalledFunction();
  if(cur_fn->arg_size() == 0)
    return true;

  /* If the previous instruction was not a conditional branch
   * instruction, we assume nothing has changed and the state still
   * complies with the inner call */
  Instruction *just_executed_inst = s->prevPC->inst;
  if(just_executed_inst->getOpcode() == Instruction::Br)
  {
    BranchInst *bi = cast<BranchInst>(just_executed_inst);
    if(!bi->isUnconditional())
    {
      /* This will replace all occurances of formal args to actual args all
       * the way up to call path function */
      /* Create a fake path summary so that we can use its API to unwrap
       * constraints */
      path_summary_ty *hack = new PathSummary(cur_fn, ConstantExpr::alloc(0, Expr::Int16), s->constraints);
      std::vector<ref<Expr> > aggregated_conds = hack->unwrap_constraints(s->cur_inner_call);
      llvm::outs() << "SummaryExecutor::complies_with_inner_call: Unwrapped constraints:\n";
      print_expressions(aggregated_conds);
      aggregated_conds.insert(aggregated_conds.end(),
                            s->cur_inner_call->accumulated_conditions.begin(),
                            s->cur_inner_call->accumulated_conditions.end());
      bool res = interpreter_manager->conds_are_solvable(aggregated_conds);
      llvm::outs() << "SummaryExecutor::complies_with_inner_call(): " 
                   << (res ? "complies" : "does not comply") << " \n";
      if(res)
        return true;
      else
      {
        s->complies_with_cur_inner_call = false;
        return false;
      }
    }
  }
  else
    return true;
}
