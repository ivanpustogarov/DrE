//===-- UserSearcher.cpp --------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Common.h"

#include "UserSearcher.h"

#include "Searcher.h"
#include "Executor.h"
#include "klee/SummaryExecutor.h"

#include "llvm/Support/CommandLine.h"

using namespace llvm;
using namespace klee;

namespace {
  cl::list<Searcher::CoreSearchType>
  CoreSearch("search", cl::desc("Specify the search heuristic (default=random-path interleaved with nurs:covnew)"),
	     cl::values(clEnumValN(Searcher::DFS, "dfs", "use Depth First Search (DFS)"),
			clEnumValN(Searcher::BFS, "bfs", "use Breadth First Search (BFS)"),
			clEnumValN(Searcher::RandomState, "random-state", "randomly select a state to explore"),
			clEnumValN(Searcher::RandomPath, "random-path", "use Random Path Selection (see OSDI'08 paper)"),
			/*
			clEnumValN(Searcher::NURS_CovNew, "nurs:covnew", "use Non Uniform Random Search (NURS) with Coverage-New"),
			clEnumValN(Searcher::NURS_MD2U, "nurs:md2u", "use NURS with Min-Dist-to-Uncovered"),
			clEnumValN(Searcher::NURS_Depth, "nurs:depth", "use NURS with 2^depth"),
			clEnumValN(Searcher::NURS_ICnt, "nurs:icnt", "use NURS with Instr-Count"),
			clEnumValN(Searcher::NURS_CPICnt, "nurs:cpicnt", "use NURS with CallPath-Instr-Count"),
			clEnumValN(Searcher::NURS_QC, "nurs:qc", "use NURS with Query-Cost"),
			*/
			clEnumValN(Searcher::ShortestDistance, "SD", "shortest distance to target"),
			clEnumValN(Searcher::DRandomPath, "d-random-path", "directed random path selection"),
			clEnumValEnd));

  cl::list<unsigned>
  CoreSearchMultiples("search-mult", cl::desc("Specify the multiples for search heuristics"));

  cl::opt<bool>
  UseIterativeDeepeningTimeSearch("use-iterative-deepening-time-search", 
                                    cl::desc("(experimental)"));

  cl::opt<bool>
  UseBatchingSearch("use-batching-search", 
		    cl::desc("Use batching searcher (keep running selected state for N instructions/time, see --batch-instructions and --batch-time)"),
		    cl::init(false));

  cl::opt<unsigned>
  BatchInstructions("batch-instructions",
                    cl::desc("Number of instructions to batch when using --use-batching-search"),
                    cl::init(10000));
  
  cl::opt<double>
  BatchTime("batch-time",
            cl::desc("Amount of time to batch when using --use-batching-search"),
            cl::init(5.0));


  cl::opt<bool>
  UseMerge("use-merge", 
           cl::desc("Enable support for klee_merge() (experimental)"));
 
  cl::opt<bool>
  UseBumpMerge("use-bump-merge", 
           cl::desc("Enable support for klee_merge() (extra experimental)"));

}


bool klee::userSearcherRequiresMD2U() {
  return (std::find(CoreSearch.begin(), CoreSearch.end(), Searcher::NURS_MD2U) != CoreSearch.end() ||
	  std::find(CoreSearch.begin(), CoreSearch.end(), Searcher::NURS_CovNew) != CoreSearch.end() ||
	  std::find(CoreSearch.begin(), CoreSearch.end(), Searcher::NURS_ICnt) != CoreSearch.end() ||
	  std::find(CoreSearch.begin(), CoreSearch.end(), Searcher::NURS_CPICnt) != CoreSearch.end() ||
	  std::find(CoreSearch.begin(), CoreSearch.end(), Searcher::NURS_QC) != CoreSearch.end());
}


