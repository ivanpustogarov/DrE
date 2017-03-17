//===-- ExecutionState.cpp ------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "klee/ExecutionState.h"

#include "klee/Internal/Module/Cell.h"
#include "klee/Internal/Module/InstructionInfoTable.h"
#include "klee/Internal/Module/KInstruction.h"
#include "klee/Internal/Module/KModule.h"

#include "klee/Expr.h"

#include "Memory.h"
#if LLVM_VERSION_CODE >= LLVM_VERSION(3, 3)
#include "llvm/IR/Function.h"
#else
#include "llvm/Function.h"
#endif
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

#include <iomanip>
#include <sstream>
#include <cassert>
#include <map>
#include <set>
#include <stdarg.h>
#include <iostream>

using namespace llvm;
using namespace klee;

namespace { 
  cl::opt<bool>
  DebugLogStateMerge("debug-log-state-merge");
}

/***/

StackFrame::StackFrame(KInstIterator _caller, KFunction *_kf)
  : caller(_caller), restorePC(0), kf(_kf), callPathNode(0), 
    minDistToUncoveredOnReturn(0),varargs(0), cur_call_symbolics_seq_num(0), num_of_constraints(0),
    cur_fsummary(NULL), incomingBBIndex(0) {
  locals = new Cell[kf->numRegisters];
}

StackFrame::StackFrame(KInstIterator _caller, KInstIterator _restore, KFunction *_kf, unsigned incomingBBIndexIn)
  : caller(_caller), restorePC(_restore), kf(_kf), callPathNode(0), 
	minDistToUncoveredOnReturn(0), varargs(0),cur_call_symbolics_seq_num(0), num_of_constraints(0),
  cur_fsummary(NULL), incomingBBIndex(incomingBBIndexIn) {
  locals = new Cell[kf->numRegisters];
}

StackFrame::StackFrame(const StackFrame &s) 
  : caller(s.caller),
  	incomingBBIndex(s.incomingBBIndex),
		restorePC(s.restorePC),
    kf(s.kf),
    callPathNode(s.callPathNode),
    allocas(s.allocas),
    minDistToUncoveredOnReturn(s.minDistToUncoveredOnReturn),
    varargs(s.varargs), cur_call_symbolics_seq_num(s.cur_call_symbolics_seq_num),
    num_of_constraints(s.num_of_constraints), cur_fsummary(s.cur_fsummary),
    path_instructions(s.path_instructions)
{
  locals = new Cell[s.kf->numRegisters];
  for (unsigned i=0; i<s.kf->numRegisters; i++)
    locals[i] = s.locals[i];
}

StackFrame::~StackFrame() { 
  delete[] locals; 
}

/***/


/* *** Functions to support state pruning begin *** */

/* Constructor for basis frames 
 * 
 * Save frame's local variables (i.e. from locals)
 */
SavedFrame::SavedFrame(StackFrame & frame)
{
  unsigned numRegs = frame.kf->numRegisters;
  for (unsigned i = 0 ; i < numRegs ; ++i){
    //TODO: use copy constructor?
    locals[i] = frame.locals[i].value;
  }
  caller = frame.caller;
  kf = frame.kf;
}

/* Constructor for diff frames, locals to be filled in on demand */
SavedFrame::SavedFrame(KInstIterator caller, KFunction * callee){
  caller = caller;
  kf = callee;
}

/**
  *  Create a simplified memory snapshot of execution state
  * 
  *  Copy the following from the state:
  *  - path instructions
  *  - stack size
  *
  *  @param state Execution state this snapshot is based on
  *  @return
 */
SavedConfig::SavedConfig(int stackSizeIn, std::vector<llvm::Instruction *> pathIn)
 {
 	stackSize = stackSizeIn;
 	path_instructions = pathIn;
 }

/**
 *  Create a complete memory snapshot of execution state
 * 
 *  Copy the following from the state:
 *  - path instructions
 *  - stack
 *  - memory objects (from state.AddressSpace)
 *
 *  @param state Execution state this snapshot is based on
 *  @return
*/
SavedConfig::SavedConfig(ExecutionState& state){
  stackSize = state.stack.size();
  path_instructions = state.path_instructions;
  stack = new SavedFrame*[stackSize];
  // Copy all stack frames
  for (unsigned i = 0 ; i < stackSize ; ++i)
  {
    SavedFrame * frame = new SavedFrame(state.stack[i]);
    stack[i] = frame;
  }

  MemoryMap::iterator memItr = state.addressSpace.objects.begin();
  MemoryMap::iterator memEnd = state.addressSpace.objects.end();
  //Copy all of memory
  for ( ; memItr != memEnd ; ++memItr)
  {
  	const MemoryObject * mo = memItr->first;
  	ObjectState* os = memItr->second;
  	ref<Expr> value = os->read(0, os->size * 8);
  	objs[mo->allocSite] = value;
  }		
}


/** 
 * Find SavedConfig basis which has the same stack configuration as
 *  the state
 *
 * Iterate over this configList's savedConfig bases. Try to find one
 * which has the same stack frames as the <state>: the number of stack
 * frames should be the same; caller functions for each of the frames
 * should coincide.
 *
 * @param state Execution state for which we are looking for matching
 *              configuration
 * @param [out] found Set to true if we found a matching SavedConfig
 * @return Matching SavedConfig if we found one,
 *         Newly created SavedConfig otherwise.
 */
