#include "klee/Interrupt.h"
#include "klee/Arch.h"
#include "klee/ExecutionState.h"
#include "klee/Internal/Module/KInstruction.h"
#include <iostream>
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "AddressSpace.h"
#include "Memory.h"

#if 1

using namespace llvm;

namespace klee{

InterruptHandler::InterruptHandler(const llvm::Function * fun){
	this->fun = fun;
	summary_fun = NULL;
	gate = NULL;
	Function::const_iterator blkItr = fun->begin();
	for ( ; blkItr != fun->end() ; ++blkItr){
		BasicBlock::const_iterator instItr = blkItr->begin();
		for ( ; instItr != blkItr->end() ; ++instItr){
			const llvm::Instruction& inst = *instItr;
			Value::const_use_iterator use_itr = inst.use_begin();
			Value::const_use_iterator use_end = inst.use_end();
			for ( ; use_itr != use_end ; ++use_itr){
				const User * user = *use_itr;
				//useSet(user);
			}
		}
	}
}

void InterruptHandler::useSet(const llvm::User * use){
	if (users.find(use) != users.end()){
		return;
	}

	users.insert(use);

	Value::const_use_iterator use_itr = use->use_begin();
	Value::const_use_iterator use_end = use->use_end();
	for ( ; use_itr != use_end ; ++use_itr){
		const User * use_use = *use_itr;
		//useSet(use_use);
	}
}

}

#endif
