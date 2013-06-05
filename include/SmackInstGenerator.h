//
// Copyright (c) 2008 Zvonimir Rakamaric (zvonimir@cs.utah.edu)
// This file is distributed under the MIT License. See LICENSE for details.
//
#ifndef SMACKINSTVISITOR_H
#define SMACKINSTVISITOR_H

#include "BoogieAst.h"
#include "Values.h"
#include "llvm/Support/InstVisitor.h"

namespace smack {

    class SmackInstGenerator : public llvm::InstVisitor<SmackInstGenerator> {
    
    private:
        Values& values;
        Procedure *currProc;
        Block *currBlock;
        map<const llvm::BasicBlock*, Block*> &blockMap;
  
        Stmt * generateCall(llvm::Function *f, vector<Expr*> ps, vector<string> rs);

        void generatePhiAssigns(llvm::TerminatorInst& i);
        void generateGotoStmts(vector<pair<Expr*,string> > target);

    public:
      SmackInstGenerator(Values& v, Procedure *p, Block *b, 
          map<const llvm::BasicBlock*, Block*>& bm) 
          : values(v), currProc(p), currBlock(b), blockMap(bm) {}

      void setCurrBlock(Block *b) { currBlock = b; }
      Block * getCurrBlock() { return currBlock; }

      void processInstruction(llvm::Instruction& i);
      void visitInstruction(llvm::Instruction& i);
      void visitAllocaInst(llvm::AllocaInst& i);
      void visitBranchInst(llvm::BranchInst& i);
      void visitSwitchInst(llvm::SwitchInst& i);
      void visitPHINode(llvm::PHINode& i);
      void visitTruncInst(llvm::TruncInst& i);
      void visitUnreachableInst(llvm::UnreachableInst& i);
      void visitCallInst(llvm::CallInst& i);
      void visitReturnInst(llvm::ReturnInst& i);
      void visitLoadInst(llvm::LoadInst& i);
      void visitStoreInst(llvm::StoreInst& i);
      void visitGetElementPtrInst(llvm::GetElementPtrInst& i);
      void visitICmpInst(llvm::ICmpInst& i);
      void visitZExtInst(llvm::ZExtInst& i);
      void visitSExtInst(llvm::SExtInst& i);
      void visitBitCastInst(llvm::BitCastInst& i);
      void visitBinaryOperator(llvm::BinaryOperator& i);
      void visitPtrToIntInst(llvm::PtrToIntInst& i);
      void visitIntToPtrInst(llvm::IntToPtrInst& i);
      void visitSelectInst(llvm::SelectInst& i);
  
      // void visitAtomicCmpXchgInst(AtomicCmpXchgInst &I);
    };
}

#endif  /*SMACKINSTVISITOR_H*/