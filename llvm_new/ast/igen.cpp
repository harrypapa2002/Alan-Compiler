#include "ast.hpp"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>

// Initialize static members
llvm::LLVMContext AST::TheContext;
llvm::IRBuilder<> AST::Builder(AST::TheContext);
std::unique_ptr<llvm::Module> AST::TheModule;
std::unique_ptr<llvm::legacy::FunctionPassManager> AST::TheFPM;
llvm::Type *AST::proc = llvm::Type::getVoidTy(TheContext);
llvm::Type *AST::i8 = llvm::IntegerType::get(TheContext, 8);
llvm::Type *AST::i32 = llvm::IntegerType::get(TheContext, 32);
GenScope AST::scopes;
std::stack<GenBlock*> AST::blockStack;


llvm::ConstantInt *AST::c8(char c)
{
    return llvm::ConstantInt::get(TheContext, llvm::APInt(8, c, true));
}

llvm::ConstantInt *AST::c32(int n)
{
    return llvm::ConstantInt::get(TheContext, llvm::APInt(32, n, true));
}

llvm::ConstantArray *AST::ca8(std::string s)
{
    std::vector<llvm::Constant *> chars;
    for (char c : s)
    {
        chars.push_back(c8(c));
    }
    chars.push_back(c8('\0'));
    return llvm::dyn_cast<llvm::ConstantArray>(llvm::ConstantArray::get(llvm::ArrayType::get(i8, s.size() + 1), chars));
}

void AST::llvm_igen(bool optimize = true)
{
    TheModule = llvm::make_unique<llvm::Module>(filename, TheContext);

    scopes.openScope();
    // TODO:
    // codegenLibs();

    TheFPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());
    if (optimize)
    {
        TheFPM->add(llvm::createPromoteMemoryToRegisterPass());
        TheFPM->add(llvm::createInstructionCombiningPass());
        TheFPM->add(llvm::createReassociatePass());
        TheFPM->add(llvm::createGVNPass());
        TheFPM->add(llvm::createCFGSimplificationPass());
    }

    TheFPM->doInitialization();

    llvm::FunctionType *main_type = llvm::FunctionType::get(i32, {}, false);
    llvm::Function *main = llvm::Function::Create(main_type, llvm::Function::ExternalLinkage, "main", TheModule.get());
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);
    Builder.SetInsertPoint(BB);

    scopes.openScope();

    // Codegen the AST
    this->igen();

    // Invoke the main function of the source program
    FuncDef *mainFuncDef = dynamic_cast<FuncDef *>(this);
    if (mainFuncDef)
    {
        llvm::Function *sourceMainFunc = scopes.getFunction(*(mainFuncDef->getName()));
        if (sourceMainFunc)
        {
            Builder.CreateCall(sourceMainFunc, {});
        }
        else
        {
            std::cerr << "Error: main function not found in source program." << std::endl;
        }
    }

    // Return 0 from the LLVM main function
    Builder.CreateRet(c32(0));

    // Close the global scope
    scopes.closeScope();

    // Verify the IR
    bool bad = llvm::verifyModule(*TheModule, &llvm::errs());
    if (bad)
    {
        std::cerr << "The IR is bad!" << std::endl;
        TheModule->print(llvm::errs(), nullptr);
        std::exit(1);
    }

    // Optimize the module
    TheFPM->run(*main);

    // Print the IR
    TheModule->print(llvm::outs(), nullptr);
}

llvm::Value *StmtList::igen const override
{
    for (auto it = stmts.rbegin(); it != stmts.rend(); ++it)
    {
        auto stmt = *it;
        stmt->igen();
    }
    return nullptr;
}

llvm::Value *LocalDefList::igen const override
{
    for (auto it = defs.rbegin(); it != defs.rend(); ++it)
    {
        auto def = *it;
        def->igen();
    }
    return nullptr;
}

llvm::Value *IntConst::igen const override
{
    return c32(val);
}

llvm::Value *CharConst::igen const override
{
    return c8(val);
}

llvm::Value *BoolConst::igen const override
{
    return llvm::ConstantInt::get(TheContext, llvm::APInt(1, val, true));
}

llvm::Value *UnOp::igen const override
{
    llvm::Value *e = expr->igen();
    switch (op)
    {
    case '-':
        return Builder.CreateNeg(e, "negtmp");
    case '+':
        return e;
    default:
        return nullptr;
    }
}

llvm::Value *BinOp::igen const override
{
    llvm::Value *l = left->igen();
    llvm::Value *r = right->igen();
    switch (op)
    {
    case '+':
        return Builder.CreateAdd(l, r, "addtmp");
    case '-':
        return Builder.CreateSub(l, r, "subtmp");
    case '*':
        return Builder.CreateMul(l, r, "multmp");
    case '/':
        return Builder.CreateSDiv(l, r, "divtmp");
    case '%':
        return Builder.CreateSRem(l, r, "modtmp");
    default:
        return nullptr;
    }
}

llvm::Value *CondCompOp::igen const override
{
    llvm::Value *l = left->igen();
    llvm::Value *r = right->igen();
    switch (op)
    {
    case lt:
        return Builder.CreateICmpSLT(l, r, "lttmp");
    case gt:
        return Builder.CreateICmpSGT(l, r, "gttmp");
    case lte:
        return Builder.CreateICmpSLE(l, r, "ltetmp");
    case gte:
        return Builder.CreateICmpSGE(l, r, "gtetmp");
    case eq:
        return Builder.CreateICmpEQ(l, r, "eqtmp");
    case neq:
        return Builder.CreateICmpNE(l, r, "neqtmp");
    default:
        return nullptr;
    }
}

llvm::Value *CondBoolOp::igen const override
{
    llvm::Value *l = left->igen();
    llvm::Value *r = right->igen();
    switch (op)
    {
    case '&':
        return Builder.CreateAnd(l, r, "andtmp");
    case '|':
        return Builder.CreateOr(l, r, "ortmp");
    default:
        return nullptr;
    }
}

llvm::Value *CondUnOp::igen const override
{
    return Builder.CreateNot(cond->igen();, "nottmp");
}

llvm::Value *VarDef::igen const override{
    llvm::Type* t = translateType(type, ParameterType::VALUE);
    llvm::AllocaInst *Alloca = Builder.CreateAlloca(t, nullptr, *name);
    if (!blockStack.empty()) {
        GenBlock* currentBlock = blockStack.top();
        currentBlock->addLocal(*name, type, ParameterType::VALUE);
        currentBlock->addValue(*name, Alloca);
    } else {
        std::cerr << "Error: Block stack is empty, cannot add variable definition." << std::endl;
    }

    return nullptr;
}

