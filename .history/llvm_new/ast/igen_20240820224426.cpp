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
std::stack<GenBlock *> AST::blockStack;

llvm::ConstantInt *AST::c1(bool c)
{
    return llvm::ConstantInt::get(TheContext, llvm::APInt(1, c, true));
}

llvm::ConstantInt *AST::c8(char c)
{
    return llvm::ConstantInt::get(TheContext, llvm::APInt(8, c, true));
}

llvm::ConstantInt *AST::c32(int n)
{
    return llvm::ConstantInt::get(TheContext, llvm::APInt(32, n, true));
}

// TODO:: Remove "if" clauses lines 62-76
void AST::llvm_igen(bool optimize)
{
    TheModule = std::make_unique<llvm::Module>(filename, TheContext);

    scopes.openScope();

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
    codegenLibs();

    llvm::FunctionType *main_type = llvm::FunctionType::get(i32, {}, false);
    llvm::Function *main = llvm::Function::Create(main_type, llvm::Function::ExternalLinkage, "main", TheModule.get());
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);

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
    return c1(val);
}

llvm::Value *UnOp::igen() const
{
    llvm::Value *loadedExpr = expr->igen();
    if (llvm::isa<llvm::AllocaInst>(loadedExpr))
    {
        llvm::AllocaInst *exprAlloc = llvm::cast<llvm::AllocaInst>(loadedExpr);
        loadedExpr = Builder.CreateLoad(exprAlloc->getAllocatedType(), exprAlloc, "load_expr");
    }
    else if(loadedExpr->getType()->isPointerTy()){
        loadedExpr = Builder.CreateLoad(translateType(expr->getType(), ParameterType::VALUE), loadedExpr, "load_expr");
    }
    
    llvm::Value *result = nullptr;

    switch (op)
    {
    case '-':
        result = Builder.CreateNeg(loadedExpr, "negtmp");
        break;
    case '+':
        result = loadedExpr;
        break;
    default:
        return nullptr;
    }

    llvm::AllocaInst *alloca = Builder.CreateAlloca(result->getType(), nullptr, "unop_tmp");
    Builder.CreateStore(result, alloca);
    return alloca;
}

llvm::Value *BinOp::igen() const
{
    llvm::Value *leftVal = left->igen();
    llvm::Value *rightVal = right->igen();

    if (llvm::isa<llvm::AllocaInst>(leftVal))
    {
        llvm::AllocaInst *leftAlloc = llvm::cast<llvm::AllocaInst>(leftVal);
        leftVal = Builder.CreateLoad(leftAlloc->getAllocatedType(), leftAlloc, "left_load");
    }
    else if(leftVal->getType()->isPointerTy()){
        leftVal = Builder.CreateLoad(translateType(left->getType(), ParameterType::VALUE), leftVal, "left_load");
    }

    if (llvm::isa<llvm::AllocaInst>(rightVal))
    {
        llvm::AllocaInst *rightAlloc = llvm::cast<llvm::AllocaInst>(rightVal);
        rightVal = Builder.CreateLoad(rightAlloc->getAllocatedType(), rightAlloc, "right_load");
    }
    else if(rightVal->getType()->isPointerTy()){
        rightVal = Builder.CreateLoad(translateType(right->getType(), ParameterType::VALUE), rightVal, "right_load");
    }

    llvm::Value *result = nullptr;

    switch (op)
    {
    case '+':
        result = Builder.CreateAdd(leftVal, rightVal, "addtmp");
        break;
    case '-':
        result = Builder.CreateSub(leftVal, rightVal, "subtmp");
        break;
    case '*':
        result = Builder.CreateMul(leftVal, rightVal, "multmp");
        break;
    case '/':
        result = Builder.CreateSDiv(leftVal, rightVal, "divtmp");
        break;
    case '%':
        result = Builder.CreateSRem(leftVal, rightVal, "modtmp");
        break;
    default:
        return nullptr;
    }

    llvm::AllocaInst *alloca = Builder.CreateAlloca(result->getType(), nullptr, "binop_tmp");
    Builder.CreateStore(result, alloca);
    return alloca;
}

