#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "lexer.hpp"
#include "types.hpp"
#include "symbol.hpp"
#include <llvm/Pass.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>


extern Type *typeInteger;
extern Type *typeByte;
extern Type *typeVoid;




inline std::ostream &operator<<(std::ostream &out, compare c)
{
    switch (c)
    {
    case lt:
        out << "<";
        break;
    case gt:
        out << ">";
        break;
    case lte:
        out << "<=";
        break;
    case gte:
        out << ">=";
        break;
    case eq:
        out << "==";
        break;
    case neq:
        out << "!=";
        break;
    }
    return out;
}

inline std::ostream &operator<<(std::ostream &out, ParameterType p)
{
    switch (p)
    {
    case ParameterType::VALUE:
        out << "Value";
        break;
    case ParameterType::REFERENCE:
        out << "Reference";
        break;
    }
    return out;
}

inline std::ostream &operator<<(std::ostream &out, TypeEnum t)
{
    switch (t)
    {
    case TypeEnum::INT:
        out << "Int";
        break;
    case TypeEnum::BYTE:
        out << "Byte";
        break;
    case TypeEnum::VOID:
        out << "Void";
        break;
    case TypeEnum::ARRAY:
        out << "Array";
        break;
    case TypeEnum::REFERENCE:
        out << "Reference";
        break;
    }
    return out;
}

class AST
{
public:
    virtual ~AST() {}
    virtual void printOn(std::ostream &out) const = 0;
    virtual void sem() {}
    virtual llvm::Value* igen() const { return nullptr; }

    void llvm_igen(bool optimize=true) {
    // Initialize
        TheModule = std::make_unique<llvm::Module>("alan program", TheContext);
        TheFPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());
        if (optimize) {
          TheFPM->add(llvm::createPromoteMemoryToRegisterPass());
          TheFPM->add(llvm::createInstructionCombiningPass());
          TheFPM->add(llvm::createReassociatePass());
          TheFPM->add(llvm::createGVNPass());
          TheFPM->add(llvm::createCFGSimplificationPass());
        }
        TheFPM->doInitialization();

        // Initialize types
        i8  = llvm::IntegerType::get(TheContext, 8);
        i32 = llvm::IntegerType::get(TheContext, 32);
        i64 = llvm::IntegerType::get(TheContext, 64);

        nl_type = llvm::ArrayType::get(i8, 2);

        // Initialize global variables
        TheNL = new llvm::GlobalVariable(
          *TheModule, nl_type, true, llvm::GlobalValue::PrivateLinkage,
          llvm::ConstantArray::get(nl_type, {c8('\n'), c8('\0')}), "nl");
        TheNL->setAlignment(llvm::MaybeAlign(1));

        // Initialize library functions
        llvm::FunctionType *writeInteger_type =
          llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {i64}, false);
        TheWriteInteger =
          llvm::Function::Create(writeInteger_type, llvm::Function::ExternalLinkage,
                           "writeInteger", TheModule.get());
        llvm::FunctionType *writeString_type =
          llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext),
                            {llvm::PointerType::get(i8, 0)}, false);
        TheWriteString =
          llvm::Function::Create(writeString_type, llvm::Function::ExternalLinkage,
                           "writeString", TheModule.get());
        // Define and start the main function.
        llvm::FunctionType *main_type = llvm::FunctionType::get(i32, {}, false);
        llvm::Function *main =
          llvm::Function::Create(main_type, llvm::Function::ExternalLinkage,
                           "main", TheModule.get());
        llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);
        Builder.SetInsertPoint(BB);

        // Emit the program code
        igen();

        Builder.CreateRet(c32(0));

        // Verify the IR.
        bool bad = llvm::verifyModule(*TheModule, &llvm::errs());
        if (bad) {
          std::cerr << "The IR is bad!" << std::endl;
          TheModule->print(llvm::errs(), nullptr);
          std::exit(1);
        }

        // Optimize!
        TheFPM->run(*main);

        // Print out the IR.
        TheModule->print(llvm::outs(), nullptr);
    }

