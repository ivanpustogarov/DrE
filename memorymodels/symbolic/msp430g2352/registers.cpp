
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
extern "C" bool CACTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CACTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CACTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CACTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CACTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CACTL2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool CAPD_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CAPD_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CAPD_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P1SEL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1SEL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P1SEL2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P2SEL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2SEL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P2SEL2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0IV_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TA0CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0CTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TA0CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0CCTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TA0CCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0CCTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TA0CCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0CCTL2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TA0R_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0R_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0R_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TA0CCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0CCR0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TA0CCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0CCR1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TA0CCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TA0CCR2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USICTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USICTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USICTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USICTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USICTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USICTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USICKCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USICKCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USICKCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USICNT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USICNT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USICNT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USISRL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USISRL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USISRL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USISRH_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USISRH_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USISRH_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USICTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USICTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USICTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USICCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USICCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USICCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool USISR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> USISR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"USISR_arr" + llvm::utostr(++use_count), w);
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
extern "C" ref<Expr> usb_setup_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "@" << addr <<"\n";

	//ref<ConstantExpr> addrExpr = ConstantExpr::create(addr, w);
	ref<ConstantExpr> addrExpr = Expr::createPointer(addr);
	ObjectPair op;
	s->addressSpace.resolveOne(addrExpr, op, NULL);
	const MemoryObject * mo = op.first;
	const ObjectState * os = op.second;
	

	std::cout << "addr in " << addr << "\n"
						<< " guest_address " << mo->guest_address << "\n";


	std::cout << "mo " << mo << "\n";
	uint64_t offset = addr - mo->guest_address;

	std::cout	<< "usb_setup_r offset is " << offset << "\n";

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
