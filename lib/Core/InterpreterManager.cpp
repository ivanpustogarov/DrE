//===-- InterpreterManager.cpp ----------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "klee/InterpreterManager.h"
#include "klee/Interpreter.h"
#include "Context.h"
#include "klee/util/ExprUtil.h"
#include "klee/util/ExprSMTLIBPrinter.h"
#include "klee/ExecutorCommandLineParameters.h"

#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
#include "llvm/IR/DataLayout.h"
#else
#if LLVM_VERSION_CODE <= LLVM_VERSION(3, 1)
#include "llvm/Target/TargetData.h"
#else
#include "llvm/DataLayout.h"
#include "llvm/TypeBuilder.h"
#endif
#endif

#include <map>
#include <set>
#include <vector>
#include <list>


using namespace llvm;
using namespace klee;

std::vector<path_summary_ty *> split_psmmry_on_inner_calls(path_summary_ty *psmmry);
unsigned compute_ugly_hash(unsigned prev_hash, unsigned val);
unsigned compute_simple_path_hash(path_summary_ty *simple_path_start);



InterpreterManager::InterpreterManager() :
    kmodule(0)
{
}

InterpreterManager::InterpreterManager(const Interpreter::InterpreterOptions &_interpreterOpts,
                                       Architecture *_arch,
                                       KModule *_kmodule,
                                       Solver *_coreSolver):
  arch(_arch), kmodule(_kmodule), coreSolver(_coreSolver),
  interpreterOpts(_interpreterOpts)
{
}

/*
const llvm::Module *InterpreterManager::setModule(llvm::Module *module) 
{
  assert(!kmodule && module && "can only register one module"); // XXX gross
  kmodule = new KModule(module);

  // Initialize the context.
#if LLVM_VERSION_CODE <= LLVM_VERSION(3, 1)
  TargetData *TD = kmodule->targetData;
#else
  DataLayout *TD = kmodule->targetData;
#endif
  Context::initialize(TD->isLittleEndian(),
                      (Expr::Width) TD->getPointerSizeInBits());

  //specialFunctionHandler = new SpecialFunctionHandler(*this);

  //specialFunctionHandler->prepare();
  //kmodule->prepare(opts, interpreterHandler);
  //specialFunctionHandler->bind();

  //if (StatsTracker::useStatistics()) {
  //  statsTracker = 
  //    new StatsTracker(*this,
  //                     interpreterHandler->getOutputFilename("assembly.ll"),
  //                     userSearcherRequiresMD2U());
  //}
  
  return module;
}
*/



std::vector<ref<Expr> > InterpreterManager::extract_concat_subexpressions(ref<Expr> e)
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

template <typename T>
bool CheckCommon( const std::vector<T> &inVectorA, const std::vector<T> &inVectorB )
{
    std::vector<T> temp;
    std::set_intersection(inVectorA.begin(), inVectorA.end(), 
                          inVectorB.begin(), inVectorB.end(),
                          std::back_inserter(temp));
    return !temp.empty();
}


/* Check if <smmry> fits <inner_call>
*/
bool InterpreterManager::comp_symbex_can_glue2(path_summary_ty *smmry, InnerCall *inner_call)
{
  llvm::Function *called_fn = inner_call->call_inst->getCalledFunction();
  assert(smmry->fn == called_fn);
  unsigned num_args = called_fn->arg_size(); 

  if(smmry->type != PathSummary::RET_SUMMARY_TYPE)
    return false;

  /* Check cached stuff */
  if(inner_calls_fit_cache[inner_call->shallow_hash()].count(smmry->shallow_hash()))
  {
    llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): inner call/smmry combinations: " 
               << inner_call->shallow_hash() << " / " << smmry->shallow_hash() 
	       << " is cached as fitting\n";
    return true;
  }

  if(inner_calls_nofit_cache[inner_call->shallow_hash()].count(smmry->shallow_hash()))
  {
    llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): inner call/smmry combinations: " 
               << inner_call->shallow_hash() << " / " << smmry->shallow_hash() 
	       << " is cached as not fitting\n";
    return false;
  }
  
  /* Go hard way */
  bool can_glue = false;

  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): num_args = " << num_args << "\n";
  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): inner_call->actual_args.size()s = " 
                         << inner_call->actual_args.size() << "\n";
  /* ivan: in fact we don't even collect such summaries, see function run_inner_calls() */
  if((num_args == 0) && (inner_call->call_inst->getCalledFunction()->getReturnType()->isVoidTy()))
  {
    llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): no args and no void return type => no conditions => can glue\n";
    return true;
  }


  /*  Collect constraints for each actual argument from smmry.
   *  ivan: Do we really need this, why not just add all conditions from
   *  the summary to <aggreated_conds>?*/
  //llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): Extracting constraints for actual arguments from f1_smmry.path_constraints.\n";

  /* This will replace all occurances of formal args to actual args all
   * the way up to call path function, inner_call here is the one which smmry should fit */
  std::vector<ref<Expr> > aggregated_conds = smmry->unwrap_constraints(inner_call);
  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): Unwrapped constraints:\n";
  print_expressions(aggregated_conds);

  ref<Expr> retval_unwrapped = smmry->unwrap_retvalue(inner_call);
  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): Unwrapped retvalue:\n";
  llvm::outs() << retval_unwrapped << "\n";


  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): replacing inner call symbolics with actual return value.\n";
  /* In the accumulated conds, we need to replace call symbolics with the actual return value */
  for(std::vector< ref<Expr> >::const_iterator it_1  = inner_call->accumulated_conditions.begin(); 
                                               it_1 != inner_call->accumulated_conditions.end(); ++it_1)
  {
    const ref<Expr> cond = *it_1;
    llvm::outs() << "\n" << cond << "\n";
    ref<Expr> tmp;
    llvm::outs() << "Replacing " << inner_call->symbolics << " with " << retval_unwrapped << "\n";
    tmp = replace_subexpr(cond, inner_call->symbolics, retval_unwrapped);
    aggregated_conds.push_back(tmp);
    llvm::outs() << tmp << "\n";
  }

  //aggregated_conds.insert(aggregated_conds.end(),
  //                        inner_call->accumulated_conditions.begin(),
  //                        inner_call->accumulated_conditions.end());

  llvm::outs() << "\nInterpreterManager::comp_symbex_can_glue2(): All constraints:\n";
  print_expressions(aggregated_conds);

  bool res = conds_are_solvable(aggregated_conds);
  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): " 
               << (res ? "can" : "cannot") << " glue with this inner call\n";


  /* Cache the result */
  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): caching this inner call/smmry combinations: " 
               << inner_call->shallow_hash() << " / " << smmry->shallow_hash() << "\n";
  if(res)
    inner_calls_fit_cache[inner_call->shallow_hash()].insert(smmry->shallow_hash());
  else
    inner_calls_nofit_cache[inner_call->shallow_hash()].insert(smmry->shallow_hash());

  return res;
}





/* Check if smmry's constraints on the actual arguments of end_function
 * get along with constraint in upper_call (the call is supposed to
 * belong to a lower-level call-path function. 
 * */
bool InterpreterManager::comp_symbex_can_glue2(path_summary_ty *smmry, UpperCall *upper_call)
{
  assert(smmry->fn == upper_call->caller);

  if(smmry->type != PathSummary::TARGET_FUNC_SUMMARY_TYPE)
    return false;

  if(smmry->target_func_actual_args.size() == 0)
    return true;

  /* Check cached stuff */
  if(upper_calls_fit_cache[upper_call->shallow_hash()].count(smmry->shallow_hash()))
  {
    llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): upper call/smmry combinations: " 
               << upper_call->shallow_hash() << " / " << smmry->shallow_hash() 
	       << " is cached as fitting\n";
    return true;
  }

  if(upper_calls_nofit_cache[upper_call->shallow_hash()].count(smmry->shallow_hash()))
  {
    llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): upper call/smmry combinations: " 
               << upper_call->shallow_hash() << " / " << smmry->shallow_hash() 
	       << " is cached as not fitting\n";
    return false;
  }
  
  /* Go hard way */

  bool can_glue = false;
  std::vector<std::vector<ref<Expr> > > smmry_arg_conds; // We keep conditions (for f2's actual arguments) from f1's state.constraints
  std::vector<std::vector<ref<Expr> > > upper_call_arg_conds;  // Stores conditions on f2_formal_arg, which are extracted from a summary
  std::vector<ref<Expr> > aggregated_conds;

  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): smmry's name = " << smmry->fn->getName() << "(); upper_calls fn =  " <<
                  upper_call->fn->getName() << "()\n";

  unsigned num_args = upper_call->fn->arg_size(); 
  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): num_args = " << num_args << "\n";
  if(num_args == 0)
  {
    llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): no args => no conditions => return true\n";
    return true;
  }

  /* Init arrays */
  for(unsigned i=0; i < num_args; i++)
    {std::vector<ref<Expr> > v1; smmry_arg_conds.push_back(v1);
     std::vector<ref<Expr> > v2; upper_call_arg_conds.push_back(v2);}

  //upper_call_arg_conds = upper_call->actual_args_conditions;

  /*  Collect constraints for each actual argument from smmry.
   *  ivan: Do we really need this, why not just add all conditions from
   *  the summary to <aggreated_conds>?*/
  //llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): Extracting constraints for actual arguments from f1_smmry.path_constraints.\n";
  for(std::vector< ref<Expr> >::const_iterator it_1  = smmry->path_constraints.begin(); 
                                               it_1 != smmry->path_constraints.end(); ++it_1) //For each condition in the summary
  {
    const ref<Expr> cond = *it_1;
    aggregated_conds.push_back(cond);
  }

  /* Collect conditions from the upper call, and replace formal
   * arguments with actual arguments */
  assert(num_args);
  llvm::outs() << "Conditions from upper call:\n";
  for(std::vector< ref<Expr> >::const_iterator it_1  = upper_call->accumulated_conditions.begin(); 
                                               it_1 != upper_call->accumulated_conditions.end(); ++it_1)
  {
    const ref<Expr> cond = *it_1;
    llvm::outs() << "\n" << cond << "\n";
    ref<Expr> tmp;
    for(unsigned i=0; i<num_args; i++)
    {
      llvm::outs() << "Replacing " << upper_call->fargs[i] << " with " << smmry->target_func_actual_args[i] << "\n";
      if(i==0)
        tmp = replace_subexpr(cond, upper_call->fargs[i], smmry->target_func_actual_args[i]);
      else
        tmp = replace_subexpr(tmp, upper_call->fargs[i], smmry->target_func_actual_args[i]);
    }
    aggregated_conds.push_back(tmp);
    llvm::outs() << tmp << "\n";
  }

  
  bool res = conds_are_solvable(aggregated_conds);
  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): " 
               << (res ? "can" : "cannot") << " glue with this summary\n";

  /* Cache the result */
  llvm::outs() << "InterpreterManager::comp_symbex_can_glue2(): caching this upper call/smmry combinations: " 
               << upper_call->shallow_hash() << " / " << smmry->shallow_hash() << "\n";
  if(res)
    upper_calls_fit_cache[upper_call->shallow_hash()].insert(smmry->shallow_hash());
  else
    upper_calls_nofit_cache[upper_call->shallow_hash()].insert(smmry->shallow_hash());

  return res;


}


