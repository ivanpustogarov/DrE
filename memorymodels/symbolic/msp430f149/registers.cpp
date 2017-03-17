
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


extern "C" bool flash_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> flash_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("flash_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool IE1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> IE1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("IE1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool IFG1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> IFG1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("IFG1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ME1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ME1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ME1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool IE2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> IE2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("IE2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool IFG2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> IFG2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("IFG2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ME2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ME2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ME2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool WDTCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> WDTCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("WDTCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool MPY_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> MPY_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("MPY_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool MPYS_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> MPYS_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("MPYS_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool MAC_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> MAC_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("MAC_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool MACS_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> MACS_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("MACS_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool OP2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> OP2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("OP2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool RESLO_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> RESLO_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("RESLO_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool RESHI_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> RESHI_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("RESHI_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool SUMEXT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SUMEXT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SUMEXT_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P1IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P1IN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1IN_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P1OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P1OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1OUT_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P1DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P1DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1DIR_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P1IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P1IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1IFG_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P1IES_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P1IES_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1IES_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P1IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P1IE_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1IE_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P1SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P1SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1SEL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P2IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P2IN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2IN_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P2OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P2OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2OUT_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P2DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P2DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2DIR_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P2IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P2IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2IFG_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P2IES_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P2IES_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2IES_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P2IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P2IE_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2IE_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P2SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P2SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2SEL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P3IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P3IN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P3IN_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P3OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P3OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P3OUT_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P3DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P3DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P3DIR_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P3SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P3SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P3SEL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P4IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P4IN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P4IN_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P4OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P4OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P4OUT_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P4DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P4DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P4DIR_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P4SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P4SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P4SEL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P5IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P5IN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P5IN_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P5OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P5OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P5OUT_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P5DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P5DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P5DIR_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P5SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P5SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P5SEL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P6IN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P6IN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P6IN_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P6OUT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P6OUT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P6OUT_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P6DIR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P6DIR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P6DIR_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool P6SEL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> P6SEL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P6SEL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U0CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U0CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U0CTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U0TCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U0TCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U0TCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U0RCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U0RCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U0RCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U0MCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U0MCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U0MCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U0BR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U0BR0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U0BR0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U0BR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U0BR1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U0BR1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U0RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U0RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U0RXBUF_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U0TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U0TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U0TXBUF_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U1CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U1CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U1CTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U1TCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U1TCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U1TCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U1RCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U1RCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U1RCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U1MCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U1MCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U1MCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U1BR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U1BR0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U1BR0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U1BR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U1BR1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U1BR1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U1RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U1RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U1RXBUF_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool U1TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> U1TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("U1TXBUF_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TAIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TAIV_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TAIV_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TACTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TACTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TACTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TACCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TACCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TACCTL0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TACCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TACCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TACCTL1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TACCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TACCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TACCTL2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TAR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TAR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TAR_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TACCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TACCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TACCR0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TACCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TACCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TACCR1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TACCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TACCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TACCR2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBIV_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBIV_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBIV_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCTL0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCTL1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCTL2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCTL3_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCTL4_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCTL4_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCTL4_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCTL5_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCTL5_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCTL5_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCTL6_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCTL6_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCTL6_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBR_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCR0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCR1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCR2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCR3_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCR3_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCR3_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCR4_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCR4_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCR4_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCR5_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCR5_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCR5_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool TBCCR6_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> TBCCR6_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TBCCR6_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool DCOCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> DCOCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("DCOCTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool BCSCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> BCSCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("BCSCTL1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool BCSCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> BCSCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("BCSCTL2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool FCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> FCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("FCTL1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool FCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> FCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("FCTL2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool FCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> FCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("FCTL3_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool CACTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> CACTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CACTL1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool CACTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> CACTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CACTL2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool CAPD_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> CAPD_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CAPD_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12CTL0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12CTL1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12IFG_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12IFG_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12IFG_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12IE_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12IE_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12IE_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12IV_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12IV_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM3_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM3_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM3_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM4_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM4_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM4_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM5_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM5_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM5_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM6_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM6_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM6_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM7_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM7_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM7_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM8_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM8_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM8_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM9_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM9_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM9_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM10_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM10_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM10_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM11_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM11_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM11_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM12_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM12_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM12_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM13_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM13_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM13_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM14_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM14_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM14_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MEM15_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MEM15_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MEM15_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL2_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL3_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL4_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL4_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL4_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL5_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL5_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL5_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL6_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL6_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL6_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL7_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL7_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL7_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL8_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL8_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL8_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL9_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL9_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL9_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL10_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL10_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL10_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL11_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL11_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL11_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL12_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL12_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL12_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL13_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL13_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL13_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL14_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL14_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL14_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}
extern "C" bool ADC12MCTL15_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
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
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> ADC12MCTL15_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC12MCTL15_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
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
}