SavedConfig * ConfList::getBasis(ExecutionState& state, bool& found)
{
  std::map<SavedConfig*, std::list<SavedConfig*> >::iterator basisItr = bases.begin();
  std::map<SavedConfig*, std::list<SavedConfig*> >::iterator basisEnd = bases.end();
  
  /* Iterate over this configList's savedConfig bases. Try to find one
   * which has the same stack frames as the <state>: the number of
   * statck frames should be the same; caller functions for each of the
   * frames should coincide. */
  for ( ; basisItr != basisEnd ; ++basisItr)
  {
    bool couldMatch = true;
    SavedConfig * basis = basisItr->first;
    if (basis->stackSize != state.stack.size())
    {
#if 0
      for (int i = 0 ; i < state.stack.size() ; ++i)
      {
        StackFrame& frameI = state.stack[i];
        errs() << "frame #" << i << " : ";
        if (frameI.caller)
          errs() << "\n\tcaller " << *frameI.caller->inst;
        else 
          errs() << "\n\tcaller NONE";
        errs() << "\n\tcallee " << frameI.kf->function->getName() << "\n";
      }
    
      for (int i = 0 ; i < basis->stackSize ; i++)
      {
        SavedFrame * savedFrame = basis->stack[i];
        errs() << "saved frame #" << i << " :\n";
        if (savedFrame->caller)
          errs() << "\tcaller" << *savedFrame->caller->inst << "\n";
        else 
          errs() << "\tcaller NONE\n";
      }
#endif

      couldMatch = false;
    } else 
    {
      for (int i = 0 ; i < state.stack.size() ; ++i)
      {
        KInstIterator& stateCaller = state.stack[i].caller;
        KInstIterator& basisCaller = basis->stack[i]->caller;
    
        //TODO: check callee
    
        if (stateCaller != basisCaller)
        {
          couldMatch = false;
          break;
        }
      }
    }
    
    if (couldMatch)
    {
      found = true;
      return basis;
    }
  }

  /* Could not find an appropriate basis => it is new memory
   * configuration. Let's save it. */
  llvm::outs() << "ConfList::getBasis(): couldn't find basis match, making a new one\n";
  SavedConfig * newBasis = new SavedConfig(state);
  found = false;
  return newBasis;
}

/**
 * Check if two expressions are equal (takes symbolic peripherals into account)
 * 
 * Check if two expressions are composed of either identical read
 * expressions or read expressions from peripherals
 * For example this two expressions will be considered equal:
 * (Read w8 0 P1DIR_arr1) and (Read w8 0 P1DIR_arr2) 
 *
 * @param a First symbolic expression 
 * @param b Second symbolic expression
 * @return True if two expressions a equoivalent
 *         False  otherwise
 *
*/
bool exprMergeEquiv(Expr& a, Expr& b)
{
  
  if (&a == 0 && &b == 0)
    return true;

  if (&a == 0 || &b == 0)
    return false;

  if (a.getKind() != b.getKind())
    return false;

  if (a.getKind() == Expr::Constant)
    return (a == b);

  /* If both expressions are simple reads (e.g. (Read w8 0 P1DIR_arr1) ) */
  if (a.getKind() == Expr::Read)
  {

    //llvm::outs() << "exprMergeEquiv(): both are reads\n";
    /*
    llvm::outs() << "a has " << a.getNumKids() << " kids\n";
    llvm::outs() << "kid is " << a.getKid(0);
    */
    ReadExpr * rA = (ReadExpr *)&a;
    ReadExpr * rB = (ReadExpr *)&b;

    // This is a virtual method. For ConstantExpr it will
    // compare the width and APInt value. It returns 0 if contents are
    // equal.
    int contents = a.compareContents(b);
    //llvm::outs() << "exprMergeEquiv(): contents are " << (contents ? "different" : "equal") << "\n";

    //llvm::outs() << "read expr updates" << *(rA->updates.root) << "\n";
    if (rA->fromPeripheral && rB->fromPeripheral)
    {
      //llvm::outs() << "both read exprs are from peripherals!\n";
      return true;
    }
    //llvm::outs() << "not from peripherals\n";

    /*
    if (!exprMergeEquiv(rA->index, rB->index)){
      return false;
    }
    */
    return (contents == 0);

    /*
    if (rA->updates.root->isSymbolicArray()){
      std::cout << "isSymbolic\n";
    } else {
      std::cout << " has concrete values\n";
    }
    std::cout << "index " << rA->index << "\n";
    std::cout << "kind is ";
    Expr::printKind(std::cout, a.getKind());
    */
  } else 
  /* Consider each subexpression recursively. They all should match
   * pairwise for the initial expressions to be equal */
  {
    int aKids = a.getNumKids();
    int bKids = b.getNumKids();
    if (aKids != bKids){
      return false;
    }
    for (int i = 0 ; i < a.getNumKids() ; ++i){
      ref<Expr> aKidI = a.getKid(i);
      ref<Expr> bKidI = b.getKid(i);
      //bool kidImatch = exprMergeEquiv(*aKidI, *bKidI, depth + 1);
      #if 0
      if (aKidI == 0 || bKidI == 0){
        std::cout << "A kid or b kid is null!\n";
      }
      #endif
      bool kidImatch = exprMergeEquiv(*aKidI, *bKidI);
      if (kidImatch == false){
        return false;
      }
    }
    return true;
  }
}

/**
 * Check if two expressions are equal (takes symbolic peripherals into account)
 */ 
