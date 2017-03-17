//===-- PathSummary.h ----------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef KLEE_NESTEDCALL_H
#define KLEE_NESTEDCALL_H

#include "klee/Constraints.h"
#include "klee/Expr.h"
#include "klee/Internal/ADT/TreeStream.h"
#include "klee/util/ExprPPrinter.h"
#include "klee/util/ExprUtil.h"

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

class PathSummary;
typedef PathSummary path_summary_ty;
typedef std::map<llvm::Value *, std::vector<const Array *> > global_symbolic_replacements_ty;
typedef ConstraintManager constraints_ty;

/* This class represents an inner call inside a function for which we are
 * building a partial function summary */
class InnerCall {

  private:
    unsigned _shallow_hash = 0;

  public:
    ref<Expr> symbolics; // Symbolic value which replaced the result of the call
    /* This is the sequence number of the call in the function to which
       this SupllCall corresponds */
    unsigned seq_num;

    /* Upper level inner call (the which called us) */
    InnerCall *parent_inner_call;

    /* Constraints necessary to reach this inner call from withing
     * the function summary to which this call belongs */
    constraints_ty  constraints;
    std::vector<ref<Expr> > unwrapped_constraints;

    /* Constraints necessary to reach this inner call from the
     * call path function down to this inner call 
     * This is a union of unwprapped_constraints and accumulated_conditions
     * of the parent_inner_call */
    std::vector<ref<Expr> > accumulated_conditions;

    llvm::CallInst *call_inst;
    /* This holds constraints on the return value posed by
       the path summary to which this InnerCall belongs */
    std::vector< ref<Expr> > retval_conditions;
    /* This holds constraints on the return value posed by
       the path summary of the next on-path function; we set this 
       field dynamically. Everytime we set these conditions, we clear
       the previous ones.*/
    bool conditions2_set;
    std::vector< ref<Expr> > retval_conditions2;
    /* This fields holds condtions on globals variables posed
       by the path summary to which this InnerCall belongs.*/
    std::vector< ref<Expr> > globals_conditions;
    
    /* The inner call was called with these arguments */
    std::vector<ref<Expr> > actual_args; 
    /* Inner call belongs to a function with the following formal args 
     * This filed can also be obtained from <call_inst> */
    std::vector<ref<Expr> > fargs; 
    /* This field holds condtions on formal arguments posed
       by the path summary to which this InnerCall belongs.*/
    std::vector<std::vector< ref<Expr> > > formal_args_conditions;
    /* Set this filed to true if we find a path summary for this
     * function which satisfies all conditions */
    bool path_summary_found;
    /* Path summaries for the inner call function */
    std::vector<PathSummary *> connected_summaries;

    InnerCall();
    InnerCall(ref<Expr> s, llvm::CallInst *ci, constraints_ty p_constraints);
    /* Copy everything but the <retval_conditions2>,
     * which whence will be empty vectors */
    InnerCall(InnerCall *inner_call);
    std::vector<ref<Expr> > extract_concat_subexpressions(ref<Expr> e);
    /* Extract and save path constraints for each actual arugument */
    void update_formal_args_conds(ConstraintManager path_constraints, std::vector< ref<Expr> > actual_args);
    bool contains_array(ref<Expr> _concat, const Array *a);
    /* Extract and save path constraints on global variables */
    void update_constraints_on_globals(global_symbolic_replacements_ty &glb_symb_rplcmnts,
                                       ConstraintManager &path_constraints);
    /* Take <constraints> and replace all formal args with actual args all the way towards
     * the mega parent call path function */
    void unwrap_constraints(path_summary_ty *smmry);

    unsigned compute_shallow_hash();
    unsigned shallow_hash() {assert(_shallow_hash); return _shallow_hash;};

};

/* An instance of this class is part of a path summary of a call-graph function.
 * It represents an "socket" to function one level above in the call graph.
 * We need this "backward" interface because we start building function from the bottom-most
 * function in the call graph */
class UpperCall {
  private:
    unsigned _shallow_hash = 0;

  public:
    /* Path summary this upper calls belongs to */
    PathSummary *owner_smmry;
    /* Function this upper calls belongs (<fn> should be the same as <owner_smmry->fn>) */
    llvm::Function *fn;
    /* The upper level function */
    llvm::Function *caller;
    /* This are formal args of the summary to which this upper call belongs (i.e.
       it should be the same as <owner_smmry->fargs>*/
    std::vector<ref<Expr> > fargs;

