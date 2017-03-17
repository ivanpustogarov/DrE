//===-- PathSummary.cpp ----------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

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

using namespace llvm;
using namespace klee;

/* ** UpperCall methods begin */
UpperCall::UpperCall() : fn(NULL), caller(NULL)
{
}

UpperCall::UpperCall(llvm::Function *_fn, llvm::Function *_caller) : 
              fn(_fn),caller(_caller)
{
  for(int i = 0; i<_fn->arg_size(); i++)
    actual_args_conditions.push_back(std::vector<ref<Expr> >()); // Initialize the vector for for argument <i>
}

UpperCall::UpperCall(UpperCall *upper_call) : caller(upper_call->caller), fn(upper_call->fn),
             actual_args_conditions(upper_call->actual_args_conditions),
	     connected_summaries(upper_call->connected_summaries),
       accumulated_conditions(upper_call->accumulated_conditions),
       fargs(upper_call->fargs)
{

}


/** Propagate conditions on the actual function parameters from
 *  <lower_level_upper_call> to this upper call.
 *
 * Check if actual arguments of target_function call of <smmry> coincide
 * with <smmry> function formal arguments. If yes, propagate
 * <lower_level_upper_call>'s conditions on arguments to the
 * corresponding conditions of this current upper call.
 * Note this upper call should belong to <smmr>.
 * */
//void UpperCall::add_actual_args_conds(UpperCall *lower_level_upper_call, path_summary_ty *smmry)
void UpperCall::add_actual_args_conds(UpperCall *lower_level_upper_call, path_summary_ty *smmry)
{
  assert(smmry->upper_call);
  llvm::outs() << "UpperCall::add_actual_args_conds(): Adding constranints from previous upper_call\n";

  //smmry->fargs[i] == smmry->target_func_actual_args[i]

  /* If summary's formal argument <f_i> is an actual argument for
   * the smmry's end function, then we need to pass conditions from
   * <lower_level_upper_call> on this actual arg to the smmry's
   * upper_call */
  for(unsigned i=0; i< smmry->target_func_actual_args.size() ; i++)
    for(unsigned j=0; j < smmry->fargs.size(); j++)
      if(smmry->target_func_actual_args[i] == smmry->fargs[j])
	    {
	      this->actual_args_conditions[j].insert(
	              this->actual_args_conditions[j].end(),
	              lower_level_upper_call->actual_args_conditions[i].begin(),
	              lower_level_upper_call->actual_args_conditions[i].end()
	      );
        llvm::outs() << "InterpreterManager::add_actual_args_conds(): added "
	              << "lower level upper call's actual arg conds for arg " << j << " to this upper "
	              << " call's actual arg conds for arg " << i << "\n";
	    }
}

/** Extract and save path constraints for each actual arugument 
 *
 * We extract constraint for each actual arguments of the upper
 * call from the current path constraints. We will need them later,
 * when we execute the upper call. We need to be sure that
 * those constraint are satisfied on function's formal
 * arguments.
 * This function updates <actual_args_conditions> field.
 * 
 * @param cur_path_cods Path constraints collected up to the call
 *                      instruction
 * @param actual_args Actual call instrution arguments
 * @return <void>
 */
void UpperCall::update_actual_args_conds(ConstraintManager path_constraints, std::vector< ref<Expr> > formal_args)
{
  //llvm::Function *called_func = call_inst->getParent()->getParent();
  llvm::outs() << "UpperCall::update_actual_args_conds(): Extracting constraints for"
                   " formal arguments for " << fn->getName() << "()\n";
  unsigned num_args = formal_args.size();
  //actual_args_conditions.reserve(num_args);
  static unsigned id = 0;
  for(unsigned i=0; i<num_args; i++)
  {
    llvm::outs() << "UpperCall::update_actual_args_conds(): Extracting constraints for " << formal_args[i] << "\n";
    //actual_args_conditions.push_back(std::vector<ref<Expr> >()); // Initialize the vector for for argument <i>
    /* Extract conditions from the current path constraints */
    for(std::vector< ref<Expr> >::const_iterator it_1  = path_constraints.begin(); 
                                                 it_1 != path_constraints.end(); ++it_1) //For each condition in the summary
    {
      const ref<Expr> cond = *it_1;
      std::vector<ref<Expr> > concats = extract_concat_subexpressions(cond);
      for(std::vector<ref<Expr> >::iterator it_2 = concats.begin(); it_2 != concats.end(); ++it_2) 
      { 
        ref<Expr> concat = *it_2;
        if(formal_args[i] == concat) 
        {
          actual_args_conditions[i].push_back(cond);
          break;
        }
      }
    }
  }

  for(unsigned i=0; i<num_args; i++)
  {llvm::outs() << "UpperCall::update_actual_args_conds(): Conditions for actual arg" << i << " = " << formal_args[i] << "\n";
    for(std::vector< ref<Expr> >::iterator it_1  = actual_args_conditions[i].begin(); it_1 != actual_args_conditions[i].end(); ++it_1)
      llvm::outs() << *it_1 << "\n";}
}

/* Extract constraints from the prev upper call,
 * replacing prev upper call's formal args with actual args from the
 * summary. Put those extracted conds to this upper call.
 * @param smmry Path summary that owns this upper call (i.e. this upper
 *              call is for the next function in the call path)
 * @param prev_upper_call <smmary> fits <prev_upper_call>  */
