#include "codegen.hpp"
#include "../ast/ast.hpp"

// Define LLVM types globally to avoid re-initialization
llvm::Type* i32 = llvm::IntegerType::get(AST::TheContext, 32);;
llvm::Type* i8 =  llvm::IntegerType::get(AST::TheContext, 8);
llvm::Type* proc =  llvm::Type::getVoidTy(AST::TheContext);

llvm::Type* translateType(Type* type, ParameterType pt) {
    llvm::Type* t = nullptr;
    if (type->getType() == TypeEnum::INT) {
        t = i32;
    } else if (type->getType() == TypeEnum::BYTE) {
        t = i8;
    } else if (type->getType() == TypeEnum::VOID) {
        t = proc;
    } else if (type->getType() == TypeEnum::ARRAY) {
        t = translateType(type->getBaseType(), ParameterType::VALUE)->getPointerTo();
    }
    if (pt == ParameterType::REFERENCE) {
        t = t->getPointerTo();
    }
    return t;
}

// GenBlock constructor
GenBlock::GenBlock() : func(nullptr), block(nullptr), hasReturnFlag(false) {}

// GenBlock destructor
GenBlock::~GenBlock() {
    for (auto& it : allocas) {
        delete it.second;
    }
}

// Set function for GenBlock
void GenBlock::setFunc(llvm::Function* f) {
    func = f;
}

// Get function for GenBlock
llvm::Function* GenBlock::getFunc() {
    return func;
}

// Add value for GenBlock
void GenBlock::addAlloca(const std::string& name, llvm::AllocaInst* value) {
    allocas[name] = value;
}

// Get value for GenBlock
llvm::AllocaInst* GenBlock::getAlloca(const std::string& name) {
    return allocas[name];
}

// Set block for GenBlock
void GenBlock::setBlock(llvm::BasicBlock* b) {
    block = b;
}

// Get block for GenBlock
llvm::BasicBlock* GenBlock::getBlock() {
    return block;
}

// Add return for GenBlock
void GenBlock::addReturn() {
    hasReturnFlag = true;
}

// Check if block has return for GenBlock
bool GenBlock::hasReturn() {
    return hasReturnFlag;
}

// GenScope constructor
GenScope::GenScope() {}

// GenScope destructor
GenScope::~GenScope() {}

// Open a new scope in GenScope
void GenScope::openScope() {
    functions.push(std::unordered_map<std::string, llvm::Function*>());
}

// Close the current scope in GenScope
void GenScope::closeScope() {

    functions.pop();
}

// Add a function to the current scope in GenScope
void GenScope::addFunction(const std::string& name, llvm::Function* func) {
    functions.top()[name] = func;
}

// Get a function from the scopes in GenScope
llvm::Function* GenScope::getFunction(const std::string& name) {
    std::stack<std::unordered_map<std::string, llvm::Function*>> temp = functions;
    while (!temp.empty()) {
        auto& scope = temp.top();
        auto it = scope.find(name);
        if (it != scope.end()) {
            return it->second;
        }
        temp.pop();
    }
    return nullptr;
}