/* Check if conditions in <vexpr> do not contradict each other */
bool InterpreterManager::conds_are_solvable(std::vector< ref<Expr> > &vexpr)
{
  llvm::outs() << "InterpreterManager::conds_are_solvable(): checking the following conds:\n";
  print_expressions(vexpr);
  if(vexpr.size() == 0)
    return true;


  /* Create And expression out of <vexpr>*/
  ref<Expr> conjunction = vexpr[0];
  /* We compute our own hash because different conjunctions can boil down to false/true,
   * for which KLEE will compute the same hash (but the conjunctions are different!),
   * so we need to combine expressions manually */
  unsigned ugly_hash = vexpr[0]->hash();
  if(vexpr.size() >= 2) 
  {
    conjunction = AndExpr::create(vexpr[0], vexpr[1]);
    ugly_hash = compute_ugly_hash(ugly_hash, vexpr[1]->hash());
    for(unsigned i = 2; i<vexpr.size(); i++)
    {
      conjunction = AndExpr::create(conjunction, vexpr[i]);
      ugly_hash = compute_ugly_hash(ugly_hash, vexpr[i]->hash());
    }
  }
  llvm::outs() << "Here is our conjunction:\n" << conjunction << " with ugly hash = " << ugly_hash << "\n";

  /* Check if already checked these constraints */
  if(valid_constraints.count(ugly_hash))
  {
    llvm::outs() << "matching hash (for valid): " << ugly_hash << "\n";
    return true;
  }
  if(invalid_constraints.count(ugly_hash))
  {
    llvm::outs() << "matching hash (for invalid): " << ugly_hash << "\n";
    return false;
  }

  std::vector< ref<Expr> > empty;
  ref<Expr> true_expr =  ConstantExpr::create(1, Expr::Bool);
  ref<Expr> match = EqExpr::create(true_expr, true_expr);
  empty.push_back(match);
  ConstraintManager cm(empty);

/* Experimenting */
  //ConstraintManager cm1(vexpr);
  std::vector< ref<Expr> > just_one;
  ref<Expr> tr =  ConstantExpr::create(1, Expr::Bool);
  ref<Expr> eqtrue = EqExpr::create(tr, tr);
  just_one.push_back(eqtrue);
  ConstraintManager cm2(just_one);
  Solver::Validity valid_debug;
  coreSolver->evaluate(Query(cm2, conjunction), valid_debug); 
  llvm::outs() << "valid_debug = " << valid_debug << "\n";
/* *** */

#if 0  
  Solver::Validity valid;
  for(int i = 0; i < vexpr.size(); i++)
  {
    llvm::outs() << "Checking " << vexpr[i] << "\n\n";
    coreSolver->evaluate(Query(cm, vexpr[i]), valid); 
    if ((valid != Solver::Unknown) &&  (valid != Solver::True))
      break;
    cm.addConstraint(vexpr[i]);
  }

  llvm::outs() << "valid = " << valid << "\n";
#endif

  //if ((valid == Solver::Unknown) ||  (valid == Solver::True))
  if ((valid_debug == Solver::Unknown) ||  (valid_debug == Solver::True))
  {
    //assert((valid_debug == Solver::Unknown) ||  (valid_debug == Solver::True));
    valid_constraints[ugly_hash] = conjunction; // We really care only about keys, not what we store
    return true;
  }
  else
  {
    //assert(valid == valid_debug);
    invalid_constraints[ugly_hash] = conjunction;
    return false;
  }

  //llvm::outs() << "debug_result = " << debug_result << "\n";
  //llvm::outs() << "vexpr[0] = " << vexpr[0] << "\n";
  //llvm::outs() << "debug_result1 = " << debug_result1 << "\n";
  //llvm::outs() << "vexpr[1] = " << vexpr[1] << "\n";
  //llvm::outs() << "debug_result2 = " << debug_result2 << "\n";

#if 0 // Some debug printing
/* ============== */
    std::string Str;
    llvm::raw_string_ostream info(Str);
    ExprSMTLIBPrinter printer;
    printer.setOutput(info);
    Query query(cm1, ConstantExpr::alloc(0, Expr::Bool));
    printer.setQuery(query);
    printer.generateOutput();
    llvm::outs() << info.str();
/* ===================*/
    std::string Str1;
    llvm::raw_string_ostream info1(Str1);
    ExprPPrinter::printConstraints(info1, cm1);
    llvm::outs() << info1.str();
/* ===================*/
#endif
  
  //return solver_result1;
}


#if 0
/* Replace all concat expressions in <conditions> with <x> and check
 * the system can be solved.*
 */
bool InterpreterManager::conds_are_solvable(ref<Expr> x, std::vector< ref<Expr> > *conditions)
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
    //llvm::outs() << "Executor::conds_are_solvable(): replacing concats in\n" << tmp << "\n"
    //                "with " << x << "\n";
    //comp_symbex_replace_for_retvalue(tmp, x);


    //llvm::outs() << "Executor::conds_are_solvable(): the updated constraint:\n" << tmp << "\n";
    */ 

    ref<Expr> tmp = comp_symbex_replace_for_retvalue(e, x);

    vexpr.push_back(tmp);
  }

  llvm::outs() << "Executor::conds_are_solvable(): checking the following constraints:\n";
  print_expressions(vexpr);

  ref<Expr> true_expr =  ConstantExpr::create(1, Expr::Bool);
  ConstraintManager cm(vexpr);
  //bool success = solver->solver->mayBeTrue(Query(cm, true_expr), solver_result);
  //bool success = solver->solver->mayBeTrue(Query(cm, vexpr.back()), solver_result);
  for(std::vector< ref<Expr> >::iterator it = vexpr.begin(); it != vexpr.end(); ++it)
  {
    //bool success = solver->solver->mayBeTrue(Query(cm, *it), solver_result);
    bool success = coreSolver->mayBeTrue(Query(cm, *it), solver_result);
    assert(success && "FIXME: Unhandled solver failure");
    if(!solver_result)
      break;
  }
  llvm::outs() << "Executor::conds_are_solvable(): result = " << solver_result << "\n";

  if(!solver_result)
    return false;

  return true;
}
#endif

#if 0 // moved to ExprUtils
/* Replace <orig_concat> in <expr> by <new_concat> */
ref<Expr> InterpreterManager::replace_subexpr(ref<Expr> expr, ref<Expr> &token_old, ref<Expr> &token_new)
{
  if (isa<ConstantExpr>(expr))
    return expr;

  unsigned numkids = expr->getNumKids();
  assert(numkids && "zero numkids for non costant expression, wtf!?");
  //llvm::outs() << "InterpreterManager::replace_subexpr(): " << numkids << " kids\n";
  assert((numkids<=4) && "numkids>4 ");
  ref<Expr> arr[4];
  for(unsigned i = 0; i<numkids; i++)
  {
    //if(isa<ConcatExpr>(expr->getKid(0)))
    if(expr->getKid(i) == token_old)
      arr[i] = token_new;
    else
      arr[i] = replace_subexpr(expr->getKid(i), token_old, token_new);
  }
  ref<Expr> tmp = expr->rebuild(arr);
  return tmp;
}
#endif

#if 0
/* Replace all concat expressions in <conditions> with <retvalue> */
ref<Expr> InterpreterManager::comp_symbex_replace_for_retvalue(ref<Expr> expr, ref<Expr> &retvalue)
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
    //llvm::outs() << "Executor::comp_symbex_replace_for_retvalue():  considerting select:\n" << *se << "\n";
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
    llvm::outs() << "InterpreterManager::comp_symbex_replace_for_retvalue(): general case\n";
    unsigned numkids = expr->getNumKids();
    assert(numkids && "zero numkids for non costant expression, wtf!?");
    if(numkids == 1)
    {
      llvm::outs() << "InterpreterManager::comp_symbex_replace_for_retvalue(): general case, 1 kid\n";
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
      llvm::outs() << "InterpreterManager::comp_symbex_replace_for_retvalue(): general case, 2 kids\n";
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
      llvm::outs() << "InterpreterManager::comp_symbex_replace_for_retvalue(): general case, " << numkids << " kids\n";
      assert(0 && "number of kids is not supported");
    }
  }
  assert(0 && "expression type is not supported yet");
}
#endif


