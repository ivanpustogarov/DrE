#!/usr/bin/python
import sys
import os

def writeInstrInterrupt(output_file, interrupt, gate_fun):
	output_file.write("""
extern "C" bool %s(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\\n";
}
return true;
}""" % (gate_fun))

def writeBBLInterrupt(output_file, interrupt, gate_fun):
	output_file.write("""
extern "C" bool %s(klee::Architecture * arch, klee::ExecutionState * state){
if (state->interruptFun){ 
	return false;
}
std::cerr << "Enter BBL interrupt check\\n";

KInstruction * pcInst = state->prevPC;
//not as basic block head
if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
	std::cerr << "Not a BBL Head\\n";
	return false;
}

klee::ref<Expr> sr = arch->getSR(*state);
if (ConstantExpr * ce = dyn_cast<ConstantExpr>(sr)){
	uint8_t value = ce->getZExtValue();
	uint16_t big_value = value;
	std::cerr << "STATUS REGISTER VALUE in " << __PRETTY_FUNCTION__ << " has value " 
						<< std::hex << big_value << "\\n";
	if (value & GIE){
		return true;
	}
	return false;
} else {
	std::cerr << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\\n";
}
return true;
}""" % (gate_fun))

def writeNeverInterrupt(output_file, interrupt, gate_fun):
	output_file.write("""
extern "C" bool %s(klee::Architecture * arch, klee::ExecutionState * state){
	return false;
}""" % gate_fun)

def writeCPUOFFInterrupt(output_file, interrupt, gate_fun):
	if(gate_fun != "check_ADC10"):
		output_file.write("""
extern "C" bool %s (klee::Architecture * arch, klee::ExecutionState * state, TimingSolver *solver)
{
  if (state->interruptFun){ 
    return false;
  }
  llvm::outs() << "Enter BBL interrupt check\\n";

  KInstruction * pcInst = state->prevPC;
  //not as basic block head
  if (pcInst && pcInst->inst && pcInst->inst->getParent()->getFirstNonPHI() != pcInst->inst){
    llvm::outs() << "Not a BBL Head\\n";
    return false;
  }

  if(is_cpuoff(arch, state, solver))
    return true;
  else
    return false;
}
""" % (gate_fun))

def usage():	
	sys.stderr.write("USAGE: dummy_interrupts.py <path_to_interrupt_file> <output_dir> <mode>\n")
	sys.stderr.write("       modes are: never, bll, instruction, cpuoff\n")
	sys.exit(1)


