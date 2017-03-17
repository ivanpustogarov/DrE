
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
extern "C" bool UC1IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UC1IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UC1IE_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UC1IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UC1IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UC1IFG_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12CTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12CTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12IFG_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12IE_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12IV_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM3_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM4_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM4_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM4_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM5_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM5_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM5_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM6_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM6_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM6_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM7_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM7_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM7_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM8_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM8_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM8_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM9_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM9_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM9_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM10_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM10_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM10_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM11_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM11_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM11_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM12_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM12_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM12_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM13_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM13_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM13_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM14_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM14_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM14_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MEM15_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MEM15_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MEM15_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL3_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL4_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL4_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL4_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL5_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL5_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL5_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL6_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL6_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL6_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL7_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL7_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL7_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL8_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL8_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL8_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL9_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL9_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL9_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL10_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL10_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL10_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL11_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL11_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL11_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL12_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL12_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL12_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL13_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL13_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL13_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL14_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL14_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL14_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12MCTL15_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12MCTL15_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12MCTL15_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool FCTL4_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FCTL4_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"FCTL4_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool MPY_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"MPY_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool MPYS_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"MPYS_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool MAC_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"MAC_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool MACS_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"MACS_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool OP2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"OP2_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool RESLO_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RESLO_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"RESLO_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool RESHI_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RESHI_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"RESHI_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool SUMEXT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SUMEXT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"SUMEXT_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P5IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P5IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P5IN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P5OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P5OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P5OUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P5DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P5DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P5DIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P5SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P5SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P5SEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P5REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P5REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P5REN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P6IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P6IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P6IN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P6OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P6OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P6OUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P6DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P6DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P6DIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P6SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P6SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P6SEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P6REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P6REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P6REN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P7IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P7IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P7IN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P7OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P7OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P7OUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P7DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P7DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P7DIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P7SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P7SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P7SEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P7REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P7REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P7REN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P8IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P8IN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P8IN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P8OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P8OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P8OUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P8DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P8DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P8DIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P8SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P8SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P8SEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool P8REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P8REN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"P8REN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool PAIN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"PAIN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool PAOUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAOUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"PAOUT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool PADIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PADIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"PADIR_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool PASEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASEL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"PASEL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool PAREN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAREN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"PAREN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool SVSCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SVSCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"SVSCTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TBCCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCTL3_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCTL4_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCTL4_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCTL4_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCTL5_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCTL5_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCTL5_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCTL6_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCTL6_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCTL6_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TBCCR3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCR3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCR3_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCR4_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCR4_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCR4_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCR5_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCR5_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCR5_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TBCCR6_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TBCCR6_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TBCCR6_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA1CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1CTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1CTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1BR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1BR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1BR0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1BR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1BR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1BR1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1MCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1MCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1MCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1STAT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1STAT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1STAT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1RXBUF_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1TXBUF_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1ABCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1ABCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1ABCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1IRTCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IRTCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1IRTCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCA1IRRCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IRRCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCA1IRRCTL_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1CTL0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1CTL1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1BR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1BR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1BR0_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1BR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1BR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1BR1_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1I2CIE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1I2CIE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1I2CIE_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1STAT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1STAT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1STAT_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1RXBUF_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1TXBUF_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1I2COA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1I2COA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1I2COA_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool UCB1I2CSA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB1I2CSA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"UCB1I2CSA_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TLV_CHECKSUM_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TLV_CHECKSUM_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TLV_CHECKSUM_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TLV_DCO_30_TAG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TLV_DCO_30_TAG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TLV_DCO_30_TAG_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TLV_DCO_30_LEN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TLV_DCO_30_LEN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TLV_DCO_30_LEN_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TLV_ADC12_1_TAG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TLV_ADC12_1_TAG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TLV_ADC12_1_TAG_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool TLV_ADC12_1_LEN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cout << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TLV_ADC12_1_LEN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cout << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"TLV_ADC12_1_LEN_arr" + llvm::utostr(++use_count), w);
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