bool exprMergeEquiv(ref<Expr> a, ref<Expr> b)
{
	bool smudgeMerge = true;

	if (a.isNull() && b.isNull()){
		return true;
	}
	if (a.isNull()){
		return false;
	}
	if (b.isNull()){
		return false;
	}
	return exprMergeEquiv(*a, *b);
}

/* Check if <large> contains <small>.
 * <small> \in <large> means that <small>'s constrains is a subset of
 * <large>'s constraints */
bool path_includes(std::vector<llvm::Instruction *> large, std::vector<llvm::Instruction *> small)
{
  llvm::outs() << "path_includes(): inside\n";
  if(small.size() > large.size())
  {
    llvm::outs() << "path_includes(): small is bigger then large => return false\n";
    return false;
  }
  unsigned i;
  for(i = 0; i<small.size(); i++)
  {
    if(small[i] != large[i])
    {
      llvm::outs() << "path_includes():  the following instructions did not match (at position " << i << ":\n";
      llvm::outs() << *(small[i]) << " and " << large[i] << "\n";
      return false;
    }
  }
  llvm::outs() << "path_includes(): returning true\n";
  return true;
}

/** Compare <conflicts> with previously saved for <basis> 
 *
 * @param conflicts Possibly new conflicts for <basis>
 * @param basis Memory configuration <conflicts> is based on
 * @return True if <conflicts> does not coincide with previously saved
 *         False otherwise
 * 
 */
bool ConfList::distinct(SavedConfig* conflicts, SavedConfig* basis, ExecutionState& state, int thresh)
{
	std::list<SavedConfig *>::iterator diffItr = bases[basis].begin();
	std::list<SavedConfig *>::iterator diffEnd = bases[basis].end();


  /* Loop over already saved memory config conflicts.
   * <diff> is a saved conflict. Check they are the same as our new <conflicts> */
	for ( ; diffItr != diffEnd ; ++diffItr)
  {
		SavedConfig * diff = *diffItr;
		int possibleMatch = true;

		ValMap::iterator dObjItr = diff->objs.begin();
		ValMap::iterator dObjEnd = diff->objs.end();
		ValMap::iterator cObjItr = conflicts->objs.begin();
		ValMap::iterator cObjEnd = conflicts->objs.end();
		/* Iterate over memory objects, break if
		 * they were allocating by different allocate sites */
		while (dObjItr != dObjEnd && cObjItr != cObjEnd && possibleMatch)
		{
			const llvm::Value * dKey = dObjItr->first;
			const llvm::Value * cKey = cObjItr->first;

     /* Check if  allocation instructions match  
			Ivan: can we just replace the stuff below with (dKey == cKey) ?*/
			if (dKey < cKey)
			{
				possibleMatch = false;
				dObjItr++;
			} else if (dKey == cKey)
			{
        /* Check if expressions are syntactically equivalent  */
				if (!exprMergeEquiv(dObjItr->second, cObjItr->second))
					possibleMatch = false;
				cObjItr++;
				dObjItr++;
			} else 
			{
				possibleMatch = false;
				cObjItr++;
			}
		}

    /* Check if <diff> and <conflicts> have different number of objects
     * Ivan: The two loops below look very strange, just replace them with
		 * if(diff->objs.size() != conflicts->objs) */
		while (cObjItr != cObjEnd && dObjItr == dObjEnd && possibleMatch)
		{
			possibleMatch = false;
			++cObjItr;
		}

		while (cObjItr == cObjEnd && dObjItr != dObjEnd && possibleMatch){
			possibleMatch = false;
			++dObjItr;
		}

		/* If memory doesn't match, no need to check the stack */
		if (!possibleMatch)
			continue;

    /* Now let's compare stack frames */
		if (conflicts->stack == NULL && diff->stack == NULL)
		{
			//Both stacks are the same as the basis
		} else if (conflicts->stack == NULL && diff->stack != NULL) 
		{
			possibleMatch = false;
		} else if (conflicts->stack != NULL && diff->stack == NULL) 
		{
			possibleMatch = false;
		} else 
		{
			for (int fIdx = 0; fIdx < conflicts->stackSize && possibleMatch; ++fIdx){
				SavedFrame * cFrame = conflicts->stack[fIdx];
				SavedFrame * dFrame = diff->stack[fIdx];
				if (cFrame == NULL && dFrame != NULL){
					possibleMatch = false;
					break;
				}
				else if (cFrame != NULL && dFrame == NULL){
					possibleMatch = false;
					break;
				}
				else if (cFrame == NULL && dFrame == NULL){
					//doesn't hurt potential match : both frames same as basis
					continue;
				}
				RegMap::iterator cRegItr = cFrame->locals.begin();
				RegMap::iterator cRegEnd = cFrame->locals.end();
				for ( ; cRegItr != cRegEnd && possibleMatch ; ++cRegItr){
					RegMap::iterator dRegItr = dFrame->locals.find(cRegItr->first);
					if (dRegItr == dFrame->locals.end()){
						possibleMatch = false;
					} else if (!exprMergeEquiv(cRegItr->second, dRegItr->second)){
						possibleMatch = false;
					}
				}
			}
		}

    /* Finally check path constraints,  */
    if(possibleMatch && !path_includes(conflicts->path_instructions, diff->path_instructions))
    {
      llvm::outs() << "ConfList::diff(): No memory conflicts, but path does not match for existing conflict\n";
		  possibleMatch = false;
    }

		if (possibleMatch == true){
			std::cout << "found match\n";
			return false;
		}
	}

	return true;
}




