#ifndef __CODEGEN_HPP__
#define __CODEGEN_HPP__

#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <stack>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h> 

#include "../symbol/symbol.hpp"
#include "../symbol/types.hpp"

// Function to translate custom types to LLVM types
llvm::Type* translateType(Type* type, ParameterType pt);

class GenBlock {
private:
    llvm::Function* func;
    std::vector<llvm::Type*> args;
    std::unordered_map<std::string, llvm::Type*> locals;
    std::unordered_map<std::string, llvm::AllocaInst*> values;
    std::unordered_map<std::string, llvm::AllocaInst*> addresses;
    llvm::BasicBlock* block;
    bool hasReturnFlag; 

public:
    GenBlock();
    ~GenBlock();

    void setFunc(llvm::Function* f);
    llvm::Function* getFunc();

    void addArg(std::string name, Type* type, ParameterType pt);
    const std::vector<llvm::Type*>& getArgs();

    void addLocal(std::string name, Type* type, ParameterType pt);
    llvm::Type* getLocal(std::string name);

    void addValue(std::string name, llvm::AllocaInst* value);
    llvm::AllocaInst* getValue(std::string name);

    void addAddress(std::string name, llvm::AllocaInst* address);
    llvm::AllocaInst* getAddress(std::string name);

    void setBlock(llvm::BasicBlock* b);
    llvm::BasicBlock* getBlock();

    void addReturn();
    bool hasReturn();

    bool isReference(std::string name);
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