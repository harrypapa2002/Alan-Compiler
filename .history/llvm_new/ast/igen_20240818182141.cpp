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
llvm::Type *AST::i1 = llvm::IntegerType::get(TheContext, 1);
llvm::Type *AST::i8 = llvm::IntegerType::get(TheContext, 8);
llvm::Type *AST::i32 = llvm::IntegerType::get(TheContext, 32);
GenScope AST::scopes;
std::stack<GenBlock *> AST::blockStack;

llvm::ConstantInt *AST::c1(bool b)
{
    return llvm::ConstantInt::get(TheContext, llvm::APInt(1, b, true));
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
    // TODO:
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
    ////std::cout << "Generating code for local definition list" << std::endl;
    for (auto it = defs.rbegin(); it != defs.rend(); ++it)
    {
        auto def = *it;
        def->igen();
    }
    return nullptr;
}

llvm::Value *IntConst::igen() const
{
    //std::cout << "Generating code for integer constant " << val << std::endl;
    llvm::AllocaInst *alloca = Builder.CreateAlloca(i32, nullptr, "int_const");
    Builder.CreateStore(c32(val), alloca);
    return alloca;
}

llvm::Value *CharConst::igen() const
{
    //std::cout << "Generating code for character constant " << val << std::endl;
    llvm::AllocaInst *alloca = Builder.CreateAlloca(i8, nullptr, "char_const");
    Builder.CreateStore(c8(val), alloca);
    return alloca;
}

llvm::Value *BoolConst::igen() const
{
    //std::cout << "Generating code for boolean constant " << val << std::endl;
    llvm::AllocaInst *alloca = Builder.CreateAlloca(i1, nullptr, "bool_const");
    Builder.CreateStore(c1(val), alloca);
    return alloca;
}

llvm::Value *UnOp::igen() const
{
    //std::cout << "Generating code for unary operation" << std::endl;
    llvm::AllocaInst *allocaExpr = llvm::cast<llvm::AllocaInst>(expr->igen());
    llvm::Value *loadedExpr = Builder.CreateLoad(allocaExpr->getAllocatedType(), allocaExpr, "load_unop");
    llvm::AllocaInst *alloca = Builder.CreateAlloca(loadedExpr->getType(), nullptr, "unop_tmp");
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

    Builder.CreateStore(result, alloca);
    return alloca;
}

llvm::Value *BinOp::igen() const
{
    //std::cout << "Generating code for binary operation" << std::endl;
    llvm::AllocaInst *l = llvm::cast<llvm::AllocaInst>(left->igen());
    llvm::AllocaInst *r = llvm::cast<llvm::AllocaInst>(right->igen());

    llvm::Type *t = l->getAllocatedType();

    llvm::AllocaInst *alloca = Builder.CreateAlloca(t, nullptr, "binop_tmp");

    llvm::Value *leftVal = Builder.CreateLoad(t, l);
    llvm::Value *rightVal = Builder.CreateLoad(t, r);

    switch (op)
    {
    case '+':
        Builder.CreateStore(Builder.CreateAdd(leftVal, rightVal, "addtmp"), alloca);
        break;
    case '-':
        Builder.CreateStore(Builder.CreateSub(leftVal, rightVal, "subtmp"), alloca);
        break;
    case '*':
        Builder.CreateStore(Builder.CreateMul(leftVal, rightVal, "multmp"), alloca);
        break;
    case '/':
        Builder.CreateStore(Builder.CreateSDiv(leftVal, rightVal, "divtmp"), alloca);
        break;
    case '%':
        Builder.CreateStore(Builder.CreateSRem(leftVal, rightVal, "modtmp"), alloca);
        break;
    default:
        return nullptr;
    }

    return alloca;
}

