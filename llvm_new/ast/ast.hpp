#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <llvm/IR/Value.h> 
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include "../lexer/lexer.hpp"
#include "../symbol/types.hpp"
#include "../symbol/symbol.hpp"
#include "../codegen/codegen.hpp"

// Operator overloads
std::ostream &operator<<(std::ostream &out, compare c);
std::ostream &operator<<(std::ostream &out, ParameterType p);
std::ostream &operator<<(std::ostream &out, TypeEnum t);

std::string compareToString(compare op);

// AST Base Class
class AST
{
public:
    virtual ~AST() {}
    virtual void printOn(std::ostream &out) const = 0;
    virtual void sem() {}
    virtual llvm::Value* igen() const { return nullptr; } 
    void llvm_igen(bool optimize = true);
    static llvm::LLVMContext TheContext;
    void codegenLibs();
protected:
    static llvm::IRBuilder<> Builder;
    static std::unique_ptr<llvm::Module> TheModule;
    static std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;
    std::string filename;
    static llvm::Type *proc;
    static llvm::Type *i1;
    static llvm::Type *i8;
    static llvm::Type *i32;
    static GenScope scopes;
    static std::stack<GenBlock*> blockStack;
    static llvm::ConstantInt* c1(bool b); 
    static llvm::ConstantInt* c8(char c);
    static llvm::ConstantInt* c32(int n);

};

std::ostream &operator<<(std::ostream &out, const AST &ast);

// Expr Class
class Expr : public AST
{
public:
    virtual ~Expr() {}
    virtual void printOn(std::ostream &out) const override = 0;
    virtual void sem() override = 0;
    virtual llvm::Value* igen() const override = 0;
    virtual std::string* getName() const { return nullptr; }
    Type *getType() const;
    TypeEnum getTypeEnum() const;

protected:
    Type *type;
};

// Stmt Class
class Stmt : public AST
{
public:
    virtual ~Stmt() {}
    virtual void printOn(std::ostream &out) const override = 0;
    virtual void sem() override = 0;
    virtual llvm::Value* igen() const override = 0;
    void setExternal(bool e);
    bool isReturnStatement() const;

protected:
    bool external;
    bool isReturn;
};

// StmtList Class
class StmtList : public Stmt
{
public:
    StmtList();
    ~StmtList();
    void append(Stmt *stmt);
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    std::vector<Stmt *> stmts;
};

// LocalDef Class
class LocalDef : public AST
{
public:
    virtual ~LocalDef() {}
    virtual void printOn(std::ostream &out) const override = 0;
    virtual void sem() override = 0;

protected:
    Type *type;
};

// LocalDefList Class
class LocalDefList : public AST
{
public:
    LocalDefList();
    ~LocalDefList();
    void append(LocalDef *def);
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;


private:
    std::vector<LocalDef *> defs;
};

// Fpar Class
class Fpar : public AST
{
public:
    Fpar(std::string *n, Type *t, ParameterType p);
    ~Fpar();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    ParameterSymbol *getParameterSymbol() const;
    ParameterType getParameterType() const;
    std::string* getName() const;
    Type *getType() const;
    bool getIsArray() const;
    
private:
    ParameterType parameterType;
    std::string *name;
    Type *type;
    ParameterSymbol *parameterSymbol;
    bool isArray;
    
};

class CapturedVar {
public:
    CapturedVar(const std::string& name, Type* type, bool isParam = false, ParameterType paramType = ParameterType::VALUE);

    const std::string& getName() const;
    Type* getType() const;
    bool getIsParam() const;
    ParameterType getParameterType() const;

private:
    std::string name;
    Type* type;
    bool isParam;
    ParameterType parameterType;
};

// FparList Class
class FparList : public AST
{
public:
    FparList();
    ~FparList();
    void append(Fpar *f);
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    const std::vector<Fpar *> &getParameters() const;

private:
    std::vector<Fpar *> fpar;
};

// FuncDef Class
class FuncDef : public LocalDef
{
public:
    FuncDef(std::string *n, Type *t, LocalDefList *l, Stmt *s, FparList *f = nullptr);
    ~FuncDef();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;
    std::string* getName() const; 
    void setReturn();

private:
    std::string *name;
    FparList *fpar;
    Type *type;
    LocalDefList *localDef;
    Stmt *stmts;
    bool hasReturn;
    std::vector<CapturedVar*> capturedVars;
};

