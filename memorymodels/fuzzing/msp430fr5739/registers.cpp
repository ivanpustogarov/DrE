
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
extern "C" bool ADC10CTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10CTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10CTL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10CTL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10CTL2_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL2_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10CTL2_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL2_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10CTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10CTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10LO_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10LO_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10LO_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10LO_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10LO_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10LO_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10HI_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10HI_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10HI_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10HI_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10HI_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10HI_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10MCTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10MCTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10MCTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10MCTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10MCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10MCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10MEM0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10MEM0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10MEM0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10MEM0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10MEM0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10MEM0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IE_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IE_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IE_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IE_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IFG_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IFG_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IFG_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IFG_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IV_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IV_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IV_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IV_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool ADC10IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC10IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL2_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL2_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL2_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL2_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL3_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL3_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL3_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL3_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL4_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL4_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL4_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL4_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL4_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL4_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL5_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL5_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL5_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL5_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL5_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL5_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL6_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL6_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL6_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL6_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CSCTL6_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CSCTL6_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL2_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL2_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL2_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL2_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL3_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL3_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL3_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL3_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDINT_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDINT_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDINT_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDINT_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDINT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDINT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDIV_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDIV_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDIV_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDIV_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CDIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CDIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCDI_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCDI_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCDI_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCDI_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCDI_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCDI_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCDIRB_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCDIRB_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCDIRB_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCDIRB_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCDIRB_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCDIRB_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCINIRES_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCINIRES_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCINIRES_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCINIRES_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCINIRES_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCINIRES_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCRESR_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCRESR_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCRESR_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCRESR_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool CRCRESR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRCRESR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL2_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL2_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL2_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL2_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL3_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL3_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL3_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL3_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL4_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL4_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL4_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL4_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMACTL4_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMACTL4_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMAIV_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMAIV_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMAIV_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMAIV_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMAIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMAIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA0CTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA0CTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA0CTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA0CTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA0CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA0CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA0SA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA0SA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA0DA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA0DA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA0SZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA0SZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA1CTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA1CTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA1CTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA1CTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA1CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA1CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA1SA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA1SA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA1DA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA1DA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA1SZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA1SZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA2CTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA2CTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA2CTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA2CTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA2CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA2CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA2SA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA2SA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA2DA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA2DA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool DMA2SZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> DMA2SZ_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool FRCTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FRCTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool FRCTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FRCTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool FRCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> FRCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool GCCTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> GCCTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool GCCTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> GCCTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool GCCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> GCCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool GCCTL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> GCCTL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool GCCTL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> GCCTL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool GCCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> GCCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUCTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUCTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUCTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUCTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUCTL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUCTL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUCTL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUCTL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUSEG_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUSEG_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUSEG_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUSEG_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUSEG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUSEG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUSAM_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUSAM_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUSAM_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUSAM_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPUSAM_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPUSAM_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RESLO_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RESLO_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RESLO_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RESLO_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RESLO_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RESLO_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RESHI_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RESHI_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RESHI_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RESHI_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RESHI_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RESHI_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SUMEXT_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SUMEXT_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SUMEXT_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SUMEXT_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SUMEXT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SUMEXT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32L_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32L_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32L_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32L_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32H_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32H_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32H_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32H_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS32L_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS32L_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS32L_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS32L_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS32L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS32L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS32H_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS32H_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS32H_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS32H_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPYS32H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPYS32H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC32L_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC32L_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC32L_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC32L_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC32L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC32L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC32H_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC32H_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC32H_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC32H_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MAC32H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MAC32H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS32L_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS32L_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS32L_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS32L_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS32L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS32L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS32H_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS32H_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS32H_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS32H_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MACS32H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MACS32H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2L_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2L_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2L_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2L_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2H_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2H_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2H_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2H_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool OP2H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> OP2H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES2_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES2_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES2_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES2_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES3_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES3_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES3_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES3_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RES3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RES3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32CTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32CTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32CTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32CTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool MPY32CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> MPY32CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PMMCTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PMMCTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PMMCTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PMMCTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PMMCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PMMCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PMMIFG_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PMMIFG_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PMMIFG_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PMMIFG_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PMMIFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PMMIFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PM5CTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PM5CTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PM5CTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PM5CTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PM5CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PM5CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIN_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIN_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIN_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIN_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAOUT_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAOUT_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAOUT_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAOUT_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAOUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAOUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PADIR_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PADIR_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PADIR_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PADIR_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PADIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PADIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAREN_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAREN_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAREN_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAREN_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAREN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAREN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASEL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASEL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASEL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASEL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASEL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASEL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASEL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASEL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASEL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASEL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASEL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASEL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASELC_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASELC_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASELC_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASELC_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PASELC_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PASELC_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIES_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIES_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIES_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIES_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIES_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIES_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIE_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIE_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIE_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIE_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIFG_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIFG_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIFG_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIFG_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PAIFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PAIFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P1IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P1IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P2IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P2IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIN_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIN_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIN_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIN_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBOUT_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBOUT_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBOUT_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBOUT_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBOUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBOUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBDIR_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBDIR_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBDIR_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBDIR_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBDIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBDIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBREN_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBREN_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBREN_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBREN_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBREN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBREN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSEL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSEL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSEL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSEL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSEL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSEL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSEL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSEL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSEL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSEL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSEL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSEL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSELC_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSELC_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSELC_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSELC_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBSELC_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBSELC_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIES_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIES_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIES_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIES_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIES_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIES_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIE_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIE_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIE_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIE_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIFG_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIFG_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIFG_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIFG_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PBIFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PBIFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P3IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P3IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool P4IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> P4IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJIN_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJIN_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJIN_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJIN_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJIN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJIN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJOUT_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJOUT_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJOUT_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJOUT_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJOUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJOUT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJDIR_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJDIR_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJDIR_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJDIR_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJDIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJDIR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJREN_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJREN_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJREN_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJREN_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJREN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJREN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSEL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSEL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSEL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSEL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSEL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSEL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSEL1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSEL1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSEL1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSEL1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSEL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSEL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSELC_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSELC_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSELC_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSELC_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool PJSELC_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> PJSELC_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool REFCTL0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> REFCTL0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool REFCTL0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> REFCTL0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool REFCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> REFCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCCTL01_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCCTL01_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCCTL01_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCCTL01_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCCTL01_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCCTL01_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCCTL23_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCCTL23_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCCTL23_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCCTL23_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCCTL23_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCCTL23_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS0CTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS0CTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS0CTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS0CTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS0CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS0CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS1CTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS1CTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS1CTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS1CTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS1CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS1CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCPS_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCPS_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCTIM0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCTIM0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCTIM0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCTIM0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCTIM0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCTIM0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCTIM1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCTIM1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCTIM1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCTIM1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCTIM1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCTIM1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCDATE_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCDATE_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCDATE_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCDATE_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCDATE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCDATE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCYEAR_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCYEAR_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCYEAR_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCYEAR_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCYEAR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCYEAR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCAMINHR_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCAMINHR_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCAMINHR_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCAMINHR_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCAMINHR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCAMINHR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCADOWDAY_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCADOWDAY_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCADOWDAY_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCADOWDAY_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool RTCADOWDAY_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> RTCADOWDAY_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool BIN2BCD_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> BIN2BCD_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool BCD2BIN_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> BCD2BIN_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRIE1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRIE1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRIE1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRIE1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRIE1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRIE1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRIFG1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRIFG1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRIFG1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRIFG1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRIFG1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRIFG1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRRPCR_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRRPCR_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRRPCR_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRRPCR_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SFRRPCR_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SFRRPCR_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSCTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSCTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSCTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSCTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSBSLC_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSBSLC_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSBSLC_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSBSLC_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSBSLC_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSBSLC_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBC_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBC_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBC_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBC_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBC_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBC_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBI0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBI0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBI0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBI0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBI0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBI0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBI1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBI1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBI1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBI1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBI1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBI1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBO0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBO0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBO0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBO0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBO0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBO0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBO1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBO1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBO1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBO1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSJMBO1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSJMBO1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSBERRIV_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSBERRIV_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSBERRIV_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSBERRIV_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSBERRIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSBERRIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSUNIV_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSUNIV_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSUNIV_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSUNIV_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSUNIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSUNIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSSNIV_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSSNIV_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSSNIV_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSSNIV_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSSNIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSSNIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSRSTIV_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSRSTIV_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSRSTIV_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSRSTIV_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool SYSRSTIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> SYSRSTIV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0CCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0CCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0R_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0R_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0CCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0CCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0CCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0CCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA0EX0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA0EX0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1CCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1CCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1CCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1CCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1R_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1R_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1CCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1CCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1CCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1CCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1CCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1CCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TA1EX0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TA1EX0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0CCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0CCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0CCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0CCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0R_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0R_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0CCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0CCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0CCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0CCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0CCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0CCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0EX0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0EX0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB0IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB0IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1CCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1CCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1CCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1CCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1R_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1R_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1CCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1CCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1CCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1CCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1CCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1CCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB1EX0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB1EX0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2CCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2CCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2CCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2CCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2R_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2R_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2CCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2CCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2CCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2CCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2CCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2CCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool TB2EX0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> TB2EX0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0CTLW0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0CTLW0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0CTLW0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0CTLW0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0CTLW0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0CTLW0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0CTLW1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0CTLW1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0CTLW1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0CTLW1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0CTLW1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0CTLW1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0BRW_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0BRW_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0BRW_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0BRW_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0BRW_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0BRW_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0MCTLW_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0MCTLW_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0MCTLW_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0MCTLW_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0MCTLW_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0MCTLW_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0STATW_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0STATW_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0RXBUF_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0RXBUF_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0RXBUF_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0RXBUF_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0TXBUF_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0TXBUF_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0TXBUF_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0TXBUF_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0ABCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0ABCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IRCTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IRCTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IRCTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IRCTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IRCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IRCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IE_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IE_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IE_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IE_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IFG_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IFG_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IFG_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IFG_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA0IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA0IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0CTLW0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0CTLW0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0CTLW0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0CTLW0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0CTLW0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0CTLW0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0CTLW1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0CTLW1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0CTLW1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0CTLW1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0CTLW1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0CTLW1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0BRW_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0BRW_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0BRW_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0BRW_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0BRW_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0BRW_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0STATW_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0STATW_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0STATW_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0STATW_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0STATW_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0STATW_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0TBCNT_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0TBCNT_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0TBCNT_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0TBCNT_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0TBCNT_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0TBCNT_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0RXBUF_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0RXBUF_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0RXBUF_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0RXBUF_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0TXBUF_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0TXBUF_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0TXBUF_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0TXBUF_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA2_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA2_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA2_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA2_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA3_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA3_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA3_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA3_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2COA3_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2COA3_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0ADDRX_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0ADDRX_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0ADDRX_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0ADDRX_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0ADDRX_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0ADDRX_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0ADDMASK_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0ADDMASK_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0ADDMASK_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0ADDMASK_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0ADDMASK_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0ADDMASK_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2CSA_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2CSA_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2CSA_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2CSA_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0I2CSA_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0I2CSA_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0IE_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0IE_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0IE_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0IE_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0IFG_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0IFG_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0IFG_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0IFG_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCB0IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCB0IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1CTLW0_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1CTLW0_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1CTLW0_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1CTLW0_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1CTLW0_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1CTLW0_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1CTLW1_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1CTLW1_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1CTLW1_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1CTLW1_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1CTLW1_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1CTLW1_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1BRW_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1BRW_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1BRW_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1BRW_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1BRW_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1BRW_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1MCTLW_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1MCTLW_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1MCTLW_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1MCTLW_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1MCTLW_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1MCTLW_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1STATW_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1STATW_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1RXBUF_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1RXBUF_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1RXBUF_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1RXBUF_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1TXBUF_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1TXBUF_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1TXBUF_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1TXBUF_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1ABCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1ABCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IRCTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IRCTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IRCTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IRCTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IRCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IRCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IE_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IE_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IE_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IE_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IE_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IFG_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IFG_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IFG_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IFG_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool UCA1IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> UCA1IV_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool WDTCTL_L_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> WDTCTL_L_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}
extern "C" bool WDTCTL_H_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> WDTCTL_H_r(ExecutionState* s, uint64_t addr, Expr::Width w){
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