protected:
    static llvm::LLVMContext TheContext;
    static llvm::IRBuilder<> Builder;
    static std::unique_ptr<llvm::Module> TheModule;
    static std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;

    static llvm::GlobalVariable *TheNL;
    static llvm::Function *TheWriteInteger;
    static llvm::Function *TheWriteString;

    static llvm::Type *i8;
    static llvm::Type *i32;
    static llvm::Type *i64;
    static llvm::ArrayType *vars_type;
    static llvm::ArrayType *nl_type;

    static llvm::ConstantInt* c8(char c) {
      return llvm::ConstantInt::get(TheContext, llvm::APInt(8, c, true));
    }
    static llvm::ConstantInt* c32(int n) {
      return llvm::ConstantInt::get(TheContext, llvm::APInt(32, n, true));
    }
    static llvm::ConstantArray* ca8(std::string s) {
        std::vector<llvm::Constant*> chars;
        for (char c : s) {
            chars.push_back(c8(c));
        }
        chars.push_back(c8('\0'));
        return llvm::dyn_cast<llvm::ConstantArray>(llvm::ConstantArray::get(llvm::ArrayType::get(i8, s.size() + 1), chars));
    }
    static llvm::Type *getLLVMType(Type *t) {
        switch (t->getType())
        {
        case TypeEnum::INT:
            return i32;
        case TypeEnum::BYTE:
            return i8;
        case TypeEnum::ARRAY:
            return llvm::ArrayType::get(getLLVMType(t->getBaseType()), t->getSize());
        }
        return nullptr;
    }
    Type *type;
};

inline std::ostream &operator<<(std::ostream &out, const AST &ast)
{
    ast.printOn(out);
    return out;
}

class Expr : public AST
{
public:
    virtual ~Expr() {}
    // virtual void eval() const = 0;
    virtual void printOn(std::ostream &out) const override = 0;

    virtual void sem() override = 0;

    Type *getType() const { return type; }

    TypeEnum getTypeEnum() const { return type->getType(); }
protected:
    Type *type;
};

class Stmt : public AST
{
public:
    virtual ~Stmt() {}
    virtual void printOn(std::ostream &out) const override = 0;
    virtual void sem() override = 0;
    void setExternal(bool e) { external = e; }
    bool isReturnStatement() const { return isReturn; }
protected:
    bool external;
    bool isReturn;
};


class StmtList : public Stmt
{
public:
    StmtList() : stmts() {}
    ~StmtList()
    {
        for (Stmt *s : stmts)
            delete s;
    }

    void append(Stmt *stmt) { stmts.push_back(stmt); }
    virtual void printOn(std::ostream &out) const override
    {
        out << "Stmt(";
        bool first = true;
        for (auto it = stmts.rbegin(); it != stmts.rend(); ++it)
        {
            auto stmt = *it; // dereference the reverse iterator to get the element

            if (stmt)
            {
                if (!first)
                {
                    out << ", ";
                }
                out << *stmt;
                first = false;
            }
        }

        out << ")";
    }

    virtual void sem() override
    {
        for (auto it = stmts.rbegin(); it != stmts.rend(); ++it)
        {
            auto stmt = *it; // dereference the reverse iterator to get the element
            stmt->setExternal(external);
            stmt->sem();
            if(stmt->isReturnStatement()) st.setReturnStatementFound();
        }
        isReturn = false;
    }
    llvm::Value* igen() const override {
        for (auto it = stmts.rbegin(); it != stmts.rend(); ++it)
        {
            auto stmt = *it; // dereference the reverse iterator to get the element
            stmt->igen();
        }
        return nullptr;
    }
private:
    std::vector<Stmt *> stmts;
};

class LocalDef : public AST
{
public:
    virtual ~LocalDef() {}
    virtual void printOn(std::ostream &out) const override = 0;
    virtual void sem() override = 0;

protected:
    Type *type;
};

