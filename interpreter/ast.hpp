#ifndef __AST_HPP__
#define __AST_HPP__


#include <iostream>
#include <vector>
#include <string>
#include "lexer.hpp"
#include "types.hpp"
#include "symbol.hpp"

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

class AST
{
public:
    virtual ~AST() {}
    virtual void printOn(std::ostream &out) const = 0;
    virtual void sem() {}

protected:
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
    virtual void eval() const = 0;
    void type_check(Type *t) const
    {
        if (type->getType() != t->getType())
        {
            yyerror("Type mismatch");
        }
    }

protected:
    Type *type;

};

class Stmt : public AST
{
public:
    Stmt() : stmts() {}
    ~Stmt()
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
            stmt->sem();
        }
    }

private:
    std::vector<Stmt *> stmts;
};

class LocalDef : public AST
{
public:
    virtual void printOn(std::ostream &out) const = 0;
    virtual void sem() override {}

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

private:
    std::vector<LocalDef *> defs;
};

class Fpar : public AST
{
public:
    Fpar(std::string *n, Type *t, ParameterType p) : name(n), type(t){

        parameterType = p;
    }
    ~Fpar()
    {
        delete name;
        delete type;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "Fpar(" << *name << ", " << *type << ", " << parameterType << ")";
    }
    virtual void sem() override
    {
        
    }

private:
    std::string *name;
    Type *type;
    ParameterType parameterType;
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


private:
    std::vector<Fpar *> fpar;
};

class FuncDef : public LocalDef
{
public:
    FuncDef(std::string *n, Type *t, LocalDefList *l, Stmt *s, FparList *f = nullptr) : name(n), fpar(f), type(t), localDef(l), stmts(s) {}
    ~FuncDef()
    {
        delete name;
        delete fpar;
        delete type;
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
        out << *type << ", " << *localDef << ", " << *stmts << ")";
    }

    

private:
    std::string *name;
    FparList *fpar;
    Type *type;
    LocalDefList *localDef;
    Stmt *stmts;
};

class VarDef : public LocalDef
{
public:
    VarDef(std::string *n, Type *t, int arraySize = -1) : name(n), type(t), size(arraySize) {}
    ~VarDef()
    {
        delete name;
        delete type;
    }
    virtual void printOn(std::ostream &out) const override
    {
        out << "VarDef(" << *name << ", " << *type;
        if (size >= 0)
        {
            out << ", Array Size: " << size;
        }
        out << ")";
    }

private:
    std::string *name;
    Type *type;
    int size;
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

private:
    std::vector<Expr *> exprs;
};

class Cond : public AST
{
    virtual void printOn(std::ostream &out) const override = 0;
    virtual void sem() override = 0;
};

class UnOp : public Expr
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
    }
private:
    char op;
    Expr *expr;
};

class BinOp : public Expr
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
    }
private:
    char op;
    Expr *left;
    Expr *right;
};

class CondCompOp : public Cond
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
        TypeEnum t = left->getType()
        if(t != TypeEnum::INT && t != TypeEnum::BYTE) yyerror("Cannot compare arrays");
        right->type_check(t);
        t = right->getType();
        if(t != TypeEnum::INT && t != TypeEnum::BYTE) yyerror("Cannot compare arrays");// this should be redundant
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
private:
    char op;
    Cond *cond;
};

class IntConst : public Expr
{
public:
    IntConst(int v) : val(v) {}
    virtual void printOn(std::ostream &out) const override
    {
        out << "Const(" << val << ")";
    }
    virtual void sem() override
    {
        type = new IntType();
    }
private:
    int val;
};

class BoolConst : public Cond
{
public:
    BoolConst(bool v) : val(v) {}
    virtual void printOn(std::ostream &out) const override
    {
        out << "BoolConst(" << val << ")";
    }
    virtual void sem() override {}
private:
    bool val;
};

class CharConst : public Expr
{
public:
    CharConst(std::string *v) : val(v) {}
    virtual void printOn(std::ostream &out) const override
    {
        out << "CharConst(" << *val << ")";
    }
    virtual void sem() override
    {
        type = new ByteType();
    }
private:
    std::string *val;
};

class StringConst : public Expr
{
public:
    StringConst(std::string *v) : val(v) {}
    ~StringConst() { delete val; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "StrConst(" << *val << ")";
    }
    virtual void sem() override
    {
        type = new ArrayType(new ByteType(), val->size());
    }
private:
    std::string *val;
};

class Id : public Expr
{
public:
    Id(std::string *n) : name(n) {}
    ~Id() { delete name; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "Id(" << *name << ")";
    }
    virtual void sem() override
    {
        Symbol *entry = st.findSymbol(name);
        type = entry->getType();
    }
private:
    std::string *name;
};

class ArrayAccess : public Expr
{
public:
    ArrayAccess(std::string *n, Expr *index) : name(n), indexExpr(index) {}
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
        Symbol *entry = st.findSymbol(name);
        Type *t = entry->getType();
        if(t->getType() != TypeEnum::ARRAY) yyerror("Variable is not an array");
        indexExpr->sem();
        if(indexExpr->getType() != TypeEnum::INT) yyerror("Array index must be integer");
        type = t->getBaseType();
    }
private:
    std::string *name;
    Expr *indexExpr;
};

class Let : public Stmt
{
public:
    Let(Expr *l, Expr *r) : lexpr(l), rexpr(r) {}
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
        Symbol *entry = st.findSymbol(lexpr->getName());
        rexpr->type_check(entry->getType());
        lexpr->sem();
        rexpr->sem();
    }
private:
    Expr *lexpr;
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

private:
    std::string *name;
    ExprList *exprs;
};

class ProcCall : public Stmt
{
public:
    ProcCall(Expr *f) : funcCall(f) {}
    ~ProcCall() { delete funcCall; }
    virtual void printOn(std::ostream &out) const override
    {
        out << "ProcCall(" << *funcCall << ")";
    }

private:
    Expr *funcCall;
};

class If : public Stmt
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

private:
    Cond *cond;
    Stmt *thenStmt;
    Stmt *elseStmt;
};

class While : public Stmt
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

private:
    Expr *expr;
};

#endif