void UpperCall::pull_constraints(path_summary_ty *smmry, UpperCall *prev_upper_call)
{
  //llvm::outs() << "UpperCall::pull constraints(): Pulling constraints for"
  //                 " for " << this->fn->getName() << "() from " << prev_upper_call->fn->getName()<< "\n";
  this->accumulated_conditions.clear();
  /* First pull constraints from the summary */
  llvm::outs() << "UpperCall::pull_constraints(): Pulling constraints from smmry\n";
  for(std::vector< ref<Expr> >::const_iterator it  = smmry->path_constraints.begin(); 
                                               it != smmry->path_constraints.end(); ++it)
    this->accumulated_conditions.push_back(*it);
  
  llvm::outs() << "UpperCall::pull constraints(): Pulled the folloing constraints from smmry:\n";
  print_expressions(this->accumulated_conditions);

  /* Second pull constraints from the previuos upper call, replacing
   * it's formal args by actual args */
  if(!prev_upper_call)
  {
    this->compute_shallow_hash();
    return;
  }
  unsigned num_args = prev_upper_call->fargs.size();
  if(!num_args)
  {
    this->compute_shallow_hash();
    return;
  }
  llvm::outs() << "UpperCall::pull constraints(): Pulling constraints from prev upper call\n";
  for(std::vector< ref<Expr> >::const_iterator it  = prev_upper_call->accumulated_conditions.begin(); 
                                               it != prev_upper_call->accumulated_conditions.end(); ++it)
  {
    const ref<Expr> cond = *it;
    llvm::outs() << "\n" << cond << "\n";
    ref<Expr> tmp;
    for(unsigned i=0; i<num_args; i++)
    {
      llvm::outs() << "Replacing " << prev_upper_call->fargs[i] << " with " << smmry->target_func_actual_args[i] << "\n";
      if(i==0)
        tmp = replace_subexpr(cond, prev_upper_call->fargs[i], smmry->target_func_actual_args[i]);
      else
        tmp = replace_subexpr(tmp, prev_upper_call->fargs[i], smmry->target_func_actual_args[i]);
    }
    this->accumulated_conditions.push_back(tmp);
  }
  llvm::outs() << "UpperCall::pull constraints(): now we have the following accumulated_conditions:\n";
  print_expressions(this->accumulated_conditions);
  this->compute_shallow_hash();
  return;
}

/* ** UpperCall methods end */


/* ** InnerCall methods begin */

/* Copy everything but the <retval_conditions2>,
 * which whence will be empty vectors */
InnerCall::InnerCall(InnerCall *inner_call) :
      symbolics(inner_call->symbolics),
      seq_num(inner_call->seq_num),
      call_inst(inner_call->call_inst),
      retval_conditions(inner_call->retval_conditions),
      conditions2_set(false),
      globals_conditions(inner_call->globals_conditions),
      formal_args_conditions(inner_call->formal_args_conditions),
      path_summary_found(false),
      connected_summaries(inner_call->connected_summaries),
      actual_args(inner_call->actual_args),
      parent_inner_call(inner_call->parent_inner_call),
      fargs(inner_call->fargs),
      unwrapped_constraints(inner_call->unwrapped_constraints),
      accumulated_conditions(inner_call->accumulated_conditions)

{
}

InnerCall::InnerCall() : seq_num(0), conditions2_set(false), path_summary_found(false),
                        parent_inner_call(NULL)
{
}

InnerCall::InnerCall(ref<Expr> s, llvm::CallInst *ci, constraints_ty p_constraints) : 
                      symbolics(s), call_inst(ci),
                      seq_num(0), conditions2_set(false),
                      path_summary_found(false),
		      constraints(p_constraints),
                      parent_inner_call(NULL)
{
}



std::vector<ref<Expr> > InnerCall::extract_concat_subexpressions(ref<Expr> e)
{
  std::vector<ref<Expr> > res;

  //const ConstantExpr *ce = dyn_cast<ConstantExpr>(e);
  //if (!ce)
  if(!isa<ConstantExpr>(e))
  {
    //if (const ConcatExpr *ce = dyn_cast<ConcatExpr>(e)) 
    if(isa<ConcatExpr>(e))
    {
      //llvm::outs() << "Executor::extract_concat_subexpressions(): Found a concat expression: " << *ce << "\n";
      res.push_back(e);
    }

    Expr *ep = e.get();
    for (unsigned i=0; i<ep->getNumKids(); i++)
    {
      std::vector<ref<Expr> > sub_res;
      sub_res = extract_concat_subexpressions(ep->getKid(i));
      res.insert(res.end(), sub_res.begin(), sub_res.end());
    }
  }
  return res;
}

/* Extract and save path constraints for each actual arugument 
 *
 * We extract constraint for each actual arguments of the inner
 * call from the current path constraints. We will need them later,
 * when we execute the inner call. We need to be sure that
 * those constraint are satisfied on function's formal
 * arguments.
 * This function updates <formal_args_conditions> field.
 * 
 * @param cur_path_cods Path constraints collected up to the call
 *                      instruction
 * @param actual_args Actual call instrution arguments
 * @return <void>
 */