class LocalDefList : public AST
{
public:
    LocalDefList() : defs() {}
    ~LocalDefList()
    {
        for (LocalDef *d : defs)
            delete d;
    }
    void append(LocalDef *def) { defs.push_back(def); }
    virtual void printOn(std::ostream &out) const override
    {
        out << "LocalDefList(";
        bool first = true;
        for (auto it = defs.rbegin(); it != defs.rend(); ++it)
        {
            auto def = *it; // dereference the reverse iterator to get the element
            if (def)
            {
                if (!first)
                {
                    out << ", ";
                }
                out << *def;
                first = false;
            }
        }
        out << ")";
    }

    virtual void sem() override
    {
        for (auto it = defs.rbegin(); it != defs.rend(); ++it)
        {
            auto def = *it; // dereference the reverse iterator to get the element
            def->sem();
        }
    }
    llvm::Value* igen() const override {
        for (auto it = defs.rbegin(); it != defs.rend(); ++it)
        {
            auto def = *it; // dereference the reverse iterator to get the element
            def->igen();
        }
        return nullptr;
    }
private:
    std::vector<LocalDef *> defs;
};

class Fpar : public AST
{
public:
    Fpar(std::string *n, Type *t, ParameterType p) : name(n), type(t)
    {

        parameterType = p;
        parameterSymbol = nullptr;
    }
    ~Fpar()
    {
        delete name;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "Fpar(" << *name << ", "  << ", " << parameterType << ")";
    }
    virtual void sem() override
    {
        if (st.findSymbolInCurrentScope(*name))
        {
            yyerror(("Parameter '" + *name + "' already declared in the same scope").c_str());
        }
        parameterSymbol = new ParameterSymbol(*name, type, parameterType);
        st.addSymbol(*name, parameterSymbol);
    }

    ParameterSymbol *getParameterSymbol() const { return parameterSymbol; }

private:
    std::string *name;
    Type *type;
    ParameterType parameterType;
    ParameterSymbol *parameterSymbol;
};

class FparList : public AST
{
public:
    FparList() : fpar() {}
    ~FparList()
    {
        for (Fpar *f : fpar)
            delete f;
    }
    void append(Fpar *f) { fpar.push_back(f); }
    virtual void printOn(std::ostream &out) const override
    {
        out << "FparList(";
        bool first = true;
        for (auto it = fpar.rbegin(); it != fpar.rend(); ++it)
        {
            auto f = *it; // dereference the reverse iterator to get the element
            if (f)
            {
                if (!first)
                {
                    out << ", ";
                }
                out << *f;
                first = false;
            }
        }

        out << ")";
    }

    virtual void sem() override
    {
        for (auto it = fpar.rbegin(); it != fpar.rend(); ++it)
        {
            auto f = *it; // dereference the reverse iterator to get the element
            f->sem();
        }
    }

    const std::vector<Fpar *> &getParameters() const { return fpar; }

private:
    std::vector<Fpar *> fpar;
};

class FuncDef : public LocalDef
{
public:
    FuncDef(std::string *n, Type *t, LocalDefList *l, Stmt *s, FparList *f = nullptr) : name(n), fpar(f), type(t), localDef(l), stmts(s)
    {
        funcSymbol = nullptr;
    }
    ~FuncDef()
    {
        delete name;
        delete fpar;
        delete localDef;
        delete stmts;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "FuncDef(" << *name << ", ";
        if (fpar)
            out << *fpar << ", ";
        else
            out << "nullptr, ";
        out  << ", " << *localDef << ", " << *stmts << ")";
        
    }

    virtual void sem() override
    {
        if (st.findSymbol(*name))
        {
            yyerror(("Function name '" + *name + "' already declared").c_str());
        }

        funcSymbol = new FunctionSymbol(*name, type);
        st.addSymbol(*name, funcSymbol);

        st.enterFunctionScope(funcSymbol);

        if (fpar)
        {
            fpar->sem();
            for (auto &param : fpar->getParameters())
            {
                funcSymbol->addParameter(*param->getParameterSymbol());
            }
        }

        if (localDef)
        {
            localDef->sem();
        }

        if (stmts)
        {
            stmts->setExternal(true);
            stmts->sem();
        }

        if (funcSymbol->getNeedsReturn())
        {
            yyerror(("Non void function' " + *name + "' does not have a return statement").c_str());
        }

        st.exitFunctionScope();
    }

