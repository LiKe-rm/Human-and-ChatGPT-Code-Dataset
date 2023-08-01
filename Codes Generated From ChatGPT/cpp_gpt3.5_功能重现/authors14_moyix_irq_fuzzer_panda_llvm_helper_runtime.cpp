#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/ModuleUtils.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <set>

using namespace llvm;

// Set of QEMU helper function names
static std::set<std::string> panda_funcs = {"panda_malloc", "panda_memcpy", "panda_exit"};

// LLVM pass to modify function calls in generated code from TCG
struct PandaCallMorphFunctionPass : public FunctionPass {
  static char ID;
  PandaCallMorphFunctionPass() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    for (BasicBlock &BB : F) {
      for (Instruction &I : BB) {
        if (auto *CI = dyn_cast<CallInst>(&I)) {
          Function *Callee = CI->getCalledFunction();
          if (Callee && !Callee->isIntrinsic() && !Callee->isDeclaration() &&
              !Callee->getName().startswith("mem") &&
              !Callee->getName().startswith("io")) {
            std::string func_name = Callee->getName().str();
            if (panda_funcs.count(func_name)) {
              std::string new_name = func_name + "_panda";
              if (!Callee->getParent()->getFunction(new_name)) {
                Function *new_func = Function::Create(Callee->getFunctionType(),
                                                      Callee->getLinkage(),
                                                      new_name,
                                                      Callee->getParent());
                new_func->copyAttributesFrom(Callee);
                Callee->getParent()->getFunctionList().insert(Callee, new_func);
              }
              Function *new_callee = Callee->getParent()->getFunction(new_name);
              CI->setCalledFunction(new_callee);
              if (new_callee->getReturnType() != CI->getType()) {
                CI->mutateType(new_callee->getReturnType());
              }
            } else if (!Callee->getParent()->getFunction(func_name + "_funcs")) {
              std::string new_name = func_name + "_funcs";
              Function *new_func = Function::Create(Callee->getFunctionType(),
                                                    Callee->getLinkage(),
                                                    new_name,
                                                    Callee->getParent());
              new_func->copyAttributesFrom(Callee);
              Callee->getParent()->getFunctionList().insert(Callee, new_func);
              Function *new_callee = Callee->getParent()->getFunction(new_name);
              CI->setCalledFunction(new_callee);
              if (new_callee->getReturnType() != CI->getType()) {
                CI->mutateType(new_callee->getReturnType());
              }
            }
          }
        }
      }
    }
    return true;
  }
};

char PandaCallMorphFunctionPass::ID = 0;

// Function to include the execution of QEMU helper functions in the LLVM JIT
void init_llvm_helpers() {
  static bool initialized = false;
  if (!initialized) {
    initialized = true;
    std::string error;
    auto *helper_mod = parseIRFile("std：：string helper_path = /path/to/helper/module.bc")
// Read the helper module
Expected<std::unique_ptr<Module>> module_or_err =
    parseIRFile(helper_path, error);
if (!module_or_err) {
  errs() << "Failed to read helper module: " << helper_path << "\n";
  return;
}

// Link the helper module into the JIT
Module *helper_module = module_or_err.get().release();
if (Linker::linkModules(*global_module, std::move(helper_module),
                        Linker::Flags::LinkOnlyNeeded)) {
  errs() << "Failed to link helper module: " << helper_path << "\n";
  return;
}

// Verify the linked module
if (verifyModule(*global_module, &errs())) {
  errs() << "Failed to verify linked module\n";
  return;
}

// Create a PandaCallMorphFunctionPass
PandaCallMorphFunctionPass *panda_pass = new PandaCallMorphFunctionPass();

// Add the pass to the function pass manager
legacy::FunctionPassManager pm(global_module);
pm.add(panda_pass);
pm.run(*global_function);

delete panda_pass;
}

//用于在 LLVM JIT 中启用或禁用 QEMU 帮助程序函数的命令行选项

//从 PassRegistry 注销 PandaCallMorphFunctionPass 的函数

int main（int argc， char **argv） {
LLVMInitializeNativeTarget（）;
LLVMInitializeNative

//初始化全局模块和函数
global_module = new Module（“global_module”， getGlobalContext（））;
global_function

// Initialize the function pass manager
PassManagerBuilder builder;
builder.OptLevel = 3;
builder.SizeLevel = 0;
builder.Inliner = createFunctionInliningPass(builder.OptLevel, builder.SizeLevel, false);
legacy::FunctionPassManager fpm(global_module);
builder.populateFunctionPassManager(fpm);

// Enable QEMU helper functions in the LLVM JIT if the command-line option is set
if (enable_helpers) {
init_llvm_helpers();
}

// Run the function pass manager
fpm.doInitialization();
fpm.run(*global_function);
fpm.doFinalization();

// Unregister the PandaCallMorphFunctionPass from the PassRegistry if QEMU helper functions are disabled
if (!enable_helpers) {
unregisterPandaPasses();
}

return 0;
}