    /* Conditions from the bottom function in the call path up to this 
     * upper call (with formal args repaced by actual args along the way) */
    std::vector<ref<Expr> > accumulated_conditions;
    /* This fields holds condtions on actual arguments for 
       a function which will call the function this upper call belongs
       to.  These conditions should be satisfied by the caller */
    /* FIXME: deprecated field */
    std::vector<std::vector< ref<Expr> > > actual_args_conditions;
    /* Path summaries for the caller functions which satisfy conditions
     * on the actual arguments */
    std::vector<PathSummary *> connected_summaries;

    UpperCall();
    /* Copy everything including formal_args_conditions and
     * connected summaries */
    UpperCall(UpperCall *upper_call);
    UpperCall(llvm::Function *_fn, llvm::Function *_caller);
    void update_actual_args_conds(ConstraintManager path_constraints, std::vector< ref<Expr> > formal_args);
    void pull_constraints(path_summary_ty *smmry, UpperCall *prev_upper_call);
    std::vector<ref<Expr> > unwrap_constraints_once(path_summary_ty *smmry);
    void add_actual_args_conds(UpperCall *lower_level_upper_call, path_summary_ty *smmry);

    unsigned compute_shallow_hash();
    unsigned shallow_hash() {assert(_shallow_hash); return _shallow_hash;};
};

/* This is a comparator class for <call_symbolic_replacements> map.
 *  We expect the either constant expression returned by
 *  MemoryObject:getBaseAddr() or concat expression return by createTempRead() .
 * In the later case The expressions are equal if
 * the Arrays for lhs and rhs are the same.
 * Constant expressions go before Concat*/
struct classcomp {
  bool operator() (ref<Expr> _l, ref<Expr> _r) const
  {
    //ref<ConcatExpr> lc =  
    //llvm::outs() << "classcomp:: _l = " << _l << "\n";
    //llvm::outs() << "classcomp:: _r = " << _r << "\n";
    ConcatExpr *l = dyn_cast<ConcatExpr>(_l);
    ConcatExpr *r = dyn_cast<ConcatExpr>(_r);

    ConstantExpr *cl = dyn_cast<ConstantExpr>(_l);
    ConstantExpr *cr = dyn_cast<ConstantExpr>(_r);

    ReadExpr *rl = dyn_cast<ReadExpr>(_l);
    ReadExpr *rr = dyn_cast<ReadExpr>(_r);
    
    assert(((l || cl || rl) && (r || cr || rr)) && "classcomp can only compare ReadLSB expressions, one of the arguments is not a ConcatExpr or ConstantExpr");
    
    /* constant less than concat */
    if(cl && r)
      return true;

    /* read less than concat */
    if(rl && r)
      return true;

    /* constant less than read */
    if(cl && rr)
      return true;
    //---
    /* conact bigger than consant */
    if(l && cr)
      return false;

    /* conact bigger than read */
    if(l && rr)
      return false;

    /* read bigger than constant */
    if(rl && cr)
      return false;

    /* Compare ConstantExpr */
    if(cl && cr)
    {
      /* -1 => cl < cr;
         0  => cl = cr;
	 1  => cl > cr;
      */
      int res = cl->compareContents(*cr);
      if(res == -1)
        return true;
      else 
        return false;
    }

    /* Compare ReadExpr */
    if(rl && rr) 
    { 
      const Array *al = rl->updates.root;
      const Array *ar = rr->updates.root;
      if (al < ar)
        return true;
      else 
        return false;
    }
 
    /* Compare ConcatExpr */
    if(l && r) 
    { 
      // Getting read expressions for the left side
      ref<Expr> _l1 = l->getLeft();
      ReadExpr  *l1 = dyn_cast<ReadExpr>(_l1);
      //ref<Expr> _l2 = l->getRight();
      //ReadExpr  *l2 = dyn_cast<ReadExpr>(_l2);

      // Getting read expressions for the right side
      ref<Expr> _r1 = r->getLeft();
      ReadExpr  *r1 = dyn_cast<ReadExpr>(_r1);
      //ref<Expr> _r2 = r->getRight();
      //ReadExpr  *r2 = dyn_cast<ReadExpr>(_r2);

      const Array *al = l1->updates.root;
      const Array *ar = r1->updates.root;
      
      //llvm::outs() << "classcomp:: al: @" << al << "\n";
      //llvm::outs() << "classcomp:: ar: @" << ar << "\n";

      if (al < ar)
      {
        //llvm::outs() << "classcomp:: returning true\n";
        return true;
      }
      else 
      {
        //llvm::outs() << "calsscomp:: returning false\n";
        return false;
      }
    }
  }
};

//typedef std::map<ref<Expr>, InnerCall *, classcomp> call_symbolic_replacements_ty;
typedef std::map<ref<Expr>, InnerCall *> call_symbolic_replacements_ty;

