
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
extern "C" bool SD16INCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SD16INCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SD16INCTL0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}
extern "C" bool SD16AE_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SD16AE_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SD16AE_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}
extern "C" bool SD16CONF0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SD16CONF0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SD16CONF0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}
extern "C" bool SD16CONF1_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SD16CONF1_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SD16CONF1_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}
extern "C" bool SD16CTL_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SD16CTL_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SD16CTL_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}
extern "C" bool SD16CCTL0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SD16CCTL0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SD16CCTL0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}
extern "C" bool SD16IV_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SD16IV_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SD16IV_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ref<Expr> res = os->read(offset, w);
    return res;
  }
}
extern "C" bool SD16MEM0_w(ExecutionState* s, uint64_t addr, ref<Expr> v, bool pass_through)
{
  if(pass_through)
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    return true;
  }
  else
  {
    llvm::outs() << "writing to " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const MemoryObject *mo = op.first;
    ref<Expr> offset = mo->getOffsetExpr(address);
    const ObjectState *os = op.second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(offset, v);

    /* Debug printing */
    ObjectPair op1;
    success = s->addressSpace.resolveOne(cast<ConstantExpr>(address), op1);
    assert(success && "resolve failed in registers.cpp, it's a bug");
    const ObjectState *os1 = op1.second;
    ref<Expr> new_val = os1->read(offset, v->getWidth());
    llvm::outs() << "New value = " << new_val << "\n";
    /* *** */
  
    return true;
  }
}

extern "C" ref<Expr> SD16MEM0_r(ExecutionState* s, uint64_t addr, Expr::Width w, bool get_fresh_symbolics)
{
  if(get_fresh_symbolics)
  {
    static unsigned int use_count;
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    const Array * array = Array::CreateArray("SD16MEM0_arr" + llvm::utostr(++use_count), w);
    ref<Expr> res = Expr::createTempRead(array, w, true);
    return res;
  } else
  {
    llvm::outs() << "reading from " << __PRETTY_FUNCTION__ << "\n";
    ObjectPair op;
    bool success;
    ref<Expr> address = ConstantExpr::alloc(addr, Expr::Int16);
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
//-----AUX REGISTER FUNCTIONS-----//
extern "C" ref<Expr> usb_setup_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "@" << addr <<"\n";

	//ref<ConstantExpr> addrExpr = ConstantExpr::create(addr, w);
	ref<ConstantExpr> addrExpr = Expr::createPointer(addr);
	ObjectPair op;
	s->addressSpace.resolveOne(addrExpr, op);
	const MemoryObject * mo = op.first;
	const ObjectState * os = op.second;
	

	std::cerr << "addr in " << addr << "\n"
						<< " guest_address " << mo->guest_address << "\n";


	std::cerr << "mo " << mo << "\n";
	uint64_t offset = addr - mo->guest_address;

	std::cerr	<< "usb_setup_r offset is " << offset << "\n";

	#if 0
	++use_count;
	std::string res_name = "usb_setup_" + llvm::utostr(offset) + "_" 
		+ llvm::utostr(use_count);

	if (offset == 0x0000){ //bmRequestType
		const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0001){ //bRequest
		const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0x09, w);
		return res;
	} else if (offset == 0x0002){ //wValue
		//const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0xff, w);
		return res;
	} else if (offset == 0x0004){ //wIndex
		ref<Expr> res = ConstantExpr::create(0x01, w);
		return res;
	} else if (offset == 0x0006){ //wLength
		const Array * array = new Array(res_name, w);
		ref<Expr> res = Expr::createTempRead(array, w, true);
		return res;
	}
	#endif

	if (offset == 0x0000){ //bmRequestType
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0001){ //bRequest
		ref<Expr> res = ConstantExpr::create(0x09, w);
		return res;
	} else if (offset == 0x0002){ //wValue
		ref<Expr> res = ConstantExpr::create(0x01, w);
		return res;
	} else if (offset == 0x0003){ //wValue + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0004){ //wIndex
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0005){ //wIndex + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0006){ //wLength
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0007){ //Length + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	}

	assert(0 && "unexpected offset in usb_setup_r");


	#if 0
	const Array * array = new Array(res_name, w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
	#endif
}