    llvm::Value* igen() const override {
        llvm::FunctionType *FT = llvm::FunctionType::get(getLLVMType(type), false);
        llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, *name, TheModule.get());
        llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", F);
        Builder.SetInsertPoint(BB);

        st.enterFunctionScope(funcSymbol);

        if (fpar)
        {
            for (auto &param : fpar->getParameters())
            {
                llvm::Argument *arg = F->arg_begin();
                arg->setName(param->getParameterSymbol()->getName());
                llvm::Value *v = Builder.CreateAlloca(getLLVMType(param->getParameterSymbol()->getType()), nullptr, param->getParameterSymbol()->getName());
                Builder.CreateStore(arg, v);
                param->getParameterSymbol()->setValue(v);
            }
        }

        if (localDef)
        {
            localDef->igen();
        }

        stmts->igen();

        st.exitFunctionScope();

        return F;
    }
     
private:
    std::string *name;
    FparList *fpar;
    Type *type;
    LocalDefList *localDef;
    Stmt *stmts;
    FunctionSymbol *funcSymbol;
};

class VarDef : public LocalDef
{
public:
    VarDef(std::string *n, Type *t,  bool arr, int arraySize = -1) : name(n), type(t), size(arraySize), isArray(arr) {}
    ~VarDef()
    {
        delete name;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "VarDef(" << *name << ", " ;
        if (isArray)
        {
            out << ", Array Size: " << size;
        }
        out << ")";
    }

    virtual void sem() override
    {
        if (st.findSymbolInCurrentScope(*name))
        {
            yyerror(("Variable name '" + *name + "' already declared").c_str());
        }

        if (isArray)
        {
            if (size <= 0)
            {
                yyerror("Array size must be greater than 0");
            }

            type = new ArrayType(type, size);
        }

        st.addSymbol(*name, new VariableSymbol(*name, type));
    }

    llvm::Value *igen() const override {
        llvm::AllocaInst *Alloca;
        if (isArray) Alloca = Builder.CreateAlloca(getLLVMType(type), c32(size), *name);
        else Alloca = Builder.CreateAlloca(getLLVMType(type), nullptr, *name);
        st.addSymbol(*name, new VariableSymbol(*name, type, Alloca));
        return nullptr;
    }
private:
    std::string *name;
    Type *type;
    int size;
    bool isArray;
};

class ExprList : public AST
{
public:
    ExprList() : exprs() {}
    ~ExprList()
    {
        for (Expr *e : exprs)
            delete e;
    }
    void append(Expr *expr) { exprs.push_back(expr); }
    virtual void printOn(std::ostream &out) const override
    {
        out << "ExprList(";
        bool first = true;
        for (auto it = exprs.rbegin(); it != exprs.rend(); ++it)
        {
            auto expr = *it; // dereference the reverse iterator to get the element
            if (expr)
            {
                if (!first)
                {
                    out << ", ";
                }
                out << *expr;
                first = false;
            }
        }

        out << ")";
    }

    virtual void sem() override
    {
        for (auto it = exprs.rbegin(); it != exprs.rend(); ++it)
        {
            auto expr = *it; // dereference the reverse iterator to get the element
            expr->sem();
        }
    }
    llvm::Value* igen() const override {
        for (auto it = exprs.rbegin(); it != exprs.rend(); ++it)
        {
            auto expr = *it; // dereference the reverse iterator to get the element
            expr->igen();
        }
        return nullptr;
    }
    const std::vector<Expr *> &getExprs() const { return exprs; }

private:
    std::vector<Expr *> exprs;
};

