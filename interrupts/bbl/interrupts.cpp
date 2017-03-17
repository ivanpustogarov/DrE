
#include <iostream>
#include "klee/klee.h"
#include "klee/ExecutionState.h"
#include "klee/Arch.h"
#include "klee/Internal/Module/KModule.h"
#include "klee/Internal/Module/KInstruction.h"
#include "Memory.h"
#include "klee/Expr.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"

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

extern "C" bool check_2FLASH_IP
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_8BTC
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_ADC
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_ADC10
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_ADC10_A
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_ADC10_B
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_ADC12
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_ADC12_B
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}

extern "C" bool check_ADC12_PLUS
(klee::Architecture * arch, klee::ExecutionState * state){
  if (state->interruptFun){ 
    return false;
  }
  std::cout << "Enter BBL interrupt check\n";

  KInstruction * pcInst = state->prevPC;
  //not as basic block head
  if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
    std::cout << "Not a BBL Head\n";
    return false;
  }

  klee::ref<Expr> sr = arch->getSR(*state);
  if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
    uint8_t value = ce->getZExtValue();
    uint16_t big_value = value;
    std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
      << std::hex << big_value << "\n";
    if (value & GIE){
      return true;
    }
    return false;
  } else {
    std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
  }
  return true;
}


extern "C" bool check_ADC14
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_AES
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_AES256
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_APOOL
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_AUX_SUPPLY
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_BACKUP_RAM
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_BASIC_CLOCK
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_BATTERY_CHARGER
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_BC2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_BT
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_BT_RTC
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_CAPLUS
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_CAP_TOUCH_IO_0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_CAP_TOUCH_IO_1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_CC1101
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_CCS
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_COMPA
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_COMPARATORA
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_COMPB
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_COMP_B
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_COMPD
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_COMP_D
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_COMP_E
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_CRC
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_CS
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_DAC12_1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_DAC12_2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_DACDMA
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_DMA
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_DMA_1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_DMA_3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_DMAX_3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_DMAX_6
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_EPROM
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_ESP430E
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_EUSCI_A0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_EUSCI_A1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_EUSCI_A2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_EUSCI_A3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_EUSCI_B0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_EUSCI_B1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_FLASH
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_FLASH2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_FLL
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_FLLPLUS
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_FLLPLUS_SMALL
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_FRAM
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_FRAM_FR5XX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_I2C
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_LCD
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_LCD4
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_LCD_A
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_LCD_B
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_LCD_C
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_LDO_PWR
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_MID
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_MPU
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_MPY
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_MPY32
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_MSP430X_CPU
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_MSP430XV2_CPU
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_NMI
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_OA_2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_OA_3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PMM
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PMM_FR5xx
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PMM_FRAM
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT10
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT10_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT11_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT1_MAPPING
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT1_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT2_MAPPING
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT2_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT3_MAPPING
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT3_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT4
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT4_MAPPING
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT4_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT5
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT5_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT6
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT6_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT7
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT7_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT8
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT8_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT9
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT9_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTA
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTA_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTB
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTB_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTC_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTD_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTE_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTF_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORTJ_R
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PORT_MAPPING
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_PU
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RC
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_REF
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_REF_A
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED10
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED11
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED12
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED13
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED14
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED15
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED20
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED4
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED5
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED6
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED7
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED8
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESERVED9
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RESET
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RTC
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RTC_B
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RTC_C
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_RTC_D
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SCANIF
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD16
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD16_2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD16_3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD16_A1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD16_A3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD16_A4
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD16_A6
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD16_A7
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_A1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_A2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_A3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_B
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_B2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_B3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_B4
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_B6
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SD24_B7
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SFR
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SVS
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SYS
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_SYSNMI
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T0A3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T0A5
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T0B3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T0B7
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T0D3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T1A2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T1A3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T1A5
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T1B3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T1D3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T2A2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T2A3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T2B3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_T3A2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TA2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TA3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TA5
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TB3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TB7
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TEV0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TEV1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER0_A0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER0_A1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER0_B0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER0_B1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER1_A0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER1_A1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER1_B0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER1_B1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER2_A0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER2_A1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER2_B0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMER2_B1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMERA0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMERA1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMERB0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TIMERB1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TLV
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_TP
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UART0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UART0RX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UART0TX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UART1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UART1RX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UART1TX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UCS
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UCS_RF
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_UNMI
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USART0RX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USART0TX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USART1RX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USART1TX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USB
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USB_UBM
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_A0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_A1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_A2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_A3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_AB0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCIAB0RX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCIAB0TX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_AB1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCIAB1RX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCIAB1TX
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_B0
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_B1
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_B2
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USCI_B3
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_USI
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_WDT
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
extern "C" bool check_WDT_A
(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cout << "Enter BBL interrupt check\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cout << "Not a BBL Head\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cout << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cout << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\n";
}
return true;
}