/* This class represent an execution path of a function. (Note that a
 * function summary can be represented as set of path summaries)*/
class PathSummary {

 private:
    unsigned _deep_hash = 0;
    unsigned _shallow_hash = 0;

  public:

    enum SummaryType
    {
	    RET_SUMMARY_TYPE, /* return statement was reached */
	    TARGET_FUNC_SUMMARY_TYPE /* a call to a function from call path was reached. */
    };

    /* Fields */
    /* This path summary belong to this function */
    llvm::Function *fn; 
    SummaryType type;
    /* If return type is TARGET_FUNC_SUMMARY_TYPE, we set this field to the corresponding function */
    llvm::Function *end_function;
    /* We set it to true if the path summary is until a return
     * instruction, if it is until the next on-path function, we set it
     * to false */
    bool is_return_summary; /* obsolete field. We don't use it anywhere in the code. Use <type> field instead */
    ref<Expr> return_value;
    /*  If any global variable changed during the function call, 
     *  we keep track of those variables */
    std::map<llvm::Value *, ref<Expr> > global_values; 
    /* This includes formal args, and global variables */
    constraints_ty path_constraints; 
    /* This includes constraints only on global variables */
    constraints_ty path_constraints_globals_only; 
    /* The next function in the call path, or NULL if the summary is until return instruction */
    llvm::Function *target_func; 
    /* if target_func is not NULL, this contains the list of actual arguments */
    std::vector<ref<Expr> > target_func_actual_args; 
    /* These are formal arguments of the current function (i.e. this
     * summary's function). We made those arguments symbolic; it is a
     * copy of the Executor'r fargs for this function */
    std::vector<ref<Expr> > fargs;
    /* This givees correspondence between a sybmolic expression and
     * the the call instruction which was replaced by this symbolics */
    call_symbolic_replacements_ty call_symbolic_replacements;
    UpperCall *upper_call;
    /* This filed connects an on-call-path summary with the next one on the
     * call path with which it can glue (note that all inner calls should also
     * have connected summaries for two on-call-path summaries to connect). */
    //path_summary_ty *next_path_summary;
    std::vector<path_summary_ty *> next_path_summaries;
    /* This is a copy of <path_choices> field from execution state based on
     * which this summary was created */
    std::vector<int> path_choices;
    std::vector<llvm::Instruction *> path_instructions; 
    std::vector<std::string> path_choices_debug;
    /* *** */

    /* Methods */
    PathSummary(llvm::Function *f, ref<Expr> ret, constraints_ty p_constraints,
               llvm::Function * target_fn, std::vector<ref<Expr> > tfn_args);
    PathSummary(llvm::Function *f, ref<Expr> ret, constraints_ty p_constraints);
    /* Copies everything but call_symbolic_replacements_ty,
     * We create a new call_symolics without connected summaries instead */
    PathSummary(path_summary_ty *smmry);
    void set_parent_for_inner_calls(InnerCall *_parent_inner_call);
    void clear_connected_summaries_for_inner_calls();
    /* Return true path_isntruction of both path summaries contatins the same
     * instructions */
    bool has_the_same_path_instructions(path_summary_ty *smmry);
    std::vector<ref<Expr> > extract_concat_subexpressions(ref<Expr> e);
    /* <path_constraints> contain constraints on both formal func args.
     * but for state selection, we need only constraints on globals*/
    void extract_constraints_on_globals();
    /* For each call instruction that was replaced by a symbolics, return the
     * the corresponding call instruction and conditions collected on those
     * symbolics along the path summary*/
    void update_InnerCalls_with_constraints();
    /* next_func_psmmry is the path summary of the next function on
     * the call path, with which the current summary can be glued */
    void update_InnerCalls_with_constraints2(PathSummary &next_func_psmmry);
    void update_InnerCalls_with_constraints2(UpperCall *upper_call);
    /* Clear ALL reval constraints for inner calls */
    void clear_InnerCalls_constraints();
    /* */
    void print();
    void print_structure(unsigned indent = 0);
    std::vector<ref<Expr> > get_call_symbolics(ref<Expr> complex_expr);
    bool is_inner_calls_connected();
    std::vector<ref<Expr> > unwrap_constraints(InnerCall *inner_call);
    ref<Expr> unwrap_retvalue(InnerCall *inner_call);
    void add_accumulated_conds_to_inner_calls(std::vector<ref<Expr> > add);
    InnerCall* get_InnerCall_by_seqnum(unsigned seqnum);
    unsigned compute_deep_hash();
    unsigned compute_shallow_hash();
    unsigned shallow_hash() {assert(_shallow_hash); return _shallow_hash;};
    /* *** */
};
}

#endif
