#include "ast.hpp"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

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

void AST::llvm_igen(bool optimize)
{
    isMain = true;
    TheModule = std::make_unique<llvm::Module>(filename, TheContext);

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
    //Builder.SetInsertPoint(BB);
    //scopes.openScope();

    // Codegen the AST
    this->igen();

    // Invoke the main function of the source program
    FuncDef *mainFuncDef = dynamic_cast<FuncDef *>(this);
    if (mainFuncDef)
    {
        llvm::Function *sourceMainFunc = scopes.getFunction(*(mainFuncDef->getName()));
        if (sourceMainFunc)
        {
            Builder.SetInsertPoint(BB);
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

llvm::Value *StmtList::igen() const 
{
    for (auto it = stmts.rbegin(); it != stmts.rend(); ++it)
    {
        auto stmt = *it;
        stmt->igen();
    }
    return nullptr;
}

llvm::Value *LocalDefList::igen() const 
{
    for (auto it = defs.rbegin(); it != defs.rend(); ++it)
    {
        auto def = *it;
        def->igen();
    }
    return nullptr;
}

llvm::Value *IntConst::igen() const 
{
    return c32(val);
}

llvm::Value *CharConst::igen() const 
{
    return c8(val);
}

llvm::Value *BoolConst::igen() const 
{
    return llvm::ConstantInt::get(TheContext, llvm::APInt(1, val, true));
}

llvm::Value *UnOp::igen() const 
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

llvm::Value *BinOp::igen() const 
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

llvm::Value *CondCompOp::igen() const 
{
    llvm::Value *l = left->igen();
    std::cout << "left type: " << l->getType()->getTypeID() << std::endl;
    llvm::Value *r = right->igen();
    std::cout << "right type: " << r->getType()->getTypeID() << std::endl;
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

llvm::Value *CondBoolOp::igen() const 
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

llvm::Value *CondUnOp::igen() const 
{
    return Builder.CreateNot(cond->igen(), "nottmp");
}

llvm::Value *VarDef::igen() const {
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

llvm::Value *Id::igen() const
{
    if (blockStack.empty())
    {
        std::cerr << "Error: Block stack is empty, cannot generate code for identifier." << std::endl;
        return nullptr;
    }

    GenBlock *currentBlock = blockStack.top();
    std::cout << "Generating code for identifier " << *name << std::endl;
    if (currentBlock->isReference(*name))
    {
        std::cout << "Generating code for reference" << std::endl;
        llvm::LoadInst *referenceAddress = Builder.CreateLoad(currentBlock->getLocal(*name), currentBlock->getAddress(*name));
        std::cout << "first loadinst ok\n";
        //std::cout << "deref " << currentBlock->getDeref(*name)->getTypeID() << std::endl;
        return Builder.CreateLoad(currentBlock->getDeref(*name), referenceAddress, "deref");
    }
    else
    {   
        llvm::AllocaInst * value = currentBlock->getValue(*name);
        return Builder.CreateLoad(value->getAllocatedType(), value);
    }
}


llvm::Value *ArrayAccess::igen() const
{
    if (blockStack.empty()) {
        std::cerr << "Error: Block stack is empty, cannot generate code for array access." << std::endl;
        return nullptr;
    }

    GenBlock* currentBlock = blockStack.top();
    llvm::AllocaInst* arrayPtr;
    llvm::Value* indexValue = indexExpr->igen();
    std::cout << "Generating code for array access " << *name << "["  << "]" << std::endl;
    llvm::Value* elementPtr;
    
    if (currentBlock->isReference(*name)) {
        arrayPtr = currentBlock->getAddress(*name);
        llvm::Value* arrayLoad = Builder.CreateLoad(currentBlock->getLocal(*name), arrayPtr, *name + "_arrayptr");
        std::cout << "first loadinst ok\n";
        elementPtr = Builder.CreateGEP(currentBlock->getDeref(*name), arrayLoad, indexValue, "elementptr");
        std::cout << "elementptr ok\n";
    } else {
        arrayPtr = currentBlock->getValue(*name);
        elementPtr = Builder.CreateGEP(currentBlock->getLocal(*name), arrayPtr, std::vector<llvm::Value*>({c32(0), indexValue}), "elementptr");
    }

    return elementPtr;
    
}

llvm::Value *Let::igen() const {
    llvm::Value* value = rexpr->igen();
    llvm::Value* l = lexpr->igen();
    if (l) {
        if(!l->getType()->isPointerTy()) {
            l = blockStack.top()->getValue(lexpr->getName());
        }
        Builder.CreateStore(value, l);
    } else {
        std::cerr << "Error: Variable " << " not found." << std::endl;
    }

    return nullptr;
}

llvm::Value *FuncCall::igen() const {
    llvm::Function* func = scopes.getFunction(*name);
    if (func) {
        std::vector<llvm::Value*> args;
        auto Exprs = exprs->getExprs();
        auto arg = func->arg_begin();
        for (auto it = Exprs.rbegin(); it != Exprs.rend(); ++it) {
            auto expr = *it;
            auto exprval = expr->igen();
            if (arg->getType()->isPointerTy()) {
                std::cout << "Creating call argument ref" << std::endl;
                args.push_back(exprval);
            } else {
                args.push_back(Builder.CreateLoad(arg->getType(), exprval, *name + "_arg"));
            }
            ++arg;
        }
        return Builder.CreateCall(func, args, *name + "_call");
    } else {
        std::cerr << "Error: Function " << *name << " not found." << std::endl;
    }

    return nullptr;
}

llvm::Value *If::igen() const {
    std::cout << "Generating code for if statement" << std::endl;
    llvm::Value *v = cond->igen();
    if (!v->getType()->isIntegerTy(32)) {
        v = Builder.CreateZExt(v, i32);
    }
    llvm::Value *condValue = Builder.CreateICmpNE(v, c32(0), "if_cond");
    llvm::Function* func = blockStack.top()->getFunc();
    llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(TheContext, "then", func);
    llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(TheContext, "else");
    llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(TheContext, "ifcont");

    Builder.CreateCondBr(condValue, thenBB, elseBB);

    Builder.SetInsertPoint(thenBB);
    blockStack.top()->setBlock(thenBB);
    std::cout << "Generating code for then statement" << std::endl;
    thenStmt->igen();
    Builder.CreateBr(mergeBB);
    thenBB = Builder.GetInsertBlock();

    func->getBasicBlockList().push_back(elseBB);
    Builder.SetInsertPoint(elseBB);
    if (elseStmt) {
        elseStmt->igen();
    }
    Builder.CreateBr(mergeBB);
    elseBB = Builder.GetInsertBlock();
    func->getBasicBlockList().push_back(mergeBB);
    Builder.SetInsertPoint(mergeBB);
    blockStack.top()->setBlock(mergeBB);

    return nullptr;
}

llvm::Value *While::igen() const {
    llvm::Function* func = Builder.GetInsertBlock()->getParent();
    llvm::BasicBlock* condBB = llvm::BasicBlock::Create(TheContext, "cond", func);
    llvm::BasicBlock* loopBB = llvm::BasicBlock::Create(TheContext, "loop");
    llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(TheContext, "afterloop");

    Builder.CreateBr(condBB);
    Builder.SetInsertPoint(condBB);
    llvm::Value* condValue = cond->igen();
    Builder.CreateCondBr(condValue, loopBB, afterBB);

    func->getBasicBlockList().push_back(loopBB);
    Builder.SetInsertPoint(loopBB);
    body->igen();
    Builder.CreateBr(condBB);

    func->getBasicBlockList().push_back(afterBB);
    Builder.SetInsertPoint(afterBB);

    return nullptr;
}


llvm::Value *Return::igen() const {
    llvm::Value* value = expr->igen();
    Builder.CreateRet(value);
    if (!blockStack.empty()) {
        GenBlock* currentBlock = blockStack.top();
        currentBlock->addReturn();
    } else {
        std::cerr << "Error: Block stack is empty, cannot add return statement." << std::endl;
    }

    return nullptr;
}

llvm::Value *FuncDef::igen() const {
    std::cout << "Generating code for function " << *name << std::endl;
    llvm::Type* returnType = translateType(type, ParameterType::VALUE);
    std::vector<llvm::Type*> argTypes;
    auto args = std::vector<Fpar*>();
    if(fpar)
        args = fpar->getParameters();
        
    for (auto it = args.rbegin(); it != args.rend(); ++it) {
        auto arg = *it;
        argTypes.push_back(translateType(arg->type, arg->parameterType));
        //arg->igen();
    }
    llvm::FunctionType* funcType = llvm::FunctionType::get(returnType, argTypes, false);
    llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, *name, TheModule.get());
    
    scopes.addFunction(*name, func);


    llvm::BasicBlock* BB = llvm::BasicBlock::Create(TheContext, *name + "_entry", func);
    Builder.SetInsertPoint(BB);
    
    GenBlock* currentBlock = new GenBlock();
    currentBlock->setFunc(func);
    currentBlock->setBlock(BB);
    blockStack.push(currentBlock);
    scopes.openScope();
    
    auto argIt = args.rbegin();
    for (auto arg = func->arg_begin(); arg != func->arg_end(); ++arg) {
        std::cout << "Adding argument2 " << *(*argIt)->name << std::endl;
        arg->setName(*(*argIt)->name);
        llvm::AllocaInst* Alloca = Builder.CreateAlloca(arg->getType(), nullptr, *(*argIt)->name);
        Builder.CreateStore(arg, Alloca);
        currentBlock->addArg(*(*argIt)->name, (*argIt)->type, (*argIt)->parameterType);
        if ((*argIt)->parameterType == ParameterType::REFERENCE) {
            currentBlock->addDeref(*(*argIt)->name, (*argIt)->type, ParameterType::VALUE);
            currentBlock->addAddress(*(*argIt)->name, Alloca);
        } else {
            currentBlock->addValue(*(*argIt)->name, Alloca);
        }
        ++argIt;
    }
    std::cout << "localdefs" << std::endl;
    localDef->igen();
    std::cout << "stmts" << std::endl;
    stmts->igen();

    if (!currentBlock->hasReturn()) {
        Builder.CreateRetVoid();
    }

    blockStack.pop();
    scopes.closeScope();

    if(!isMain)
        Builder.SetInsertPoint(blockStack.top()->getBlock());

    return nullptr;
}

llvm::Value *ExprList::igen() const {
    for (auto it = exprs.rbegin(); it != exprs.rend(); ++it) {
        auto expr = *it;
        expr->igen();
    }
    return nullptr;
}

llvm::Value *StringConst::igen() const {
    return Builder.CreateGlobalStringPtr(*name);
}

llvm::Value *ProcCall::igen() const {
    std::cout << "Generating code for procedure call" << std::endl;
    llvm::Function* func = scopes.getFunction(*funcCall->name);
    if (func) {
        std::vector<llvm::Value*> args;
        auto Exprs = funcCall->exprs->getExprs();
        auto arg = func->arg_begin();
        for (auto it = Exprs.rbegin(); it != Exprs.rend(); ++it) {
            auto expr = *it;
            std::cout << "Creating call argument" << std::endl;
            llvm::Value* exprval = expr->igen();
            if (arg->getType()->isPointerTy()) {
                std::cout << "Creating call argument ref" << std::endl;
                if (exprval->getTypeEnum() == TypeEnum::ARRAY) {
                    args.push_back(exprval);
                } else {
                    args.push_back(Builder.CreateLoad(arg->getType(), exprval, *funcCall->name + "_arg"));
                }
            } else {
                args.push_back(exprval);
            }
            ++arg;
        }
        std::cout << "Creating call" << std::endl;
        return Builder.CreateCall(func, args);
    } else {
        std::cerr << "Error: Function " << *funcCall->name << " not found." << std::endl;
    }
    
    return nullptr;
}

llvm::Value *Empty::igen() const {
    std::cout << "Empty" << std::endl;
    return nullptr;
}