/** 
 * TODO: add description
*/
bool InterpreterManager::path_summary_fits_inner_call(path_summary_ty *smmry,  InnerCall *inner_call)
{
  llvm::Function *f_s = smmry->fn;
  llvm::outs() << "InterpreterManager::path_summary_fits_inner_call(): -- Checking (and adapting its inner calls) next "
                  " function summary for function "<< f_s->getName() << "()\n";
  path_summary_ty *original_path_summary = smmry;
  path_summary_ty *copy_path_summary = new PathSummary(original_path_summary);
  bool added = false;
  /* This sets parent_inner_call for each copy_path_summary's inner call to <inner_call> */
  adapt_psummary_to_inner_call(inner_call, copy_path_summary);

  ref<Expr> summary_retvalue = copy_path_summary->return_value;
  llvm::outs() << "InterpreterManager::path_summary_fits_inner_call(): Checking the following function summary (for function "
               << f_s->getName() << ") and return value: "  << summary_retvalue << "; constraints:\n";
  copy_path_summary->print();

  bool can_glue = comp_symbex_can_glue2(smmry, inner_call);


  if(can_glue)
  {
    llvm::outs() << "InterpreterManager::path_summary_fits_inner_call(): conds are good, checking inner calls\n";
    int res = 1;
    copy_path_summary->clear_connected_summaries_for_inner_calls();
    res = run_inner_calls(*copy_path_summary);
    if(res)
    {
      llvm::outs() << "InterpreterManager::path_summary_fits_inner_call(): inner_call " << inner_call->seq_num << " (" << inner_call << ")"
                " for " << inner_call->call_inst->getParent()->getParent()->getName() << "() (function " <<
                f_s->getName() << "()): all inner inner calls are good for summary (adding):\n"; 
      copy_path_summary->print();
      inner_call->connected_summaries.push_back(copy_path_summary);
      added = true;
    } else
      llvm::outs() << "inner calls are not good.\n";
  }



  if(!added)
  {
    delete copy_path_summary;
    return false;
  } else
    return true;
}


/** Try to find a path summary for the inner call which satisfies all
 * the inner's call conditions. Inner call has conditions on a) return
 * value; b) formal arguments.
 */
int InterpreterManager::run_inner_call(InnerCall *inner_call)
{
  /**** 1. Hack to skip path summary for klee_div_zero_check() ****/
  llvm::CallInst *ci = inner_call->call_inst;
  llvm::Function *f_s = ci->getCalledFunction();
  if((f_s->getName().str() == "klee_div_zero_check") || (f_s->getName().str() == "abs_") || (f_s->getName().str() == "avg")
       || (f_s->getName().str() == "memset"))
  {
    //llvm::outs() << "InterpreterManager::explore_inner_call(): skipping klee_div_zero_check.\n";
    return 1;
  }
  
  /**** 2. Some debug printing ****/
  llvm::outs() << "InterpreterManager::run_inner_call(): The following call instruction"
                   " was replaced with a symbolic: " << *ci << "\n";
#if 0
  llvm::outs() << "InterpreterManager::run_inner_call(): Inner call has the"
                  " following pre-constraints on formal args:\n";
  /* a. print conditions on formal args (e.g. if we called classifyGesture(3)) ****/
  if(inner_call->formal_args_conditions.size() > 0)
    for(unsigned i = 0; i<inner_call->formal_args_conditions.size(); i++)
    {
      llvm::outs() << "For arg" << i << "\n";
      print_expressions(inner_call->formal_args_conditions[i]);
    }
  else
    llvm::outs() << "  empty\n";
#endif
  
  //llvm::outs() << "InterpreterManager::run_inner_call(): First let's check if we "
  //                 " already have a fitting path summary for the called function\n";
  
  
  /**** 3. Go through all existing path summaries for <f_s>, and find
  *       those whose 1) return value and 2) formal arg constraints satisfy
  *       inner_call. Add pointers to such summaries to inner_call.connected_summaries 
  ****/
  SummaryExecutor *smmry_executor;
  bool tried = false;
  if(!summary_interpreters.count(f_s))
  {
    llvm::outs() << "InterpreterManager::run_inner_call(): no summary executor."
                    "Going to create one and collect summaries for function " 
                 << f_s->getName() << "().\n";
    smmry_executor = create_summary_executor(f_s);
    smmry_executor->collectPathSummaries(NULL, inner_call);
    tried = true;
  }
  else if(need_more_summaries[f_s]) // We set it to true at the beginning of each round of composit symbex
  {
    llvm::outs() << "InterpreterManager::run_inner_call(): collecting more summaries for function " 
                 << f_s->getName() << "() due to new symbex round\n";
    smmry_executor = summary_interpreters[f_s];
    smmry_executor->continue_run(NULL, inner_call);
    need_more_summaries[f_s] = false;
    tried = true;
  }
  else
  {
    llvm::outs() << "InterpreterManager::run_inner_call(): not collecting summaries, will check existing\n";
    smmry_executor = summary_interpreters[f_s];
  }

  llvm::outs() << "InterpreterManager::run_inner_call(): function " << f_s->getName() << 
                  "() has " << summary_interpreters[f_s]->path_summaries.size() 
                  << " summaries; connsumms = " << inner_call->connected_summaries.size() 
		  << "; parent_inner_call = " << (inner_call->parent_inner_call ? inner_call->parent_inner_call->call_inst->getCalledFunction()->getName() : "NULL") << ".\n";

  /* Check retvalue + formal_args_constraints for each collected
   * summary; we also need to check if we can find appropriate
   * inner_calls */
  int at_least_one_summary_has_all_InnerCalls = 0;
  for(std::vector<path_summary_ty *>::iterator it_1 = summary_interpreters[f_s]->path_summaries.begin(); 
      it_1 != summary_interpreters[f_s]->path_summaries.end(); ++it_1)
  {
    path_summary_ty *smmry = *it_1;
    if(smmry->type != PathSummary::RET_SUMMARY_TYPE)
      continue;
    /* The following function will create a copy of <smmry> and add it to
     * <inner_call->connected_summaries> if <smmry> satisfies return and
     * other inner call's conditions (it will run inner calls) */
    bool res = path_summary_fits_inner_call(smmry,  inner_call);
    if(res)
      at_least_one_summary_has_all_InnerCalls = 1;
  }
  if(at_least_one_summary_has_all_InnerCalls)
    llvm::outs() << "InterpreterManager::run_inner_call(): at least one summary for inner_call " << inner_call->seq_num <<
                    " for " << inner_call->call_inst->getParent()->getParent()->getName() << "() (function " <<
                    f_s->getName() << "()) has all suppcalls\n"; 
  else
    llvm::outs() << "InterpreterManager::run_inner_call(): no summary for inner_call " << inner_call->seq_num <<
                    " for " << inner_call->call_inst->getParent()->getParent()->getName() << "() (function " <<
                    f_s->getName() << "()) has all suppcalls\n"; 
  llvm::outs() << "InterpreterManager::run_inner_call(): inner_call " << inner_call->seq_num << "(" << inner_call << ")"
                    " for " << inner_call->call_inst->getParent()->getParent()->getName() << "() (function " <<
                    f_s->getName() << "()) has " << inner_call->connected_summaries.size() << " connected summaries\n"; 
  llvm::outs() << "InterpreterManager::run_inner_call(): returning " << at_least_one_summary_has_all_InnerCalls << "\n";


  /* Existing summaries did not work for us, let's collect more summaries */
  if(!at_least_one_summary_has_all_InnerCalls && !tried) 
  {
    llvm::outs() << "InterpreterManager::run_inner_call(): collecting more summaries\n";
    unsigned n1 = summary_interpreters[f_s]->path_summaries.size();
    smmry_executor = summary_interpreters[f_s];
    smmry_executor->continue_run(NULL, inner_call);
    unsigned n2 = summary_interpreters[f_s]->path_summaries.size();
    /* Check newly collected summaries */
    if(n2>n1)
    {
      for(unsigned i = n1-1; i < n2; i++)
      {
        path_summary_ty *smmry = summary_interpreters[f_s]->path_summaries[i];
        bool res = path_summary_fits_inner_call(smmry,  inner_call);
        if(res)
          at_least_one_summary_has_all_InnerCalls = 1;
      }
    }
  }

  return at_least_one_summary_has_all_InnerCalls;
}