Searcher *getNewSearcher(Searcher::CoreSearchType type, Executor &executor) {
  Searcher *searcher = NULL;
  switch (type) {
  case Searcher::DFS: searcher = new DFSSearcher(); break;
  case Searcher::BFS: searcher = new BFSSearcher(); break;
  case Searcher::RandomState: searcher = new RandomSearcher(); break;
  case Searcher::RandomPath: searcher = new RandomPathSearcher(executor); break;
  case Searcher::NURS_CovNew: searcher = new WeightedRandomSearcher(WeightedRandomSearcher::CoveringNew); break;
  case Searcher::NURS_MD2U: searcher = new WeightedRandomSearcher(WeightedRandomSearcher::MinDistToUncovered); break;
  case Searcher::NURS_Depth: searcher = new WeightedRandomSearcher(WeightedRandomSearcher::Depth); break;
  case Searcher::NURS_ICnt: searcher = new WeightedRandomSearcher(WeightedRandomSearcher::InstCount); break;
  case Searcher::NURS_CPICnt: searcher = new WeightedRandomSearcher(WeightedRandomSearcher::CPInstCount); break;
  case Searcher::NURS_QC: searcher = new WeightedRandomSearcher(WeightedRandomSearcher::QueryCost); break;
  case Searcher::ShortestDistance: searcher = new SDSearcher(executor); break;
  case Searcher::DRandomPath: searcher = new DRandomPathSearcher(executor); break;
  }

  /* FIXME: this should be in the searchers' constructors. ivan: no time to do that */
  searcher->no_good_states = false;
  return searcher;
}

Searcher *klee::constructUserSearcher(Executor &executor) {

  // default values
  if (CoreSearch.size() == 0) {
    CoreSearch.push_back(Searcher::RandomPath);
    CoreSearch.push_back(Searcher::NURS_CovNew);
  }

  Searcher *searcher = getNewSearcher(CoreSearch[0], executor);
  
  if (CoreSearch.size() > 1) {
    std::vector<Searcher *> s;
    s.push_back(searcher);

    for (unsigned i=1; i<CoreSearch.size(); i++)
      s.push_back(getNewSearcher(CoreSearch[i], executor));
    
    searcher = new InterleavedSearcher(s,s);
    searcher->no_good_states = false;
  }

  if (UseBatchingSearch) {
    searcher = new BatchingSearcher(searcher, BatchTime, BatchInstructions);
  }

  // merge support is experimental
  if (UseMerge) {
    assert(!UseBumpMerge);
    assert(std::find(CoreSearch.begin(), CoreSearch.end(), Searcher::RandomPath) == CoreSearch.end()); // XXX: needs further debugging: test/Features/Searchers.c fails with this searcher
    searcher = new MergingSearcher(executor, searcher);
  } else if (UseBumpMerge) {
    searcher = new BumpMergingSearcher(executor, searcher);
  }
  
  if (UseIterativeDeepeningTimeSearch) {
    searcher = new IterativeDeepeningTimeSearcher(searcher);
  }

  llvm::raw_ostream &os = executor.getHandler().getInfoStream();

  os << "BEGIN searcher description\n";
  searcher->printName(os);
  os << "END searcher description\n";

  return searcher;
}

/* Copy of the function above to work with SummaryExecutor (the function
 * above did now work for SummaryExecutor, don't have time to debug it =>
 * this ugly hack). */
Searcher *klee::constructUserSearcher(SummaryExecutor &executor) {

  // default values
  if (CoreSearch.size() == 0) {
    CoreSearch.push_back(Searcher::RandomPath);
    //CoreSearch.push_back(Searcher::NURS_CovNew);
  }

  /* Check if we need to multiply searchers */
  if ((CoreSearchMultiples.size() != 0) && (CoreSearchMultiples.size() != CoreSearch.size()))
    klee_error("There should the same number of -search and -search-mult args\n");

  Searcher *searcher = getNewSearcher(CoreSearch[0], executor);
  
  if (CoreSearch.size() > 1) {
    std::vector<Searcher *> s;
    std::vector<Searcher *> copies;
    s.push_back(searcher);

    for (unsigned i=1; i<CoreSearch.size(); i++)
      s.push_back(getNewSearcher(CoreSearch[i], executor));
    //{
    //  Searcher *add_search = getNewSearcher(CoreSearch[i], executor);
    //  s.push_back(add_search);
    //}

    /* Add multiples */
    llvm::outs() << "klee::constructUserSearcher(): adding multiples\n";
    if (CoreSearchMultiples.size() != 0)
      for (unsigned i=0; i<s.size(); i++)
        for (unsigned j=0; j<CoreSearchMultiples[i]; j++)
          copies.push_back(s[i]);
    else
      copies = s;
    llvm::outs() << "klee::constructUserSearcher(): multiples added\n";
    
    searcher = new InterleavedSearcher(s, copies);
  }

  if (UseBatchingSearch) {
    llvm::outs() << "klee::constructUserSearcher(): using batch\n";
    searcher = new BatchingSearcher(searcher, BatchTime, BatchInstructions);
  }

  // merge support is experimental
  if (UseMerge) {
    llvm::outs() << "klee::constructUserSearcher(): using merge\n";
    assert(!UseBumpMerge);
    assert(std::find(CoreSearch.begin(), CoreSearch.end(), Searcher::RandomPath) == CoreSearch.end()); // XXX: needs further debugging: test/Features/Searchers.c fails with this searcher
    searcher = new MergingSearcher(executor, searcher);
  } else if (UseBumpMerge) {
    llvm::outs() << "klee::constructUserSearcher(): using bump merge\n";
    searcher = new BumpMergingSearcher(executor, searcher);
  }
  
  if (UseIterativeDeepeningTimeSearch) {
    llvm::outs() << "klee::constructUserSearcher(): using iterative deeping time searcher\n";
    searcher = new IterativeDeepeningTimeSearcher(searcher);
  }

  //llvm::raw_ostream &os = executor.getHandler().getInfoStream();

  //os << "BEGIN searcher description\n";
  //searcher->printName(os);
  //os << "END searcher description\n";

  return searcher;
}


