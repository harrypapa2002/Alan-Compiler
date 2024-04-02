#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "lexer.hpp"
#include "types.hpp"
#include "symbol.hpp"

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
            stmt->sem();
        }
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
            stmts->sem();
        }

        st.exitFunctionScope();
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
        if (st.findSymbol(*name))
        {
            yyerror(("Variable name '" + *name + "' already declared").c_str());
        }

        if (isArray)
        {
            if (size < 0)
            {
                yyerror("Array size must be greater than 0");
            }

            type = new ArrayType(type, size);
        }

        st.addSymbol(*name, new VariableSymbol(*name, type));
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

private:
    int val;
};

class CharConst : public Expr // checked
{
public:
    CharConst(unsigned char c) : val(c) {}
    virtual void printOn(std::ostream &out) const override
    {
        out << "CharConst(" << val << ")";
    }
    virtual void sem() override
    {
        type = typeByte;
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
            }
        }
        type = func->getType();
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
        thenStmt->sem();
        if (elseStmt)
            elseStmt->sem();
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
        body->sem();
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