void InnerCall::update_formal_args_conds(ConstraintManager path_constraints, std::vector< ref<Expr> > actual_args)
{
  /*  Collect constraints for each actual argument from f1_smmry */
  //llvm::Function *called_func = call_inst->getParent()->getParent();
  llvm::Function *f_s = call_inst->getCalledFunction();
  llvm::outs() << "InnerCall::update_formal_args_conds(): Extracting constraints for"
                   " actual arguments for " << f_s->getName() << "()\n";
  unsigned num_args = actual_args.size();
  assert(formal_args_conditions.empty() && "can only invoke this function once after inner call creation");
  formal_args_conditions.reserve(num_args);
  static unsigned id = 0;
  //unsigned w = 32;
  for(unsigned i=0; i<num_args; i++)
  {
    llvm::outs() << "InnerCall::update_formal_args_conds(): Extracting constraints for " << actual_args[i] << "\n";
    formal_args_conditions.push_back(std::vector<ref<Expr> >()); // Initialize the vector for for argument <i>
    const ConstantExpr *ce = dyn_cast<ConstantExpr>(actual_args[i]);

    /* If we have a constant actual argument (e.g.
     * classfiyGesture(3)) then we need to create a new Eq condition */
    if (ce)
    {
      llvm::outs() << "InnerCall::update_formal_args_conds(): expression " << actual_args[i] << " is "
                      "a constant, creating a new Eq condition\n";

      Expr::Width w = ce->getWidth();

      const Array *array = Array::CreateArray("suppcall_formal_" + f_s->getName().str() + "_" + llvm::utostr(id) ,  Expr::getMinBytesForWidth(w) );
      id++;
      ref<Expr> e = Expr::createTempRead(array, w);
      formal_args_conditions[i].push_back(EqExpr::create(e, actual_args[i]));
    }
    else  /* Else extract conditions from the current path constraints */
      for(std::vector< ref<Expr> >::const_iterator it_1  = path_constraints.begin(); 
                                                   it_1 != path_constraints.end(); ++it_1) //For each condition in the summary
      {
        const ref<Expr> cond = *it_1;
        std::vector<ref<Expr> > concats = extract_concat_subexpressions(cond);
        for(std::vector<ref<Expr> >::iterator it_2 = concats.begin(); it_2 != concats.end(); ++it_2) 
        { 
          ref<Expr> concat = *it_2;
          if(actual_args[i] == concat) 
          {
            formal_args_conditions[i].push_back(cond);
            break;
          }
        }
      }
  }

  for(unsigned i=0; i<num_args; i++)
  {llvm::outs() << "InnerCall::update_formal_args_conds(): Conditions for actual arg" << i << " = " << actual_args[i] << "\n";
    for(std::vector< ref<Expr> >::iterator it_1  = formal_args_conditions[i].begin(); it_1 != formal_args_conditions[i].end(); ++it_1)
      llvm::outs() << *it_1 << "\n";}
}


bool InnerCall::contains_array(ref<Expr> _concat, const Array *a)
{
  ConcatExpr *concat = dyn_cast<ConcatExpr>(_concat);

  assert(concat && "can only compare ReadLSB expressions");
  
  // Getting read expressions
  ref<Expr> _r1 = concat->getLeft();
  ReadExpr  *r1 = dyn_cast<ReadExpr>(_r1);
  //ref<Expr> _r2 = concat->getRight();
  //ReadExpr  *r2 = dyn_cast<ReadExpr>(_r2);

  const Array *concat_array = r1->updates.root;
  
  //llvm::outs() << "classcomp:: al: @" << al << "\n";
  //llvm::outs() << "classcomp:: ar: @" << ar << "\n";

  if (concat_array == a)
  {
    //llvm::outs() << "InnerCall::contains_array(): returning true\n";
    return true;
  }
  else 
  {
    //llvm::outs() << "InnerCall::contains_array(): returning false\n";
    return false;
  }
}


/* Extract and save path constraints on global variables
 *
 * We extract constraint for each global variable 
 * call from the current ptah constraints. We will need them later,
 * when we execute the supplementar call. We need to be sure that
 * those constraint are satisfies during the suppl func call.
 * This function updates <globals_conditions> field.
 * 
 * @param cur_path_cods Path constraints collected up to the call
 *                      instruction
 * @return <void>
 */
void InnerCall::update_constraints_on_globals(global_symbolic_replacements_ty &glb_symb_rplcmnts,
                                   ConstraintManager &path_constraints)
{
  //llvm::outs() << "InnerCall::update_constraints_on_globals(): Inside\n";
  //llvm::outs() << "InnerCall::update_constraints_on_globals(): number of global "
  //                 "symbolic replacements = " <<  glb_symb_rplcmnts.size()  << "\n";
  for(global_symbolic_replacements_ty::iterator it_1 =  glb_symb_rplcmnts.begin();
                                                it_1 != glb_symb_rplcmnts.end(); ++it_1)
  {
    //llvm::Value *global_value = it_1->first;
    const Array *array  = it_1->second[it_1->second.size()-1];
    //llvm::outs() << "InnerCall::update_constraints_on_globals(): Considering global  " << 
    //                 global_value->getName() << "\n";

    for(std::vector< ref<Expr> >::const_iterator it_2  = path_constraints.begin();
                                                 it_2 != path_constraints.end(); ++it_2)
    {
      const ref<Expr> e = *it_2;
      std::vector<ref<Expr> > concats = extract_concat_subexpressions(e);

        for(std::vector<ref<Expr> >::iterator it_3 = concats.begin(); it_3 != concats.end(); ++it_3)
        {
          ref<Expr> concat = *it_3;
          if(contains_array(concat, array))
          {
            //llvm::outs() << "InnerCall::update_constraints_on_globals(): Match\n";
          } else
          {
            //llvm::outs() << "InnerCall::update_constraints_on_globals(): NoMatch\n";
          }
        }

    }
  }
}


PathSummary::PathSummary(llvm::Function *f, ref<Expr> ret, constraints_ty p_constraints,
  llvm::Function * target_fn, std::vector<ref<Expr> > tfn_args):
fn(f),
return_value(ret),
path_constraints(p_constraints),
target_func(target_fn),
target_func_actual_args(tfn_args),
is_return_summary(false),
upper_call(NULL),
end_function(NULL),
type(PathSummary::RET_SUMMARY_TYPE),
_deep_hash(0)
{
  compute_shallow_hash();
}

PathSummary::PathSummary(llvm::Function *f, ref<Expr> ret, constraints_ty p_constraints):
  fn(f),
  return_value(ret),
  path_constraints(p_constraints),
  target_func(NULL),
  is_return_summary(true),
  upper_call(NULL),
  end_function(NULL),
  type(PathSummary::RET_SUMMARY_TYPE),
  _deep_hash(0)
{
  compute_shallow_hash();
}