llvm::Value *CondCompOp::igen() const
{
    //std::cout << "Generating code for conditional comparison operation" << std::endl;
    llvm::AllocaInst *l = llvm::cast<llvm::AllocaInst>(left->igen());
    llvm::AllocaInst *r = llvm::cast<llvm::AllocaInst>(right->igen());

    llvm::Type *t = l->getAllocatedType();

    llvm::AllocaInst *alloca = Builder.CreateAlloca(t, nullptr, "compop_tmp");

    llvm::Value *leftVal = Builder.CreateLoad(t, l);
    llvm::Value *rightVal = Builder.CreateLoad(t, r);

    llvm::Value *result;
    switch (op)
    {
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

    Builder.CreateStore(result, alloca);
    return alloca;
}

llvm::Value *CondBoolOp::igen() const
{
    //std::cout << "Generating code for conditional boolean operation" << std::endl;
    llvm::AllocaInst *l = llvm::cast<llvm::AllocaInst>(left->igen());
    llvm::AllocaInst *r = llvm::cast<llvm::AllocaInst>(right->igen());

    llvm::Type *t = l->getAllocatedType();

    llvm::AllocaInst *alloca = Builder.CreateAlloca(t, nullptr, "boolop_tmp");

    llvm::Value *leftVal = Builder.CreateLoad(t, l);
    llvm::Value *rightVal = Builder.CreateLoad(t, r);

    llvm::Value *result;
    switch (op)
    {
    case '&':
        result = Builder.CreateAnd(leftVal, rightVal, "andtmp");
        break;
    case '|':
        result = Builder.CreateOr(leftVal, rightVal, "ortmp");
        break;
    default:
        return nullptr;
    }

    Builder.CreateStore(result, alloca);
    return alloca;
}

llvm::Value *CondUnOp::igen() const
{
    //std::cout << "Generating code for conditional unary operation" << std::endl;
    llvm::AllocaInst *c = llvm::cast<llvm::AllocaInst>(cond->igen());

    llvm::Type *condType = c->getAllocatedType();

    llvm::AllocaInst *alloca = Builder.CreateAlloca(condType, nullptr, "unop_tmp");

    llvm::Value *condVal = Builder.CreateLoad(condType, c);
    llvm::Value *result = Builder.CreateNot(condVal, "nottmp");

    Builder.CreateStore(result, alloca);
    return alloca;
}

// TODO: Remove addLocal
llvm::Value *VarDef::igen() const
{
    //std::cout << "Generating code for variable definition: " << *name << std::endl;
    llvm::Type *t = nullptr;

    if (isArray)
    {
        llvm::Type *elementType = translateType(type, ParameterType::VALUE);
        t = llvm::ArrayType::get(elementType, size);
    }
    else
    {
        t = translateType(type, ParameterType::VALUE);
    }

    llvm::AllocaInst *Alloca = Builder.CreateAlloca(t, nullptr, *name);

    if (!blockStack.empty())
    {
        GenBlock *currentBlock = blockStack.top();
        currentBlock->addAlloca(*name, Alloca);
    }
    else
    {
        std::cerr << "Error: Block stack is empty, cannot add variable definition." << std::endl;
    }

    return nullptr;
}
// TODO:: Remove "if" related to blockstack.empty() and "cout", check getPointerElementType() to avoid use of deref if possible
llvm::Value *Id::igen() const
{
    if (blockStack.empty())
    {
        std::cerr << "Error: Block stack is empty, cannot generate code for identifier." << std::endl;
        return nullptr;
    }

    GenBlock *currentBlock = blockStack.top();
    // std::cout << "Generating code for identifier " << *name << std::endl;
    llvm::AllocaInst *allocaInst = currentBlock->getAlloca(*name);

    if (allocaInst->getAllocatedType()->isPointerTy())
    {
        llvm::Type *allocatedType = allocaInst->getAllocatedType();
        return Builder.CreateLoad(allocatedType, allocaInst, *name + "_load");
    }
    else
    {
        return allocaInst;
    }
}

// TODO: Check references here
llvm::Value *ArrayAccess::igen() const
{

    if (blockStack.empty())
    {
        std::cerr << "Error: Block stack is empty, cannot generate code for array access." << std::endl;
        return nullptr;
    }

    GenBlock *currentBlock = blockStack.top();

    // Generate code for the index expression
    llvm::AllocaInst *indexAlloc = llvm::cast<llvm::AllocaInst>(indexExpr->igen());
    llvm::Value *indexValue = Builder.CreateLoad(indexAlloc->getAllocatedType(), indexAlloc, "load_index");

    //std::cout << "Generating code for array access " << *name << "[" << "]" << std::endl;

    llvm::Type *elementType = translateType(type, ParameterType::VALUE);
    llvm::AllocaInst *arrayPtrAlloc = currentBlock->getAlloca(*name);
    llvm::Value *elementPtr = nullptr;

    if (arrayPtrAlloc->getAllocatedType()->isPointerTy())
    {
        // If the array is a reference, load the pointer to the array
        llvm::Value *arrayLoad = Builder.CreateLoad(arrayPtrAlloc->getAllocatedType(), arrayPtrAlloc, *name + "_arrayptr");

        // Here we expect the arrayLoad to be a pointer to an array, so we cast it as needed
        elementPtr = Builder.CreateGEP(elementType, arrayLoad, indexValue, "elementptr");
        std::cerr << "Generated GEP for element access" << std::endl;
    }
    else
    {
        elementPtr = Builder.CreateGEP(arrayPtrAlloc->getAllocatedType(), arrayPtrAlloc, std::vector<llvm::Value *>({c32(0), indexValue}), "elementptr");
    }

    llvm::AllocaInst *alloca = Builder.CreateAlloca(elementType, nullptr, "array_element");
    llvm::Value *elementValue = Builder.CreateLoad(elementType, elementPtr, "element_value");
    Builder.CreateStore(elementValue, alloca);

    return alloca;
}

llvm::Value *Let::igen() const
{
    //std::cout << "Generating code for let statement" << std::endl;

    llvm::AllocaInst *rValueAlloc = llvm::cast<llvm::AllocaInst>(rexpr->igen());
    llvm::AllocaInst *lValueAlloc = llvm::cast<llvm::AllocaInst>(lexpr->igen());

    llvm::Type *rValueType = rValueAlloc->getAllocatedType();

    llvm::Value *rValue = Builder.CreateLoad(rValueType, rValueAlloc);

    Builder.CreateStore(rValue, lValueAlloc);

    return nullptr;
}

llvm::Value *FuncCall::igen() const
{
    //std::cout << "Generating code for function call " << *name << std::endl;
    llvm::Function *func = scopes.getFunction(*name);
    std::vector<llvm::Value *> args;

    if (exprs)
    {
        auto funcArgs = func->args();
        auto exprList = exprs->getExprs();
        auto exprIt = exprList.rbegin(); 
        for (auto &arg : funcArgs)
        {
            // std::cout << "arg: " << arg.getName().str() << std::endl;
            llvm::AllocaInst *argAlloc = llvm::cast<llvm::AllocaInst>((*exprIt)->igen());
            ++exprIt;

            if (arg.getType()->isPointerTy())
            {
                // If the function argument expects a pointer, pass the alloca directly (handles references)
                args.push_back(argAlloc);
            }
            else
            {
                // If the function argument expects a value, load the value from the alloca
                llvm::Value *loadedValue = Builder.CreateLoad(argAlloc->getAllocatedType(), argAlloc, *name + "_arg");
                args.push_back(loadedValue);
            }
        }
    }

    llvm::Type *returnType = func->getReturnType();
    // std::cout << "Function return type settled" << std::endl;

    if (returnType->isVoidTy())
    {
        // If the function returns void, just call the function and return nullptr
        Builder.CreateCall(func, args);
        // std::cout << "Function call generated for void return type" << std::endl;
        return nullptr;
    }

    // Create an alloca for the return value
    llvm::AllocaInst *retAlloca = Builder.CreateAlloca(returnType, nullptr, *name + "_ret");
    // std::cout << "Alloca for return value created" << std::endl;

    // Generate the function call
    llvm::Value *callResult = Builder.CreateCall(func, args, *name + "_call");
    // std::cout << "Function call generated" << std::endl;

    // Store the function call result in the alloca
    Builder.CreateStore(callResult, retAlloca);

    return retAlloca;
}

llvm::Value *If::igen() const
{
    ////std::cout << "Generating code for if statement" << std::endl;
    llvm::AllocaInst *condAlloc = llvm::cast<llvm::AllocaInst>(cond->igen());
    llvm::Value *v = Builder.CreateLoad(condAlloc->getAllocatedType(), condAlloc);

    if (!v->getType()->isIntegerTy(32))
    {
        v = Builder.CreateZExt(v, i32);
    }
    llvm::Value *condValue = Builder.CreateICmpNE(v, c32(0), "if_cond");
    llvm::Function *func = blockStack.top()->getFunc();
    llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(TheContext, "then", func);
    llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(TheContext, "else");
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(TheContext, "ifcont");

    Builder.CreateCondBr(condValue, thenBB, elseBB);

    Builder.SetInsertPoint(thenBB);
    blockStack.top()->setBlock(thenBB);
    ////std::cout << "Generating code for then statement" << std::endl;
    thenStmt->igen();
    if (!blockStack.top()->hasReturn())
    {
        Builder.CreateBr(mergeBB);
    }
    thenBB = Builder.GetInsertBlock();

    func->getBasicBlockList().push_back(elseBB);
    Builder.SetInsertPoint(elseBB);
    blockStack.top()->setBlock(elseBB);
    if (elseStmt)
    {
        elseStmt->igen();
    }
    if (!blockStack.top()->hasReturn())
    {
        Builder.CreateBr(mergeBB);
    }
    elseBB = Builder.GetInsertBlock();
    func->getBasicBlockList().push_back(mergeBB);
    Builder.SetInsertPoint(mergeBB);
    blockStack.top()->setBlock(mergeBB);

    return nullptr;
}

llvm::Value *While::igen() const
{
    ////std::cout << "Generating code for while statement" << std::endl;
    llvm::Function *TheFunction = blockStack.top()->getFunc();
    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(TheContext, "cond", TheFunction);
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(TheContext, "loop");
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterloop");

    Builder.CreateBr(condBB);
    Builder.SetInsertPoint(condBB);
    blockStack.top()->setBlock(condBB);

    llvm::AllocaInst *condAlloc = llvm::cast<llvm::AllocaInst>(cond->igen());
    llvm::Value *condValue = Builder.CreateLoad(condAlloc->getAllocatedType(), condAlloc, "load_cond");

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
    ////std::cout << "Generating code for return statement" << std::endl;
    llvm::AllocaInst *valueAlloc = llvm::cast<llvm::AllocaInst>(expr->igen());
    llvm::Value *value = Builder.CreateLoad(valueAlloc->getAllocatedType(), valueAlloc, "ret_val");
    Builder.CreateRet(value);
    if (!blockStack.empty())
    {
        GenBlock *currentBlock = blockStack.top();
        currentBlock->addReturn();
    }
    else
    {
        std::cerr << "Error: Block stack is empty, cannot add return statement." << std::endl;
    }

    return nullptr;
}

llvm::Value *FuncDef::igen() const
{
    ////std::cout << "Generating code for function " << *name << std::endl;
    llvm::Type *returnType = translateType(type, ParameterType::VALUE);
    std::vector<llvm::Type *> argTypes;
    auto args = fpar ? fpar->getParameters() : std::vector<Fpar *>();

    for (auto it = args.rbegin(); it != args.rend(); ++it)
    {
        auto arg = *it;
        // std::cout << "arg: " << *arg->getName() << "type: " << arg->getType()->getType() << std::endl;
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
    // std::cout << "localdefs" << std::endl;
    localDef->igen();
    ////std::cout << "stmts" << std::endl;
    stmts->igen();

    if (!currentBlock->hasReturn())
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

llvm::Value* StringConst::igen() const {
    // Create a global string constant in the module
    llvm::Constant* globalStr = Builder.CreateGlobalStringPtr(*name, "global_str");

    // Calculate the length of the string including the null terminator
    size_t strLength = name->length() + 1;

    // Create an alloca instruction to allocate space for the string on the stack
    llvm::AllocaInst* alloca = Builder.CreateAlloca(llvm::ArrayType::get(i8, strLength), nullptr, "str_const_alloca");

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


void AST::codegenLibs() {
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