class Cond : public AST // checked
{
public:
    virtual void printOn(std::ostream &out) const override = 0;
    virtual void sem() override = 0;
};

class UnOp : public Expr // checked
{
public:
    UnOp(char o, Expr *e) : op(o), expr(e) {}
    ~UnOp() { delete expr; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "UnOp(" << op << ", " << *expr << ")";
    }
    virtual void sem() override
    {
        expr->sem();
        if (expr->getTypeEnum() != TypeEnum::INT)
            yyerror("Unary operator can only be applied to integers");
        type = typeInteger;
    }
    llvm::Value* igen() const override {
        llvm::Value* e = expr->igen();
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
private:
    char op;
    Expr *expr;
};

class BinOp : public Expr // checked
{
public:
    BinOp(Expr *l, char o, Expr *r) : op(o), left(l), right(r) {}
    ~BinOp()
    {
        delete left;
        delete right;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "BinOp(" << op << ", " << *left << ", " << *right << ")";
    }
    virtual void sem() override
    {
        left->sem();
        right->sem();

        if (!equalTypes(left->getTypeEnum(), right->getTypeEnum()))
        {
            yyerror("Type mismatch");
        }

        if (!equalTypes(left->getTypeEnum(), TypeEnum::INT) && !equalTypes(left->getTypeEnum(), TypeEnum::BYTE))
        {
            yyerror("Binary operator can only be applied to integers or bytes");
        }

        type = left->getType();
    }
    llvm::Value* igen() const override {
        llvm::Value* l = left->igen();
        llvm::Value* r = right->igen();
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
private:
    char op;
    Expr *left;
    Expr *right;
};

class CondCompOp : public Cond // checked
{
public:
    CondCompOp(Expr *l, compare o, Expr *r) : op(o), left(l), right(r) {}
    ~CondCompOp()
    {
        delete left;
        delete right;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "CondCompOp(" << op << ", " << *left << ", " << *right << ")";
    }
    virtual void sem() override
    {
        left->sem();
        right->sem();
        TypeEnum t = left->getTypeEnum();
        if (!equalTypes(t, right->getTypeEnum()))
        {
            yyerror("Type mismatch");
        }
        if (t != TypeEnum::INT && t != TypeEnum::BYTE)
            yyerror("Comparison operator can only be applied to integers or bytes");
    }
    llvm::Value* igen() const override {
        llvm::Value* l = left->igen();
        llvm::Value* r = right->igen();
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
private:
    compare op;
    Expr *left;
    Expr *right;
};

class CondBoolOp : public Cond
{
public:
    CondBoolOp(Cond *l, char o, Cond *r) : op(o), left(l), right(r) {}
    ~CondBoolOp()
    {
        delete left;
        delete right;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "CondBoolOp(" << op << ", " << *left << ", " << *right << ")";
    }
    virtual void sem() override
    {
        left->sem();
        right->sem();
    }
    llvm::Value* igen() const override {
        llvm::Value* l = left->igen();
        llvm::Value* r = right->igen();
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
private:
    char op;
    Cond *left;
    Cond *right;
};

class CondUnOp : public Cond
{
public:
    CondUnOp(char o, Cond *c) : op(o), cond(c) {}
    ~CondUnOp() { delete cond; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "BoolUnOp(" << op << ", " << *cond << ")";
    }
    virtual void sem() override
    {
        cond->sem();
    }
    llvm::Value* igen() const override {
        llvm::Value* c = cond->igen();
        switch (op)
        {
        case '!':
            return Builder.CreateNot(c, "nottmp");
        default:
            return nullptr;
        }
    }
private:
    char op;
    Cond *cond;
};

class IntConst : public Expr // checked
{
public:
    IntConst(int v) : val(v) {}
    virtual void printOn(std::ostream &out) const override
    {
        out << "Const(" << val << ")";
    }
    virtual void sem() override
    {
        type = typeInteger;
    }
    llvm::Value* igen() const override {
        return c32(val);
    }
    int getValue() const { return val; }

private:
    int val;
};

class CharConst : public Expr // checked
{
public:
    CharConst(unsigned char c) : val(c) {}
    virtual void printOn(std::ostream &out) const override
    {   
        out << "CharConst(";
        if (val <= 255 && val >= 0) out << (int)val;
        else out << val;
        out << ")";
    }
    virtual void sem() override
    {
        type = typeByte;
    }
    llvm::Value* igen() const override {
        return c8(val);
    }
private:
    unsigned char val;
};

class Lval : public Expr // checked
{
public:
    virtual ~Lval() {}
    virtual void printOn(std::ostream &out) const override
    {
        out << "Lval(" << *name << ")";
    }
    virtual void sem() override {}