/** 
 * upper call belongs to the prevous function to original_path_summary
 * 
*/
bool InterpreterManager::path_summary_fits_upper_call(path_summary_ty *original_path_summary,  UpperCall *upper_call)
{
  llvm::Function *f_s = original_path_summary->fn;
  llvm::outs() << "InterpreterManager::path_summary_fits_upper_call(): inside:"
               <<  " function summary for function "<< f_s->getName() << "(); upper_call belongs to function "
	       << upper_call->fn->getName() << "; smmry->end_function = " << original_path_summary->end_function->getName() << "\n";
  path_summary_ty *copy_path_summary = new PathSummary(original_path_summary);
  bool added = false;
  adapt_psummary_to_upper_call(upper_call, copy_path_summary);


  llvm::outs() << "InterpreterManager::path_summary_fits_upper_call(): Checking the following function summary (for function "
               << f_s->getName() << "(); constraints:\n";
  copy_path_summary->print();

  /* Check that the actual args of the target function satisfy
   * upper_call's actual args constraints */

  if(comp_symbex_can_glue2(copy_path_summary, upper_call))
  {
    llvm::outs() << "InterpreterManager::path_summary_fits_upper_call(): actual args constraints are good. checking inner_calls\n";
    int res = 1;
    copy_path_summary->clear_connected_summaries_for_inner_calls();
    res = run_inner_calls(*copy_path_summary);
    if(res)
    {
      llvm::outs() << "InterpreterManager::path_summary_fits_upper_call():  all inner inner calls are good for summary; checking next upper call:\n"; 
      copy_path_summary->print();

      /* Check next level upper call */
      std::vector<const llvm::Function *>::iterator it;
      it = std::find(path_manager->call_path.begin(),
                     path_manager->call_path.end(), (const llvm::Function *)(copy_path_summary->fn));
      assert(it != path_manager->call_path.end());
      unsigned idx = std::distance(path_manager->call_path.begin(), it);
      llvm::outs() << "InterpreterManager::path_summary_fits_upper_call(): copy_path_summary->fn = "
                   << copy_path_summary->fn->getName() << "; idx = " << idx << "\n"; 
      llvm::Function *caller = NULL;
      int res2;
      if(idx != 0) /* if we are not working with main() */
      {
        llvm::outs() << "InterpreterManager::path_summary_fits_upper_call(): creating new upper call\n";
        caller = (Function *)(path_manager->call_path[idx-1]);
        UpperCall *new_upper_call = new UpperCall(copy_path_summary->fn, caller);
        new_upper_call->fargs = copy_path_summary->fargs;
       	new_upper_call->owner_smmry = copy_path_summary;
        /* This will scan summary's path constrains and extract
         * conditions on the formal args (which are conditions on the
         * actual args for the upper_call) */
        //new_upper_call->update_actual_args_conds(copy_path_summary->path_constraints, copy_path_summary->fargs);
        /* Pull constraints from the previous upper call */
        new_upper_call->pull_constraints(copy_path_summary, upper_call);
        copy_path_summary->upper_call = new_upper_call;
        /* This will pass conditions from lower level <upper_call> to the
         * next level's <new_upper_call> */
        //new_upper_call->add_actual_args_conds(upper_call, copy_path_summary);
        /* Run upper call with updated constraints */
        res2 = run_upper_call(new_upper_call); /* This will collect <connected_summaries> for the upper calls further up along the call_path */
      } else
      {
        llvm::outs() << "InterpreterManager::path_summary_fits_upper_call(): at the top => not creating new upper call, instead adding summary to the list of candidates\n";
        candidates.push_back(copy_path_summary);
        res2 = true;
      }

      if(res2)
      {
        upper_call->connected_summaries.push_back(copy_path_summary);
        copy_path_summary->next_path_summaries.push_back(upper_call->owner_smmry);
        added = true;
      }
      else 
        llvm::outs() << "next level up call is not good.\n";
    }
     else
      llvm::outs() << "inner calls are not good.\n";
  }
  else
    llvm::outs() << "Conditiosn do not match\n";
  if(!added)
  {
    delete copy_path_summary;
    return false;
  } else
  {
    llvm::outs() << "InterpreterManager::path_summary_fits_upper_call(): for summry->fn = " 
                 << copy_path_summary->fn->getName() << "(); upper call belongs to " 
                 << upper_call->fn->getName() << "() returning true\n";
    return true;
  }
}




/* Find apporpritate path summaries (i.e. which satisfy all conditions)
 * for the <path_smmry>'s upper call */
int InterpreterManager::run_upper_call(UpperCall *upper_call)
{
  assert(upper_call);

  Function *f0 = NULL; // f0 (if exisists) calls f1
  Function *f1 = upper_call->caller; // f1 calls f2, we will execut f1
  Function *f2 = upper_call->fn; // This is the target function for f2's summary executor
  SummaryExecutor *smmry_executor = NULL;

  /* Note that call_path is a std::vector which starts with main() and ends with assert() */
  std::vector<const llvm::Function *>::iterator it;
  it = std::find(path_manager->call_path.begin(),
                 path_manager->call_path.end(), (const llvm::Function *)f1);
  assert(it != path_manager->call_path.end());
  unsigned f1_idx = std::distance(path_manager->call_path.begin(), it);
  //unsigned N = path_manager->call_path.size();
  if(f1_idx - 1 >= 0)
    f0 = (Function *)(path_manager->call_path[f1_idx-1]);

  llvm::outs() << " +++ InterpreterManager::run_upper_call(): running symbex for path part: " 
               << f1->getName()  << "() -> " << f2->getName() << "().\n";
  
  /* 1. Start collecting path summaries until we find the one which
   * reaches a call to <f2> or (until we time out) */
  bool tried = false;
  if(!summary_interpreters.count(f1))
  {
    llvm::outs() << "InterpreterManager::run_upper_call(): no summary executor."
                    "Going to create one and collect summaries for function " 
                 << f1->getName() << "().\n";
    smmry_executor = create_summary_executor(f1);
    smmry_executor->collectPathSummaries(upper_call, NULL);
    tried = true;
  }
  else if(need_more_summaries[f1]) // We set it to true at the beginning of each round of composit symbex
  {
    smmry_executor = summary_interpreters[f1];
    smmry_executor->continue_run(upper_call, NULL);
    need_more_summaries[f1] = false;
    tried = true;
  }
  else
  {
    smmry_executor = summary_interpreters[f1];
    llvm::outs() << "InterpreterManager::run_upper_call(): not collecting summaries, will check existing\n";
  }

  assert(smmry_executor && "Summary Executor is NULL, it's a bug");
  llvm::outs() << "InterpreterManager::run_upper_call(): finished collecting summaries for " 
               << smmry_executor->func->getName() << "() (" 
               << smmry_executor->path_summaries.size() << " summaries)\n";
  //llvm::outs() << "InterpreterManager::run_upper_call(): function " << f1->getName() << 
  //                "() has " << summary_interpreters[f1]->path_summaries.size() 
  //                << " summaries;\n";
  
  int at_least_one_summary_fits = 0;

  std::vector<path_summary_ty *> smmries = summary_interpreters[f1]->path_summaries;
  for(std::vector<path_summary_ty *>::iterator it_1 = smmries.begin(); it_1 != smmries.end(); ++it_1)
  {
    path_summary_ty *smmry = *it_1;
    //smmry->clear_InnerCalls_constraints();
    //smmry->update_InnerCalls_with_constraints();

    if ( (smmry->type != PathSummary::TARGET_FUNC_SUMMARY_TYPE) || (smmry->end_function != f2) )
    {
      llvm::outs() << "InterpreterManager::run_upper_call(): skipping summary.\n";
      continue;
    }
    /* The following function will create a copy of <smmry>,
      check conditions, run inner calls, and add the copy summry to
      upper_call->connected_summaries */
    bool res = path_summary_fits_upper_call(smmry, upper_call);
    if(res)
      at_least_one_summary_fits = 1;
  }

  return at_least_one_summary_fits;
}

/* Find apporpritate path summries (i.e. which satisfy all conditions)
 * for each of the  current path summary's inner call */
int InterpreterManager::run_inner_calls(path_summary_ty &path_smmry)
{
  /* Go through all call symbolic replacements */
  for(call_symbolic_replacements_ty::iterator it_1  = path_smmry.call_symbolic_replacements.begin();
                                              it_1 != path_smmry.call_symbolic_replacements.end(); ++it_1)
  {
    InnerCall *inner_call = it_1->second;
    llvm::outs() << "InterpreterManager::run_inner_calls(): exploring inner_call " << inner_call->seq_num 
                 << " for function " << path_smmry.fn->getName() << "(): "
                 << inner_call->call_inst->getCalledFunction()->getName() << "()\n";
    llvm::outs() << "InterpreterManager::run_inner_calls(): parent_inner_call = " 
                 << (inner_call->parent_inner_call ? inner_call->parent_inner_call->call_inst->getCalledFunction()->getName() : "NULL") << "\n";
    /* If inner call function does not have any args, there is not sense in collecting summaries */
    if(false && (inner_call->call_inst->getCalledFunction()->arg_size() == 0)
         && (inner_call->call_inst->getCalledFunction()->getReturnType()->isVoidTy()))
    {
      llvm::outs() << "InterpreterManager::run_inner_calls(): skipping inner call as it has no args and has no users\n"; 
      continue;
    }
    /* This will update unwrapped_constraints and accumulated_conditions */
    //inner_call->constraints = path_smmry.path_constraints;
    llvm::outs() << "InterpreterManager::run_inner_calls(): unwrapping conditions for this inner call\n"; 
    inner_call->unwrap_constraints(&path_smmry); // This will also recompute shallow hash
    int res = run_inner_call(inner_call);
    if(res == 0)
      return 0;
  }
  return 1;
}

