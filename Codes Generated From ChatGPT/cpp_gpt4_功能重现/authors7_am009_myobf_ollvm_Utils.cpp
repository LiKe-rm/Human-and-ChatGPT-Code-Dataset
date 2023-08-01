#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Pass.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/IR/InstIterator.h>
#include <random>

using namespace llvm;

static cl::opt<bool> Obfuscate("fla", cl::desc("Enable Function-Level Obfuscation"));
static cl::opt<float> ObfuscateRate("fla-rate", cl::desc("Obfuscation Rate (0.0 - 1.0)"), cl::init(0.5));

namespace {
  struct Obfuscator : public FunctionPass {
    static char ID;
    Obfuscator() : FunctionPass(ID) {}

    bool valueEscapes(Instruction *Inst) {
      BasicBlock *BB = Inst->getParent();
      for (User *U : Inst->users()) {
        if (Instruction *UI = dyn_cast<Instruction>(U)) {
          if (UI->getParent() != BB)
            return true;
        }
      }
      return false;
    }

    void fixStack(Function &F) {
      for (BasicBlock &BB : F) {
        for (Instruction &I : BB) {
          if (!isa<AllocaInst>(&I) && valueEscapes(&I)) {
            I.moveBefore(BB.getFirstNonPHI());
          }
        }
      }
    }

    std::string readAnnotate(GlobalVariable *G) {
      if (!G->hasInitializer())
        return "";

      ConstantArray *C = dyn_cast<ConstantArray>(G->getInitializer());
      std::string Annotate;
      for (unsigned i = 0; i < C->getNumOperands(); ++i) {
        if (ConstantDataSequential *DS = dyn_cast<ConstantDataSequential>(C->getOperand(i))) {
          Annotate += DS->getAsCString().str();
        }
      }
      return Annotate;
    }

    bool toObfuscate(Function *F) {
      if (F->hasAvailableExternallyLinkage())
        return false;

      std::string Annotate = readAnnotate(F->getParent()->getNamedGlobal("llvm.global.annotations"));
      if (Annotate.find("nofla") != std::string::npos)
        return false;

      if (Annotate.find("fla") != std::string::npos)
        return true;

      if (Obfuscate) {
        static std::mt19937 generator;
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(generator) <= ObfuscateRate;
      }
      return false;
    }

    bool runOnFunction(Function &F) override {
      if (toObfuscate(&F)) {
        fixStack(F);
        return true;
      }
      return false;
    }
  };
}

char Obfuscator::ID = 0;
static RegisterPass<Obfuscator> X("obfuscator", "LLVM Code Obfuscator");