/**
 * Compare state's memory configuration (stack frames and memory
 * objects) with saved configurations. Return the difference if any.
 *
 * TODO: break this function into several smaller functions.
 *
 * First, find saved memory configuration basis <basis> for the state's
 * current instruction (it is memory configuration when this instruction
 * was executed for the first time by some state). 
 * 
 * Second, compare this <basis> with state's current memory
 * configuration. This involves comparing expressions in: 1) each stack
 * frame and each local in this frame; 2) each memory object.  If any
 * two expressions do not match, we save state's version of the
 * expression into <conflicts> configuration.
 * 
 * Third, if <conflicts> are not empty compare them with previously
 * saved conflicts for <basis>. If it a completely new conflict, save
 * it.
 *
 * @param state Execution state for which we are looking equivalent
 *              memory configuration
 * @param [out] prunable We set it to true if we found an equivalent
 *                       memory configuration. We set it to false
 *                       otherwise.
 * @return NULL if either, 1) there was no saved memory configuration for
 *               the state's current instruction, or 2) we found a
 *               matching memory (or conflict) configuration. 
 *         <conflicts> configuration (i.e. new difference between
 *                     state's memory configuration and <basis> for the current
 *                     instruction.
 *
 * */
SavedConfig * ConfList::diff(ExecutionState& state, bool& prunable)
{
  bool basisFound;
  /* Fast search. Just check if we have matching stack configuration.
   * This will return either matching saved config, or a newly created
   * config if there was not match */
  //llvm::outs() << "ConfList::diff(): Going inside getBasis()\n";
  SavedConfig * basis = getBasis(state, basisFound);
  if (!basisFound)
  {
    //llvm::outs() << "ConfList::diff(): since this is a new basis, can't match anything else\n";
    bases[basis];
    prunable = false;
    return NULL;
  }

  /* We have a saved config which matches <state>'s stack configuration
   * Let's now check it in more detail */
  unsigned stackSize = state.stack.size();
  SavedConfig * conflicts = new SavedConfig(stackSize, state.path_instructions);
  
  conflicts->stack = new SavedFrame*[stackSize];
  bool stackHasConflicts = false;
  //llvm::outs() << "ConfList::diff(): Comparing stack frames in detail\n";
  /* Compare state's and basis' stack frames by comparing their locals.
     If two stack frames are different (i.e. some of their locals are
     different), we save the state's frame in <conflicts>. For conflict
     frames we store only locals which do not match */
  for (int stackIdx = 0 ; stackIdx < stackSize ; ++stackIdx)
  {
    SavedFrame * basisFrame = basis->stack[stackIdx];
    StackFrame& of = state.stack[stackIdx];
    //llvm::outs() << "ConfList::diff(): Comparing stack frame " << stackIdx << "; it has " <<  of.kf->numRegisters << " locals\n";
    //Diff this stack frame
    SavedFrame * conflictsFrame = new SavedFrame(of.caller, of.kf);
    bool frameHasConflicts = false;

    /* Iterate over stack frame locals */
    for (unsigned i=0; i < of.kf->numRegisters; i++) 
    {
      ref<Expr> basisVal = basisFrame->locals[i];
      ref<Expr> stateVal = of.locals[i].value;
      	
      if (basisVal.isNull() && !stateVal.isNull()) 
      {
        //llvm::outs() << "ConfList::diff(): basisVal is NULL; stateVal = " << stateVal << "\n";
        conflictsFrame->locals[i] = stateVal;
        frameHasConflicts = true;
      } else if (!basisVal.isNull() && stateVal.isNull())
      {
        //llvm::outs() << "ConfList::diff(): stateVal is NULL; basisVal = " << basisVal << "\n";
        conflictsFrame->locals[i] = NULL;
        frameHasConflicts = true;
      } else if (basisVal.isNull() && stateVal.isNull())
      {
        //Values still match if both are null
      } else 
      {
        //llvm::outs() << "ConfList::diff(): Going to compare " << basisVal << " vs " << stateVal << "\n";
	      /* basisVal.compare returns 0 if basisVal is structurally equivalent to
	      stateVal. This function checks if two expressions are of he same
	      kind and then invokes compareContents() which is a virtual
	      method (for Constant expressions it check that the APInt values
	      are equal. In case of ReadExpr it compares the corresponding
	      update list (by comparing each update node).
	      E.g. '(Read w8 0 P1DIR_arr1)' vs '(Read w8 0 P1DIR_arr1)'
	      are equivalent, but 'Read w8 0 P1DIR_arr1)' vs '(Read w8 0
	      P1DIR_arr2)' are not */
        if (basisVal.compare(stateVal) != 0)
        {
          /* For our purposes 'Read w8 0 P1DIR_arr1)' vs '(Read w8 0
	        * P1DIR_arr2)' are still considered equal (since P1DIR_arr1
	        * and P1DIR_arr2 are both come from peripherals */
	        if (!exprMergeEquiv(*basisVal, *stateVal))
	        {
            conflictsFrame->locals[i] = stateVal;
            frameHasConflicts = true;
          }
        } else
        {
          llvm::outs() << "ConfList::diff(): expressions are structurally equivalent\n";
        }
      }
    }

    if (frameHasConflicts)
    {
    	conflicts->stack[stackIdx] = conflictsFrame;
    	stackHasConflicts = true;
    } else 
    {
    	conflicts->stack[stackIdx] = NULL;
    	delete conflictsFrame;
    }
  }
  //llvm::outs() << "ConfList::diff(): stackHasConflicts = " << stackHasConflicts << "\n";


  //llvm::outs() << "ConfList::diff(): Done finding stack conflicts\n";

  if (stackHasConflicts == false)
  {
    delete[] conflicts->stack;
    conflicts->stack = NULL;
    //llvm::outs() << "ConfList::diff(): No stack conflicts\n";
  } else 
  {
    //llvm::outs() << "ConfList::diff(): Stack conflicts exist\n";
  }

  MemoryMap::iterator ai = state.addressSpace.objects.begin();
  MemoryMap::iterator ae = state.addressSpace.objects.end();
  /* Now it's time to check objects from state's addressSpace */
  // Map a memory value to all of it's versions. First in line is the 
  // current, followed by each saved version
  for ( ; ai != ae ; ++ai)
  {
    const MemoryObject * mo =  ai->first;
    ObjectState * os = ai->second;
    Expr::Width size = mo->size * 8; // This <size> goes to
                                     // os->read() which takes 
                                     // size in bits, while
                                     // mo->size is in bytes


    ref<Expr> stateExpr = os->read(0, size);
    /*
    if (containsSmudge(res_expr)){
      //No need to replace one smudge with another, right?
      //TODO: check
      continue;
    }
    */

    //At this point we have the state value of a single memory object
    // the below loop gathers all different values
    const llvm::Value * allocPt = mo->allocSite;


    ValMap::iterator valueItr = basis->objs.find(allocPt);
    /* The state has object which savedConfig does not have */
    if (valueItr == basis->objs.end()) 
    {
      assert(allocPt);
      //if (allocPt == NULL)
      //{
      //    errs() << "Caught a null!\n";
      //}
      //llvm::outs() << "\n\n\nConfList::diff(): allocPt " << *allocPt << "\n";
      //llvm::outs() << "ConfList::diff(): doesn't exist in basis\n";
      conflicts->objs[allocPt] = stateExpr;
    } else 
    {
      ref<Expr> valExpr = valueItr->second;
      if (!exprMergeEquiv(*valExpr, *stateExpr)){
        //errs() << "\n\n\nallocPt " << *allocPt << "\n";
        //errs() << "mismatch: " << exprMergeEquiv(*valExpr, *stateExpr, true);
        conflicts->objs[allocPt] = stateExpr;
      }
    }
  }

  /* Finally, if there are no stack/memory conflicts, check
   * (implicitely) path constraints.
   * The main idea here is to check path instructions: 1) if path
   * instructions are the same, then they should have the same
   * constraints. We are also find if state's path instructions contain
   * basis' path instructions: in this case basis have less constraints,
   * then the state => basis is able to generate the state .*/
  bool path_instructions_match = path_includes(state.path_instructions, basis->path_instructions);

  //llvm::outs() << "ConfList::diff(): Done finding memory conflicts\n";

  if (!conflicts->objs.empty())
  {
    //llvm::outs() << "ConfList::diff(): Memory conflicts exist\n";
  }

  if ( (conflicts->stack == NULL) && (conflicts->objs.size() == 0))
    if(!path_instructions_match)
      llvm::outs() << "ConfList::diff(): No memory conflicts, but path does not match for basis\n";

  if ( (conflicts->stack == NULL) && (conflicts->objs.size() == 0) && path_instructions_match)
  {
    //llvm::outs() << "ConfList::diff(): No conflicts\n";
    delete conflicts;
    prunable = true;
    return NULL;
  }

  int thresh = 0;

  /* Now we have all the conflicting locals and memory objects from the state.
     Let's see if we have such a configuration among <basis>'s saved conflicts */
  //llvm::outs() << "ConfList::diff(): let's check already existing conflicts\n";
  bool areConflictsUnique = distinct(conflicts, basis, state, thresh);
  //bool areConflictsUnique = true;;
  if (!areConflictsUnique)
  {
    //llvm::outs() << "ConfList::diff(): conflicts match a diff'ed version\n";
    delete conflicts;
    prunable = true;
    return NULL;
  }
			
  //llvm::outs() << "ConfList::diff(): No matching conflicts. That was a new memory configuration.\n";
  //At this point, conflicts are unique
  prunable = false;
  //We're not in smudging mode
  bases[basis].push_front(conflicts);
  return conflicts;

}



