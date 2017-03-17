#ifndef KLEE_ARCHICTURE_EXT
#define KLEE_ARCHICTURE_EXT

#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/StringExtras.h"
//#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
//#include "llvm/Support/CallSite.h"

#include "Interrupt.h"

#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <dlfcn.h>

#include "Expr.h"

#define MEMORY_FLASH   (1 << 0) 
#define MEMORY_RAM     (1 << 1)
#define MEMORY_SPECIAL (1 << 2)

namespace klee{

class ExecutionState;
//class KInstruction;
struct KInstruction;
class KModule;
class Executor;
class Architecture;

//typedef void (*flash_write_t)(ExecutionState *, uint64_t, ref<Expr> value);
//typedef ref<Expr> (*flash_read_t)(ExecutionState *, uint64_t, Expr::Width w);
typedef bool (*special_write_t)(ExecutionState *, uint64_t, ref<Expr> value, bool pass_through);
typedef ref<Expr> (*special_read_t)(ExecutionState*, uint64_t, Expr::Width w,  bool get_fresh_symbolics);
typedef std::map<uint64_t, special_write_t> WriteMap;
typedef std::map<uint64_t, special_read_t> ReadMap;


class SpecialMemory{
	public:
		uint64_t base;
		uint64_t size;
		std::string name;

		SpecialMemory(std::string nameIn, std::stringstream& tokens, 
		void * regHandle, ReadMap& readMap, WriteMap& writeMap)
		: name(nameIn){
			std::string addrTok;
			tokens >> addrTok;
			//address = std::strtoll(i->getName().str().c_str()+1, &end, 0);
			{
				const char * addrTokStart = addrTok.c_str();
				char * addrTokEnd;
				base = ::strtoll(addrTokStart, &addrTokEnd, 16);
			}

			tokens >> addrTok;
			{
				const char * addrTokStart = addrTok.c_str();
				char * addrTokEnd;
				size = ::strtoll(addrTokStart, &addrTokEnd, 16);
			}

			//get the reader and write function
			special_write_t writer = 
				(special_write_t)dlsym(regHandle,(name+"_w").c_str());
			special_read_t reader = 
				(special_read_t)dlsym(regHandle,(name+"_r").c_str());
			if (writer == NULL){
				std::cerr << "writer is null for " << name+"_w" << "\n";
			}
			if (reader == NULL){
				std::cerr << "reader is null for " << name+"_r" << "\n";
			}

			for (uint64_t i = 0 ; i < size ; i++){
				readMap[base + i] = reader;
				writeMap[base + i] = writer;
			}

		}

		SpecialMemory(Architecture * arch, uint64_t base, uint64_t size, 
			std::string name, ReadMap& readMap, WriteMap& writeMap);
};

class FlashMemory{
	public:
		uint64_t begin;
		uint64_t end;

		FlashMemory(uint64_t beginIn, uint64_t endIn){
			begin = beginIn;
			end = endIn;
		}	
};

/* TODO: add better description.
 * This class defines an MSP430 chip memory layout: memory address for
 * peripheral devices, and function which are used to read/write from them.
 */
class Architecture{
	public:
    uint64_t pointer_size;
		std::map<std::string, SpecialMemory *> namedAddresses;
		std::map<std::string, SpecialMemory *> regions;
		//std::map<uint16_t, llvm::Function *> intrinsics;
		std::vector<FlashMemory *> flashSegs;
		std::set<llvm::Function *> intrinsics;
		std::set<std::string> intrinsic_names;
		uint8_t * memory;
		uint64_t memory_size;
		uint16_t heap_min;

		ReadMap readMap;
		WriteMap writeMap;
		InterruptVector interruptVector;

		special_read_t flashReader;
		special_write_t flashWriter;

    /* We moved this field to ExecutionState, as arch can be shared between different Executors
		ref<ConstantExpr> statusRegisterAddress;  We allocate a memory object for
                                                the status register, and keep its address
                                                in this variable
    */
		//uint16_t SRAddress; /* not really used anywhere */

		void * regHandle;
		void* intrHandle;

		bool isIntrinsic(llvm::Function * fun){
			std::string name = fun->getName().str();
			std::set<std::string>::iterator nameItr = intrinsic_names.find(name);

			bool inIntrinsicNames = false;
			if (nameItr != intrinsic_names.end()){
				inIntrinsicNames = true;
			} else {
				inIntrinsicNames = false;
			}

			return inIntrinsicNames;
		}

		bool handleIntrinsic(KInstruction * inst, llvm::Function * tgt, ExecutionState& state);
		//void handleSRSet(ExecutionState& state, uint8_t value);
		//void handleSRSet(ExecutionState& state, uint16_t value);
    void handleSRSet(ExecutionState& state, ref<Expr> value);

		void addIntrinsics(){
			intrinsic_names.insert("__nop");
			intrinsic_names.insert("__dint");
			intrinsic_names.insert("__eint");
			intrinsic_names.insert("__read_status_register");
			intrinsic_names.insert("__get_interrupt_state");
			intrinsic_names.insert("__write_status_register");
			intrinsic_names.insert("__set_interrupt_state");
			intrinsic_names.insert("__read_stack_pointer");
			intrinsic_names.insert("__write_stack_pointer");
			intrinsic_names.insert("__bic_status_register");
			intrinsic_names.insert("__bis_status_register");
			intrinsic_names.insert("__bic_status_register_on_exit");
			intrinsic_names.insert("__bis_status_register_on_exit");
			intrinsic_names.insert("__builtin_frame_address");
			intrinsic_names.insert("__builtin_return_address");
			intrinsic_names.insert("__delay_cycles");
			intrinsic_names.insert("__swap_bytes");
			intrinsic_names.insert("__get_watchdog_clear_value");
			intrinsic_names.insert("__set_watchdog_clear_value");
			intrinsic_names.insert("__watchdog_clear");
		}

		Architecture(std::string plugPath, std::string memSpec, std::string intrSpec, std::string chip, const llvm::Module * module);

		SpecialMemory * specialSemantics(const llvm::GlobalVariable& var);
		void defineLayout(std::stringstream& tokens);
		void defineRange(std::stringstream& tokens);
		void printFlags(uint64_t address);

		void addFlashMemory(uint64_t start, uint64_t end){
			for (uint64_t i = start; i <= end; i++){
				memory[i] |= MEMORY_SPECIAL;
				memory[i] |= MEMORY_FLASH;
			}
			flashSegs.push_back(new FlashMemory(start, end));
		}
		void addSpecialMemory(SpecialMemory * memoryLoc){
			std::cerr << "Adding " << memoryLoc->name << " at " << std::hex << "0x" << memoryLoc->base << "\n";
			namedAddresses[memoryLoc->name] = memoryLoc;
			for (uint64_t i = 0; i < memoryLoc->size; i++){
				memory[memoryLoc->base + i] |= MEMORY_SPECIAL;
			}
			//std::cerr << "Add named memory loc " << memoryLoc->name << "\n";
			//memory->allocate(size, :q
		}

		ref<Expr> getSR(ExecutionState & state);
    ref<Expr> getPeriphReg16(ExecutionState &state, ref<ConstantExpr> periph_register_address);
    void setPeriphReg16(ExecutionState & state, ref<ConstantExpr> periph_register_address, ref<Expr> new_value);

};

class NoArch : public Architecture{
	public:
		const SpecialMemory * specialSemantics(const llvm::GlobalVariable*& var) {
			return NULL;
		}
};

}

#endif
