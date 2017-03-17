#include "klee/Arch.h"
#include "klee/ExecutionState.h"
#include "klee/Expr.h"
#include "klee/Interpreter.h"
#include "klee/Interrupt.h"

#include "klee/Internal/Module/KInstruction.h"
#include "klee/Internal/Module/KModule.h"

#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "AddressSpace.h"
#include "Memory.h"
#include "Common.h"


#include <iostream>
#include <fstream>

using namespace klee;
using namespace llvm;

SpecialMemory * Architecture::specialSemantics(const llvm::GlobalVariable& var){
	const std::string varName = var.getName();
  llvm::outs() << "Architecture::specialSemantics(): special semantics of " << varName << "\n";

	std::map<std::string, SpecialMemory *>::iterator naEnd =
	namedAddresses.end(); 
	for (std::map<std::string, SpecialMemory *>::iterator naItr =
	namedAddresses.begin(); 
	naItr != naEnd ; ++naItr){
		std::string name = naItr->first;
	}

	if (namedAddresses.find(varName) != namedAddresses.end()){
		SpecialMemory * res = namedAddresses[varName];
		return res;
	}

	if (regions.find(varName) != regions.end()){
		SpecialMemory * region = regions[varName];
		return region;
	}

	return NULL;
}

void Architecture::defineLayout(std::stringstream& tokens){
	std::string range;
	tokens >> range;
	char * end;
	memory_size = ::strtoll(range.c_str(), &end, 16);
	//memory_size = 0x2000;
  llvm::outs() << "Architecture::defineLayout(): memory is " << memory_size << " bytes\n";
	//TODO: is this right? It seems like we should want to do an allocateFixed
	memory = new uint8_t[memory_size](); //Zero-initialize memory
}

void Architecture::defineRange(std::stringstream& tokens){
	int start;
	int end;
	
	{ //Get the range start
		std::string token;
		tokens >> token;
		char * tokenEnd;
		start = ::strtoll(token.c_str(), &tokenEnd, 16);
	}

	{ //Get the range end
		std::string token;
		tokens >> token;
		char * tokenEnd;
		end = ::strtoll(token.c_str(), &tokenEnd, 16);
	}

	uint8_t flags = 0;
	while (tokens.good()){
		std::string token;
		tokens >> token;
		if (token == "flash"){
			flags |= MEMORY_FLASH;
			addFlashMemory(start, end);
		} else if (token == "RAM"){
			flags |= MEMORY_RAM;
		} else if (token == "peripheral"){
			flags |= MEMORY_SPECIAL;
		} else if (token == "persistent"){
			tokens >> token;
      llvm::outs() << "Architecture::defineLayout(): found a persistent list " << token << "\n";
			/*
			SpecialMemory * region = new SpecialMemory(start, end - start, token);
			regions[token] = region;
			*/
		} else {
			llvm::outs() << "Architecture::defineLayout(): UNKNOWN Range token " << token << "\n";
		}
	}

	for (int i = start ; i <= end ; i++){
		if (flags & MEMORY_FLASH){
      llvm::outs() << "Architecture::defineLayout(): flash at " << i << "\n";
		}
		memory[i] |= flags;
	}
}

//void Architecture::handleSRSet(ExecutionState& state, uint8_t value){
//void Architecture::handleSRSet(ExecutionState& state, uint16_t value){
void Architecture::handleSRSet(ExecutionState& state, ref<Expr> value){
	ObjectPair op;
  llvm::outs() << "Architecture::handleSRSet(): resolving address of SR\n";
	//state.addressSpace.resolveOne(statusRegister, op, this);
	state.addressSpace.resolveOne(state.statusRegisterAddress, op);

	const MemoryObject * mo = op.first;
	const ObjectState * os = op.second;
	ObjectState * wos = state.addressSpace.getWriteable(mo, os);
	unsigned offset = 0;
	//os->read8(0);
	//wos->write8(offset, value);
	wos->write(offset, value);
}

ref<Expr> Architecture::getSR(ExecutionState &state){
	ObjectPair op;
	//state.addressSpace.resolveOne(statusRegister, op, this);
	state.addressSpace.resolveOne(state.statusRegisterAddress, op);
	const ObjectState * os = op.second;
	//ref<Expr> value = os->read8(0);
	ref<Expr> value = os->read(0, Expr::Int16);
	return value;
}

