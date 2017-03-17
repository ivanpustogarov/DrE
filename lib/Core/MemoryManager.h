//===-- MemoryManager.h -----------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef KLEE_MEMORYMANAGER_H
#define KLEE_MEMORYMANAGER_H

#include <set>
#include <stdint.h>
#include "Memory.h"
#include "klee/Arch.h"

namespace llvm {
  class Value;
}

namespace klee {
  class MemoryObject;
  class Architecture;

  class MemoryManager {
  private:
    typedef std::set<MemoryObject*> objects_ty;
    objects_ty objects;

  public:
    MemoryManager() {}
    ~MemoryManager();

    Architecture *arch;

    MemoryObject *allocate(uint64_t size, bool isLocal, bool isGlobal,
                           const llvm::Value *allocSite);
    //MemoryObject *allocate_guest(uint64_t size, bool isLocal, bool isGlobal,
    //                       const llvm::Value *allocSite, Architecture * arch, ExecutionState *state);
    MemoryObject *allocateFixed(uint64_t address, uint64_t size,
                                const llvm::Value *allocSite, bool specMem = false);
    void deallocate(const MemoryObject *mo);
    void markFreed(MemoryObject *mo);
    void clear_objects() {objects.clear();};
  };

} // End klee namespace

#endif
