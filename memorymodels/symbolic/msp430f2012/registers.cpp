
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
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("ADC10MEM_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USICTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USICTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USICTL0_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USICTL1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USICTL1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USICTL1_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USICKCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USICKCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USICKCTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USICNT_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USICNT_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USICNT_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USISRL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USISRL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USISRL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USISRH_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USISRH_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USISRH_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USICTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USICTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USICTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USICCTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USICCTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USICCTL_arr" + llvm::utostr(++use_count), w);
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
extern "C" bool USISR_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
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

extern "C" ref<Expr> USISR_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("USISR_arr" + llvm::utostr(++use_count), w);
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