#!/usr/bin/python
import sys
import os

def writeChaosFun(output_file, pieces):
	reg = pieces[1]

	write_fun = """
extern "C" bool %s_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\\n";
	return true;
}""" % reg
	output_file.write(write_fun + "\n")

	read_fun = """
extern "C" ref<Expr> %s_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\\n";
	const Array * array = new Array(
		"%s_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}""" % (reg, reg)
	output_file.write(read_fun)
         
def writeChaosActual(output_file, pieces):
	reg = pieces[1]

	write_fun = """
extern "C" bool %s_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\\n";
    /* *** */
  
    return true;
  }
}""" % reg
	output_file.write(write_fun + "\n")

	read_fun = """
extern "C" ref<Expr> %s_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\\n";
    const Array * array = Array::CreateArray("%s_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}""" % (reg, reg)
	output_file.write(read_fun)

def writeFailFun(output_file, pieces):
	reg = pieces[1]

	write_fun = """
extern "C" bool %s_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "invalid write to " << __PRETTY_FUNCTION__ << "\\n";
	return false;
}""" % reg
	output_file.write(write_fun + "\n")

	read_fun = """
extern "C" ref<Expr> %s_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "invalid write to " << __PRETTY_FUNCTION__ << "\\n";
	return NULL;
}""" % (reg)
	output_file.write(read_fun)
	
def writeFuzzFun(output_file, pieces):
	reg = pieces[1]

	write_fun = """
extern "C" bool %s_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\\n";
	return true;
}""" % reg
	output_file.write(write_fun + "\n")

	read_fun = """
extern "C" ref<Expr> %s_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\\n";
	ref<Expr> res = ConstantExpr::alloc(rand(), w);
	return res;
}""" % (reg)
	output_file.write(read_fun)

def write_const_fun(output_file, reg, const_value):

	write_fun = 'extern "C" bool %s_w(ExecutionState* s, uint64_t addr, ref<Expr> v){\n' % reg
	write_fun+= '\tstd::cerr << "writing to " << __PRETTY_FUNCTION__ << "\\n";\n'
	write_fun+= '\treturn true;\n'
	write_fun+= "}\n\n"
	output_file.write(write_fun)
	read_fun = 'extern "C" ref<Expr> %s_r(ExecutionState* s, uint64_t addr, Expr::Width w){\n'%reg
	read_fun +='\tstatic unsigned int use_count;\n'
	read_fun +='\tstd::cerr << "reading from " << __PRETTY_FUNCTION__ << "\\n";\n' 
	read_fun += "\tref<Expr> res = ConstantExpr::create(%s, w);\n" % (const_value)
	read_fun +='\treturn res;\n'
	read_fun +="}\n\n"
	output_file.write(read_fun)


def writeConstFun(output_file, pieces):
	reg = pieces[1]
	const_value = pieces[4].split("=")[1]

	write_fun = 'extern "C" bool %s_w(ExecutionState* s, uint64_t addr, ref<Expr> v){\n' % reg
	write_fun+= '\tstd::cerr << "writing to " << __PRETTY_FUNCTION__ << "\\n";\n'
	write_fun+= '\treturn true;\n'
	write_fun+= "}\n\n"
	output_file.write(write_fun)
	read_fun = 'extern "C" ref<Expr> %s_r(ExecutionState* s, uint64_t addr, Expr::Width w){\n'%reg
	read_fun +='\tstatic unsigned int use_count;\n'
	read_fun +='\tstd::cerr << "reading from " << __PRETTY_FUNCTION__ << "\\n";\n' 
	read_fun += "\tref<Expr> res = ConstantExpr::create(%s, w);\n" % (const_value)
	read_fun +='\treturn res;\n'
	read_fun +="}\n\n"
	output_file.write(read_fun)

def writePassthroughFun(output_file, pieces):
	reg = pieces[1]

	write_fun ="""
extern "C" bool %s_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\\n";

	ref<ConstantExpr> addrExpr = ConstantExpr::create(addr, v->getWidth());
	ObjectPair op;
	s->addressSpace.resolveOne(addrExpr, op, NULL);
	const MemoryObject * mo = op.first;
	const ObjectState * os = op.second;
	ObjectState * wos = s->addressSpace.getWriteable(mo, os);
	ref<Expr> offset = 
		mo->getOffsetExpr(addrExpr);
	wos->write(offset, v);
	return true;
}""" % reg
	output_file.write(write_fun + "\n")

	read_fun = """
extern "C" ref<Expr> %s_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;

	ref<ConstantExpr> addrExpr = ConstantExpr::create(addr, w);
	ObjectPair op;
	s->addressSpace.resolveOne(addrExpr, op, NULL);
	const MemoryObject * mo = op.first;
	const ObjectState * os = op.second;
	ref<Expr> offset = mo->getOffsetExpr(addrExpr);
	return os->read(offset, w);

	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\\n";
	ref<Expr> res = ConstantExpr::create(0x01, w);
	return res;
}""" % reg
	output_file.write(read_fun)

if __name__ == "__main__":
	fuzz = False
	fail = False
	chaos = False
	if len(sys.argv) >= 2:
		if sys.argv[1] == 'fuzz':
			fuzz = True
		if sys.argv[1] == 'fail':
			fail = True
		if sys.argv[1] == 'chaos':
			chaos = True
		

	layout = "layout.txt"
	output_name = "registers.cpp"
	layout_stream = open(layout, "r")
	output_file = open(output_name, "w")

	#Print the header on the output stream
	output_file.write("""
#include <iostream>
#include "klee/klee.h"
#include "klee/ExecutionState.h"
#include "klee/Internal/Module/KModule.h"
#include "klee/Internal/Module/KInstruction.h"
#include "Common.h"
#include "Memory.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"

using namespace klee;

"""
	)

	if fuzz == True:
		writeFuzzFun(output_file, ["flash", "flash"])
        elif chaos == True:
		writeChaosFun(output_file, ["flash", "flash"])
	else:
		writeChaosActual(output_file, ["flash", "flash"])

	for line in layout_stream:
		line = line.strip()
		pieces = line.split()
		#if len(pieces) < 3:
		#	print "junk line", line
		if pieces[0] == "addr":
			print "register", pieces[1], "at", pieces[2], "of", pieces[3], "bytes"
			reg = pieces[1]
			if len(pieces) > 4:
				if pieces[4].startswith("const_val"):
					writeConstFun(output_file, pieces)
				elif pieces[4] == "chaos":
					writeChaosFun(output_file, pieces)
				elif pieces[4] == "passthrough":
					writePassthroughFun(output_file, pieces)
			elif fuzz == True:
				writeFuzzFun(output_file, pieces)
			elif fail == True:	
				writeFailFun(output_file, pieces)
                        elif chaos == True:
				writeChaosFun(output_file, pieces)
                        else:
				writeChaosActual(output_file, pieces)

		elif pieces[0] == "interrupt":
			continue
		else:
			print "ignoring directive \"%s\"" % pieces[0]

	try:
		aux_registers = open("aux_registers.cpp")
		output_file.write("\n//-----AUX REGISTER FUNCTIONS-----//\n")
		for line in aux_registers:
			output_file.write(line)
	except IOError:
		print "couldn't open aux registers"

