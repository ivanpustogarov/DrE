
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
extern "C" bool ADC10DTC0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> ADC10DTC0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC10DTC0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool ADC10DTC1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> ADC10DTC1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC10DTC1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool ADC10AE0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> ADC10AE0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC10AE0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool ADC10CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> ADC10CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC10CTL0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool ADC10CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> ADC10CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC10CTL1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool ADC10MEM_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> ADC10MEM_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading (fresh_symbolics) from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC10MEM_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading (existing value) from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    //ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    ref<Expr> address = ConstantExpr::alloc(addr, Context::get().getPointerWidth());
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}
extern "C" bool ADC10SA_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> ADC10SA_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC10SA_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool BCSCTL3_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> BCSCTL3_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("BCSCTL3_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P1SEL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> P1SEL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1SEL2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P1REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> P1REN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P1REN_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P2SEL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> P2SEL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2SEL2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P2REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> P2REN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P2REN_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P3SEL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> P3SEL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P3SEL2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool P3REN_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> P3REN_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("P3REN_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0IV_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0IV_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0CTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0CCTL0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0CCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0CCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0CCTL1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0CCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0CCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0CCTL2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0R_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0R_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0R_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0CCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0CCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0CCR0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0CCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0CCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0CCR1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA0CCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA0CCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA0CCR2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1IV_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1IV_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1CTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1CCTL0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1CCTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1CCTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1CCTL1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1CCTL2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1CCTL2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1CCTL2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1R_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1R_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1R_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1CCR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1CCR0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1CCR0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1CCR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1CCR1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1CCR1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool TA1CCR2_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> TA1CCR2_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("TA1CCR2_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0CTL0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0CTL1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0BR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0BR0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0BR0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0BR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0BR1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0BR1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0MCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0MCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0MCTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0STAT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0STAT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0STAT_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0RXBUF_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0TXBUF_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0ABCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0ABCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0ABCTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0IRTCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0IRTCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0IRTCTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCA0IRRCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCA0IRRCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCA0IRRCTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0CTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0CTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0CTL0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0CTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0CTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0CTL1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0BR0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0BR0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0BR0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0BR1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0BR1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0BR1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0I2CIE_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0I2CIE_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0I2CIE_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0STAT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0STAT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0STAT_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0RXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0RXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0RXBUF_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0TXBUF_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0TXBUF_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0TXBUF_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0I2COA_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0I2COA_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0I2COA_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool UCB0I2CSA_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> UCB0I2CSA_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("UCB0I2CSA_arr" + llvm::utostr(++use_count), w);
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
    //llvm::outs() << "DEBUG: before assert()\n";
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
extern "C" bool CALDCO_16MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> CALDCO_16MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CALDCO_16MHZ_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool CALBC1_16MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> CALBC1_16MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CALBC1_16MHZ_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool CALDCO_12MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> CALDCO_12MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CALDCO_12MHZ_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool CALBC1_12MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> CALBC1_12MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CALBC1_12MHZ_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool CALDCO_8MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> CALDCO_8MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CALDCO_8MHZ_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool CALBC1_8MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> CALBC1_8MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CALBC1_8MHZ_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool CALDCO_1MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> CALDCO_1MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CALDCO_1MHZ_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool CALBC1_1MHZ_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> CALBC1_1MHZ_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("CALBC1_1MHZ_arr" + llvm::utostr(++use_count), w);
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