// VarDef Class
class VarDef : public LocalDef
{
public:
    VarDef(std::string *n, Type *t, bool arr, int arraySize = -1);
    ~VarDef();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    std::string *name;
    Type *type;
    int size;
    bool isArray;
};

// ExprList Class
class ExprList : public AST
{
public:
    ExprList();
    ~ExprList();
    void append(Expr *expr);
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;
    const std::vector<Expr *> &getExprs() const;

private:
    std::vector<Expr *> exprs;
};

// Cond Class
class Cond : public AST 
{
public:
    virtual void printOn(std::ostream &out) const override = 0;
    virtual void sem() override = 0;
    virtual llvm::Value* igen() const override = 0;
};

// UnOp Class
class UnOp : public Expr 
{
public:
    UnOp(char o, Expr *e);
    ~UnOp();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    char op;
    Expr *expr;
};

// BinOp Class
class BinOp : public Expr 
{
public:
    BinOp(Expr *l, char o, Expr *r);
    ~BinOp();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    char op;
    Expr *left;
    Expr *right;
};

// CondCompOp Class
class CondCompOp : public Cond 
{
public:
    CondCompOp(Expr *l, compare o, Expr *r);
    ~CondCompOp();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    compare op;
    Expr *left;
    Expr *right;
};

// CondBoolOp Class
class CondBoolOp : public Cond
{
public:
    CondBoolOp(Cond *l, char o, Cond *r);
    ~CondBoolOp();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    char op;
    Cond *left;
    Cond *right;
};

// CondUnOp Class
class CondUnOp : public Cond
{
public:
    CondUnOp(char o, Cond *c);
    ~CondUnOp();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    char op;
    Cond *cond;
};

// IntConst Class
class IntConst : public Expr 
{
public:
    IntConst(int v);
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    int getValue() const;
    virtual llvm::Value* igen() const override;

private:
    int val;
};

// CharConst Class
class CharConst : public Expr 
{
public:
    CharConst(unsigned char c);
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    unsigned char val;
};

// Lval Class
class Lval : public Expr 
{
public:
    virtual ~Lval() {}
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override = 0;
    virtual std::string* getName() const override;

protected:
    std::string *name;
};

// StringConst Class
class StringConst : public Lval 
{
public:
    StringConst(std::string *v);
    ~StringConst();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;
protected:
    std::string *name;
};

// BoolConst Class
class BoolConst : public Cond 
{
public:
    BoolConst(bool v);
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    bool val;
};

// Id Class
class Id : public Lval 
{
public:
    Id(std::string *n);
    ~Id();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    SymbolType symbolType;
};

// ArrayAccess Class
class ArrayAccess : public Lval 
{
public:
    ArrayAccess(std::string *n, Expr *index);
    ~ArrayAccess();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;
    Expr *getIndexExpr() const;

private:
    Expr *indexExpr;
};

// Let Class
class Let : public Stmt 
{
public:
    Let(Lval *l, Expr *r);
    ~Let();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    Lval *lexpr;
    Expr *rexpr;
};

// FuncCall Class
class FuncCall : public Expr
{
public:
    FuncCall(std::string *n, ExprList *e = nullptr);
    ~FuncCall();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;
    ExprList *getExprs() const;
    virtual std::string* getName() const override;

protected:
    std::string *name;
    ExprList *exprs;
    std::vector<CapturedVar*> capturedVars;
    bool isNested;
};

// ProcCall Class
class ProcCall : public Stmt 
{
public:
    ProcCall(FuncCall *f);
    ~ProcCall();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    FuncCall *funcCall;
};

// If Class
class If : public Stmt 
{
public:
    If(Cond *c, Stmt *t, Stmt *e = nullptr);
    ~If();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    Cond *cond;
    Stmt *thenStmt;
    Stmt *elseStmt;
};

// While Class
class While : public Stmt 
{
public:
    While(Cond *c, Stmt *b);
    ~While();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    Cond *cond;
    Stmt *body;
};

// Return Class
class Return : public Stmt
{
public:
    Return(Expr *e = nullptr);
    ~Return();
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override;
    virtual llvm::Value* igen() const override;

private:
    Expr *expr;
};

// Empty Class
class Empty : public Stmt
{
public:
    virtual void printOn(std::ostream &out) const override;
    virtual void sem() override {}
    virtual llvm::Value* igen() const override;

};

#endif // AST_HPP