    std::string getName() const { return *name; }

protected:
    std::string *name;
};

class StringConst : public Lval // checked
{
public:
    StringConst(std::string *v)
    {
        name = v;
    }
    ~StringConst() { delete name; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "StrConst(" << *name << ")";
    }
    virtual void sem() override
    {
        type = new ArrayType(typeByte, name->size() + 1);
    }
    llvm::Value* igen() const override {
        return ca8(*name);
    }    

};

class BoolConst : public Cond // checked
{
public:
    BoolConst(bool v) : val(v) {}
    virtual void printOn(std::ostream &out) const override
    {
        out << "BoolConst(" << val << ")";
    }
    virtual void sem() override
    {
    }
    llvm::Value* igen() const override {
        return c32(val);
    }
private:
    bool val;
};

class Id : public Lval // checked
{
public:
    Id(std::string *n)
    {
        name = n;
    }
    ~Id() { delete name; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "Id(" << *name << ",  " << type->getType()  << ")";
    }
    virtual void sem() override
    {
        Symbol *entry = st.findSymbol(*name);
        if (!entry)
        {
            yyerror("Variable not declared");
        }

        symbolType = entry->getSymbolType();

        if (symbolType == SymbolType::FUNCTION)
        {
            yyerror("Function cannot be used as a variable");
        }

        type = entry->getType();
    }
    llvm::Value* igen() const override {
        Symbol *e = st.findSymbol(*name);
        llvm::Value *v = e->getValue();
        llvm::Type *t = getLLVMType(e->getType());
        return Builder.CreateLoad(t, v, *name);
    }
private:
    SymbolType symbolType;
};

class ArrayAccess : public Lval // checked
{
public:
    ArrayAccess(std::string *n, Expr *index) : indexExpr(index)
    {
        name = n;
    }
    ~ArrayAccess()
    {
        delete name;
        delete indexExpr;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "ArrayAccess(" << *name << ", Index: ";
        out << *indexExpr << ")";
        out << ")";
    }
    virtual void sem() override
    {

        indexExpr->sem();
        if (indexExpr->getTypeEnum() != TypeEnum::INT)
            yyerror("Array index must be integer");

        Symbol *entry = st.findSymbol(*name);
        if (!entry)
        {
            yyerror("Variable not declared");
        }
        if(entry->getSymbolType() == SymbolType::FUNCTION)
        {
            yyerror("Function cannot be used as a variable");
        }
        Type *t = entry->getType();

        if (t->getType() != TypeEnum::ARRAY)
            yyerror("Variable is not an array");

        type = t->getBaseType();
    }

    Expr *getIndexExpr() const { return indexExpr; }

