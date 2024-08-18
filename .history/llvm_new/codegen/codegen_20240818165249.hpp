#ifndef __CODEGEN_HPP__
#define __CODEGEN_HPP__

#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <stack>
#include <llvm/Pass.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

#include "../symbol/symbol.hpp"
#include "../symbol/types.hpp"

// Function to translate custom types to LLVM types
llvm::Type* translateType(Type* type, ParameterType pt);

class GenBlock {
private:
    llvm::Function* func;
    llvm::BasicBlock* block;
    bool hasReturnFlag; 
    std::unordered_map<std::string, llvm::AllocaInst*> allocas;

public:
    GenBlock();
    ~GenBlock();

    void setFunc(llvm::Function* f);
    llvm::Function* getFunc();

    void addAlloca(std::string name, llvm::AllocaInst* value);
    llvm::AllocaInst* getAlloca(std::string name);

    void setBlock(llvm::BasicBlock* b);
    llvm::BasicBlock* getBlock();

    void addReturn();
    bool hasReturn();
};

class GenScope {
private:
    std::stack<std::unordered_map<std::string, llvm::Function*>> functions;

public:
    GenScope();
    ~GenScope();

    void openScope();
    void closeScope();

    void addFunction(std::string name, llvm::Function* func);
    llvm::Function* getFunction(std::string name);
};

#endif // __CODEGEN_HPP__
