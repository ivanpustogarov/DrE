#ifndef KLEE_INTERRUPT_EXT
#define KLEE_INTERRUPT_EXT

#include "llvm/IR/Module.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
//#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
//#include "llvm/Support/CallSite.h"
#include "../../lib/Core/TimingSolver.h"

#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <dlfcn.h>

namespace llvm{
class Function;
class Module;
}

namespace klee{

class ExecutionState;
//class KInstruction;
struct KInstruction;
class Executor;
class Architecture;
class InterruptHandler;
class TimingSolver;

class SummaryFunction{
};

//typedef bool (*interrupt_gate)(klee::Architecture *, klee::ExecutionState *);
typedef bool (*interrupt_gate)(klee::Architecture *, klee::ExecutionState *, TimingSolver *);
typedef std::vector<InterruptHandler *> InterruptVector;

class InterruptHandler{
public:
	interrupt_gate gate;
	const llvm::Function * fun;
	SummaryFunction * summary_fun;

	//Everything that defines a value used in this interrupt
	std::vector<const llvm::Value *> deps;

	//Everything that uses a value defined in this interrupt
	std::set<const llvm::User *> users;

	InterruptHandler(const llvm::Function * fun);
	void useSet(const llvm::User * user);
};

}

#endif