/* Copy of the function above to work with ForwardExecutor (the function
 * above did now work for SummaryExecutor, don't have time to debug it =>
 * this ugly hack). */
Searcher *klee::constructUserSearcher(ForwardExecutor &executor) {

  // default values
  if (CoreSearch.size() == 0) {
    CoreSearch.push_back(Searcher::RandomPath);
    //CoreSearch.push_back(Searcher::NURS_CovNew);
  }

  /* Check if we need to multiply searchers */
  if ((CoreSearchMultiples.size() != 0) && (CoreSearchMultiples.size() != CoreSearch.size()))
    klee_error("There should the same number of -search and -search-mult args\n");

  Searcher *searcher = getNewSearcher(CoreSearch[0], executor);
  
  if (CoreSearch.size() > 1) {
    std::vector<Searcher *> s;
    std::vector<Searcher *> copies;
    s.push_back(searcher);

    for (unsigned i=1; i<CoreSearch.size(); i++)
      s.push_back(getNewSearcher(CoreSearch[i], executor));

    /* Add multiples */
    llvm::outs() << "klee::constructUserSearcher(): adding multiples\n";
    if (CoreSearchMultiples.size() != 0)
      for (unsigned i=0; i<s.size(); i++)
        for (unsigned j=0; j<CoreSearchMultiples[i]; j++)
          copies.push_back(s[i]);
    else
      copies = s;
    llvm::outs() << "klee::constructUserSearcher(): multiples added\n";
    
    searcher = new InterleavedSearcher(s, copies);
  }

  if (UseBatchingSearch) {
    llvm::outs() << "klee::constructUserSearcher(): using batch\n";
    searcher = new BatchingSearcher(searcher, BatchTime, BatchInstructions);
  }

  // merge support is experimental
  if (UseMerge) {
    llvm::outs() << "klee::constructUserSearcher(): using merge\n";
    assert(!UseBumpMerge);
    assert(std::find(CoreSearch.begin(), CoreSearch.end(), Searcher::RandomPath) == CoreSearch.end()); // XXX: needs further debugging: test/Features/Searchers.c fails with this searcher
    searcher = new MergingSearcher(executor, searcher);
  } else if (UseBumpMerge) {
    llvm::outs() << "klee::constructUserSearcher(): using bump merge\n";
    searcher = new BumpMergingSearcher(executor, searcher);
  }
  
  if (UseIterativeDeepeningTimeSearch) {
    llvm::outs() << "klee::constructUserSearcher(): using iterative deeping time searcher\n";
    searcher = new IterativeDeepeningTimeSearcher(searcher);
  }

  return searcher;
}

#if 0
/* TODO: add interleaved searches */
Searcher *klee::constructUserSearcher(SummaryExecutor &executor) 
{
  llvm::outs() << "klee::constructUserSearcher(): constructing new SDSearcher\n";
  Searcher *searcher = new SDSearcher(executor); 
  return searcher;
}

/* TODO: add interleaved searches */
Searcher *klee::constructUserSearcher(ForwardExecutor &executor) 
{
  llvm::outs() << "klee::constructUserSearcher(ForwardExecutor): constructing new SDSearcher\n";
  assert(executor.path_manager);
  Searcher *searcher = new SDSearcher(executor); /* TODO: create a dedicated path-summary-complying searcher */
  return searcher;
}
#endif