llvm::Value *CondCompOp::igen() const
{
    llvm::Value *leftVal = left->igen();
    llvm::Value *rightVal = right->igen();
    // std::cout << "op left done\n";
    if (llvm::isa<llvm::AllocaInst>(leftVal))
    {
        // std::cout << "left is an alloca\n";
        llvm::AllocaInst *leftAlloc = llvm::cast<llvm::AllocaInst>(leftVal);
        leftVal = Builder.CreateLoad(leftAlloc->getAllocatedType(), leftAlloc, "left_load");
    }
    else if(leftVal->getType()->isPointerTy()){
        leftVal = Builder.CreateLoad(translateType(left->getType(), ParameterType::VALUE), leftVal, "left_load");
    }

    if (llvm::isa<llvm::AllocaInst>(rightVal))
    {
        llvm::AllocaInst *rightAlloc = llvm::cast<llvm::AllocaInst>(rightVal);
        rightVal = Builder.CreateLoad(rightAlloc->getAllocatedType(), rightAlloc, "right_load");
    }
    else if(rightVal->getType()->isPointerTy()){
        rightVal = Builder.CreateLoad(translateType(right->getType(), ParameterType::VALUE), rightVal, "right_load");
    }
    
    llvm::Value *result = nullptr;
    switch (op)
    {
        // std::cout << "op switch\n";
    case lt:
        result = Builder.CreateICmpSLT(leftVal, rightVal, "lttmp");
        break;
    case gt:
        result = Builder.CreateICmpSGT(leftVal, rightVal, "gttmp");
        break;
    case lte:
        result = Builder.CreateICmpSLE(leftVal, rightVal, "ltetmp");
        break;
    case gte:
        result = Builder.CreateICmpSGE(leftVal, rightVal, "gtetmp");
        break;
    case eq:
        result = Builder.CreateICmpEQ(leftVal, rightVal, "eqtmp");
        break;
    case neq:
        result = Builder.CreateICmpNE(leftVal, rightVal, "neqtmp");
        break;
    default:
        return nullptr;
    }

    // std::cout << "op done\n";
    return result;
}

llvm::Value *CondBoolOp::igen() const
{
    llvm::Value *leftValue = left->igen();
    llvm::Value *rightValue = right->igen();

    llvm::Value *result;
    switch (op)
    {
    case '&':
        result = Builder.CreateAnd(leftValue, rightValue, "andtmp");
        break;
    case '|':
        result = Builder.CreateOr(leftValue, rightValue, "ortmp");
        break;
    default:
        return nullptr;
    }

    return result;
}

llvm::Value *CondUnOp::igen() const
{
    llvm::Value *condValue = cond->igen();
    llvm::Value *result = Builder.CreateNot(condValue, "nottmp");

    return result;
}

// TODO: Remove addLocal
llvm::Value *VarDef::igen() const
{
    llvm::Type *t = nullptr;

    if (isArray)
    {
        llvm::Type *elementType = translateType(type->getBaseType(), ParameterType::VALUE);
        t = llvm::ArrayType::get(elementType, size);
    }
    else
    {
        t = translateType(type, ParameterType::VALUE);
    }

    llvm::AllocaInst *Alloca = Builder.CreateAlloca(t, nullptr, *name);

    GenBlock *currentBlock = blockStack.top();
    currentBlock->addAlloca(*name, Alloca);

    return nullptr;
}

llvm::Value *Id::igen() const
{
    GenBlock *currentBlock = blockStack.top();
    llvm::AllocaInst *allocaInst = currentBlock->getAlloca(*name);

    if (allocaInst->getAllocatedType()->isPointerTy())
    {
        return Builder.CreateLoad(allocaInst->getAllocatedType(), allocaInst, *name + "_load");
    }
    else
    {
        return allocaInst;
    }
}

