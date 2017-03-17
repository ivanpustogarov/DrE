//===-- MemoryManager.cpp -------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Common.h"

#include "CoreStats.h"
#include "Memory.h"
#include "MemoryManager.h"

#include "klee/ExecutionState.h"
#include "klee/Expr.h"
#include "klee/Solver.h"

#include "llvm/Support/CommandLine.h"

using namespace klee;

/***/

MemoryManager::~MemoryManager() { 
  while (!objects.empty()) {
    MemoryObject *mo = *objects.begin();
    if (!mo->isFixed)
      free((void *)mo->host_address);
    objects.erase(mo);
    delete mo;
  }
}


///* Allocate new memory with malloc. Find a free memory chunk of size
// * <size> in the state's address space and mark it reserved.
// *
// * We first use malloc() to allocate the memory on the host (this is the
// * where we will actually store the data). We then need to map this
// * memory on the guest: we iterate over state->addressSpace.objects
// * guest_addresses and try to find a free memory region of size bigger
// * then <size> We don't differentiate between the heap and the stack: we
// * put everything into one big chunk 
// *
// * @param size Size of the new memory to allcoate
// * @param isLocal True if the object is local (i.e. it goes to the stack)
// * @param isGlobal True if the object is gloabl (i.e. does not go to the stack)
// * @param allocSite Allocation instruction for this alloc
// * @param arch Architecture for the current device
// * @param state The state Address Space of which we consider
// *
// * @return pointer to the allocated MemoryObject
// */
//MemoryObject *MemoryManager::allocate_guest(uint64_t size, bool isLocal,
//                                            bool isGlobal, const llvm::Value *allocSite,
//                                            Architecture * arch, ExecutionState *state) 
//{
//	if (size>10*1024*1024) 
//  {
//		klee_warning_once(0, "failing large alloc: %u bytes", (unsigned) size);
//		return 0;
//	}
//
//	uint16_t heap_min = 0x8000;
//  assert(state);
//
//  /* Some debug printing */
//#if 1
//	std::cout << "MemoryManager::allocate_guest(): working with state "  << state << "\n";
//	std::cout << "MemoryManager::allocate_guest(): Allocation memory max is " << arch->memory_size - 1 << "\n";
//	std::cout << "MemoryManager::allocate_guest(): Attempting allocation of " << size << "\n";
//	if (const llvm::Function * f = dyn_cast<llvm::Function>(allocSite)){
//		llvm::errs() << "MemoryManager::allocate_guest(): site is " << f->getName() << "\n";
//	} else {
//		llvm::errs() << "MemoryManager::allocate_guest(): site is " << *allocSite << "\n";
//	}
//#endif
//
//  /* Allocate physical space at the host */
//	uint64_t host_address = (uint64_t) (unsigned long) malloc((unsigned) size);
//
//  /* Now we need to: 
//   * 1. Find a free memory chunk at the guest (guest_address)
//   * 2. Create a new memory object with host_address and guest address
//   * Note that state->addressSpace.objects is a map of memory objects 
//   * sorted by guest_address, see AddressSpace.h */
//  MemoryMap::iterator obj_begin = state->addressSpace.objects.begin();
//  MemoryMap::iterator obj_end = state->addressSpace.objects.end();
//	unsigned prev_begin = 0;
//	unsigned cur_end = 0;
//  llvm::outs() << "MemoryManager::allocate_guest(): Going to allocate" <<
//    " space for a new object of size " << size << ". " <<
//    "state->addressSpace.objects.size() = " <<
//    state->addressSpace.objects.size() << "\n";
//	uint64_t guest_address;
//	bool first = false;
//
//  /* If we don't have any objects yet, reserve space at the
//   * highest memory address */
//	if (obj_begin == obj_end) 
//  {
//		guest_address = arch->memory_size - 1 - size;
//		std::cout << "MemoryManager::allocate_guest(): This is the first memory object. guest addr: "  << guest_address << "\n";
//		std::cout << "MemoryManager::allocate_guest(): arch->memory_size =  "  << arch->memory_size << "\n";
//		first = true;
//	}
//  /* Else iterate through objects from the end: i.e from highest to lowest memory address */
//  else 
//  {
//    const MemoryObject *obj = NULL;
//		--obj_end; // Now it points to the latest object (at highest memory location)
//    obj = obj_end->first;
//		prev_begin = obj->guest_address;
//    while (obj_begin != obj_end)
//	  {
//	  	--obj_end; // Going from the end
//      obj = obj_end->first;
//      //const MemoryObject *obj = obj_end->first;
//	  	cur_end = obj->guest_address + obj->size;
//
//      llvm::outs() << "MemoryManager::allocate_guest(): looking at an object at [" << obj->guest_address << "-" << obj->guest_address + obj->size << ")\n";
//	  	llvm::outs() << "MemoryManager::allocate_guest(): cur end " << cur_end << " prev begin " << prev_begin << "\n";
//
//	  	if ( (prev_begin - size >= cur_end) && (cur_end + size < arch->memory_size) )
//      {
//	  		guest_address = prev_begin - size;
//        llvm::outs() << "MemoryManager::allocate_guest(): There was an appropriate memory gap\n";
//	  		llvm::outs() << "MemoryManager::allocate_guest(): updated address is " << guest_address << "\n";
//	  		break;
//	  	} 
//      //else
//	  	//	std::cout << "obj at " << obj->guest_address << "-" << cur_end << " has gap of " << prev_begin - cur_end << "\n"; 
//	  	//  std::cout << "setting prev_begin to " << obj->guest_address << "\n";
//	  	prev_begin = obj->guest_address;
//	  	//++obj_itr;
//	  }
//  }
//
//  /* We reached the wilderness */
//	if (!first && obj_begin == obj_end)
//  {
//    llvm::outs() << "MemoryManager::allocate_guest(): extending guest memory past the last object\n";
//		guest_address = prev_begin - size;
//	}
//
//	++stats::allocations;
//
//  llvm::outs() << "MemoryManager::allocate_guest(): Allocation address is g:" << guest_address << "; h:" << host_address << "\n";
//
//	//if (guest_address < heap_min){
//	//	std::cout << "Oh no! Less than heap min!!\n";
//	//}
//
//  /* Finally create new MemoryObject */
//	MemoryObject *res = new MemoryObject(guest_address, host_address, size, isLocal, isGlobal, false,
//			allocSite, this);
//	//std::cout << "Going to insert object\n";
//	objects.insert(res);
//	//std::cout << "Inserted object\n";
//	if (guest_address < 1000){
//    llvm::outs() << "MemoryManager::allocate_guest(): Guest address seems to be too low\n";
//	}
//	return res;
//}