/* *** Functions to support state pruning end *** */

ExecutionState::ExecutionState(KFunction *kf) :
    interruptFun(NULL),
    interrupt_depth(0),
    cur_inner_call(NULL),
    complies_with_cur_inner_call(true),
    cur_upper_call(NULL),
    cur_fsummary(NULL), 
    next_fsummary(NULL), 
    //cur_callgraph_fsummary(NULL),
    //next_callgraph_fsummary(NULL),
    ret_value_constraints(NULL),
    target_func(NULL),
    lastPathIndex(0),
    pathDeviationDepth(0),
    debug1(0),
    debug2(0),
    onPathInsts(0),
    isOnPath(false),
    first_offroad_block(NULL),
    pc(kf->instructions),
    prevPC(pc),

    queryCost(0.), 
    weight(1),
    depth(0),
    statusRegisterAddress(ConstantExpr::create(0, Expr::Int16)),

    instsSinceCovNew(0),
    coveredNew(false),
    forkDisabled(false),
    ptreeNode(0) {
  pushFrame(0, kf);
}

ExecutionState::ExecutionState(const std::vector<ref<Expr> > &assumptions)
    : constraints(assumptions), queryCost(0.), ptreeNode(0), pathDeviationDepth(0),
      debug1(0), debug2(0), onPathInsts(0), isOnPath(false), first_offroad_block(NULL),
      lastPathIndex(0), target_func(NULL), ret_value_constraints(NULL),
      cur_fsummary(NULL), next_fsummary(NULL),
      //cur_callgraph_fsummary(NULL), next_callgraph_fsummary(NULL),
      cur_inner_call(NULL),
      complies_with_cur_inner_call(true),
      cur_upper_call(NULL),
      interruptFun(NULL),
      interrupt_depth(0),
      statusRegisterAddress(ConstantExpr::create(0, Expr::Int16))
{
}