void InterpreterManager::do_backward_symbex()
{

  assert(path_manager && "Path Manager required but not set");
  assert(kmodule && "KModule required but not set");
  assert(coreSolver && "Core Solver required but not set");

  Function *f0 = NULL; // f0 (if exisists) calls f1
  Function *f1 = NULL; // f1 calls f2
  Function *f2 = NULL; // the target function (i.e. assert())
  SummaryExecutor *smmry_executor;

  /* Note that call_path is a std::vector which starts with main() and ends with assert() */
  unsigned N = path_manager->call_path.size();
  if(path_manager->call_path.size() >= 3)
    f0 = (Function *)(path_manager->call_path[N-3]);
  f1 = (Function *)(path_manager->call_path[N-2]);
  f2 = (Function *)(path_manager->call_path[N-1]);

  llvm::outs() << " +++ InterpreterManager::do_backward_symbex(): running symbex for path part: " 
               << f1->getName()  << "() -> " << f2->getName() << "().\n";
  
  /* 1. Start collecting path summaries until we find the one which
   * reaches a call to <f2> or (until we time out) */
  if(!summary_interpreters.count(f1))
  {
    smmry_executor = create_summary_executor(f1);
    /* Hack to pass f2 = assert() as a target function */
    UpperCall *fake_upper_call = new UpperCall(f2, f1);
    smmry_executor->collectPathSummaries(fake_upper_call, NULL);
    delete fake_upper_call;
  }
  else
  {
    smmry_executor = summary_interpreters[f1];
    /* Hack to pass f2 = assert() as a target function */
    UpperCall *fake_upper_call = new UpperCall(f2, f1);
    //smmry_executor->collectPathSummaries(fake_upper_call, NULL);
    smmry_executor->continue_run(fake_upper_call, NULL);
    delete fake_upper_call;
  }

  llvm::outs() << "InterpreterManager::do_backward_symbex(): finished collecting summaries for " 
               << smmry_executor->func->getName() << "() (" 
               << smmry_executor->path_summaries.size() << " summaries)\n";
  llvm::outs() << "InterpreterManager::do_backward_symbex(): Will check inner calls now.\n";

  /* 2. Run inner calls for each collected summaries */
  std::vector<path_summary_ty *> smmries = summary_interpreters[f1]->path_summaries;
  llvm::outs() << "InterpreterManager::do_backward_symbex(): looking for the last before assert() function: " << f1->getName() <<
                   "() ( " << smmries.size() << " summaries)\n";
  for(std::vector<path_summary_ty *>::iterator it_1 = smmries.begin(); it_1 != smmries.end(); ++it_1)
  {
    path_summary_ty *smmry = *it_1;
    //smmry->clear_InnerCalls_constraints();
    //smmry->update_InnerCalls_with_constraints();
    if ( (smmry->type == PathSummary::TARGET_FUNC_SUMMARY_TYPE) && 
         (smmry->end_function == f2) )
    {
      llvm::outs() << "InterpreterManager::do_backward_symbex(): considering good looking summary:\n";
      smmry->print();
      llvm::outs() << "InterpreterManager::do_backward_symbex(): going to run inner calls\n";
      smmry->clear_connected_summaries_for_inner_calls();
      smmry->set_parent_for_inner_calls(NULL);
      
      /* We collect inner calls for the bottom functon => no prev upper call => no additional constraints */
      int res1 = run_inner_calls(*smmry); /* This will collect <connected_summaries> for the inner calls */
      if(res1)
        llvm::outs() << "InterpreterManager::do_backward_symbex(): inner calls collected successfully\n"; 
      int res2 = 0; /* Set to 1 if we were able to find summaries fitting the upper call */
      if(f0 && res1) 
      {
        llvm::outs() << "InterpreterManager::do_backward_symbex(): going to run upper call for " << f0->getName() << "\n";
        UpperCall *new_upper_call = new UpperCall(f1, f0); // This upper call belongs to f1 and the caller is f0
       	new_upper_call->fargs = smmry->fargs;
       	new_upper_call->owner_smmry = smmry;
        /* This will scan summary's path constrains and extract
         * conditions on the formal args (which are conditions on the
         * actual args for the upper_call) */
        //new_upper_call->update_actual_args_conds(smmry->path_constraints, smmry->fargs);
        /* Pull constraints from the previous upper call */
        new_upper_call->pull_constraints(smmry, NULL);
        smmry->upper_call = new_upper_call;
        /* We are at the bottom of the call_path -> don't have
         * lower-level upper call, so just run upper call with updated
         * constraints */
        res2 = run_upper_call(smmry->upper_call); /* This will collect <connected_summaries> for the upper call further up along the call_path */
      } else if(res1)
      {
        llvm::outs() << "InterpreterManager::do_backward_symbex(): at the top => not creating new upper call, instead adding summary to the list of candidates\n";
        candidates.push_back(smmry);
        res2 = true;
      }
        
      if(res1 && res2)
      {
        llvm::outs() << "InterpreterManager::do_backward_symbex(): the following summary for " 
                       << smmry->fn->getName() << "() is gluable, has appropriate suppl calls, has"
		       << "appropriate upper call\n";
        smmry->print();
      }
    }
    else
      llvm::outs() << "InterpreterManager::do_backward_symbex(): skipping summary.\n";
  }
}


#if 0
void InterpreterManager::do_backward_symbex()
{

  assert(path_manager && "Path Manager required but not set");
  assert(kmodule && "KModule required but not set");
  assert(coreSolver && "Core Solver required but not set");

  Function *f1;
  Function *f2;
  SummaryExecutor *smmry_executor;

  /* Build function summaries for all functions along the call path to
   * the target function (starging from the end) */
  for(unsigned i = 1; i<= path_manager->call_path.size()-1; i++)
  {
    f1 = (Function *)(path_manager->call_path[path_manager->call_path.size()-(i+1)]); // the one which calls assert() = printGesture()
    f2 = (Function *)(path_manager->call_path[path_manager->call_path.size()-i]); // assert() 
    llvm::outs() << " +++ InterpreterManager::do_backward_symbex(): running symbex for path part: " << f1->getName() 
                 << "() -> " << f2->getName() << "().\n";
  
    /* 1. Start collecting path summaries until we find the one which
     * reaches a call to <f2> or (until we time out) */
    if(!summary_interpreters.count(f1))
    {
      smmry_executor = create_summary_executor(f1);
      smmry_executor->collectPathSummaries(f2, NULL);
    }
    else
    {
      smmry_executor = summary_interpreters[f1];
      smmry_executor->continue_run(f2, NULL);
    }
    llvm::outs() << "InterpreterManager::do_backward_symbex(): finished collecting summaries for " 
                 << smmry_executor->func->getName() << "() (" 
                 << smmry_executor->path_summaries.size() << " summaries)\n";
    llvm::outs() << "InterpreterManager::do_backward_symbex(): Will check inner calls now.\n";

    /* 2. Run supplementary functions (those which we replaced by symbolic values) */
    if(i==1)
    {
      std::vector<path_summary_ty *> smmries = summary_interpreters[f1]->path_summaries;
      llvm::outs() << "InterpreterManager::do_backward_symbex(): looking for the last before assert() function: " << f1->getName() <<
                       "() ( " << smmries.size() << " summaries)\n";
      for(std::vector<path_summary_ty *>::iterator it_1 = smmries.begin(); it_1 != smmries.end(); ++it_1)
      {
        path_summary_ty *smmry = *it_1;
        smmry->clear_InnerCalls_constraints();
        smmry->update_InnerCalls_with_constraints();
        if ( (smmry->type == PathSummary::TARGET_FUNC_SUMMARY_TYPE) && 
             (smmry->end_function == f2) )
        {
          llvm::outs() << "InterpreterManager::do_backward_symbex(): considering good looking summary:\n";
          smmry->print();
          llvm::outs() << "InterpreterManager::do_backward_symbex(): going to run inner calls\n";
          smmry->clear_connected_summaries_for_inner_calls();
          int res = run_inner_calls(*smmry); /* This will collect <connected_summaries> for the inner calls */
          if(res)
          {
            llvm::outs() << "InterpreterManager::do_backward_symbex(): the following summary for " 
                           << smmry->fn->getName() << "() is gluable and has appropriate suppl calls\n";
	          smmry->print();
          }
        }
        else
	      {
          llvm::outs() << "InterpreterManager::do_backward_symbex(): skipping summary.\n";
	      }
      }
    } 
    /* We need to find summaries of the next function with which we can
     * glue and update constraints on call symbolics */
    else
    {
      /* We do the following. NOTE: <f1> calls <f2>
       * 1. We consider each good (so far) f1's summary.
       * 2. If we can glue it with an f2's summary, we make a copy of
       *    this summary (this copy will have no connected summaries for
       *    its suppl calls).
       * 3. Try to collect all suppl calls for the copy.
       * 4. If all suppl calls can be collected, save the copy 
       * 5. Erase all old good summaries for f1 (if a summary was really
       *    good, we have its copies in in the copy list
       * 6. Move summaries from the copy list to good_summaries[f1] list */
      std::vector<path_summary_ty *> &f1_smmries = summary_interpreters[f1]->path_summaries;
      std::vector<path_summary_ty *> &f2_smmries = summary_interpreters[f2]->path_summaries;
      //std::vector<path_summary_ty *> summaries_to_keep; // if we can glue (+find all supp calls) f1 summary with a f2's summary, we add a copy here
      llvm::outs() << "InterpreterManager::do_backward_symbex(): looking for summaries which we can glue for functions: " << f1->getName() <<
                       "() ( " << f1_smmries.size() << " summaries) and " << f2->getName() << "() ("
                       <<  f2_smmries.size() << " summaries)\n";
      int k = 0, j = 0;
      bool time_to_start_forwrad_symbex_debug = false;
      for(std::vector<path_summary_ty *>::iterator it_1 = f1_smmries.begin(); it_1 != f1_smmries.end(); ++it_1)
      {
        k++;
        j = 0;
        path_summary_ty *f1_smmry = *it_1;
        f1_smmry->clear_InnerCalls_constraints();
        f1_smmry->update_InnerCalls_with_constraints();
        /* 1. <f1> should call <f2> */
        if((f1_smmry->type != PathSummary::TARGET_FUNC_SUMMARY_TYPE) || (f1_smmry->end_function != f2))
          continue;
        for(std::vector<path_summary_ty *>::iterator it_2 = f2_smmries.begin(); it_2 != f2_smmries.end(); ++it_2)
        {
          path_summary_ty *f2_smmry = *it_2;
          j++;
          llvm::outs() << "InterpreterManager::do_backward_symbex(): Considering the following summaries: (k = "
                       << k << "; j = " << j << ") \n";
          f1_smmry->print();
          f2_smmry->print();

	  /* Discard f2's return summaries */
	  llvm::Function *f3 =  (Function *)(path_manager->call_path[path_manager->call_path.size()-i+1]);
          if ( (f2_smmry->type != PathSummary::TARGET_FUNC_SUMMARY_TYPE) || (f2_smmry->end_function != f3) )
          {
            llvm::outs() << "InterpreterManager::do_backward_symbex(): f2 does not end up calling " 
	                 << f3->getName() << "()\n";
            continue;
          }


          /* Discard the f2 summary if it doesn't have next path
           * summaries (f2 is the last function before assert() in the
           * call graph) */
          if((i > 2) && f2_smmry->next_path_summaries.empty())
          {
            llvm::outs() << "InterpreterManager::do_backward_symbex(): f2 summary is a dead end (no next path summaries)\n";
            continue;
          }

          /* Discard the f2 summary if we cannot glue with it */
          if(!comp_symbex_can_glue1(*f1_smmry, *f2_smmry))
          {
            llvm::outs() << "InterpreterManager::do_backward_symbex(): cannot glue with f2 summary\n";
            continue;
          }
          
          /* f1_smmary can glue with f2_smmary let's update its inner
           * calls constraints and run them. */
          f1_smmry->clear_connected_summaries_for_inner_calls();
          llvm::outs() << "InterpreterManager::do_backward_symbex(): can glue. Let's add new conditions on arguments\n";
          f1_smmry->update_InnerCalls_with_constraints2(*f2_smmry);
          llvm::outs() << "InterpreterManager::do_backward_symbex(): Running inner functions for " << f1_smmry->fn->getName() << "()\n";
          int res = run_inner_calls(*f1_smmry); // Run inner func for f1_summary

          /* Discard the f2 summary if gives unsolvable constraints on
           * the f1's inner calls */
          if(res == 0)
          {
            llvm::outs() << "InterpreterManager::do_backward_symbex(): the following summary chain for " 
                         << f1_smmry->fn->getName() << "() is gluable. We were not able to find suppl calls though.\n";
            continue;
          }

          /* If we got here we can connect <f1_smmry> and <f2_smmry> */
          llvm::outs() << "InterpreterManager::do_backward_symbex(): the following summary chain for " 
                       << f1_smmry->fn->getName() << "() is gluable and all inner calls have connected path summaries\n";
          f1_smmry->next_path_summaries.push_back(f2_smmry);
          for(std::vector<int>::iterator it_3 = f1_smmry->path_choices.begin(); it_3 != f1_smmry->path_choices.end(); ++it_3)
            llvm::outs() << *it_3 << " -> ";
          llvm::outs() << "\n";
        }
      }
    }

    llvm::outs() << "\n\n\n\n";
  }

  llvm::outs() << " \n\n\n +++ InterpreterManager::do_backward_symbex(): [FINISHED WITH BACKWARD SYMBEX] \n\n\n";

}
#endif