// TODO: Check references here
llvm::Value *ArrayAccess::igen() const
{
    GenBlock *currentBlock = blockStack.top();

    llvm::Value *indexValue = indexExpr->igen();

    if (llvm::isa<llvm::AllocaInst>(indexValue))
    {
        llvm::AllocaInst *indexAllocInst = llvm::cast<llvm::AllocaInst>(indexValue);
        indexValue = Builder.CreateLoad(indexAllocInst->getAllocatedType(), indexAllocInst, "load_index");
    }
    else if (indexValue->getType()->isPointerTy())
    {
        indexValue = Builder.CreateLoad(indexValue->getType(), indexValue, "load_index");
    }

    // std::cout << "Generated code for index expression" << std::endl;

    llvm::Type *elementType = translateType(type, ParameterType::VALUE);

    // std::cout << elementType->getTypeID() << std::endl;

    llvm::AllocaInst *arrayPtrAlloc = currentBlock->getAlloca(*name);
    llvm::Value *elementPtr = nullptr;

    if (!arrayPtrAlloc->getAllocatedType()->isArrayTy())
    {
        llvm::Value *arrayLoad = Builder.CreateLoad(arrayPtrAlloc->getAllocatedType(), arrayPtrAlloc, *name + "_arrayptr");

        elementPtr = Builder.CreateGEP(elementType, arrayLoad, indexValue, "elementptr");
        //`std::cerr << "Generated GEP for element access" << std::endl;
    }
    else
    {
        elementPtr = Builder.CreateGEP(arrayPtrAlloc->getAllocatedType(), arrayPtrAlloc, std::vector<llvm::Value *>({c32(0), indexValue}), "elementptr");
    }

    // std::cout << "Generated code for array access" << std::endl;

    return elementPtr;
}

llvm::Value *Let::igen() const
{
    // std::cout << "Let::igen()" << *lexpr << "\n"<< *rexpr << std::endl;
    llvm::Value *rValue = rexpr->igen();
    if (llvm::isa<llvm::AllocaInst>(rValue))
    {
        llvm::AllocaInst *rValueAlloc = llvm::cast<llvm::AllocaInst>(rValue);
        rValue = Builder.CreateLoad(rValueAlloc->getAllocatedType(), rValueAlloc);
    }
    else if (rValue->getType()->isPointerTy())
    {
        rValue = Builder.CreateLoad(translateType(lexpr->getType(), ParameterType::VALUE), rValue);
    }

    llvm::Value *lValue = lexpr->igen();

    Builder.CreateStore(rValue, lValue);

    return nullptr;
}

llvm::Value *FuncCall::igen() const
{
    llvm::Function *func = scopes.getFunction(*name);
    std::vector<llvm::Value *> args;

    if (exprs)
    {
        auto funcArgs = func->args();
        auto exprList = exprs->getExprs();
        auto exprIt = exprList.rbegin();
        for (auto &arg : funcArgs)
        {
            llvm::Value *argAlloc = (*exprIt)->igen();
            ++exprIt;

            if (arg.getType()->isPointerTy())
            {
                // If the function argument expects a pointer, pass the alloca directly (handles references)
                args.push_back(argAlloc);
            }
            else
            {
                // If the function argument expects a value, load the value from the alloca
                if (argAlloc->getType()->isPointerTy())
                {
                    llvm::Value *loadedValue = Builder.CreateLoad(arg.getType(), argAlloc, *name + "_arg");
                    args.push_back(loadedValue);
                }
                else
                {
                    args.push_back(argAlloc);
                }
            }
        }
    }

    if ( func->getReturnType()->isVoidTy())
    {
        Builder.CreateCall(func, args);
        return nullptr;
    }

    return Builder.CreateCall(func, args, *name + "_call");
}

llvm::Value *If::igen() const
{
    llvm::Value *condValue = cond->igen();
    llvm::Function *func = blockStack.top()->getFunc();
    llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(TheContext, "then", func);
    llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(TheContext, "else");
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(TheContext, "ifcont");

    if (!condValue->getType()->isIntegerTy(32))
    {
        condValue = Builder.CreateZExt(condValue, i32);
    }

    condValue = Builder.CreateICmpNE(condValue, c32(0), "if_cond");

    Builder.CreateCondBr(condValue, thenBB, elseBB);

    Builder.SetInsertPoint(thenBB);
    blockStack.top()->setBlock(thenBB);
    thenStmt->igen();

    if (!Builder.GetInsertBlock()->getTerminator())
    {
        Builder.CreateBr(mergeBB);
    }

    func->getBasicBlockList().push_back(elseBB);
    Builder.SetInsertPoint(elseBB);
    blockStack.top()->setBlock(elseBB);
    if (elseStmt)
    {
        elseStmt->igen();
    }

    if (!Builder.GetInsertBlock()->getTerminator())
    {
        Builder.CreateBr(mergeBB);
    }

    func->getBasicBlockList().push_back(mergeBB);
    Builder.SetInsertPoint(mergeBB);
    blockStack.top()->setBlock(mergeBB);

    return nullptr;
}