/* copies everything but call_symbolic_replacements_ty,
 * We create a new call_symolics without connected summaries instead */
PathSummary::PathSummary(path_summary_ty *smmry):
  path_instructions(smmry->path_instructions),
  path_choices_debug(smmry->path_choices_debug),
  path_choices(smmry->path_choices),
  fn(smmry->fn), 
  is_return_summary(smmry->is_return_summary),
  return_value(smmry->return_value),
  global_values(smmry->global_values),
  path_constraints(smmry->path_constraints),
  path_constraints_globals_only(smmry->path_constraints_globals_only),
  target_func(smmry->target_func),
  target_func_actual_args(smmry->target_func_actual_args),
  fargs(smmry->fargs),
  next_path_summaries(smmry->next_path_summaries),
  upper_call(smmry->upper_call),
  end_function(smmry->end_function),
  type(smmry->type),
  _shallow_hash(smmry->_shallow_hash),
  _deep_hash(0)
  //next_path_summary(NULL)
{
  /* Copy each symbolic replacement with constructor which copies connected summaries too */
  for(call_symbolic_replacements_ty::iterator it  = smmry->call_symbolic_replacements.begin();
                                              it != smmry->call_symbolic_replacements.end(); ++it)
  {
    InnerCall *inner_call = it->second;
    InnerCall *new_inner_call = new InnerCall(inner_call);
    this->call_symbolic_replacements[new_inner_call->symbolics] = new_inner_call;
  }
  //next_path_summaries.clear();
}

void PathSummary::set_parent_for_inner_calls(InnerCall *_parent_inner_call)
{
  for(call_symbolic_replacements_ty::iterator it  = call_symbolic_replacements.begin();
                                              it != call_symbolic_replacements.end(); ++it)
  {
    InnerCall *inner_call = it->second;
    inner_call->parent_inner_call = _parent_inner_call;
  }
  return;
}

void PathSummary::clear_connected_summaries_for_inner_calls()
{
  for(call_symbolic_replacements_ty::iterator it  = call_symbolic_replacements.begin();
                                              it != call_symbolic_replacements.end(); ++it)
  {
    InnerCall *inner_call = it->second;
    inner_call->connected_summaries.clear();
  }
  return;
}

/* Return true path_isntruction of both path summaries contatins the same
 * instructions */
bool PathSummary::has_the_same_path_instructions(path_summary_ty *smmry)
{
  unsigned num_insts = this->path_instructions.size();
  if(smmry->path_instructions.size() != num_insts)
    return false;
  for(unsigned i = 0; i<num_insts; i++)
    if(this->path_instructions[i] != smmry->path_instructions[i])
      return false;
  return true;
}

std::vector<ref<Expr> > PathSummary::extract_concat_subexpressions(ref<Expr> e)
{
  std::vector<ref<Expr> > res;

  //const ConstantExpr *ce = dyn_cast<ConstantExpr>(e);
  //if (!ce)
  if(!isa<ConstantExpr>(e))
  {
    //if (const ConcatExpr *ce = dyn_cast<ConcatExpr>(e)) 
    if(isa<ConcatExpr>(e))
    {
      //llvm::outs() << "Executor::extract_concat_subexpressions(): Found a concat expression: " << *ce << "\n";
      res.push_back(e);
    }

    Expr *ep = e.get();
    for (unsigned i=0; i<ep->getNumKids(); i++)
    {
      std::vector<ref<Expr> > sub_res;
      sub_res = extract_concat_subexpressions(ep->getKid(i));
      res.insert(res.end(), sub_res.begin(), sub_res.end());
    }
  }
  return res;
}


/* <path_constraints> contain constraints on both formal func args.
 * but for state selection, we need only constraints on globals*/
void PathSummary::extract_constraints_on_globals()
{
  //path_constraints_globals_only.clear();
  //llvm::outs() << "PathSummary::extract_constraints_on_globals(): extracting (by eliminating)...\n";
  for(std::vector< ref<Expr> >::const_iterator it_1  = path_constraints.begin();
                                             it_1 != path_constraints.end(); ++it_1)
  {
    const ref<Expr> e = *it_1;
    std::vector<ref<Expr> > concats =  extract_concat_subexpressions(e);
    bool should_add = true;

    /* Elimnating constraints on formal arguments */
    for(std::vector<ref<Expr> >::iterator it_2  = fargs.begin(); it_2 != fargs.end(); ++it_2)
    {
      ref<Expr> arg = *it_2;
      for(std::vector<ref<Expr> >::iterator it_3 = concats.begin(); it_3 != concats.end(); ++it_3)
      {
        ref<Expr> concat = *it_3;
        //llvm::outs() << "PathSummary::extract_constraints_on_globals(): Comparing " << arg << " and "
        //             << concat << "\n";
        if(arg == concat)
        {
          //llvm::outs() << "Match\n";
          should_add = false;
          break;
        } else
        {
          //llvm::outs() << "NoMatch\n";
        }
      }
      if(!should_add)
        break;
    }


    /* Eliminating constraints on call symbolics */
    for(call_symbolic_replacements_ty::iterator it_1  = call_symbolic_replacements.begin(); 
                                                it_1 != call_symbolic_replacements.end(); ++it_1)
    {
      for(std::vector<ref<Expr> >::iterator it_3 = concats.begin(); it_3 != concats.end(); ++it_3)
      {
        ref<Expr> concat = *it_3;
        //llvm::outs() << "PathSummary::extract_constraints_on_globals(): Comparing " << it_1->first << " and "
        //             << concat << "\n";
        if(it_1->first == concat)
        {
          //llvm::outs() << "Match\n";
          should_add = false;
          break;
        } else
        {
          //llvm::outs() << "NoMatch\n";
        }
      }
      if(!should_add)
        break;
    }



    if(should_add)
      path_constraints_globals_only.addConstraint(e);
  }

  llvm::outs() << "PathSummary::extract_constraints_on_globals(): we got the following conds"
                  " on globals for function " << fn->getName() << "():\n";
  for(std::vector< ref<Expr> >::const_iterator it_2  = path_constraints_globals_only.begin();
                                                 it_2 != path_constraints_globals_only.end(); ++it_2)
    llvm::outs() << *it_2 << "\n";
    llvm::outs() << "PathSummary::extract_constraints_on_globals(): - \n";
}

