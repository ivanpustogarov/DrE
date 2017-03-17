//===-- ExecutorCommandLineParameters.h - Abstract Execution Engine Interface -----*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//===----------------------------------------------------------------------===//

#ifndef KLEE_EXECUTORCOMMANDLINE_H
#define KLEE_EXECUTORCOMMANDLINE_H


#include "klee/CommandLine.h"
#include "klee/Internal/ADT/RNG.h"

//enum OP_Frequency{ NeverFreq, BBLFreq, InstructionFreq };
//namespace {

  enum OP_Frequency{ NeverFreq, BBLFreq, InstructionFreq };
  extern llvm::cl::opt<unsigned> MaxForks;
  extern llvm::cl::opt<bool> OnlyReplaySeeds;
  extern llvm::cl::opt<double> MaxStaticForkPct;
  extern llvm::cl::opt<double> MaxStaticSolvePct;
  extern llvm::cl::opt<double> MaxStaticCPForkPct;
  extern llvm::cl::opt<double> MaxStaticCPSolvePct;
  extern llvm::cl::opt<double> MaxInstructionTime;
  extern llvm::cl::opt<bool> MaxMemoryInhibit;
  extern llvm::cl::opt<bool> RandomizeFork;
  extern llvm::cl::opt<unsigned> MaxDepth;
  extern llvm::cl::opt<bool> AllExternalWarnings;
  extern llvm::cl::opt<bool> DebugPrintInstructions;
  extern llvm::cl::opt<unsigned int> StopAfterNInstructions;
  extern llvm::cl::opt<OP_Frequency> MergeFrequency;
  extern llvm::cl::opt<unsigned> MaxMemory;
  extern llvm::cl::opt<bool> DumpStatesOnHalt;
  extern llvm::cl::opt<bool> OnlyOutputStatesCoveringNew;
  extern llvm::cl::opt<bool> AlwaysOutputSeeds;
  extern llvm::cl::opt<bool> EmitAllErrors;
  extern llvm::cl::opt<bool> NoExternals;
  extern llvm::cl::opt<bool> AllowExternalSymCalls;
  extern llvm::cl::opt<bool> SuppressExternalWarnings;
  extern llvm::cl::opt<bool> SimplifySymIndices;
  extern llvm::cl::opt<unsigned> MaxSymArraySize;
  extern llvm::cl::opt<bool> NamedSeedMatching;
  extern llvm::cl::opt<bool> ZeroSeedExtension;
  extern llvm::cl::opt<bool> AllowSeedExtension; 
  extern llvm::cl::opt<bool> AllowSeedTruncation;
  extern llvm::cl::opt<bool> WithInterrupts;
  extern llvm::cl::opt<bool> BreakOnFirstFit;
  extern llvm::cl::opt<bool> ForwardOnly;
//}
//
namespace klee {
  extern RNG theRNG;
}

#endif
