
#include <iostream>
#include "klee/klee.h"
#include "klee/ExecutionState.h"
#include "klee/Internal/Module/KModule.h"
#include "klee/Internal/Module/KInstruction.h"
#include "Common.h"
#include "Memory.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/Instruction.h"
#include "llvm/BasicBlock.h"
#include "llvm/Function.h"
#include "llvm/Value.h"

using namespace klee;


extern "C" bool flash_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> flash_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool IE1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> IE1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool IFG1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> IFG1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DCOCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DCOCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool BCSCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> BCSCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool BCSCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> BCSCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool BCSCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> BCSCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool FCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool FCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool FCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1IES_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IES_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2IES_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IES_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TAIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TAIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TACTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TACCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TACCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TAR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TAR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TACCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TACCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool WDTCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> WDTCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CALDCO_1MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALDCO_1MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CALBC1_1MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALBC1_1MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
//-----AUX REGISTER FUNCTIONS-----//
extern "C" ref<Expr> usb_setup_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "@" << addr <<"\n";

	//ref<ConstantExpr> addrExpr = ConstantExpr::create(addr, w);
	ref<ConstantExpr> addrExpr = Expr::createPointer(addr);
	ObjectPair op;
	s->addressSpace.resolveOne(addrExpr, op, NULL);
	const MemoryObject * mo = op.first;
	const ObjectState * os = op.second;
	

	std::cerr << "addr in " << addr << "\n"
						<< " guest_address " << mo->guest_address << "\n";


	std::cerr << "mo " << mo << "\n";
	uint64_t offset = addr - mo->guest_address;

	std::cerr	<< "usb_setup_r offset is " << offset << "\n";

	#if 0
	++use_count;
	std::string res_name = "usb_setup_" + llvm::utostr(offset) + "_" 
		+ llvm::utostr(use_count);

	if (offset == 0x0000){ //bmRequestType
		const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0001){ //bRequest
		const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0x09, w);
		return res;
	} else if (offset == 0x0002){ //wValue
		//const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0xff, w);
		return res;
	} else if (offset == 0x0004){ //wIndex
		ref<Expr> res = ConstantExpr::create(0x01, w);
		return res;
	} else if (offset == 0x0006){ //wLength
		const Array * array = new Array(res_name, w);
		ref<Expr> res = Expr::createTempRead(array, w, true);
		return res;
	}
	#endif

	if (offset == 0x0000){ //bmRequestType
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0001){ //bRequest
		ref<Expr> res = ConstantExpr::create(0x09, w);
		return res;
	} else if (offset == 0x0002){ //wValue
		ref<Expr> res = ConstantExpr::create(0x01, w);
		return res;
	} else if (offset == 0x0003){ //wValue + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0004){ //wIndex
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0005){ //wIndex + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0006){ //wLength
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0007){ //Length + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	}

	assert(0 && "unexpected offset in usb_setup_r");


	#if 0
	const Array * array = new Array(res_name, w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
	#endif
}