/* Clear retval_conditions and retval_conditions2 */
void PathSummary::clear_InnerCalls_constraints()
{
  for(call_symbolic_replacements_ty::iterator it_1  = call_symbolic_replacements.begin(); 
                                              it_1 != call_symbolic_replacements.end(); ++it_1)
  {
    it_1->second->retval_conditions.clear();  
    it_1->second->retval_conditions2.clear(); 
    it_1->second->conditions2_set = false;
  }
}

/* For each call instruction that was replaced by a symbolics, return the
 * the corresponding call instruction and conditions collected on those
 * symbolics along the path summary
 * Note: we don't clear retval_conditions in this function, as it might
 * have constraints which come outside of current path summary (see
 * function InterpreterManager::adapt_psummary_to_inner_call(), and parent_inner_call) */
void PathSummary::update_InnerCalls_with_constraints()
{
  llvm::outs() << "PathSummary::update_InnerCalls_with_constraints(): inside; for function " << fn->getName() << "().\n";
  for(call_symbolic_replacements_ty::iterator it_1  = call_symbolic_replacements.begin(); 
                                              it_1 != call_symbolic_replacements.end(); ++it_1)
  {
    //ref<Expr> symb_replc = it_1->first;       // symbolics
    //InnerCall inner_call = it_1->second; 

    /* Collect conditions along the path summary. */
    for(std::vector< ref<Expr> >::const_iterator it_2  = path_constraints.begin();
                                                 it_2 != path_constraints.end(); ++it_2)
    {
      const ref<Expr> e = *it_2;
      std::vector<ref<Expr> > concats =  extract_concat_subexpressions(e);
      for(std::vector<ref<Expr> >::iterator it_3 = concats.begin(); it_3 != concats.end(); ++it_3)
      {
        ref<Expr> concat = *it_3;
        if(it_1->first == concat)
        {
          //inner_call.retval_conditions.push_back(e);
          it_1->second->retval_conditions.push_back(e);
          break;
        }
      }
    }
    //llvm::outs() << "PathSummary::update_InnerCalls_with_constraints(): inner_call.retval_conditions.size() = " <<
    //                 inner_call.retval_conditions.size() << "; it_1->second.retval_conditions.size() = " << 
    //                 it_1->second.retval_conditions.size() << "\n";
    //llvm::outs() << "PathSummary::update_InnerCalls_with_constraints(): constraints for " << it_1->first <<
    //                 " it_1->second.retval_conditions.size() = " << 
    //                 it_1->second->retval_conditions.size() << "\n";
  }
}

void PathSummary::update_InnerCalls_with_constraints2(UpperCall *upper_call)
{
  assert((upper_call->caller == this->fn));
  assert((upper_call->fn == this->end_function));
  for(call_symbolic_replacements_ty::iterator it_1  = call_symbolic_replacements.begin(); it_1 != call_symbolic_replacements.end(); ++it_1)
  {
    //it_1->second->retval_conditions2.clear(); // Clear conditins from previous summaries
    std::vector<int> used_arg_indices;
    /* Second check if the call symbolic replacement was used as f2's actual parameter */
    std::vector<ref<Expr> > f2_actual_args = target_func_actual_args;
    for(unsigned i = 0; i < f2_actual_args.size(); i++)
    {
      if(it_1->first == f2_actual_args[i])
      {
        llvm::outs() << "PathSummary::update_InnerCalls_with_constraints2(): call symbolics " << it_1->first << " is used "
                        " as a the actual function argument for function " << upper_call->fn->getName() << "() at"
                        " position " << i << "\n";

        used_arg_indices.push_back(i);
      }
    }
    /* now we need to collect constraints from <next_func_psmmry> */
    llvm::outs() << "PathSummary::update_InnerCalls_with_constraints2(): Extracting conditions for those arguments\n";
    for(std::vector<int>::iterator it_2 = used_arg_indices.begin(); it_2 != used_arg_indices.end(); ++it_2)
    {
      int arg_idx = *it_2;
      it_1->second->retval_conditions2.insert(it_1->second->retval_conditions2.end(),
                         upper_call->actual_args_conditions[arg_idx].begin(),
                         upper_call->actual_args_conditions[arg_idx].end()
	         );
    }

  }
}

/* next_func_psmmry is the path summary of the next function on
 * the call path, with which the current summary can be glued
 * Note that this will clear constraints from previoud calls of this
 * function */