ExecutionState::~ExecutionState() {
  for (unsigned int i=0; i<symbolics.size(); i++)
  {
    const MemoryObject *mo = symbolics[i].first;
    assert(mo->refCount > 0);
    mo->refCount--;
    if (mo->refCount == 0)
      delete mo;
  }

  while (!stack.empty()) popFrame();
}

ExecutionState::ExecutionState(const ExecutionState& state):
    complies_with_cur_inner_call(state.complies_with_cur_inner_call),
    interruptFun(state.interruptFun),
    interrupt_depth(state.interrupt_depth),
    path_instructions(state.path_instructions),
    path_choices_debug(state.path_choices_debug),
    path_choices(state.path_choices),
    cur_inner_call(state.cur_inner_call),
    cur_upper_call(state.cur_upper_call),
    global_symbolic_replacements(state.global_symbolic_replacements),
    cur_fsummary(state.cur_fsummary),
    next_fsummary(state.next_fsummary),
    //call_symbolic_replacements(state.call_symbolic_replacements),
    ret_value_constraints(state.ret_value_constraints),
    target_func(state.target_func),
    lastPathIndex(state.lastPathIndex),
    path_arc_falures(state.path_arc_falures),
    callHistory(state.callHistory),
    first_offroad_block(state.first_offroad_block),
    isOnPath(state.isOnPath),
    pathDeviationDepth(state.pathDeviationDepth),
    debug1(state.debug1),
    debug2(state.debug2),
    onPathInsts(state.onPathInsts),
    fnAliases(state.fnAliases),
    pc(state.pc),
    prevPC(state.prevPC),
    stack(state.stack),
    incomingBBIndex(state.incomingBBIndex),

    addressSpace(state.addressSpace),
    constraints(state.constraints),

    queryCost(state.queryCost),
    weight(state.weight),
    depth(state.depth),

    pathOS(state.pathOS),
    symPathOS(state.symPathOS),

    instsSinceCovNew(state.instsSinceCovNew),
    coveredNew(state.coveredNew),
    forkDisabled(state.forkDisabled),
    coveredLines(state.coveredLines),
    ptreeNode(state.ptreeNode),
    symbolics(state.symbolics),
    arrayNames(state.arrayNames),
    statusRegisterAddress(state.statusRegisterAddress),
    blacklisted_psummaries(state.blacklisted_psummaries)
{
  for (unsigned int i=0; i<symbolics.size(); i++)
    symbolics[i].first->refCount++;
  /// IVAN ADDITIONS BEGIN
  
  /* We need to make a copy of each suppl call: they should be different
   * for each resuling path summary at the end execution 
   * Note that connected summaries ARE copied */ 
  for (std::map<llvm::Function *, call_symbolic_replacements_ty>::const_iterator it_1  = state.call_symbolic_replacements.begin();
                                               it_1 != state.call_symbolic_replacements.end(); ++it_1)
  {
    llvm::Function *f = it_1->first;
    call_symbolic_replacements_ty call_replacements = it_1->second;

    ///* Copy each suppl call and put to temporary <copy_call_replacements> */
    //call_symbolic_replacements_ty copy_call_replacements;
    for(call_symbolic_replacements_ty::iterator it_2  = call_replacements.begin();
                                                it_2 != call_replacements.end(); ++it_2)
    {
      InnerCall *original_inner_call = it_2->second;
      InnerCall *copy_inner_call = new InnerCall(original_inner_call);
      //copy_call_replacements[copy_inner_call->symbolics] = copy_inner_call;
      this->call_symbolic_replacements[f][copy_inner_call->symbolics] = copy_inner_call;
    }
  }
    //this->call_symbolic_replacements[f] = copy_call_replacements

  /// IVAN ADDITIONS END
}

ExecutionState *ExecutionState::branch() {
  depth++;

  ExecutionState *falseState = new ExecutionState(*this);
  falseState->coveredNew = false;
  falseState->coveredLines.clear();

  weight *= .5;
  falseState->weight -= weight;

  return falseState;
}

void ExecutionState::pushFrame(KInstIterator caller, KFunction *kf) {
  stack.push_back(StackFrame(caller,kf));
}

/* This function is used when the execution state goes into an
 * interrupt. The use of prevPC actually causes a problem for ESE. If
 * the instruction just executed is a call from A to B, then the end of
 * the interrupt should return to the beginning of B. However, the
 * interrupt will actually return to the callsite in A, then advance the
 * PC forward so it will work as if the call to B never happened.
 * This is why we need special <restore> instruction */
void ExecutionState::pushFrame(KInstIterator caller, KInstIterator restore, KFunction *kf) {
  stack.push_back(StackFrame(caller,restore,kf,incomingBBIndex));
}