int InterpreterManager::do_forward_symbex(llvm::Function *f,
                                 int argc,
                                 char **argv,
                                 char **envp,
                                 int start_ndx)
{
  llvm::Function *mainFn = (llvm::Function *)(path_manager->call_path[0]);
 
  if(ForwardOnly)
  {
    /* Run forward executor with NULL summary path, so it will not follow anything */
    forward_interpreter->runFunction(mainFn, NULL, argc, argv, envp);
    return 0;
  }

  llvm::outs() << "+++ InterpreterManager::do_forward_symbex():: Starting forward symbex with mainFn= " << mainFn->getName() << "\n";
  llvm::outs() << "    InterpreterManager::do_forward_symbex():: candidates.size() = " << candidates.size() << "\n";
  std::vector<path_summary_ty *> complex_summaries = candidates;
  unsigned k;
  for(k = start_ndx; k<complex_summaries.size(); k++)
  {
    llvm::outs() << "InterpreterManager::do_forward_symbex(): Considering the following summary for the"
                    " main() function:\n";
    path_summary_ty *complex_smmry = complex_summaries[k];
    complex_smmry->print();
    complex_smmry->print_structure();

    std::vector<path_summary_ty *> simple_paths = split_path_candidate(complex_smmry);
    llvm::outs() << "\nThe number of produced simple paths = " << simple_paths.size() << "\n";

#if 0 // Some debug printing
    llvm::outs() << "\nHere is the complex candidate:\n";
    complex_smmry->print_structure();

    std::vector<path_summary_ty *> simple_paths = split_path_candidate(mainFn_smmry);
    llvm::outs() << "\nThe number of produced simple paths = " << simple_paths.size() << "\n";
    llvm::outs() << "\nHere is the first simple path:\n";
    assert(simple_paths[0]);
    simple_paths[0]->print_structure();

    llvm::outs() << "\n\n\nHere is the second simple path:\n";
    simple_paths[1]->print_structure();

    llvm::outs() << "\n\n\nHere is the third simple path:\n";
    simple_paths[2]->print_structure();
    mainFn_smmry = simple_paths[0];
#endif


    for(int j = 0; j < simple_paths.size(); j++)
    {
      path_summary_ty *simple_path = simple_paths[j];
      assert(simple_path);

      unsigned ugly_hash = compute_simple_path_hash(simple_path);

      llvm::outs() << "\n\nChecking the following simple path (with hash = " << ugly_hash << "):\n";
      simple_path->print_structure();

      if(checked_simple_paths.count(ugly_hash))
      {
        llvm::outs() << "Already checked this path. continue\n";
	//exit(0);
	continue;
      }

      /* Check we have a non call path summaries by accident */
      assert( (simple_path->type == PathSummary::TARGET_FUNC_SUMMARY_TYPE) && (simple_path->end_function == path_manager->call_path[1]) );
      /* Make sure we have next_path_summaries. Note that call path includes assert(), so the minimun length should be 2 */
      assert((path_manager->call_path.size() <= 2) || !(simple_path->next_path_summaries.empty()));
      forward_interpreter->runFunction(mainFn, simple_path, argc, argv, envp);

      checked_simple_paths[ugly_hash] = simple_path;
    }
  }
  return k;

}


/* This function start compositional symbolic execution
 *
 * This function first launches backward compositional symbolic
 * execution along the previously build path from main() to assert(). It
 * determines and stores constraints on the formal and actual arguments
 * of the function along the path, and constraints on return values for
 * function which are invoked in between.
 *
 * Second, this function launches forward symbolic execution, trying not
 * to deviate the path, and reusing the collected during the previous
 * step function summaries.
 * 
 * Parameters to this function are used only for forward symbolic execution.
 * 
 * @param f Pointer to the main function (i.e. the  function from which we want to start forward symbex)
 * @param argc
 * @param argv
 * @param envp Parameters for the main function.
*/
void InterpreterManager::startCompositSymbEx(llvm::Function *f,
                                 int argc,
                                 char **argv,
                                 char **envp)
{
  int i = 1;
  int start_ndx = 0;
  int icfg_change_timeout = 1200; // change every 20 minutes
  int change_time = time(NULL);
  while(1)
  {

    if(ForwardOnly)
    {
      do_forward_symbex(f, argc, argv, envp, start_ndx);
      return;
    }

    llvm::outs() << "SYMBEX ROUND " << i << "\n";
    /* Collect and glue together path summaries for different functions*/ 
    do_backward_symbex();

    /* Did not work => need to collect more summaries */
    for (std::map<llvm::Function *,bool>::iterator it=need_more_summaries.begin(); it!=need_more_summaries.end(); ++it)
      need_more_summaries[it->first] = true;
    i++;

    if((i%2) == 0)
    {
      llvm::outs() << "SYMBEX ROUND " << i << " start_ndx = " << start_ndx << "\n";
      start_ndx = do_forward_symbex(f, argc, argv, envp, start_ndx);
    }

    if( (time(NULL) - change_time) >= icfg_change_timeout )
    {
      llvm::outs() << " CHANGING ICFG!\n";
      change_time = time(NULL);
      path_manager->rotate_icfg();
    }
  }
  return;
}

SummaryExecutor* InterpreterManager::create_summary_executor(llvm::Function *f)
{
    assert(!summary_interpreters.count(f) && "Only one SummaryExecutor per function is allowed");
    SummaryExecutor *smmry_executor;
    smmry_executor = new SummaryExecutor(interpreterOpts, coreSolver, kmodule);
    assert(smmry_executor && "could not allocate memory for summary executor");
    smmry_executor->setFunction(f);
    smmry_executor->setArch(arch);
    smmry_executor->setPathManager(path_manager);
    smmry_executor->interpreter_manager = this;
    summary_interpreters[f] = smmry_executor;
    need_more_summaries[f] = false;
    return smmry_executor;
}