/* Return the value of a 16-bit peripheral register (e.g. ACD10CTL0)
 *
 * Peripheral register is specifed by its address. In order to find the
 * address based on the peripheral's name you can use something like
 * that:
 *  static ref<ConstantExpr> ADC10CTL0_address =
 *         ConstantExpr::create(arch->namedAddresses["ADC10CTL0"]->base,
 *                                    Context::get().getPointerWidth());
 *
 * @param state Execution state for which we want to get the register value
 * @param periph_register_address Address of the peripheral
 * @return value of peripheral register */
ref<Expr> Architecture::getPeriphReg16(ExecutionState & state, ref<ConstantExpr> periph_register_address)
{
	ObjectPair op;
	state.addressSpace.resolveOne(periph_register_address, op);
	const ObjectState * os = op.second;
  ref<Expr> value = os->read(0, Expr::Int16);
	return value;
}

/* Set the value of a 16-bit peripheral register (e.g. ACD10CTL0)
 *
 * Peripheral register is specifed by its address. In order to find the
 * address based on the peripheral's name you can use something like
 * that:
 *  static ref<ConstantExpr> ADC10CTL0_address =
 *         ConstantExpr::create(arch->namedAddresses["ADC10CTL0"]->base,
 *                                    Context::get().getPointerWidth());
 *
 * @param state Execution state for which we want to set the register value
 * @param periph_register_address Address of the peripheral
 * @param new_value Value to set
 * @return value of peripheral register */
void Architecture::setPeriphReg16(ExecutionState & state,
                                       ref<ConstantExpr> periph_register_address,
                                       ref<Expr> new_value)
{
	ObjectPair op;
	state.addressSpace.resolveOne(periph_register_address, op);
	const MemoryObject * mo = op.first;
	const ObjectState * os = op.second;
	ObjectState * wos = state.addressSpace.getWriteable(mo, os);
        wos->write(0, new_value);
	return;
}

bool Architecture::handleIntrinsic(KInstruction * inst, llvm::Function * tgt, ExecutionState& state){
	std::string name = tgt->getName();
	if (name == "bis_status_register"){
		return true;
	}
	else if (name == "__nop"){
		return true;
	}
	else if (name == "__eint"){
		//handleSRSet(state, 0xFFFF);
		handleSRSet(state, ConstantExpr::alloc(0xffff, Expr::Int16));
		return true;
	}
	else if (name == "__dint"){
		handleSRSet(state, ConstantExpr::alloc(0x0000, Expr::Int16));
		return true;
	}
	else if (name == "__delay_cycles"){
		//Just a nop
		return true;
	}
	return false;
}

void Architecture::printFlags(uint64_t address){
	if (address >= memory_size){
		//FIXME: out of bounds
		return;
	}
	uint8_t byte = memory[address];
	if (byte & MEMORY_FLASH){
    llvm::outs() << "FLASH ";
	}
	if (byte & MEMORY_RAM){
    llvm::outs() << "RAM ";
	}
	if (byte & MEMORY_SPECIAL){
    llvm::outs() << "SPECIAL ";
	}
  llvm::outs() << "\n";
}