if __name__ == "__main__":
	if len(sys.argv) < 4:
		usage()
	layout = sys.argv[1]
	output_dir = sys.argv[2]

	modes = ['never', 'bbl', 'instruction', 'cpuoff']
	if len(sys.argv) < 4:
		usage()

	mode = sys.argv[3]
	if not mode in modes:
		usage()

	output_name = os.path.join(output_dir, "interrupts.cpp")
	layout_stream = open(layout, "r")
	output_file = open(output_name, "w")

	output_file.write("""
#include <iostream>
#include "klee/klee.h"
#include "klee/ExecutionState.h"
#include "klee/Arch.h"
#include "klee/Solver.h"
#include "klee/Internal/Module/KModule.h"
#include "klee/Internal/Module/KInstruction.h"
#include "Memory.h"
#include "TimingSolver.h"
#include "klee/Expr.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"

/* #define C                   (0x0001) */
/* #define Z                   (0x0002) */
/* #define N                   (0x0004) */
/* #define V                   (0x0100) */
/* #define GIE                 (0x0008) */
/* #define CPUOFF              (0x0010) */
/* #define OSCOFF              (0x0020) */
/* #define SCG0                (0x0040) */
/* #define SCG1                (0x0080) */

/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)

/************************************************************
* STATUS REGISTER BITS
************************************************************/

#define C                      (0x0001)
#define Z                      (0x0002)
#define N                      (0x0004)
#define V                      (0x0100)
#define GIE                    (0x0008)
#define CPUOFF                 (0x0010)
#define OSCOFF                 (0x0020)
#define SCG0                   (0x0040)
#define SCG1                   (0x0080)

#define LPM0                   (CPUOFF)
#define LPM1                   (SCG0+CPUOFF)
#define LPM2                   (SCG1+CPUOFF)
#define LPM3                   (SCG1+SCG0+CPUOFF)
#define LPM4                   (SCG1+SCG0+OSCOFF+CPUOFF)

/* ADC10CTL0 */
#define ADC10SC                (0x001)        /* ADC10 Start Conversion */
#define ENC                    (0x002)        /* ADC10 Enable Conversion */
#define ADC10IFG               (0x004)        /* ADC10 Interrupt Flag */
#define ADC10IE                (0x008)        /* ADC10 Interrupt Enalbe */
#define ADC10ON                (0x010)        /* ADC10 On/Enable */

/* ADC10CTL1 */
#define SHS_0                  (0x0000)       /* ADC10SC */
#define SHS_1                  (0x0400)       /* TA3 OUT1 */
#define SHS_2                  (0x0800)       /* TA3 OUT0 */
#define SHS_3                  (0x0C00)       /* TA3 OUT2 */

using namespace klee;

/* Check if both GIE and CPUOFF are set. 
 * return true if yes (and reset CPUOFF flag), false otherwise*/
extern "C" bool is_cpuoff(klee::Architecture * arch, klee::ExecutionState * state, TimingSolver *solver)
{
  bool ret = false;
  klee::ref<Expr> sr = arch->getSR(*state);
  {
    llvm::outs() << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\\n";
    ref<ConstantExpr> gie_expr = ConstantExpr::create(GIE,Expr::Int16);
    ref<Expr> check1 = AndExpr::create(sr, gie_expr);
    bool result;
    /* Check if GIE is set */
    bool success = solver->mayBeTrue(*state, check1, result);
    assert(success && "FIXME: Unhandled solver failure");
    if(result)
    {    
      llvm::outs() << "GIE is enabled\\n";

      ref<Expr> check2 = AndExpr::create(sr,ConstantExpr::create(CPUOFF,Expr::Int16));
      /* Check if CPUOFF is set */
      success = solver->mayBeTrue(*state, check2, result);
      assert(success && "FIXME: Unhandled solver failure");
      if(result)
      {    
        llvm::outs() << "CPUOFF is set\\n";
        /* Reset CPUOFF */
        ref<Expr> CPUOFF_reset_mask = ConstantExpr::alloc(0xFFEF, Expr::Int16);
        ref<Expr> new_val = AndExpr::create(sr, CPUOFF_reset_mask);
        arch->handleSRSet(*state, new_val);
        ret = true;
      } else 
        llvm::outs() << "CPUOFF is NOT set\\n";
    } else 
        llvm::outs() << "GIE is NOT set\\n";
  }
  return ret; 
}



extern "C" bool check_ADC10(klee::Architecture * arch, klee::ExecutionState * state, TimingSolver *solver)
{
  if (state->interruptFun)
  {
    return false;
  }
  llvm::outs() << "check_ADC10(): Enter CPUOFF interrupt check\\n";

  KInstruction * pcInst = state->prevPC;

  bool ret = false;
  klee::ref<Expr> sr = arch->getSR(*state);
  {
    llvm::outs() << "SYMBOLIC STATUS REGISTERi at " << __PRETTY_FUNCTION__ << "\\n";
    ref<ConstantExpr> gie_expr = ConstantExpr::create(GIE,Expr::Int16);
    ref<Expr> check1 = AndExpr::create(sr, gie_expr);
    bool result; 
    bool success = solver->mayBeTrue(*state, check1, result);
    assert(success && "FIXME: Unhandled solver failure");
    if(result)
    {
      llvm::outs() << "GIE is enabled\\n";

      ref<Expr> check2 = AndExpr::create(sr,ConstantExpr::create(CPUOFF,Expr::Int16));
      success = solver->mayBeTrue(*state, check2, result);
      assert(success && "FIXME: Unhandled solver failure");
      if(result)
      {
        llvm::outs() << "CPUOFF is set\\n";
        ref<Expr> CPUOFF_reset_mask = ConstantExpr::alloc(0xFFEF, Expr::Int16);
        ref<Expr> new_val = AndExpr::create(sr, CPUOFF_reset_mask);
        arch->handleSRSet(*state, new_val);
        ret = true;
      } else
        llvm::outs() << "CPUOFF is NOT set\\n";

      static ref<ConstantExpr> ADC10CTL0_address =
                  ConstantExpr::create(arch->namedAddresses["ADC10CTL0"]->base,
                                       Context::get().getPointerWidth());
      static ref<ConstantExpr> ADC10CTL1_address = 
                  ConstantExpr::create(arch->namedAddresses["ADC10CTL0"]->base,
                                      Context::get().getPointerWidth());
      klee::ref<Expr>  ADC10CTL0_val = arch->getPeriphReg16(*state, ADC10CTL0_address);
      klee::ref<Expr>  ADC10CTL1_val = arch->getPeriphReg16(*state, ADC10CTL1_address);


      ref<Expr> check3 = AndExpr::create(ADC10CTL0_val,ConstantExpr::create(ADC10SC,Expr::Int16));
      success = solver->mayBeTrue(*state, check3, result);
      if (result) /* and if SC bit (it's bit 0) is set */
      {
        llvm::outs() << "SC is set\\n";
        ref<Expr> SC_reset_mask = ConstantExpr::alloc(0xfffE, Expr::Int16);
        ref<Expr> new_val = AndExpr::create(ADC10CTL0_val, SC_reset_mask);
        arch->setPeriphReg16(*state, ADC10CTL0_address, new_val);
        llvm::outs() << "new ADC10MCTL0 value = " << new_val << "\\n";
        ret = true;
      } else
        llvm::outs() << "SC is NOT set\\n";
    } else
        llvm::outs() << "GIE is NOT set\\n";

  }
  if(!ret)
    return false;
  //assert(ret && "ret should be true at this point --> bug");
  /* We have ADC10 interrupt => write new symbolic value to the
   * ADC10MEM register */
        static unsigned int use_count;
  static ref<ConstantExpr> ADC10MEM_address =
               ConstantExpr::create(arch->namedAddresses["ADC10MEM"]->base,
                                     Context::get().getPointerWidth());
        const Array * array = Array::CreateArray("ADC10MEM_arr" + llvm::utostr(++use_count), Expr::Int16);
        ref<Expr> new_adc10_value = Expr::createTempRead(array, Expr::Int16, true);
  arch->setPeriphReg16(*state, ADC10MEM_address, new_adc10_value);

  klee::ref<Expr>  new_val0 = arch->getPeriphReg16(*state, ADC10MEM_address);
  llvm::outs() << "new ADC10MEM value = " << new_val0 << "\\n";

  return ret;

}

""")

	for line in layout_stream:
		if len(line) == 0:
			continue
		interrupt = line
		gate_fun = "check_" + line
		if mode == "instruction":
			writeInstrInterrupt(output_file, interrupt, gate_fun)
		elif mode == "never":
			writeNeverInterrupt(output_file, interrupt, gate_fun)
		elif mode == 'bbl':
			writeBBLInterrupt(output_file, interrupt, gate_fun)
		elif mode == 'cpuoff':
			writeCPUOFFInterrupt(output_file, interrupt, gate_fun)
		else:	
			usage()