/* Thus function updates constraints for <smmry>'s inner calls
 *  based on <parent_inner_call>.
 *  1. If smmry's return value is a call symbolics, we need to pass
 *     parent_inner_call retavlue conditions to the corresponding inner
 *     call.
 *  2. If a <smmry inner call>'s actual arg is a smmry's formal arg, we
 *     need to pass parent_inner_call formal arg constraints to the
 *     corresponding child inner call 
 *  3. Set field <parent_inner_call> for each inner call to <parent_inner_call>*/
void InterpreterManager::adapt_psummary_to_inner_call(InnerCall *parent_inner_call, path_summary_ty *smmry)
{

#if 0
  std::vector<ref<Expr> > ret_conds = parent_inner_call->retval_conditions;
  ret_conds.insert(ret_conds.end(), parent_inner_call->retval_conditions2.begin(),
                     parent_inner_call->retval_conditions2.end());
#endif
  
  ref<Expr> result = smmry->return_value;
  ConstantExpr *ce = dyn_cast<ConstantExpr>(result);

  for(call_symbolic_replacements_ty::iterator it_1  = smmry->call_symbolic_replacements.begin();
                                              it_1 != smmry->call_symbolic_replacements.end(); ++it_1)
  {
    ref<Expr> child_symbolics = it_1->first;
    InnerCall *child_inner_call = it_1->second;
    /* Set parent inner call */
    child_inner_call->parent_inner_call = parent_inner_call;
    child_inner_call->connected_summaries.clear();

#if 0
    child_inner_call->retval_conditions.clear();
    child_inner_call->retval_conditions2.clear();

    /* If return value is a call symbolics, we need to pass
     * current retavlue conditions to the corresponding inner call*/
    if (!ce) 
    {
      //std::vector<ref<Expr> > symbs = extract_call_symbolics_from_expression(smmry, result);
      std::vector<ref<Expr> > symbs = smmry->get_call_symbolics(result);
      assert( (symbs.size() <= 1) && "Complex symbolic return values are not supported yet");

      std::vector<ref<Expr> > concats = extract_concat_subexpressions(result);
      std::vector<ref<Expr> >::iterator it_2 = std::find(concats.begin(), concats.end(), child_symbolics);
      if(it_2 != concats.end())
      {
        llvm::outs() << "InterpreterManager::adapt_psummary_to_inner_call(): adding the parent suppl"
                        " call's retval_conditions to suppl call " << child_inner_call->seq_num <<
                        " " << *(child_inner_call->call_inst) << "\n";
        print_expressions(parent_inner_call->retval_conditions);
        print_expressions(parent_inner_call->retval_conditions2);
        child_inner_call->retval_conditions.insert(child_inner_call->retval_conditions.end(),
                     parent_inner_call->retval_conditions.begin(), parent_inner_call->retval_conditions.end());
        child_inner_call->retval_conditions.insert(child_inner_call->retval_conditions.end(),
                     parent_inner_call->retval_conditions2.begin(), parent_inner_call->retval_conditions2.end());
      }
    }

    /* If summary's formal argument <f_i> is an actual argument for
     * child_inner_call, then we need to pass conditions on <f_i> to the
     * child inner call */
    for(unsigned i=0; i < smmry->fargs.size(); i++)
      for(unsigned j=0; j< child_inner_call->actual_args.size() ; j++)
        if(smmry->fargs[i] == child_inner_call->actual_args[j])
	      {
	        child_inner_call->formal_args_conditions[j].insert(
	                child_inner_call->formal_args_conditions[j].end(),
	                parent_inner_call->formal_args_conditions[i].begin(),
	                parent_inner_call->formal_args_conditions[i].end()
	        );
          llvm::outs() << "InterpreterManager::adapt_psummary_to_inner_call(): added "
	                << "parent inner call's formal arg conds for arg " << i << " to child inner "
	                << " call's formal arg conds for arg " << j << "\n";
	      }
#endif

  }
  //smmry->update_InnerCalls_with_constraints();
  return;
}

void InterpreterManager::adapt_psummary_to_upper_call(UpperCall *upper_call, path_summary_ty *smmry)
{
  //smmry->update_InnerCalls_with_constraints();
  //smmry->update_InnerCalls_with_constraints2(upper_call);

  /* Take constraints from the upper call (to which this smmry fits) and 
   * and replace all occurences of formal args to actual args from the smmry */
  if(!(smmry->call_symbolic_replacements.empty()))
  {
    llvm::outs() << "InterpreterManager::adapt_psummary_to_upper_call(): adding the following constraints" 
                 << " from the upper call to inner calls accumulated conds:\n";
    /* This will recompute upper_call's shallow hash */
    std::vector<ref<Expr> > pulled_constraints = upper_call->unwrap_constraints_once(smmry);
    print_expressions(pulled_constraints);
    /* This will add pulled_constraints to each inner call */
    smmry->add_accumulated_conds_to_inner_calls(pulled_constraints); // This will also recompute shallow hashes
                                                                     // for each smmry's inner call
  }
  return;
}


/* Path chains splitting functions */


/* We have a path summary <owner> with possibly several inner calls.
 * <inner_call> is one of them.  <inner_call> might have several
 * connected summaries. We want to create copies of owner, so that each
 * copy is exactly the same as <owner> but constains only one connected
 * summary for the corresponding inner call. Note that for other inner
 * calls it will still have multiple connected summaries, this is OK
   
 psummary(owner)
      |
      |              | ---> connected summary
      |< innercall* <| ---> connected summary
      |              | ---> connected summary
      |
      |
      |             | ---> connected summary
      |< innercall <| ---> connected summary
      |             | ---> connected summary

   --- 
    * inner call to split
 
 */
std::vector<path_summary_ty *> split_psmmry_on_inner_call(path_summary_ty *owner, InnerCall *inner_call)
{

   std::vector<path_summary_ty *> res;
   /* End of recurstion: if there is nothing to split, return the original summary */
   if(inner_call->connected_summaries.size() == 0)
   {
     res.push_back(owner);
     return res;
   }

   /* For each unique chain we create a new copy of path summary */
   for(unsigned i = 0; i < inner_call->connected_summaries.size(); i++)
   {
     /* If inner_call->connected_summaries[i] does not have inner calls, the next function
      * will return a vector with just one element: inner_call->connected_summaries[i] */
     std::vector<path_summary_ty *> path_chains = split_psmmry_on_inner_calls(inner_call->connected_summaries[i]);
     for(unsigned j = 0; j < path_chains.size(); j++)
     {
       /* This will create new instances of inner calls */
       path_summary_ty *copy = new PathSummary(owner);
       copy->call_symbolic_replacements[inner_call->symbolics]->connected_summaries.clear();
       copy->call_symbolic_replacements[inner_call->symbolics]->connected_summaries.push_back(path_chains[j]);
       res.push_back(copy);
     }
   }
   return res;
}

#define SIMPLE_PATHS_MAX_NUM 100
std::vector<path_summary_ty *> split_psmmry_on_inner_calls(path_summary_ty *psmmry)
{

  std::vector<path_summary_ty *>  path_chains;
  /* End of recurstion: if there is nothing to split, return the original summary */
  if(psmmry->call_symbolic_replacements.size() == 0)
  {
    path_chains.push_back(psmmry);
    return path_chains;
  }
  

  unsigned count = 0;
  for(call_symbolic_replacements_ty::iterator it  = psmmry->call_symbolic_replacements.begin();
                                              it != psmmry->call_symbolic_replacements.end(); ++it)
  {
    /* The first inner call => we can split from psmmry */
    if(count == 0)
    {
      InnerCall *inner_call = it->second;
      /* This will create a copy for psmmary for each inner_call's connected summary */
      path_chains = split_psmmry_on_inner_call(psmmry, inner_call);
    }
    /* Otherwise we need to split the path_chains */
    else
    {
      InnerCall *inner_call = it->second;
      std::vector<path_summary_ty *>  new_path_chains;
      /* Split each summary constructed during the previous iteration */
      for(unsigned i = 0; i < path_chains.size(); i++)
      {
        std::vector<path_summary_ty *>  tmp = split_psmmry_on_inner_call(path_chains[i], inner_call);;
        new_path_chains.insert(new_path_chains.end(), tmp.begin(), tmp.end());
      }
      /* Now copy to path_chains so we reuse them during the next iteration */
      path_chains = new_path_chains;
    }
    if(path_chains.size() > SIMPLE_PATHS_MAX_NUM)
    {
      llvm::outs() << "InterpreterManager::split_psmmry_on_inner_calls():  Warning, path_chains.size() = " 
                   <<  path_chains.size() << " is too big, resizig to " << SIMPLE_PATHS_MAX_NUM << "\n";
      path_chains.resize(SIMPLE_PATHS_MAX_NUM);
    }
    count++;
  }

  return path_chains;
}


path_summary_ty *connect_summaries(std::vector<std::vector<path_summary_ty *> > path_chains, 
                     std::vector<unsigned> indices)
{
  
  path_summary_ty *next = NULL;
  /* If we got here, path_chains.size() should be at least 2 */
  assert((path_chains.size() >= 2) && "Connecting is a binary operation and you just one element");

  /* start from bottom level function (i.e. the one which calls assert()
   * in the call path */
  path_summary_ty *copy = NULL;
  for(int i = path_chains.size()-1; i >= 0; i--)
  {
    unsigned ndx = indices[i];
    path_summary_ty *original = path_chains[i][ndx];
    llvm::outs() << "connect_summaries: Considerting summary for " << original->fn->getName() 
                 << "() with index " << ndx << "\n";
    copy = new PathSummary(original);
    assert(copy && "memory error");
    copy->next_path_summaries.clear();
    if(i != (path_chains.size() - 1))
      copy->next_path_summaries.push_back(next);
    next = copy;
  }
  llvm::outs() << "connect_summaries: leaving\n"; 
  return copy;
}



