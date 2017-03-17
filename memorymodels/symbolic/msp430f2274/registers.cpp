
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
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> flash_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"flash_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool IE1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> IE1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"IE1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool IFG1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> IFG1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"IFG1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool IE2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> IE2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"IE2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool IFG2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> IFG2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"IFG2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC10DTC0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10DTC0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC10DTC0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC10DTC1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10DTC1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC10DTC1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC10AE0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10AE0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC10AE0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC10AE1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10AE1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC10AE1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC10CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC10CTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC10CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC10CTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC10MEM_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10MEM_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC10MEM_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC10SA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10SA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC10SA_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool DCOCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DCOCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"DCOCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool BCSCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> BCSCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"BCSCTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool BCSCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> BCSCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"BCSCTL2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool BCSCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> BCSCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"BCSCTL3_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool FCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"FCTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool FCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"FCTL2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool FCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"FCTL3_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool OA0CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OA0CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"OA0CTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool OA0CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OA0CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"OA0CTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool OA1CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OA1CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"OA1CTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool OA1CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OA1CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"OA1CTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P1IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1IN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P1OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1OUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P1DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1DIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P1IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1IFG_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P1IES_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IES_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1IES_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P1IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1IE_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P1SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1SEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P1REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1REN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P2IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2IN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P2OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2OUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P2DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2DIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P2IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2IFG_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P2IES_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IES_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2IES_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P2IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2IE_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P2SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2SEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P2REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2REN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P3IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P3IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P3IN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P3OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P3OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P3OUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P3DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P3DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P3DIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P3SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P3SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P3SEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P3REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P3REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P3REN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P4IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P4IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P4IN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P4OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P4OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P4OUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P4DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P4DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P4DIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P4SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P4SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P4SEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P4REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P4REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P4REN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TAIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TAIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TAIV_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TACTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TACTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TACCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TACCTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TACCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TACCTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TACCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TACCTL2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TAR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TAR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TAR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TACCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TACCR0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TACCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TACCR1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TACCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TACCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TACCR2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBIV_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCTL2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCR0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCR1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCR2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0CTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0CTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0BR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0BR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0BR0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0BR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0BR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0BR1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0MCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0MCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0MCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0STAT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0STAT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0STAT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0RXBUF_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0TXBUF_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0ABCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0ABCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0ABCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0IRTCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IRTCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0IRTCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA0IRRCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IRRCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA0IRRCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0CTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0CTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0BR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0BR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0BR0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0BR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0BR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0BR1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0I2CIE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2CIE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0I2CIE_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0STAT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0STAT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0STAT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0RXBUF_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0TXBUF_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0I2COA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0I2COA_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB0I2CSA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2CSA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB0I2CSA_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool WDTCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> WDTCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"WDTCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CALDCO_16MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALDCO_16MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CALDCO_16MHZ_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CALBC1_16MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALBC1_16MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CALBC1_16MHZ_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CALDCO_12MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALDCO_12MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CALDCO_12MHZ_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CALBC1_12MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALBC1_12MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CALBC1_12MHZ_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CALDCO_8MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALDCO_8MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CALDCO_8MHZ_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CALBC1_8MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALBC1_8MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CALBC1_8MHZ_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CALDCO_1MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALDCO_1MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CALDCO_1MHZ_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CALBC1_1MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CALBC1_1MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CALBC1_1MHZ_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
//-----AUX REGISTER FUNCTIONS-----//
