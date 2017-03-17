//===-- UserSearcher.h ------------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef KLEE_USERSEARCHER_H
#define KLEE_USERSEARCHER_H

namespace klee {
  class Executor;
  class SummaryExecutor;
  class ForwardExecutor;
  class Searcher;

  // XXX gross, should be on demand?
  bool userSearcherRequiresMD2U();

  Searcher *constructUserSearcher(Executor &executor);
  Searcher *constructUserSearcher(SummaryExecutor &executor);
  Searcher *constructUserSearcher(ForwardExecutor &executor);
}

#endif