    llvm::Value* igen() const override {
        Symbol *e = st.findSymbol(*name);
        llvm::Value *v = e->getValue();
        llvm::Type *t = getLLVMType(e->getType());
        llvm::Value *i = indexExpr->igen();
        llvm::Value *l = Builder.CreateGEP(t, v, std::vector<llvm::Value *>{c32(0), i}, "arrayidx");
        return Builder.CreateLoad(getLLVMType(e->getType()->getBaseType()), l, "arraytmp");
    }
private:
    Expr *indexExpr;
};

class Let : public Stmt // checked
{
public:
    Let(Lval *l, Expr *r) : lexpr(l), rexpr(r) {}
    ~Let()
    {
        delete lexpr;
        delete rexpr;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "Let(" << *lexpr << ", " << *rexpr << ")";
    }
    virtual void sem() override
    {
        lexpr->sem();
        rexpr->sem();

        Symbol *entry = st.findSymbol(lexpr->getName());
        if (!entry)
        {
            yyerror("Variable not declared");
        }
        SymbolType symbolType = entry->getSymbolType();
        if (symbolType == SymbolType::FUNCTION)
        {
            yyerror("Function cannot be used as a variable");
        }

        if (!equalTypes(lexpr->getTypeEnum(), rexpr->getTypeEnum()))
        {
            yyerror("Type mismatch");
        }
        isReturn = false;
        
    }
    llvm::Value* igen() const override {
        llvm::Value *r = rexpr->igen();
        if(lexpr->getTypeEnum() == TypeEnum::ARRAY)
        {
            Symbol *e = st.findSymbol(lexpr->getName());
            llvm::Value *v = e->getValue();
            llvm::Type *t = getLLVMType(e->getType());
            llvm::Value *i = lexpr->igen();
            llvm::Value *l = Builder.CreateGEP(t, v, i, "arrayidx");
            return Builder.CreateStore(r, l);
        } 
        llvm::Value *l = st.findSymbol(lexpr->getName())->getValue();
        return Builder.CreateStore(r, l);
    }
private:
    Lval *lexpr;
    Expr *rexpr;
};

class FuncCall : public Expr
{
public:
    FuncCall(std::string *n, ExprList *e = nullptr) : name(n), exprs(e) {}
    ~FuncCall()
    {
        delete name;
        delete exprs;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "Funccall(" << *name << ", ";
        if (exprs)
            out << *exprs << ")";
        else
            out << ")";
    }

    virtual void sem() override
    {
        Symbol *entry = st.findSymbol(*name);
        if (!entry)
        {

            yyerror("Function not declared");
        }
        SymbolType symbolType = entry->getSymbolType();
        if (symbolType != SymbolType::FUNCTION)
        {
            yyerror("Variable cannot be used as a function");
        }

        FunctionSymbol *func = (FunctionSymbol *)entry;
        if (exprs)
        {
            exprs->sem();
            std::vector<ParameterSymbol> params = func->getParameters();
            if (exprs->getExprs().size() != params.size())
            {
                yyerror("Number of parameters does not match");
            }

            for (int i = 0; i < exprs->getExprs().size(); i++)
            {
                if (exprs->getExprs()[i]->getTypeEnum() != params[i].getType()->getType())
                {
                    yyerror("Type mismatch");
                }
                if(exprs->getExprs()[i]->getTypeEnum() == TypeEnum::ARRAY)
                {
                   
                   if(params[i].getType()->getBaseType()->getType() != exprs->getExprs()[i]->getType()->getBaseType()->getType())
                   {
                       yyerror("Array type mismatch");
                   }
                }
            }
        }
        type = func->getType();
    }
    llvm::Value* igen() const override {
        llvm::Function *calleeF = TheModule->getFunction(*name);
        if (!calleeF) {
            yyerror("Unknown function referenced");
        }
        std::vector<llvm::Value*> args;
        if (exprs) {
            for (auto expr : exprs->getExprs()) {
                args.push_back(expr->igen());
            }
        }
        return Builder.CreateCall(calleeF, args, "calltmp");
    }
private:
    std::string *name;
    ExprList *exprs;
};

class ProcCall : public Stmt // checked
{
public:
    ProcCall(FuncCall *f) : funcCall(f) {}
    ~ProcCall() { delete funcCall; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "ProcCall(" << *funcCall << ")";
    }

    virtual void sem() override
    {
        funcCall->sem();
    }
    llvm::Value* igen() const override {
        funcCall->igen();
    }
private:
    FuncCall *funcCall;
};

class If : public Stmt // checked
{
public:
    If(Cond *c, Stmt *t, Stmt *e = nullptr) : cond(c), thenStmt(t), elseStmt(e) {}
    ~If()
    {
        delete cond;
        delete thenStmt;
        delete elseStmt;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "If(" << *cond << ", " << *thenStmt << ", ";
        if (elseStmt)
            out << *elseStmt << ")";
        else
            out << "nullptr)";
    }

