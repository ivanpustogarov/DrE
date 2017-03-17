//===-- InterpreterManager.h - Abstract Execution Engine Interface -----*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//===----------------------------------------------------------------------===//

#ifndef KLEE_INTERPRETERMANAGER_H
#define KLEE_INTERPRETERMANAGER_H

#include "klee/PathManager.h"
#include "klee/SummaryExecutor.h"
#include "klee/ForwardExecutor.h"
#include "klee/Arch.h"
#include "klee/Interpreter.h"
#include "klee/Internal/Module/KModule.h"
#include "klee/Solver.h"
#include <vector>
#include <string>
#include <map>
#include <set>

namespace llvm {
class Function;
class Module;
class raw_ostream;
class raw_fd_ostream;
  class Value;
}

namespace klee {
class Interpreter;
class PathManager;
class TreeStreamWriter;
class Architecture;
class KModule;
template<class T> class ref;
class Expr;
class SummaryExecutor;
class ForwardExecutor;

/* This class is responsible for keeping track and running executors
 * (e.g Executor, SummaryExecutor, etc.) */
class InterpreterManager {
public:

  std::map<llvm::Function *, SummaryExecutor *> summary_interpreters;
  /* This is used to control collecting summaries for inner calls, it is
   * set to false in create_summary_executor(), it is set to true when
   * we run the next round of composit symbex */
  std::map<llvm::Function *, bool> need_more_summaries; 
  ForwardExecutor *forward_interpreter;
  PathManager *path_manager;
  Architecture *arch;
  KModule *kmodule;
  Solver *coreSolver;
  const Interpreter::InterpreterOptions interpreterOpts;
  double slave_search_freq;
  /* Pause collecting path summaries after this time (in seconds) */
  int collect_timeout; 
  int smmries_per_run; 
  std::vector<PathSummary *> candidates;
  /* The following two fields are used to store hashes of constraints
   * which we already checked.  only the key matters for us, the content
   * (which is now the conjunction of the constraints) is not important
   * and not used */
  std::map<unsigned, ref<Expr> > valid_constraints;
  std::map<unsigned, ref<Expr> > invalid_constraints;

  /* Cache of rewrites. When we try to glue path summaries, we rewrite their arguments.
   * which might take a lot of time if there are many complex nested constraints.
   * As we might glue the same path summaries over and over again, we keep a cache
   * of previous replacements. This cache is used before calling function klee::replace_subexpr() */
  //typedef std::map<ref<Expr>, ref<Expr> > ref2ref_map;
  //typedef std::map<ref<Expr>, ref2ref_map> ref2map_map;
  //std::map<unsigned, ref2map_map>  expr_replace_cache;
  std::map<unsigned, std::set<unsigned> > upper_calls_fit_cache;
  std::map<unsigned, std::set<unsigned> > upper_calls_nofit_cache;

  std::map<unsigned, std::set<unsigned> > inner_calls_fit_cache;
  std::map<unsigned, std::set<unsigned> > inner_calls_nofit_cache;

  /* The following field stores already checked (by forward executor) simple
   * paths */
  std::map<unsigned, path_summary_ty *> checked_simple_paths;

  InterpreterManager();
  InterpreterManager(const Interpreter::InterpreterOptions &_interpreterOpts, Architecture *_arch, KModule *_kmodule, Solver *_coreSolver);
  ~InterpreterManager() {};
  //void startCompositSymbEx();
  void startCompositSymbEx(llvm::Function *f, int argc, char **argv, char **envp);
  //bool comp_symbex_can_glue(llvm::Function *f1, ExecutionState &f1_state, std::vector< ref<Expr> > f2_actual_args);
  //bool comp_symbex_can_glue1(path_summary_ty &f1_smmry, path_summary_ty &f2_smmry);

  bool comp_symbex_can_glue2(path_summary_ty *smmry, UpperCall *upper_call);
  bool comp_symbex_can_glue2(path_summary_ty *smmry, InnerCall *inner_call);

  bool conds_are_solvable(std::vector< ref<Expr> > &vexpr);
  //bool conds_are_solvable(ref<Expr> x, std::vector< ref<Expr> > *conditions);
  //ref<Expr> comp_symbex_replace_for_retvalue(ref<Expr> expr, ref<Expr> &retvalue);
  int run_inner_calls(path_summary_ty &path_smmry);
  int run_upper_call(UpperCall *upper_call);
  //const llvm::Module *setModule(llvm::Module *module);


  std::vector<path_summary_ty *> split_path_candidate(path_summary_ty *candidate);


#if 0
  /// ModuleOptions - Module level options which can be set when
  /// registering a module with the interpreter.
  struct ModuleOptions {
    std::string LibraryDir;
    bool Optimize;
    bool CheckDivZero;
    bool CheckOvershift;

    ModuleOptions(const std::string& _LibraryDir, 
                  bool _Optimize, bool _CheckDivZero,
                  bool _CheckOvershift)
      : LibraryDir(_LibraryDir), Optimize(_Optimize), 
        CheckDivZero(_CheckDivZero), CheckOvershift(_CheckOvershift) {}
  };

  enum LogType
  {
	  STP, //.CVC (STP's native language)
	  KQUERY, //.PC files (kQuery native language)
	  SMTLIB2, //.SMT2 files (SMTLIB version 2 files)
          CVS // IVAN was here
  };
#endif

private:
  std::vector<ref<Expr> > extract_concat_subexpressions(ref<Expr> e);
  int run_inner_call(InnerCall *inner_call);
  bool path_summary_fits_inner_call(path_summary_ty *smmry,  InnerCall *inner_call);
  bool path_summary_fits_upper_call(path_summary_ty *original_path_summary,  UpperCall *upper_call);
  SummaryExecutor* create_summary_executor(llvm::Function *f);
  void adapt_psummary_to_inner_call(InnerCall *parent_inner_call, path_summary_ty *smmry);
  void adapt_psummary_to_upper_call(UpperCall *upper_call, path_summary_ty *smmry);
  bool check_formal_args_against_psummary(path_summary_ty &smmry, std::vector<std::vector< ref<Expr> > > &formal_args_conditions);
  void do_backward_symbex();
  int do_forward_symbex(llvm::Function *f, int argc, char **argv, char **envp, int start_ndx);
  void build_path_hash_chains(path_summary_ty *copy_path_summary);
  uint64_t ugly_hash(uint64_t prev_hash, uint64_t val);

#if 0
  /// Register the module to be executed.  
  ///
  /// \return The final module after it has been optimized, checks
  /// inserted, and modified for interpretation.
  const llvm::Module *setModule(llvm::Module *module, const ModuleOptions &opts) = 0;
  void setArch(Architecture * arch) = 0;
  void startCompositionalSymbEx(llvm::Function *f, int argc, char **argv, char **envp) = 0;
#endif

};

} // End klee namespace

#endif
