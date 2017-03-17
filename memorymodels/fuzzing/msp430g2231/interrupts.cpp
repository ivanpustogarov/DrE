#include <iostream>
#include "klee/klee.h"
#include "klee/ExecutionState.h"
#include "klee/Arch.h"
#include "klee/Internal/Module/KModule.h"
#include "klee/Internal/Module/KInstruction.h"
#include "Memory.h"
#include "klee/Expr.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/Instruction.h"
#include "llvm/BasicBlock.h"
#include "llvm/Function.h"
#include "llvm/Value.h"

#define C                   (0x0001)
#define Z                   (0x0002)
#define N                   (0x0004)
#define V                   (0x0100)
#define GIE                 (0x0008)
#define CPUOFF              (0x0010)
#define OSCOFF              (0x0020)
#define SCG0                (0x0040)
#define SCG1                (0x0080)

using namespace klee;

extern "C" bool check_usb_ubm(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_usi(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_unmi(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_port1(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_port2(klee::Architecture * arch, klee::ExecutionState * state){ 
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_adc10(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_usciabotx(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}
extern "C" bool check_usciaborx(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_timer_a0(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_timer_a1(klee::Architecture * arch , klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}


extern "C" bool check_timer0_a1(klee::Architecture * arch , klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_timer0_a0(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}
extern "C" bool check_wdt(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	return true;
}
extern "C" bool check_comparatora(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	return true;
}

extern "C" bool check_timer1_a1(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_timer1_a0(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_nmi(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}

extern "C" bool check_reset(klee::Architecture * arch, klee::ExecutionState * state){
	if (state->interruptFun){ 
		return false;
	}
	
	klee::ref<Expr> sr = arch->getSR(*state);
	if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
		uint8_t value = ce->getZExtValue();
		uint16_t big_value = value;
		std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
							<< std::hex << big_value << "\n";
		if (value & GIE){
			return true;
		}
		return false;
	} else {
		std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
	}
	return true;
}
