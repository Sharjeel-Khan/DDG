//
// Created by sharjeel on 11/18/18.
//

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/ADT/StringRef.h"

using namespace std;
using namespace llvm;

#include <fstream>
#include <iostream>
#include <utility>
#include <string>
#include <vector>

#define DEBUG_TYPE "ddg"

namespace {
    struct DDG : public FunctionPass {
        static char ID;

        LLVMContext* pC;
        Function *bp_init, *bp_fini, *bp_checkedge, *func_start, *func_end;
        DDG() : FunctionPass(ID) {}

       
        bool runOnFunction(Function &F) override {
          bool bRet = false;
          bool first = true;

          if(!F.isDeclaration()) {
            bRet = true;
            Value* v_function;

            /**************************************************************************
             * Instrument the initial and final instrumented functions at the beginning
             * and ending of the main function
             **************************************************************************/
            if(F.getName() == "main"){
              {
                BasicBlock *Entry = &(F.getEntryBlock());
                Instruction *insertAt = &*(Entry->getFirstInsertionPt());
                IRBuilder<> IRB(insertAt);
                IRB.CreateCall(bp_init);
              }

              std::vector<BasicBlock*> ExitBlocks;
              for (BasicBlock &I : F)
                  if (isa<ReturnInst>(I.getTerminator()) ||
                      isa<UnreachableInst>(I.getTerminator()))
                      ExitBlocks.push_back(&I);

              for(auto i:ExitBlocks)
              {
                  BasicBlock *BB = &*i;
                  IRBuilder<> IRB(BB->getTerminator());
                  IRB.CreateCall(bp_fini);
              }
            }

            for (BasicBlock &B : F) {
              /**************************************************************************
               * Instrument the checkedge function at the beginning of each basic block
               **************************************************************************/
              {
                Instruction *insertAt = &*(B.getFirstInsertionPt());
                CallInst *CI = dyn_cast<CallInst>(insertAt);
                if(CI && insertAt->getOperand(insertAt->getNumOperands() - 1)->getName() == "bp_init"){
                  insertAt = insertAt->getNextNode();
                }
                IRBuilder<> IRB(insertAt);
                if(first){
                  v_function = IRB.CreateGlobalStringPtr(F.getName());
                  first = false;
                }
                Value* v_name = IRB.CreateGlobalStringPtr(B.getName());

                IRB.CreateCall(bp_checkedge, {v_function, v_name});
                  
              }
              
            }
          }


          return bRet;
        }

        bool doInitialization(Module &M) override
        {
          pC = &(M.getContext());
          IRBuilder<> IRB(*pC);

          {
            Constant *confun_init;
            confun_init = M.getOrInsertFunction("bp_init", IRB.getVoidTy());
            bp_init = cast<Function>(confun_init);
          }

          {
            Constant *confun_checkedge;
            confun_checkedge = M.getOrInsertFunction("bp_checkedge", IRB.getVoidTy(), IRB.getInt8PtrTy(), IRB.getInt8PtrTy());
            bp_checkedge = cast<Function>(confun_checkedge);
          }

          {
            Constant *confun_fini;
            confun_fini = M.getOrInsertFunction("bp_fini", IRB.getVoidTy());
            bp_fini = cast<Function>(confun_fini);
          }

          return false;
        }

        virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesCFG();
            AU.setPreservesAll();
        }
    };
}
char DDG::ID = 0;
static RegisterPass<DDG> X_ddg("DDG", "My Pass");