void ExecutionState::popFrame() {
  StackFrame &sf = stack.back();
  for (std::vector<const MemoryObject*>::iterator it = sf.allocas.begin(), 
         ie = sf.allocas.end(); it != ie; ++it)
    addressSpace.unbindObject(*it);
  stack.pop_back();
  ///IVAN ADDITIONS BEGIN
  cur_fsummary = stack.back().cur_fsummary; 
  ///IVAN ADDITIONS END
}

void ExecutionState::addSymbolic(const MemoryObject *mo, const Array *array) { 
  mo->refCount++;
  symbolics.push_back(std::make_pair(mo, array));
}
///

std::string ExecutionState::getFnAlias(std::string fn) {
  std::map < std::string, std::string >::iterator it = fnAliases.find(fn);
  if (it != fnAliases.end())
    return it->second;
  else return "";
}

void ExecutionState::addFnAlias(std::string old_fn, std::string new_fn) {
  fnAliases[old_fn] = new_fn;
}

void ExecutionState::removeFnAlias(std::string fn) {
  fnAliases.erase(fn);
}

/**/

llvm::raw_ostream &klee::operator<<(llvm::raw_ostream &os, const MemoryMap &mm) {
  os << "{";
  MemoryMap::iterator it = mm.begin();
  MemoryMap::iterator ie = mm.end();
  if (it!=ie) {
    os << "MO" << it->first->id << ":" << it->second;
    for (++it; it!=ie; ++it)
      os << ", MO" << it->first->id << ":" << it->second;
  }
  os << "}";
  return os;
}

bool ExecutionState::merge(const ExecutionState &b) {
  if (DebugLogStateMerge)
    llvm::errs() << "-- attempting merge of A:" << this << " with B:" << &b
                 << "--\n";
  if (pc != b.pc)
    return false;

  // XXX is it even possible for these to differ? does it matter? probably
  // implies difference in object states?
  if (symbolics!=b.symbolics)
    return false;

  {
    std::vector<StackFrame>::const_iterator itA = stack.begin();
    std::vector<StackFrame>::const_iterator itB = b.stack.begin();
    while (itA!=stack.end() && itB!=b.stack.end()) {
      // XXX vaargs?
      if (itA->caller!=itB->caller || itA->kf!=itB->kf)
        return false;
      ++itA;
      ++itB;
    }
    if (itA!=stack.end() || itB!=b.stack.end())
      return false;
  }

  std::set< ref<Expr> > aConstraints(constraints.begin(), constraints.end());
  std::set< ref<Expr> > bConstraints(b.constraints.begin(), 
                                     b.constraints.end());
  std::set< ref<Expr> > commonConstraints, aSuffix, bSuffix;
  std::set_intersection(aConstraints.begin(), aConstraints.end(),
                        bConstraints.begin(), bConstraints.end(),
                        std::inserter(commonConstraints, commonConstraints.begin()));
  std::set_difference(aConstraints.begin(), aConstraints.end(),
                      commonConstraints.begin(), commonConstraints.end(),
                      std::inserter(aSuffix, aSuffix.end()));
  std::set_difference(bConstraints.begin(), bConstraints.end(),
                      commonConstraints.begin(), commonConstraints.end(),
                      std::inserter(bSuffix, bSuffix.end()));
  if (DebugLogStateMerge) {
    llvm::errs() << "\tconstraint prefix: [";
    for (std::set<ref<Expr> >::iterator it = commonConstraints.begin(),
                                        ie = commonConstraints.end();
         it != ie; ++it)
      llvm::errs() << *it << ", ";
    llvm::errs() << "]\n";
    llvm::errs() << "\tA suffix: [";
    for (std::set<ref<Expr> >::iterator it = aSuffix.begin(),
                                        ie = aSuffix.end();
         it != ie; ++it)
      llvm::errs() << *it << ", ";
    llvm::errs() << "]\n";
    llvm::errs() << "\tB suffix: [";
    for (std::set<ref<Expr> >::iterator it = bSuffix.begin(),
                                        ie = bSuffix.end();
         it != ie; ++it)
      llvm::errs() << *it << ", ";
    llvm::errs() << "]\n";
  }

  // We cannot merge if addresses would resolve differently in the
  // states. This means:
  // 
  // 1. Any objects created since the branch in either object must
  // have been free'd.
  //
  // 2. We cannot have free'd any pre-existing object in one state
  // and not the other

  if (DebugLogStateMerge) {
    llvm::errs() << "\tchecking object states\n";
    llvm::errs() << "A: " << addressSpace.objects << "\n";
    llvm::errs() << "B: " << b.addressSpace.objects << "\n";
  }
    
  std::set<const MemoryObject*> mutated;
  MemoryMap::iterator ai = addressSpace.objects.begin();
  MemoryMap::iterator bi = b.addressSpace.objects.begin();
  MemoryMap::iterator ae = addressSpace.objects.end();
  MemoryMap::iterator be = b.addressSpace.objects.end();
  for (; ai!=ae && bi!=be; ++ai, ++bi) {
    if (ai->first != bi->first) {
      if (DebugLogStateMerge) {
        if (ai->first < bi->first) {
          llvm::errs() << "\t\tB misses binding for: " << ai->first->id << "\n";
        } else {
          llvm::errs() << "\t\tA misses binding for: " << bi->first->id << "\n";
        }
      }
      return false;
    }
    if (ai->second != bi->second) {
      if (DebugLogStateMerge)
        llvm::errs() << "\t\tmutated: " << ai->first->id << "\n";
      mutated.insert(ai->first);
    }
  }
  if (ai!=ae || bi!=be) {
    if (DebugLogStateMerge)
      llvm::errs() << "\t\tmappings differ\n";
    return false;
  }
  
  // merge stack

  ref<Expr> inA = ConstantExpr::alloc(1, Expr::Bool);
  ref<Expr> inB = ConstantExpr::alloc(1, Expr::Bool);
  for (std::set< ref<Expr> >::iterator it = aSuffix.begin(), 
         ie = aSuffix.end(); it != ie; ++it)
    inA = AndExpr::create(inA, *it);
  for (std::set< ref<Expr> >::iterator it = bSuffix.begin(), 
         ie = bSuffix.end(); it != ie; ++it)
    inB = AndExpr::create(inB, *it);

  // XXX should we have a preference as to which predicate to use?
  // it seems like it can make a difference, even though logically
  // they must contradict each other and so inA => !inB

  std::vector<StackFrame>::iterator itA = stack.begin();
  std::vector<StackFrame>::const_iterator itB = b.stack.begin();
  for (; itA!=stack.end(); ++itA, ++itB) {
    StackFrame &af = *itA;
    const StackFrame &bf = *itB;
    for (unsigned i=0; i<af.kf->numRegisters; i++) {
      ref<Expr> &av = af.locals[i].value;
      const ref<Expr> &bv = bf.locals[i].value;
      if (av.isNull() || bv.isNull()) {
        // if one is null then by implication (we are at same pc)
        // we cannot reuse this local, so just ignore
      } else {
        av = SelectExpr::create(inA, av, bv);
      }
    }
  }

  for (std::set<const MemoryObject*>::iterator it = mutated.begin(), 
         ie = mutated.end(); it != ie; ++it) {
    const MemoryObject *mo = *it;
    const ObjectState *os = addressSpace.findObject(mo);
    const ObjectState *otherOS = b.addressSpace.findObject(mo);
    assert(os && !os->readOnly && 
           "objects mutated but not writable in merging state");
    assert(otherOS);

    ObjectState *wos = addressSpace.getWriteable(mo, os);
    for (unsigned i=0; i<mo->size; i++) {
      ref<Expr> av = wos->read8(i);
      ref<Expr> bv = otherOS->read8(i);
      wos->write(i, SelectExpr::create(inA, av, bv));
    }
  }

  constraints = ConstraintManager();
  for (std::set< ref<Expr> >::iterator it = commonConstraints.begin(), 
         ie = commonConstraints.end(); it != ie; ++it)
    constraints.addConstraint(*it);
  constraints.addConstraint(OrExpr::create(inA, inB));

  return true;
}