llvm::Value *While::igen() const
{
    llvm::Function *TheFunction = blockStack.top()->getFunc();
    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(TheContext, "cond", TheFunction);
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(TheContext, "loop");
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterloop");

    Builder.CreateBr(condBB);
    Builder.SetInsertPoint(condBB);
    blockStack.top()->setBlock(condBB);

    llvm::Value *condValue = cond->igen();

    if (!condValue->getType()->isIntegerTy(32))
    {
        condValue = Builder.CreateZExt(condValue, i32);
    }

    condValue = Builder.CreateICmpNE(condValue, c32(0), "while_cond");

    Builder.CreateCondBr(condValue, loopBB, afterBB);

    TheFunction->getBasicBlockList().push_back(loopBB);
    Builder.SetInsertPoint(loopBB);
    blockStack.top()->setBlock(loopBB);
    body->igen();
    Builder.CreateBr(condBB);

    TheFunction->getBasicBlockList().push_back(afterBB);
    Builder.SetInsertPoint(afterBB);
    blockStack.top()->setBlock(afterBB);

    return nullptr;
}

// TODO:: Remove "if" related to blockstack.empty()
llvm::Value *Return::igen() const
{
    if (!expr)
    {
        Builder.CreateRetVoid();
    }
    else
    {
        llvm::Value *value = Builder.CreateLoad(translateType(expr->getType(), ParameterType::VALUE), expr->igen(), "ret_val");
        Builder.CreateRet(value);
    }

    return nullptr;
}

llvm::Value *FuncDef::igen() const
{
    llvm::Type *returnType = translateType(type, ParameterType::VALUE);
    std::vector<llvm::Type *> argTypes;
    auto args = fpar ? fpar->getParameters() : std::vector<Fpar *>();

    for (auto it = args.rbegin(); it != args.rend(); ++it)
    {
        auto arg = *it;
        argTypes.push_back(translateType(arg->getType(), arg->getParameterType()));
    }
    llvm::FunctionType *funcType = llvm::FunctionType::get(returnType, argTypes, false);
    llvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, *name, TheModule.get());

    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, *name + "_entry", func);
    Builder.SetInsertPoint(BB);

    GenBlock *currentBlock = new GenBlock();
    currentBlock->setFunc(func);
    currentBlock->setBlock(BB);
    blockStack.push(currentBlock);

    scopes.addFunction(*name, func);
    scopes.openScope();

    if (fpar)
    {
        unsigned index = args.size();
        for (auto &param : func->args())
        {
            --index;
            param.setName(*args[index]->getName());

            llvm::AllocaInst *Alloca = Builder.CreateAlloca(param.getType(), nullptr, *args[index]->getName());

            Builder.CreateStore(&param, Alloca);
            currentBlock->addAlloca(*args[index]->getName(), Alloca);
        }
    }
    localDef->igen();
    stmts->igen();

    if (!hasReturn)
    {
        Builder.CreateRetVoid();
    }

    blockStack.pop();
    scopes.closeScope();

    if (!blockStack.empty())
        Builder.SetInsertPoint(blockStack.top()->getBlock());

    return nullptr;
}

llvm::Value *ExprList::igen() const
{
    for (auto it = exprs.rbegin(); it != exprs.rend(); ++it)
    {
        auto expr = *it;
        expr->igen();
    }
    return nullptr;
}

llvm::Value *StringConst::igen() const
{
    // Create a global string constant in the module
    llvm::Constant *globalStr = Builder.CreateGlobalStringPtr(*name, "global_str");

    // Calculate the length of the string including the null terminator
    size_t strLength = name->length() + 1;

    // Create an alloca instruction to allocate space for the string on the stack
    llvm::AllocaInst *alloca = Builder.CreateAlloca(llvm::ArrayType::get(i8, strLength), nullptr, "str_const_alloca");

    // Copy the global string to the stack-allocated memory
    Builder.CreateMemCpy(alloca, llvm::MaybeAlign(1), globalStr, llvm::MaybeAlign(1), c32(strLength));

    // Return the alloca instruction
    return alloca;
}

