#include "ast.hpp"

// Operator Overload Implementations

std::ostream &operator<<(std::ostream &out, compare c)
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

std::ostream &operator<<(std::ostream &out, ParameterType p)
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

std::ostream &operator<<(std::ostream &out, TypeEnum t)
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

// AST Base Class Method Implementations

std::ostream &operator<<(std::ostream &out, const AST &ast)
{
    ast.printOn(out);
    return out;
}

// Expr Class Method Implementations

Type *Expr::getType() const
{
    return type;
}

TypeEnum Expr::getTypeEnum() const
{
    return type->getType();
}

// Stmt Class Method Implementations

void Stmt::setExternal(bool e)
{
    external = e;
}

bool Stmt::isReturnStatement() const
{
    return isReturn;
}

// StmtList Class Method Implementations

StmtList::StmtList() : stmts() {}

StmtList::~StmtList()
{
    for (Stmt *s : stmts)
        delete s;
}

void StmtList::append(Stmt *stmt)
{
    stmts.push_back(stmt);
}

void StmtList::printOn(std::ostream &out) const
{
    out << "StmtList(";
    bool first = true;
    for (auto it = stmts.rbegin(); it != stmts.rend(); ++it)
    {
        auto stmt = *it;

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

// LocalDefList Class Method Implementations

LocalDefList::LocalDefList() : defs() {}

LocalDefList::~LocalDefList()
{
    for (LocalDef *d : defs)
        delete d;
}

void LocalDefList::append(LocalDef *def)
{
    defs.push_back(def);
}

void LocalDefList::printOn(std::ostream &out) const
{
    out << "LocalDefList(";
    bool first = true;
    for (auto it = defs.rbegin(); it != defs.rend(); ++it)
    {
        auto def = *it;
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

// Fpar Class Method Implementations

Fpar::Fpar(std::string *n, Type *t, ParameterType p) : name(n), type(t)
{
    parameterType = p;
    parameterSymbol = nullptr;
}

Fpar::~Fpar()
{
    delete name;
}

void Fpar::printOn(std::ostream &out) const
{
    out << "Fpar(" << *name << ", " << type->getType() << ", " << parameterType << ")";
}

Type *Fpar::getType() const
{
    return type;
}

ParameterSymbol *Fpar::getParameterSymbol() const
{
    return parameterSymbol;
}

std::string* Fpar::getName() const {
    return name;
}

ParameterType Fpar::getParameterType() const {
    return parameterType;
}

// FparList Class Method Implementations

FparList::FparList() : fpar() {}

FparList::~FparList()
{
    for (Fpar *f : fpar)
        delete f;
}

void FparList::append(Fpar *f)
{
    fpar.push_back(f);
}

void FparList::printOn(std::ostream &out) const
{
    out << "FparList(";
    bool first = true;
    for (auto it = fpar.rbegin(); it != fpar.rend(); ++it)
    {
        auto f = *it;
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

const std::vector<Fpar *> &FparList::getParameters() const
{
    return fpar;
}

// FuncDef Class Method Implementations

FuncDef::FuncDef(std::string *n, Type *t, LocalDefList *l, Stmt *s, FparList *f) : name(n), fpar(f), type(t), localDef(l), stmts(s)
{
    funcSymbol = nullptr;
}

FuncDef::~FuncDef()
{
    delete name;
    delete fpar;
    delete localDef;
    delete stmts;
}

void FuncDef::printOn(std::ostream &out) const
{
    out << "FuncDef(" << *name << ", ";
    if (fpar)
        out << *fpar << ", ";
    else
        out << "nullptr, ";
    out << *localDef << ", " << *stmts << ")";
}

std::string* FuncDef::getName() const {
    return name;
}

// VarDef Class Method Implementations

VarDef::VarDef(std::string *n, Type *t, bool arr, int arraySize) : name(n), type(t), size(arraySize), isArray(arr) {}

VarDef::~VarDef()
{
    delete name;
}

void VarDef::printOn(std::ostream &out) const
{
    out << "VarDef(" << *name << ", ";
    if (isArray)
    {
        out << "Array Size: " << size;
    }
    out << ")";
}

// ExprList Class Method Implementations

ExprList::ExprList() : exprs() {}

ExprList::~ExprList()
{
    for (Expr *e : exprs)
        delete e;
}

void ExprList::append(Expr *expr)
{
    exprs.push_back(expr);
}

void ExprList::printOn(std::ostream &out) const
{
    out << "ExprList(";
    bool first = true;
    for (auto it = exprs.rbegin(); it != exprs.rend(); ++it)
    {
        auto expr = *it;
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

const std::vector<Expr *> &ExprList::getExprs() const
{
    return exprs;
}

// UnOp Class Method Implementations

UnOp::UnOp(char o, Expr *e) : op(o), expr(e) {}

UnOp::~UnOp()
{
    delete expr;
}

void UnOp::printOn(std::ostream &out) const
{
    out << "UnOp(" << op << ", " << *expr << ")";
}

// BinOp Class Method Implementations

BinOp::BinOp(Expr *l, char o, Expr *r) : op(o), left(l), right(r) {}

BinOp::~BinOp()
{
    delete left;
    delete right;
}

void BinOp::printOn(std::ostream &out) const
{
    out << "BinOp(" << *left << " " << op << " " << *right << ")";
}

// CondCompOp Class Method Implementations

CondCompOp::CondCompOp(Expr *l, compare o, Expr *r) : op(o), left(l), right(r) {}

CondCompOp::~CondCompOp()
{
    delete left;
    delete right;
}

void CondCompOp::printOn(std::ostream &out) const
{
    out << "CondCompOp(" << *left << " " << op << " " << *right << ")";
}

// CondBoolOp Class Method Implementations

CondBoolOp::CondBoolOp(Cond *l, char o, Cond *r) : op(o), left(l), right(r) {}

CondBoolOp::~CondBoolOp()
{
    delete left;
    delete right;
}

void CondBoolOp::printOn(std::ostream &out) const
{
    out << "CondBoolOp(" << *left << " " << op << " " << *right << ")";
}

// CondUnOp Class Method Implementations

CondUnOp::CondUnOp(char o, Cond *c) : op(o), cond(c) {}

CondUnOp::~CondUnOp()
{
    delete cond;
}

void CondUnOp::printOn(std::ostream &out) const
{
    out << "CondUnOp(" << op << " " << *cond << ")";
}

// IntConst Class Method Implementations

IntConst::IntConst(int v) : val(v) {}

void IntConst::printOn(std::ostream &out) const
{
    out << "IntConst(" << val << ")";
}

int IntConst::getValue() const
{
    return val;
}

// CharConst Class Method Implementations

CharConst::CharConst(unsigned char c) : val(c) {}

void CharConst::printOn(std::ostream &out) const
{
    out << "CharConst(";
    if (val <= 255 && val >= 0)
        out << static_cast<int>(val);
    else
        out << val;
    out << ")";
}

// Lval Class Method Implementations

void Lval::printOn(std::ostream &out) const
{
    out << "Lval(" << *name << ")";
}

std::string* Lval::getName() const{
    return name;
}

// StringConst Class Method Implementations

StringConst::StringConst(std::string *v)
{
    name = v;
}

StringConst::~StringConst()
{
    delete name;
}

void StringConst::printOn(std::ostream &out) const
{
    out << "StringConst(" << *name << ")";
}

// BoolConst Class Method Implementations

BoolConst::BoolConst(bool v) : val(v) {}

void BoolConst::printOn(std::ostream &out) const
{
    out << "BoolConst(" << std::boolalpha << val << ")";
}

// Id Class Method Implementations

Id::Id(std::string *n)
{
    name = n;
}

Id::~Id()
{
    delete name;
}

void Id::printOn(std::ostream &out) const
{
    out << "Id(" << *name << ", " << type->getType() << ")";
}

// ArrayAccess Class Method Implementations

ArrayAccess::ArrayAccess(std::string *n, Expr *index) : indexExpr(index)
{
    name = n;
}

ArrayAccess::~ArrayAccess()
{
    delete name;
    delete indexExpr;
}

void ArrayAccess::printOn(std::ostream &out) const
{
    out << "ArrayAccess(" << *name << ", Index: " << *indexExpr << ")";
}

Expr* ArrayAccess::getIndexExpr() const
{
    return indexExpr;
}

// Let Class Method Implementations

Let::Let(Lval *l, Expr *r) : lexpr(l), rexpr(r) {}

Let::~Let()
{
    delete lexpr;
    delete rexpr;
}

void Let::printOn(std::ostream &out) const
{
    out << "Let(" << *lexpr << ", " << *rexpr << ")";
}

// FuncCall Class Method Implementations

FuncCall::FuncCall(std::string *n, ExprList *e) : name(n), exprs(e) {}

FuncCall::~FuncCall()
{
    delete name;
    delete exprs;
}

std::string* FuncCall::getName() const {
    return name;
}

ExprList* FuncCall::getExprs() const {
    return exprs;
}

void FuncCall::printOn(std::ostream &out) const
{
    out << "FuncCall(" << *name << ", ";
    if (exprs)
        out << *exprs;
    else
        out << "None";
    out << ")";
}

// ProcCall Class Method Implementations

ProcCall::ProcCall(FuncCall *f) : funcCall(f) {}

ProcCall::~ProcCall()
{
    delete funcCall;
}

void ProcCall::printOn(std::ostream &out) const
{
    out << "ProcCall(" << *funcCall << ")";
}

// If Class Method Implementations

If::If(Cond *c, Stmt *t, Stmt *e) : cond(c), thenStmt(t), elseStmt(e) {}

If::~If()
{
    delete cond;
    delete thenStmt;
    if (elseStmt)
    {
        delete elseStmt;
    }
}

void If::printOn(std::ostream &out) const
{
    out << "If(" << *cond << ", " << *thenStmt;
    if (elseStmt)
        out << ", " << *elseStmt;
    else
        out << ", None";
    out << ")";
}

// While Class Method Implementations

While::While(Cond *c, Stmt *b) : cond(c), body(b) {}

While::~While()
{
    delete cond;
    delete body;
}

void While::printOn(std::ostream &out) const
{
    out << "While(" << *cond << ", " << *body << ")";
}

// Return Class Method Implementations

Return::Return(Expr *e) : expr(e) {}

Return::~Return()
{
    delete expr;
}

void Return::printOn(std::ostream &out) const
{
    out << "Return(";
    if (expr)
        out << *expr;
    else
        out << "None";
    out << ")";
}

// Empty Class Method Implementations

void Empty::printOn(std::ostream &out) const
{
    out << "Empty()";
}