MemoryObject *MemoryManager::allocate(uint64_t size, bool isLocal, 
                                      bool isGlobal,
                                      const llvm::Value *allocSite) {
  if (size>10*1024*1024)
    klee_warning_once(0, "Large alloc: %u bytes.  KLEE may run out of memory.", (unsigned) size);
  
  uint64_t host_address = (uint64_t) (unsigned long) malloc((unsigned) size);
  if (!host_address)
    return 0;
  
  ++stats::allocations;
  /* We set the res->guest_address to zero. It will be set when the memory
   * object is mapped to a state's AddressSpace */
  MemoryObject *res = new MemoryObject(0, host_address, size, isLocal, isGlobal, false,
                                       allocSite, this);
  objects.insert(res);
  return res;
}

MemoryObject *MemoryManager::allocateFixed(uint64_t _guest_address, uint64_t size,
                                           const llvm::Value *allocSite, bool specMem) {
  /// IVAN ADDITIONS BEGIN
  //llvm::outs() << "Inside allocateFixed()\n";
  //if(!arch)
  //  llvm::outs() << "Arch is NULL, wtf?!\n";
  //else
  //  llvm::outs() << "Arch is not NULL, good, arch->memory_size = " << arch->memory_size << "\n";
  /* Check if the alloacted address is within the arch's memory limit */
  if (_guest_address >= arch->memory_size) 
  {
      llvm::outs() << "g: " << _guest_address << "\n";
      klee_error("Trying to allocate outside physical memory boundaries");
  }
  /// IVAN ADDITIONS END
#ifndef NDEBUG
  llvm::outs() << "Checking if overlapping with other objects\n";
  for (objects_ty::iterator it = objects.begin(), ie = objects.end(); it != ie; ++it) 
  {
    MemoryObject *mo = *it;
    /* Special memory (i.e. peripheral registers) can overlap with flash memory
     * regions. This is legit (according to msp430 memory layout, (e.g. see
     * ti's gcc symbols for msp430g2553 where CALBC1_12MHZ lie in flash mem
     * area). Note that special memory is allocated only once before we do
     * symbolic execution, so it will not overlap with program allocated memory. */
    if ( !specMem && (_guest_address+size > mo->guest_address) && (_guest_address < mo->guest_address+mo->size) )
      klee_error("Trying to allocate an overlapping object");
  }
#endif

  ++stats::allocations;
  /* We set res->host_address to zero: we did not use malloc() as we did in MemoryManager::allocate() */
  MemoryObject *res = new MemoryObject(_guest_address, 0, size, false, true, true,
                                       allocSite, this);
  objects.insert(res);
  llvm::outs() << "Returning from allocateFixed()\n";
  return res;
}

void MemoryManager::deallocate(const MemoryObject *mo) {
  assert(0);
}

void MemoryManager::markFreed(MemoryObject *mo) {
  if (objects.find(mo) != objects.end())
  {
    if (!mo->isFixed)
      free((void *)mo->host_address);
    objects.erase(mo);
  }
}
