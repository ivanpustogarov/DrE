//===-- ExprUtil.cpp ------------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "klee/util/ExprUtil.h"
#include "klee/util/ExprHashMap.h"

#include "klee/Expr.h"

#include "klee/util/ExprVisitor.h"

#include <set>

using namespace klee;

void klee::findReads(ref<Expr> e, 
                     bool visitUpdates,
                     std::vector< ref<ReadExpr> > &results) {
  // Invariant: \forall_{i \in stack} !i.isConstant() && i \in visited 
  std::vector< ref<Expr> > stack;
  ExprHashSet visited;
  std::set<const UpdateNode *> updates;
  
  if (!isa<ConstantExpr>(e)) {
    visited.insert(e);
    stack.push_back(e);
  }

  while (!stack.empty()) {
    ref<Expr> top = stack.back();
    stack.pop_back();

    if (ReadExpr *re = dyn_cast<ReadExpr>(top)) {
      // We memoized so can just add to list without worrying about
      // repeats.
      results.push_back(re);

      if (!isa<ConstantExpr>(re->index) &&
          visited.insert(re->index).second)
        stack.push_back(re->index);
      
      if (visitUpdates) {
        // XXX this is probably suboptimal. We want to avoid a potential
        // explosion traversing update lists which can be quite
        // long. However, it seems silly to hash all of the update nodes
        // especially since we memoize all the expr results anyway. So
        // we take a simple approach of memoizing the results for the
        // head, which often will be shared among multiple nodes.
        if (updates.insert(re->updates.head).second) {
          for (const UpdateNode *un=re->updates.head; un; un=un->next) {
            if (!isa<ConstantExpr>(un->index) &&
                visited.insert(un->index).second)
              stack.push_back(un->index);
            if (!isa<ConstantExpr>(un->value) &&
                visited.insert(un->value).second)
              stack.push_back(un->value);
          }
        }
      }
    } else if (!isa<ConstantExpr>(top)) {
      Expr *e = top.get();
      for (unsigned i=0; i<e->getNumKids(); i++) {
        ref<Expr> k = e->getKid(i);
        if (!isa<ConstantExpr>(k) &&
            visited.insert(k).second)
          stack.push_back(k);
      }
    }
  }
}

///

namespace klee {

class SymbolicObjectFinder : public ExprVisitor {
protected:
  Action visitRead(const ReadExpr &re) {
    const UpdateList &ul = re.updates;

    // XXX should we memo better than what ExprVisitor is doing for us?
    for (const UpdateNode *un=ul.head; un; un=un->next) {
      visit(un->index);
      visit(un->value);
    }

    if (ul.root->isSymbolicArray())
      if (results.insert(ul.root).second)
        objects.push_back(ul.root);

    return Action::doChildren();
  }

public:
  std::set<const Array*> results;
  std::vector<const Array*> &objects;
  
  SymbolicObjectFinder(std::vector<const Array*> &_objects)
    : objects(_objects) {}
};

}

template<typename InputIterator>
void klee::findSymbolicObjects(InputIterator begin, 
                               InputIterator end,
                               std::vector<const Array*> &results) {
  SymbolicObjectFinder of(results);
  for (; begin!=end; ++begin)
    of.visit(*begin);
}

void klee::findSymbolicObjects(ref<Expr> e,
                               std::vector<const Array*> &results) {
  findSymbolicObjects(&e, &e+1, results);
}

typedef std::vector< ref<Expr> >::iterator A;
template void klee::findSymbolicObjects<A>(A, A, std::vector<const Array*> &);

typedef std::set< ref<Expr> >::iterator B;
template void klee::findSymbolicObjects<B>(B, B, std::vector<const Array*> &);

void klee::print_expressions(std::vector<ref<Expr> > vexpr)
{
  for(std::vector<ref<Expr> >::iterator it = vexpr.begin(); it != vexpr.end(); ++it)
    llvm::outs() << *it << "\n";
  return;
}

std::vector<ref<Expr> > klee::extract_concat_subexpressions(ref<Expr> e)
{
  std::vector<ref<Expr> > res;

  const klee::ConstantExpr *ce = dyn_cast<klee::ConstantExpr>(e);
  if (!ce)
  {
    Expr *ep = e.get();

    if (const klee::ConcatExpr *ce = dyn_cast<klee::ConcatExpr>(e)) 
    {
      //llvm::outs() << "SummaryExecutor::extract_concat_subexpressions(): Found a concat expression: " << *ce << "\n";
      res.push_back(e);
    }

    for (unsigned i=0; i<ep->getNumKids(); i++)
    {
      std::vector<ref<Expr> > sub_res;
      sub_res = extract_concat_subexpressions(ep->getKid(i));
      res.insert(res.end(), sub_res.begin(), sub_res.end());
    }
  }
  return res;
}

ref<Expr> klee::replace_subexpr(ref<Expr> expr, ref<Expr> &token_old, ref<Expr> &token_new)
{
  //llvm::outs() << " <<<<<<<<<<<<<<<<<<< token_new = " << token_new << " >>>>>>>>>>>>\n";
  if (isa<ConstantExpr>(expr))
    return expr;

  if(expr == token_old)
    return token_new;

  unsigned numkids = expr->getNumKids();

  if(!numkids)
  {
    //llvm::outs() << " <<<<<<<<<<<<<<<<<<< return = " << expr << " as no kids here>>>>>>>>>>>>\n";
    return token_old;
  }

  //assert(numkids && "zero numkids for non costant expression, wtf!?");
  //llvm::outs() << "InterpreterManager::replace_subexpr(): " << numkids << " kids\n";
  assert((numkids<=4) && "numkids>4 ");
  ref<Expr> arr[4];
  for(unsigned i = 0; i<numkids; i++)
  {
    //if(isa<ConcatExpr>(expr->getKid(0)))
    //llvm::outs() << " <<<<<<<<<<<<<<<<<<< kid = " << expr->getKid(i) << " >>>>>>>>>>>>\n";
    if(expr->getKid(i) == token_old)
    {
      //llvm::outs() << " <<<<<<<<<<<<<<<<<<< match >>>>>>>>>>>>\n";
      arr[i] = token_new;
    }
    else
    {
      //llvm::outs() << " <<<<<<<<<<<<<<<<<<< no match >>>>>>>>>>>>\n";
      arr[i] = replace_subexpr(expr->getKid(i), token_old, token_new);
    }
  }

  //for(unsigned i = 0; i<numkids; i++)
  //  llvm::outs() << ">> width: " << arr[i] << " -- " << arr[i]->getWidth() << "\n";
  ref<Expr> tmp = expr->rebuild(arr);
  //llvm::outs() << " <<<<<<<<<<<<<<<<<<< rebuilt: " << tmp <<" >>>>>>>>>>>> from kids\n";
  //for(unsigned i = 0; i<numkids; i++)
  //  llvm::outs() << arr[i] << "\n";
  //llvm::outs() << " <<<<<<<<<<<<<<<<<<< expr: " << expr <<" >>>>>>>>>>>>\n";
  //ref<Expr> tmp1 = expr->rebuild(arr);
  //llvm::outs() << " <<<<<<<<<<<<<<<<<<< rebuilt1: " << tmp1 <<" >>>>>>>>>>>>\n";
  return tmp;
}