void print_indices(std::vector<unsigned> indices)
{
  for(unsigned i = 0; i < indices.size(); i++)
    llvm::outs() << indices[i] << " ";
  llvm::outs() << "\n";
}

/* Path summary chains contain inner calls which can have multiple
 * connected summaries. This function splites those possible chains
 * and creates one deterministic chain per connected summary 
 
   
       time to go for vacations =) 

 
         \ _ /
       -= (_) =-
         /   \         _\/_
           |           //o\  _\/_
    _____ _ __ __ ____ _ | __/o\\ _
  =-=-_-__=_-= _=_=-=_,-'|"'""-|-,_
   =- _=-=- -_=-=_,-"          |
 jgs =- =- -=.--" 
 
 
 */
std::vector<path_summary_ty *> InterpreterManager::split_path_candidate(path_summary_ty *candidate)
{
  llvm::outs() << "InterpreterManager::split_path_candidate(): inside\n";
  std::vector<std::vector<path_summary_ty *> > path_chains;
  path_summary_ty *psmmry = candidate;
  /* Split each of the call path summaries on inner calls */
  while(psmmry)
  {
    llvm::outs() << "InterpreterManager::split_path_candidate(): splitting summary for " << psmmry->fn->getName() << "\n";
    std::vector<path_summary_ty *> tmp = split_psmmry_on_inner_calls(psmmry);
    path_chains.push_back(tmp);
    /* In the current implementation InterpreterManager 
     * we have just one next path summary */
    if(!psmmry->next_path_summaries.empty())
      psmmry = psmmry->next_path_summaries[0];
    else
      psmmry = NULL;
  }
  //while(!psmmry->next_path_summaries.empty()); 

  assert(path_chains.size() && "path_chains should be at least of size 1 (for main())");
  if(path_chains.size() == 1)
    return path_chains[0];


  /*  Now connect all possible combinations of path summaries */
  std::vector<unsigned> indices;
  for(unsigned i = 0; i < path_chains.size(); i++)
  {
    indices.push_back(path_chains[i].size() - 1); // points the the last element
    llvm::outs() << "InterpreterManager::split_path_candidate(): the number of simple paths for "
                 << path_chains[i][0]->fn->getName() << "() is  " << path_chains[i].size() << "\n";
  }
 /*  
 | call path | path summaries
    
     main():  o o o o o o o   indices[0] 
       |                  ^       |
       v                  |--------
     foo():   x x x x x       indices[1]
       |              ^       |
       v              |--------
     boo():   p p p p p p       indices[2]
                        ^         |
		        |----------

  */
  /* start from bottom level function (i.e. boo()) */
  unsigned N = indices.size()-1;
  std::vector<path_summary_ty *> simple_paths;
  bool go = true;
  while(go)
  {
    llvm::outs() << "InterpreterManager::split_path_candidate(): considering the following indices connecting:";
    print_indices(indices);
    path_summary_ty *simple_path = connect_summaries(path_chains, indices);
    assert(simple_path);
    simple_paths.push_back(simple_path);
    /* Update indices, move them to the left */
    if(indices[N] == 0)
    {
      indices[N] = path_chains[N].size() - 1;
      for(int i = N-1; i >= 0; i--)
      {
        if(indices[i] != 0)
        {
          indices[i]--;
	  break;
        } else
	{
	  if (i == 0)
	    go = false;
          indices[i] = path_chains[i].size() - 1;
	}
      }
    }
    else
      indices[N]--;
  }

  return simple_paths;
}


unsigned compute_simple_path_hash(path_summary_ty *simple_path_start)
{
  unsigned ugly_hash = simple_path_start->compute_deep_hash();
  //if(simple_path_start->next_path_summaries.size() == 0)
  //  return ugly_hash; 
  path_summary_ty *cur = simple_path_start;
  while(cur->next_path_summaries.size())
  {
    cur = cur->next_path_summaries[0];
    ugly_hash = compute_ugly_hash(ugly_hash, cur->compute_deep_hash());
  }
  return ugly_hash;
}



/* ** */
/* OMG! fix that hash function from StackOverflow !!!
 * http://stackoverflow.com/questions/2285822/c-what-is-a-good-way-to-hash-array-data */
unsigned compute_ugly_hash(unsigned prev_hash, unsigned val)
{
  unsigned hash = (prev_hash + (324723947 + val)) ^93485734985;
  return hash;
}


/* ** Function to prepare hash chains for forward executor */
#if 0

std::vector<std::vector<llvm::BasicBlock *> > unroll_path_summary(path_summary_ty *smmry)
{
  std::vector<llvm::Instruction *> stack;
  std::vector<llvm::BasicBlock *> res;
  unsigned inner_call_seq_num = 0;

  unsigned sz = smmry->path_instructions.size(); 
  llvm::BasicBlock *prev_bb = smmry->path_instructions[0]->getParent();
  llvm::BasicBlock *cur_bb  = smmry->path_instructions[0]->getParent();
  res.push_back(cur_bb);

  for(unsigned i = 0; i < sz; i++)
  {
    llvm::Instruction *cur_inst = smmry->path_instructions[i];
    cur_bb  = smmry->path_instructions[i]->getParent();
    /* New block, add it */
    if(cur_bb != prev_bb)
    {
      res.push_back(cur_bb);
      prev_bb = cur_bb;
    }

    CallInst* callInst = dyn_cast<CallInst>((llvm::Instruction *)(cur_inst));
    if(callInst)
    {
      std::vector<std::vector<llvm::BasicBlock *> > sub_res = unroll_path_summary()
    }


    cur_bb  = smmry->path_instructions[i]->getParent();
  }

}
/
/* TODO: rename to build_blockchain */
void InterpreterManager::build_path_hash_chains(path_summary_ty *smmry)
{
  std::set<uint64_t> hashes; 
  unsigned sz = smmry->path_instructions.size(); 
  llvm::BasicBlock *prev_bb = smmry->path_instructions[0]->getParent();
  llvm::BasicBlock *cur_bb  = smmry->path_instructions[0]->getParent();

  uint64_t prev_hash = ugly_hash(0,(uint64_t)cur_bb);
  hashes.insert(prev_hash);

  for(unsigned i = 0; i < sz; i++)
  {

    llvm::Instruction *cur_inst = smmry->path_instructions[i];
    cur_bb  = smmry->path_instructions[i]->getParent();

    if(cur_bb != prev_bb)
    {
      uint64_t new_hash = ugly_hash(prev_hash,(uint64_t)cur_bb);
      hashes.insert(new_hash);
      prev_hash = new_hash;
      prev_bb = cur_bb;
    }
  }
}
#endif

/* ** */



#if 0
bool InterpreterManager::check_formal_args_against_psummary(path_summary_ty &smmry,
                                   std::vector<std::vector< ref<Expr> > > &formal_args_conditions)
{
  std::vector<ref<Expr> > combined_constraints;
  std::vector<ref<Expr> > debug_constraints; // keeps conditions on formal arguments (already replaced)
  unsigned numFormals = smmry.fargs.size();
  llvm::outs() << "InterpreterManager::check_formal_args_against_fsummary(): Creating combined (formal_args_conds + path_conds) contraints\n";
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

  llvm::outs() << "InterpreterManager::check_formal_args_against_fsummary(): checking the following combined conditions:\n";
  for(std::vector<ref<Expr> >::iterator it = combined_constraints.begin(); it != combined_constraints.end(); ++it)
    llvm::outs() << *it << "\n";
  
  if(combined_constraints.size() == 0)
  {
    llvm::outs() << "InterpreterManager::check_formal_args_against_fsummary(): Conditions are empty => result = 1 (true)\n";
    return true;
  }
  ConstraintManager cm(combined_constraints);
  bool solver_result;
  //bool success = solver->solver->mayBeTrue(Query(cm, combined_constraints[0]), solver_result);
  bool success = coreSolver->mayBeTrue(Query(cm, combined_constraints[0]), solver_result);

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
    //success1 = solver->solver->evaluate(Query(smmry.path_constraints, smmry.path_constraints.back()), debug_result); 
    success1 = coreSolver->evaluate(Query(smmry.path_constraints, smmry.path_constraints.back()), debug_result); 
    if (debug_result == Solver::Unknown)
      res_str = "unknown";
    else if (debug_result == Solver::False)
      res_str = "0";
    else if (debug_result == Solver::True)
      res_str = "1";
    llvm::outs() << "InterpreterManager::check_formal_args_against_fsummary(): debug_result = " << res_str << "\n";
  }
  else
    llvm::outs() << "InterpreterManager::check_formal_args_against_fsummary(): no additional constraints on formals\n";
  // DEBUG STUFF END

  // DEBUG STUFF BEGIN
  //ref<Expr> true_expr =  ConstantExpr::create(1, Expr::Bool);
  //ConstraintManager cm1(combined_constraints);
  //bool debug_result;
  //bool success1 = solver->solver->mayBeTrue(Query(cm1, true_expr), debug_result);
  //llvm::outs() << "SummaryExecutor::check_formal_args_against_fsummary(): debug_result = " << debug_result << "\n";
  // DEBUG STUFF END

  assert(success && "FIXME: Unhandled solver failure");
  llvm::outs() << "InterpreterManager::check_formal_args_against_fsummary(): result = " << solver_result << "\n";

  if(!solver_result)
    return false;

  return true;

}
#endif