void PathSummary::update_InnerCalls_with_constraints2(PathSummary &next_func_psmmry)
{
  for(call_symbolic_replacements_ty::iterator it_1  = call_symbolic_replacements.begin(); it_1 != call_symbolic_replacements.end(); ++it_1)
  {
    //ref<Expr> symb_replc = it_1->first;
    //InnerCall inner_call = it_1->second; 
    it_1->second->retval_conditions2.clear(); // Clear conditins from previous summaries
    std::vector<int> used_arg_indices;
    /* Second check if the call symbolic replacement was used as f2's actual parameter */
    //std::vector<ref<Expr> > f2_actual_args = f1_smmry.target_func_actual_args;
    std::vector<ref<Expr> > f2_actual_args = target_func_actual_args;
    for(unsigned i = 0; i < f2_actual_args.size(); i++)
    {
      if(it_1->first == f2_actual_args[i])
      {
        llvm::outs() << "PathSummary::update_InnerCalls_with_constraints2(): call symbolics " << it_1->first << " is used "
                        " as a the actual function argument for function " << next_func_psmmry.fn->getName() << "() at"
                        " position " << i << "\n";

        used_arg_indices.push_back(i);
      }
    }
    /* now we need to collect constraints from <next_func_psmmry> */
    llvm::outs() << "PathSummary::update_InnerCalls_with_constraints2(): Extracting conditions for those arguments\n";
    for(std::vector<int>::iterator it_2 = used_arg_indices.begin(); it_2 != used_arg_indices.end(); ++it_2)
    {
      ref<Expr> next_func_formal_arg = next_func_psmmry.fargs[*it_2];
      /* Collect conditions along the path summary. */
      for(std::vector< ref<Expr> >::const_iterator it_3  = next_func_psmmry.path_constraints.begin();
                                                   it_3 != next_func_psmmry.path_constraints.end(); ++it_3)
      {
        const ref<Expr> e = *it_3;
        std::vector<ref<Expr> > concats =  extract_concat_subexpressions(e);
        for(std::vector<ref<Expr> >::iterator it_4 = concats.begin(); it_4 != concats.end(); ++it_4)
        {
          ref<Expr> concat = *it_4;
          if(next_func_formal_arg == concat)
          {
            llvm::outs() << "PathSummary::update_InnerCalls_with_constraints2(): found a condition: " << e << "\n";
            it_1->second->retval_conditions2.push_back(e);
            it_1->second->conditions2_set = true;
            break;
          }
        }
      }
    }
  }
}

void PathSummary::print()
{
  path_summary_ty *smmry = this;
  //if(!smmry)
  //{
  //  llvm::outs() << "  NULL\n";
  //  return;
  //}

  ref<Expr> fn_result = smmry->return_value;
  ConstraintManager fn_constraints = smmry->path_constraints;

  std::string Str;
  llvm::raw_string_ostream info(Str);
  ExprPPrinter::printConstraints(info, fn_constraints);
  llvm::outs() << "Res: " << fn_result  << "; constraints:\n" << info.str() << "\n";
  return;
}

/* Loop over symbolic values which we used to replace call instructions, end
 * return those which
 *  appear in <complex_expr> */
