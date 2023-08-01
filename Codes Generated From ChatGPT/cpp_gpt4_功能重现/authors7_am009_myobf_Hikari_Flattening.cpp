#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

namespace {
    struct ControlFlowFlatteningPass: public FunctionPass {
        static char ID;
        ControlFlowFlatteningPass(): FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            if (F.empty()) {
                return false;
            }

            BasicBlock *entryBB = &F.getEntryBlock();
            BasicBlock *loopEntryBB = BasicBlock::Create(F.getContext(), "loop_entry", &F);
            BasicBlock *loopExitBB = BasicBlock::Create(F.getContext(), "loop_exit", &F);
            BasicBlock *switchBB = BasicBlock::Create(F.getContext(), "switch", &F);

            auto switchVar = new AllocaInst(Type::getInt32Ty(F.getContext()), 0, "switch_var", entryBB);
            new StoreInst(ConstantInt::get(Type::getInt32Ty(F.getContext()), 0), switchVar, entryBB);
            BranchInst::Create(loopEntryBB, entryBB);

            // Move the first basic block to the beginning of the loop
            entryBB->moveBefore(loopEntryBB);

            // Create switch instruction and connect it to the loop entry basic block
            LoadInst *switchValue = new LoadInst(switchVar, "switch_val", loopEntryBB);
            SwitchInst *switchInst = SwitchInst::Create(switchValue, loopExitBB, F.size(), loopEntryBB);

            // Add basic blocks to the switch instruction
            unsigned counter = 0;
            for (auto &BB : F) {
                if (&BB == entryBB || &BB == loopEntryBB || &BB == loopExitBB || &BB == switchBB) {
                    continue;
                }

                // Add a case for the basic block
                switchInst->addCase(ConstantInt::get(Type::getInt32Ty(F.getContext()), counter), &BB);

                // Replace conditional branches with switch jumps
                if (auto *branch = dyn_cast<BranchInst>(BB.getTerminator())) {
                    if (branch->isConditional()) {
                        auto *cond = branch->getCondition();
                        auto *trueBB = branch->getSuccessor(0);
                        auto *falseBB = branch->getSuccessor(1);
                        auto *select = SelectInst::Create(cond, trueBB, falseBB, "", &BB);
                        new StoreInst(select, switchVar, &BB);
                        BranchInst::Create(switchBB, &BB);
                        branch->eraseFromParent();
                    }
                }

                ++counter;
            }

            // Add a case for loop exit
            switchInst->addCase(ConstantInt::get(Type::getInt32Ty(F.getContext()), counter), loopExitBB);

            // Insert obfuscation code here if desired

            // Repair the stack
            for (auto &BB : F) {
                for (auto &I : BB) {
                    if (auto *callInst = dyn_cast<CallInst>(&I)) {
                        if (callInst->getCalledFunction()->getName() == "llvm.stackrestore") {
                            auto *alloca = new AllocaInst(Type::getInt8PtrTy(F.getContext()), 0, "stack_copy", entryBB);
                            new StoreInst(callInst->getArgOperand(0), alloca, entryBB);
                            LoadInst *stackCopy = new LoadInst(alloca, "load_stack_copy", &BB);
                            callInst->setArgOperand(0, stackCopy);
                        }
                    }
                }
            }
            return true;
        }
    };
} // namespace

char ControlFlowFlatteningPass::ID = 0;
static RegisterPass<ControlFlowFlatteningPass> X("control-flow-flattening", "Control Flow Flattening Pass");