Architecture::Architecture(std::string plugpath, std::string memSpec, std::string intrSpec, std::string chip, const Module * module)
{
	addIntrinsics();

	//std::string layoutFile = plugpath + "/arch/" + chip + "/layout.txt"; 
	std::string layoutFile = plugpath + "/memorymodels/" + memSpec + "/" 
		+ chip + "/layout.txt";
	std::string memFile = plugpath + "/memorymodels/" + memSpec + "/" 
		+ chip + "/libregisters.so";
	std::string isrFile = plugpath + "/interrupts/" + intrSpec 
		+ "/libinterrupts.so";

	if (intrSpec.length() == 0){
		klee_error("No interrupt spec!");
	}

	if (memSpec.length() == 0){
		klee_error("No memory spec!");
	}
	
	intrHandle = dlopen(isrFile.c_str(), RTLD_LAZY);
	regHandle = dlopen(memFile.c_str(), RTLD_LAZY);

  llvm::outs() << "Architecture::Architecture(): register path " << memFile << "\n";
	llvm::outs() << "Architecture::Architecture(): interrupt path " << isrFile << "\n";

	if (!intrHandle){
    //exit(0);
    llvm::outs() << "Architecture::Architecture(): Could not open plugin library: " << dlerror() << "\n";
    //exit(0);
    llvm::outs() << "Architecture::Architecture(): Interrupt library not at " << isrFile << "\n";
		klee_error("Plugin error");
	}
  //exit(0);
 	if (!regHandle)
  {
    llvm::outs() << "Architecture::Architecture(): Could not open plugin library: " << dlerror() << "\n";
		llvm::outs() << "Architecture::Architecture(): Memory library not at " << memFile << "\n";
		klee_error("Plugin error");
	}

	flashWriter = (special_write_t)dlsym(regHandle,("flash_w"));
	flashReader = (special_read_t)dlsym(regHandle,("flash_r"));
	if (flashReader == NULL)
		klee_error("No flash reader!");

	std::ifstream lines;
	lines.open(layoutFile.c_str());
  llvm::outs() << "Architecture::Architecture(): layout file is " << layoutFile << "\n\n";
	if (lines.good())
  {
		std::string line;
		while (lines.good())
    {
			getline(lines, line);
			std::stringstream tokenizer(line);
			std::string head;
			tokenizer >> head;
			if (head == "#")
      {
				continue;
			} else if (head == "addr")
      {
				std::string name;
				tokenizer >> name;
				SpecialMemory * memory = new SpecialMemory(name, tokenizer, 
						regHandle, readMap, writeMap);
        llvm::outs() << "Architecture::Architecture(): Adding special memory for " << name << "\n";
				addSpecialMemory(memory);
				//uint64_t base = memory->base;
				//uint64_t size = memory->size;
				//llvm::errs() << "Add named location for " << memory->name << "@" << base << "\n";
			} else if (head == "layout")
      {
				defineLayout(tokenizer);
			} else if (head == "range")
      {
				defineRange(tokenizer);
			} else if (head == "interrupt")
      {
				std::string handlerName;
				std::string gateName;
				tokenizer >> handlerName; /* Name of the interruption handler (in the analyzed program) */
				tokenizer >> gateName; /* Function name interrupts.cpp */
        llvm::outs() << "Architecture::Architecture(): interrupt handler/gate " << handlerName << " " 
					<< gateName;
				dlerror(); //Reset errors
				interrupt_gate gate = (interrupt_gate) dlsym(intrHandle, gateName.c_str());
				if (gate == NULL){
					std::string err = "no gate for " + gateName;
					klee_error("%s\n", err.c_str());
				}

        /* We have ISR handler name. Let interate over the module's functions
         * and check if a function with the very same is present there. */
				Module::const_iterator funItr = module->begin();
				Module::const_iterator funEnd = module->end();
				bool foundUser = false;
				for ( ; funItr != funEnd ; ++funItr)
        {
					const llvm::Function * fun = funItr;
					if (fun->getName().compare(handlerName) == 0)
          {
						llvm::outs() << "Architecture::Architecture(): calls ISR ";
						llvm::outs() << fun->getName() << "\n";
						//interruptMap[fun] = gate;
						InterruptHandler * handler = new InterruptHandler(fun);
						handler->gate = gate;
						interruptVector.push_back(handler);
						foundUser = true;
					}
				}
				if (foundUser == false)
          llvm::outs() << "...not used\n";
			}
		}
	}
	pointer_size = 16; /* this is obvously specific to msp430 */
}

SpecialMemory::SpecialMemory(Architecture * arch, uint64_t base, 
uint64_t size, std::string name, ReadMap& readMap, WriteMap& writeMap){
	this->base = base;
	this->size = size;
	this->name = name;

	special_write_t writer = 
		(special_write_t)dlsym(arch->regHandle,(name+"_w").c_str());
	special_read_t reader = 
		(special_read_t)dlsym(arch->regHandle,(name+"_r").c_str());
	if (writer == NULL){
    llvm::outs() << "Architecture::Architecture(): writer is null for " << name+"_w" << "\n";
	}
	if (reader == NULL){
    llvm::outs() << "Architecture::Architecture(): reader is null for " << name+"_r" << "\n";
	}

	for (uint64_t i = 0 ; i < size ; i++){
		readMap[base + i] = reader;
		writeMap[base + i] = writer;
	}
}