std::vector<ref<Expr> > PathSummary::get_call_symbolics(ref<Expr> complex_expr)
{
  std::vector<ref<Expr> > res;
  for(call_symbolic_replacements_ty::iterator it_1  = this->call_symbolic_replacements.begin();
                                              it_1 != this->call_symbolic_replacements.end(); ++it_1)
  {
    ref<Expr> symbolics = it_1->first;
    std::vector<ref<Expr> > concats = extract_concat_subexpressions(complex_expr);
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

/* Check if all inner calls have connected summaries */
bool PathSummary::is_inner_calls_connected()
{
  /* Go through all call symbolic replacements */
  for(call_symbolic_replacements_ty::iterator it_1  = this->call_symbolic_replacements.begin();
                                              it_1 != this->call_symbolic_replacements.end(); ++it_1)
  {
    InnerCall *inner_call = it_1->second;
    if(inner_call->connected_summaries.size() == 0)
      return false;
  }
  return true;
}


//std::vector<ref<Expr> > unwrap_helper(std::vector<ref<Expr> > conds, InnerCall *current, InnerCall *parent)
std::vector<ref<Expr> > unwrap_helper(std::vector<ref<Expr> > conds,
                      std::vector<ref<Expr> > fargs, InnerCall *parent)
{
  unsigned num_args = parent->actual_args.size();
  llvm::outs() << "Inside PathSummary::unwrap_helper, num_args = " << num_args << "\n";
  llvm::outs() << "                                   inner_call = " 
               << parent->call_inst->getCalledFunction()->getName() 
	       << "\n                                    fargs.size() = " 
	       << fargs.size() << "\n";
  if(!num_args)
    return conds;
  std::vector<ref<Expr> > levelup;
  for(std::vector< ref<Expr> >::const_iterator it  = conds.begin(); 
                                               it != conds.end(); ++it)
  {
    const ref<Expr> cond = *it;
    llvm::outs() << "\n" << cond << "\n";
    ref<Expr> tmp;
    for(unsigned i=0; i<num_args; i++)
    {
      llvm::outs() << "Replacing " << fargs[i] << " with " 
                   << parent->actual_args[i] << "\n";
      if(i==0)
        tmp = replace_subexpr(cond, fargs[i], parent->actual_args[i]);
      else
        tmp = replace_subexpr(tmp, fargs[i], parent->actual_args[i]);
    }
    levelup.push_back(tmp);
    llvm::outs() << tmp << "\n";
  }

  if(!(parent->parent_inner_call))
    return levelup;
  else
    return unwrap_helper(levelup, parent->fargs, parent->parent_inner_call);
}

/* Replace formal args occurances in this inner call constraints with
 * the actual args from the parent inner calls all the way up to call
 * path funtion (where inner call chain started.  Put the result into
 * unwrapped_constraints.  Also construct accumulated conditions by
 * combining new unwrapped constraints with accumulated conds from the
 * parent inner call (if it is not NULL).
 * This inner call belongs to smmry */
void InnerCall::unwrap_constraints(path_summary_ty *smmry)
{
  unsigned num_args = this->fargs.size();
  std::vector<ref<Expr> > conds;
  //for(std::vector< ref<Expr> >::const_iterator it  = this->constraints.begin(); 
  //                                             it != this->constraints.end(); ++it)
  for(std::vector< ref<Expr> >::const_iterator it  = smmry->path_constraints.begin(); 
                                               it != smmry->path_constraints.end(); ++it)
  {
    const ref<Expr> cond = *it;
    conds.push_back(cond);
  }
  if(!(this->parent_inner_call) || !num_args)
  {
    this->unwrapped_constraints = conds;
  } else
    this->unwrapped_constraints = unwrap_helper(conds, this->fargs, this->parent_inner_call);
  /* we might have added accumulated
  constraints, see function add_accumulated_conds. do don't clear
  anyhting here */
  //accumulated_conditions.clear();
  this->accumulated_conditions.insert(accumulated_conditions.end(),
                                this->unwrapped_constraints.begin(), this->unwrapped_constraints.end());

  

  /* Replace parent inner call symbolics with the actual ret value in the accumulated conditions */
  InnerCall *parent = this->parent_inner_call;;
  if(parent)
  {
    llvm::outs() << "InnerCall::unwrap_constraints(): replacing call symbolics with actual retval\n";
    ref<Expr> retval_unwrapped = smmry->unwrap_retvalue(parent);
    llvm::outs() << "InnerCall::unwrap_constraints():: Unwrapped retvalue:\n";
    llvm::outs() << retval_unwrapped << "\n";
    for(std::vector< ref<Expr> >::const_iterator it_1  = parent->accumulated_conditions.begin(); 
                                                 it_1 != parent->accumulated_conditions.end(); ++it_1)
    {
      const ref<Expr> cond = *it_1;
      llvm::outs() << "\n--\n" << cond << "\n";
      ref<Expr> tmp;
      llvm::outs() << "Replacing " << parent->symbolics << " with " << retval_unwrapped<< "\n";
      tmp = replace_subexpr(cond, parent->symbolics, retval_unwrapped);
      this->accumulated_conditions.push_back(tmp);
      llvm::outs() << tmp << "\n--\n";
    }

    //accumulated_conditions.insert(accumulated_conditions.end(),
    //         this->parent_inner_call->accumulated_conditions.begin(), 
    //         this->parent_inner_call->accumulated_conditions.end());
  }

  this->compute_shallow_hash();

}

/* This path summary fits <inner_call>. Replace all formal args
 * occurances in this summary's constraints to actual args from the
 * inner calls all the way to the call path function where the inner
 * call chain started. Return the resuling constraints.
 * NOTE: This function does not update any fieled of the path summary */
std::vector<ref<Expr> > PathSummary::unwrap_constraints(InnerCall *inner_call)
{
  unsigned num_args = this->fargs.size();
  llvm::outs() << "Inside PathSummary::unwrap_constraints, num_args = " << num_args << "\n";
  std::vector<ref<Expr> > conds;
  for(std::vector< ref<Expr> >::const_iterator it  = this->path_constraints.begin(); 
                                               it != this->path_constraints.end(); ++it)
  {
    const ref<Expr> cond = *it;
    conds.push_back(cond);
  }
  if(!num_args)
  {
    return conds;
  } else
    return unwrap_helper(conds, this->fargs, inner_call);

}

/* This path summary fits <inner_call>. Replace all formal args
 * occurances in this summary's return value to actual args from the
 * inner calls all the way to the call path function where the inner
 * call chain started. Return the resuling vale.
 * NOTE: This function does not update any filed of the path summary */
ref<Expr> PathSummary::unwrap_retvalue(InnerCall *inner_call)
{
  unsigned num_args = this->fargs.size();
  llvm::outs() << "Inside PathSummary::unwrap_retvalue, num_args = " << num_args << "\n";
  std::vector<ref<Expr> > conds;
  std::vector<ref<Expr> > unwrapped;
  conds.push_back(this->return_value);
  if(!num_args)
  {
    return this->return_value;
  } else
     unwrapped = unwrap_helper(conds, this->fargs, inner_call);
  assert(unwrapped.size());
  return unwrapped[0];

}

/* <smmry> is the upper level summary (i.e. the one which fits this
 * upper call (i.e. smmry->fn should be the same as upper_call->caller */
std::vector<ref<Expr> > UpperCall::unwrap_constraints_once(path_summary_ty *smmry)
{
  assert(smmry->fn == this->caller);
  unsigned num_args = this->fn->arg_size(); 
  llvm::outs() << "UpperCall::unwrap_constraints_once(): num_args = " << num_args << "\n";
  std::vector<ref<Expr> > res;
  if(!num_args)
    return res;
  llvm::outs() << "UpperCall::unwrap_constraints_once(): Conditions from upper call:\n";
  for(std::vector< ref<Expr> >::const_iterator it_1  = this->accumulated_conditions.begin(); 
                                               it_1 != this->accumulated_conditions.end(); ++it_1)
  {
    const ref<Expr> cond = *it_1;
    llvm::outs() << "\n" << cond << "\n";
    ref<Expr> tmp;
    for(unsigned i=0; i<num_args; i++)
    {
      llvm::outs() << "Replacing " << this->fargs[i] << " with " << smmry->target_func_actual_args[i] << "\n";
      if(i==0)
        tmp = replace_subexpr(cond, this->fargs[i], smmry->target_func_actual_args[i]);
      else
        tmp = replace_subexpr(tmp, this->fargs[i], smmry->target_func_actual_args[i]);
    }
    res.push_back(tmp);
    llvm::outs() << tmp << "\n";
  }
  this->compute_shallow_hash();
  return res;
}

void PathSummary::add_accumulated_conds_to_inner_calls(std::vector<ref<Expr> > add)
{
  /* Go through all call symbolic replacements */
  for(call_symbolic_replacements_ty::iterator it_1  = this->call_symbolic_replacements.begin();
                                              it_1 != this->call_symbolic_replacements.end(); ++it_1)
  {
    InnerCall *inner_call = it_1->second;
    inner_call->accumulated_conditions.insert(inner_call->accumulated_conditions.end(),
                      add.begin(), add.end()); 
    this->compute_shallow_hash();
  }
  return;
}

InnerCall* PathSummary::get_InnerCall_by_seqnum(unsigned seqnum)
{
  InnerCall *res = NULL;
  for(call_symbolic_replacements_ty::iterator it  = this->call_symbolic_replacements.begin();
                                              it != this->call_symbolic_replacements.end();
                                              ++it)
  {
    InnerCall *inner_call = it->second;
    llvm::outs() << "PathSummary::get_InnerCall_by_seqnum(): Considering suppl call" << *(inner_call->call_inst) <<
                      " with seq num =  " << inner_call->seq_num << "\n";
    if(seqnum == inner_call->seq_num)
      return inner_call;
  }
  return NULL;
}

/* Print inner calls and next path summary */
#define INDENT_XX "  "
void print_indent(int n)
{
  for(unsigned i = 0; i < n; i++)
    llvm::outs() << INDENT_XX;
}
void PathSummary::print_structure(unsigned l)
{
  
  print_indent(l);
  llvm::outs() << "smmry " << this->fn->getName() << "\n";
  for(call_symbolic_replacements_ty::iterator it  = this->call_symbolic_replacements.begin();
                                              it != this->call_symbolic_replacements.end();
                                              ++it)
  {
    InnerCall *inner_call = it->second;
    print_indent(l);
    llvm::outs() << "Inner call for " << inner_call->call_inst->getCalledFunction()->getName()
                 << " (" << inner_call->connected_summaries.size() << " connected summaries)\n";
    for(unsigned i = 0; i < inner_call->connected_summaries.size(); i++)
      inner_call->connected_summaries[i]->print_structure(l+1);

  }
  if(!this->next_path_summaries.empty())
    this->next_path_summaries[0]->print_structure(l);

  return;
}

///* OMG FIXME! fix that hash function from StackOverflow !!!
// * http://stackoverflow.com/questions/2285822/c-what-is-a-good-way-to-hash-array-data 
// * There is also a copy of this function in InterpreterManager!!! */
//unsigned ______compute_ugly_hash(unsigned prev_hash, unsigned val)
//{
//  unsigned hash = (prev_hash + (324723947 + val)) ^93485734985;
//  return hash;
//}


unsigned compute_ugly_hash(unsigned prev_hash, unsigned val);
/* Compute hash for simple path (simple means that each inner call
 * should have at most one connected summary ) Go through each inner
 * call and next path summary and a compute hash of path constraitns */
unsigned PathSummary::compute_deep_hash()
{
  unsigned ugly_hash = (uint64_t)(this->fn);
  ugly_hash += this->type;
  /* Hash of constraints */
  for(std::vector< ref<Expr> >::const_iterator it  = this->path_constraints.begin(); 
                                               it != this->path_constraints.end(); ++it)
  {
    const ref<Expr> cond = *it;
    ugly_hash = compute_ugly_hash(ugly_hash, cond->hash());
  }

  /* Hash of all inner calls */
  for(call_symbolic_replacements_ty::iterator it  = this->call_symbolic_replacements.begin();
                                              it != this->call_symbolic_replacements.end();
                                              ++it)
  {
    assert(it->second->connected_summaries.size() <= 1);
    if(it->second->connected_summaries.size() != 0)
    {
      path_summary_ty *connected_summary = it->second->connected_summaries[0];
      ugly_hash = compute_ugly_hash(ugly_hash, connected_summary->compute_deep_hash());
    }
  }
 
  this->_deep_hash = ugly_hash;
  return ugly_hash;
}



unsigned PathSummary::compute_shallow_hash()
{
  unsigned ugly_hash = (uint64_t)(this->fn);
  ugly_hash += this->type;
  /* Hash of constraints */
  for(std::vector< ref<Expr> >::const_iterator it  = this->path_constraints.begin(); 
                                               it != this->path_constraints.end(); ++it)
  {
    const ref<Expr> cond = *it;
    ugly_hash = compute_ugly_hash(ugly_hash, cond->hash());
  }
 
  this->_shallow_hash = ugly_hash;
  return ugly_hash;
}


unsigned InnerCall::compute_shallow_hash()
{
  /* Init hash with parent func and seq number */
  unsigned ugly_hash = (uint64_t)(this->call_inst->getParent()->getParent());
  ugly_hash = compute_ugly_hash(ugly_hash, this->seq_num);
  /* Hash of constraints */
  for(std::vector< ref<Expr> >::const_iterator it  = this->accumulated_conditions.begin(); 
                                               it != this->accumulated_conditions.end(); ++it)
  {
    const ref<Expr> cond = *it;
    ugly_hash = compute_ugly_hash(ugly_hash, cond->hash());
  }
 
  this->_shallow_hash = ugly_hash;
  return ugly_hash;
}

unsigned UpperCall::compute_shallow_hash()
{
  unsigned ugly_hash = (uint64_t)(this->fn);
  /* Hash of constraints */
  for(std::vector< ref<Expr> >::const_iterator it  = this->accumulated_conditions.begin(); 
                                               it != this->accumulated_conditions.end(); ++it)
  {
    const ref<Expr> cond = *it;
    ugly_hash = compute_ugly_hash(ugly_hash, cond->hash());
  }
 
  this->_shallow_hash = ugly_hash;
  return ugly_hash;
}