    virtual void sem() override
    {
        cond->sem();
        thenStmt->setExternal(elseStmt && external);
        thenStmt->sem();
        if (elseStmt) {
            elseStmt->setExternal(external);
            elseStmt->sem();
            if(thenStmt->isReturnStatement() && elseStmt->isReturnStatement()) st.setReturnStatementFound();
        }
    }
    llvm::Value* igen() const override {
        llvm::Value *v = cond->igen();
        llvm::Value *cond = Builder.CreateICmpNE(v, c32(0), "if_cond");
        llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
        llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else");
        llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endif");
        Builder.CreateCondBr(v, ThenBB, ElseBB);
        Builder.SetInsertPoint(ThenBB);
        thenStmt->igen();
        Builder.CreateBr(AfterBB);
        Builder.SetInsertPoint(ElseBB);
        if (elseStmt)
            elseStmt->igen();
        Builder.CreateBr(AfterBB);
        ElseBB = Builder.GetInsertBlock();
        Builder.SetInsertPoint(AfterBB);
        return nullptr;
    }
private:
    Cond *cond;
    Stmt *thenStmt;
    Stmt *elseStmt;
};

class While : public Stmt // checked
{
public:
    While(Cond *c, Stmt *b) : cond(c), body(b) {}
    ~While()
    {
        delete cond;
        delete body;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "While(" << *cond << ", " << *body << ")";
    }

    virtual void sem() override
    {
        cond->sem();
        body->setExternal(false);
        body->sem();
    }
    llvm::Value* igen() const override {
        llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *CondBB = llvm::BasicBlock::Create(TheContext, "cond", TheFunction);
        llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(TheContext, "loop");
        llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endwhile");
        Builder.CreateBr(CondBB);
        Builder.SetInsertPoint(CondBB);
        llvm::Value *v = cond->igen();
        llvm::Value *cond = Builder.CreateICmpNE(v, c32(0), "while_cond");
        Builder.CreateCondBr(v, LoopBB, AfterBB);
        Builder.SetInsertPoint(LoopBB);
        body->igen();
        Builder.CreateBr(CondBB);
        Builder.SetInsertPoint(AfterBB);
        return nullptr;
    }
private:
    Cond *cond;
    Stmt *body;
};

class Return : public Stmt
{
public:
    Return(Expr *e = nullptr) : expr(e) {}
    ~Return() { delete expr; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "Return(";
        if (expr)
            out << *expr << ")";
        else
            out << ")";
    }

    virtual void sem() override
    {

        Type *expectedReturnType = st.getCurrentFunctionReturnType();
        if (!expectedReturnType)
        {
            yyerror("Return statement not within any function scope.");
            return;
        }

        if (expr)
        {
            expr->sem();

            if (expr->getType()->getType() != expectedReturnType->getType())
            {
                yyerror("Return type does not match the function's return type.");
            }
        }
        else
        {
            if (expectedReturnType->getType() != TypeEnum::VOID)
            {
                yyerror("Missing return value in function expected to return a non-void type.");
                return;
            }
        }
        if (external)
            isReturn = true;


    }

    llvm::Value* igen() const override {
        llvm::Value *r;
        if (expr) {
            llvm::Value *e = expr->igen();
            r = Builder.CreateRet(e);
        } else r = Builder.CreateRetVoid();
        Builder.SetInsertPoint(llvm::BasicBlock::Create(TheContext, "after_ret", Builder.GetInsertBlock()->getParent()));
        return r;
    }
private:
    Expr *expr;
};

class Empty : public Stmt
{
public:
    virtual void printOn(std::ostream &out) const override
    {
        out << "Empty()";
    }
    virtual void sem() override {}
};

#endif