llvm::Value *ProcCall::igen() const
{
    return funcCall->igen();
}

llvm::Value *Empty::igen() const
{
    return nullptr;
}

void AST::codegenLibs()
{
    llvm::FunctionType *writeIntegerType =
        llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i32}, false);
    scopes.addFunction("writeInteger", llvm::Function::Create(writeIntegerType, llvm::Function::ExternalLinkage, "writeInteger", TheModule.get()));
    llvm::FunctionType *writeByteType =
        llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i8}, false);
    scopes.addFunction("writeByte", llvm::Function::Create(writeByteType, llvm::Function::ExternalLinkage, "writeByte", TheModule.get()));
    llvm::FunctionType *writeCharType =
        llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i8}, false);
    scopes.addFunction("writeChar", llvm::Function::Create(writeCharType, llvm::Function::ExternalLinkage, "writeChar", TheModule.get()));
    llvm::FunctionType *writeStringType =
        llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i8->getPointerTo()}, false);
    scopes.addFunction("writeString", llvm::Function::Create(writeStringType, llvm::Function::ExternalLinkage, "writeString", TheModule.get()));
    llvm::FunctionType *readIntegerType =
        llvm::FunctionType::get(i32, std::vector<llvm::Type *>{}, false);
    scopes.addFunction("readInteger", llvm::Function::Create(readIntegerType, llvm::Function::ExternalLinkage, "readInteger", TheModule.get()));
    llvm::FunctionType *readByteType =
        llvm::FunctionType::get(i8, std::vector<llvm::Type *>{}, false);
    scopes.addFunction("readByte", llvm::Function::Create(readByteType, llvm::Function::ExternalLinkage, "readByte", TheModule.get()));
    llvm::FunctionType *readCharType =
        llvm::FunctionType::get(i8, std::vector<llvm::Type *>{}, false);
    scopes.addFunction("readChar", llvm::Function::Create(readCharType, llvm::Function::ExternalLinkage, "readChar", TheModule.get()));
    llvm::FunctionType *readStringType =
        llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i32, i8->getPointerTo()}, false);
    scopes.addFunction("readString", llvm::Function::Create(readStringType, llvm::Function::ExternalLinkage, "readString", TheModule.get()));
    llvm::FunctionType *extendType =
        llvm::FunctionType::get(i32, std::vector<llvm::Type *>{i8}, false);
    scopes.addFunction("extend", llvm::Function::Create(extendType, llvm::Function::ExternalLinkage, "extend", TheModule.get()));
    llvm::FunctionType *shrinkType =
        llvm::FunctionType::get(i8, std::vector<llvm::Type *>{i32}, false);
    scopes.addFunction("shrink", llvm::Function::Create(shrinkType, llvm::Function::ExternalLinkage, "shrink", TheModule.get()));
    llvm::FunctionType *strlenType =
        llvm::FunctionType::get(i32, std::vector<llvm::Type *>{i8->getPointerTo()}, false);
    scopes.addFunction("strlen", llvm::Function::Create(strlenType, llvm::Function::ExternalLinkage, "strlen", TheModule.get()));
    llvm::FunctionType *strcmpType =
        llvm::FunctionType::get(i32, std::vector<llvm::Type *>{i8->getPointerTo(), i8->getPointerTo()}, false);
    scopes.addFunction("strcmp", llvm::Function::Create(strcmpType, llvm::Function::ExternalLinkage, "strcmp", TheModule.get()));
    llvm::FunctionType *strcpyType =
        llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i8->getPointerTo(), i8->getPointerTo()}, false);
    scopes.addFunction("strcpy", llvm::Function::Create(strcpyType, llvm::Function::ExternalLinkage, "strcpy", TheModule.get()));
    llvm::FunctionType *strcatType =
        llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i8->getPointerTo(), i8->getPointerTo()}, false);
    scopes.addFunction("strcat", llvm::Function::Create(strcatType, llvm::Function::ExternalLinkage, "strcat", TheModule.get()));
}