void ExecutionState::dumpStack(llvm::raw_ostream &out) const {
  unsigned idx = 0;
  const KInstruction *target = prevPC;
  for (ExecutionState::stack_ty::const_reverse_iterator
         it = stack.rbegin(), ie = stack.rend();
       it != ie; ++it) {
    const StackFrame &sf = *it;
    Function *f = sf.kf->function;
    const InstructionInfo &ii = *target->info;
    out << "\t#" << idx++;
    std::stringstream AssStream;
    AssStream << std::setw(8) << std::setfill('0') << ii.assemblyLine;
    out << AssStream.str();
    out << " in " << f->getName().str() << " (";
    // Yawn, we could go up and print varargs if we wanted to.
    unsigned index = 0;
    for (Function::arg_iterator ai = f->arg_begin(), ae = f->arg_end();
         ai != ae; ++ai) {
      if (ai!=f->arg_begin()) out << ", ";

      out << ai->getName().str();
      // XXX should go through function
      ref<Expr> value = sf.locals[sf.kf->getArgRegister(index++)].value; 
      if (isa<ConstantExpr>(value))
        out << "=" << value;
    }
    out << ")";
    if (ii.file != "")
      out << " at " << ii.file << ":" << ii.line;
    out << "\n";
    target = sf.caller;
  }
}

/* Extract call symbolic replacements from <complex_expr>
 *
 * We need this funcntion to understand how many symbolic replacements
 * are a part of the return value. We use it to decide if we need to pass
 * some constraints to a supplimentray function.
 *
 * @param state Execution state from which we check symbolic replacements
 * @param complex_expr The return value of the function that the <state> is executing
 * @return vector of symbolic replacements which are a part of complex_expr
 */
std::vector<ref<Expr> > ExecutionState::get_call_symbolics(ref<Expr> complex_expr)
{
  llvm::Function *cur_func = this->prevPC->inst->getParent()->getParent();
  std::vector<ref<Expr> > res;
  for(call_symbolic_replacements_ty::iterator it_1  = this->call_symbolic_replacements[cur_func].begin();
                                              it_1 != this->call_symbolic_replacements[cur_func].end(); ++it_1)
  {
    ref<Expr> symbolics = it_1->first;
    std::vector<ref<Expr> > concats = extract_concat_subexpressions(complex_expr);
    for(std::vector<ref<Expr> >::iterator it_2 = concats.begin(); it_2 != concats.end(); ++it_2) 
    { 
      ref<Expr> concat = *it_2;
      if( symbolics == concat) 
      {
        res.push_back(symbolics);
        break;
      }
    }
  }
  return res;
}
