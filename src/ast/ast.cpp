#include "ast.hpp"

std::string compareToString(compare op) {
    switch (op) {
        case lt:   return "<";
        case gt:   return ">";
        case lte:  return "<=";
        case gte:  return ">=";
        case eq:   return "==";
        case neq:  return "!=";
        default:   return "unknown";
    }
}

// Expr Class Method Implementations

Type *Expr::getType() const
{
    return type;
}

TypeEnum Expr::getTypeEnum() const
{
    return type ? type->getType() : TypeEnum::ERROR;
}

// Stmt Class Method Implementations

void Stmt::setExternal(bool e)
{
    external = e;
}

bool Stmt::getExternal() const
{
    return external;
}

bool Stmt::isReturnStatement() const
{
    return isReturn;
}

void Stmt::setFromIf(bool fromIf)
{
    this->fromIf = fromIf;
}

// StmtList Class Method Implementations

StmtList::StmtList(int line, int column) : Stmt(line, column), stmts() {}

StmtList::~StmtList()
{
    for (Stmt *s : stmts)
        delete s;
}

void StmtList::append(Stmt *stmt)
{
    stmts.push_back(stmt);
}

// LocalDefList Class Method Implementations

LocalDefList::LocalDefList(int line, int column) : AST(line, column), defs() {}

LocalDefList::~LocalDefList()
{
    for (LocalDef *d : defs)
        delete d;
}

void LocalDefList::append(LocalDef *def)
{
    defs.push_back(def);
}

// Fpar Class Method Implementations

Fpar::Fpar(std::string *n, Type *t, ParameterType p, int line, int column)
    : AST(line, column), name(n), type(t), parameterType(p)
{
}

Fpar::~Fpar()
{
    delete name;
}
Type *Fpar::getType() const
{
    return type;
}


std::string* Fpar::getName() const {
    return name;
}

ParameterType Fpar::getParameterType() const {
    return parameterType;
}

// CapturedVar Class Method Implementations

CapturedVar::CapturedVar(const std::string& name, Type* type, bool isParam, ParameterType paramType)
    : name(name), type(type), isParam(isParam), parameterType(paramType) {}

const std::string& CapturedVar::getName() const {
    return name;
}

Type* CapturedVar::getType() const {
    return type;
}

bool CapturedVar::getIsParam() const {
    return isParam;
}

ParameterType CapturedVar::getParameterType() const {
    return parameterType;
}

// FparList Class Method Implementations

FparList::FparList(int line, int column) : AST(line, column), fpar() {}

FparList::~FparList()
{
    for (Fpar *f : fpar)
        delete f;
}

void FparList::append(Fpar *f)
{
    fpar.push_back(f);
}

const std::vector<Fpar *> &FparList::getParameters() const
{
    return fpar;
}

// FuncDef Class Method Implementations

FuncDef::FuncDef(std::string *n, Type *t, LocalDefList *l, Stmt *s, FparList *f, int line, int column)
    : LocalDef(line, column), name(n), fpar(f), type(t), localDef(l), stmts(s), hasReturn(false)
{
    capturedVars = std::vector<CapturedVar*>();
}

FuncDef::~FuncDef()
{
    delete name;
    delete fpar;
    delete localDef;
    delete stmts;
}

std::string* FuncDef::getName() const {
    return name;
}

void FuncDef::setReturn() {
    hasReturn = true;
}

// VarDef Class Method Implementations

VarDef::VarDef(std::string *n, Type *t, bool arr, int arraySize, int line, int column)
    : LocalDef(line, column), name(n), type(t), size(arraySize), isArray(arr) {}

VarDef::~VarDef()
{
    delete name;
}

// ExprList Class Method Implementations

ExprList::ExprList(int line, int column) : AST(line, column), exprs() {}

ExprList::~ExprList()
{
    for (Expr *e : exprs)
        delete e;
}

void ExprList::append(Expr *expr)
{
    exprs.push_back(expr);
}

const std::vector<Expr *> &ExprList::getExprs() const
{
    return exprs;
}

// UnOp Class Method Implementations

UnOp::UnOp(char o, Expr *e, int line, int column) : Expr(line, column), op(o), expr(e) {}

UnOp::~UnOp()
{
    delete expr;
}

// BinOp Class Method Implementations

BinOp::BinOp(Expr *l, char o, Expr *r, int line, int column) : Expr(line, column), op(o), left(l), right(r) {}

BinOp::~BinOp()
{
    delete left;
    delete right;
}

// CondCompOp Class Method Implementations

CondCompOp::CondCompOp(Expr *l, compare o, Expr *r, int line, int column)
    : Cond(line, column), op(o), left(l), right(r) {}

CondCompOp::~CondCompOp()
{
    delete left;
    delete right;
}

// CondBoolOp Class Method Implementations

CondBoolOp::CondBoolOp(Cond *l, char o, Cond *r, int line, int column)
    : Cond(line, column), op(o), left(l), right(r) {}

CondBoolOp::~CondBoolOp()
{
    delete left;
    delete right;
}

// CondUnOp Class Method Implementations

CondUnOp::CondUnOp(char o, Cond *c, int line, int column) : Cond(line, column), op(o), cond(c) {}

CondUnOp::~CondUnOp()
{
    delete cond;
}

// IntConst Class Method Implementations

IntConst::IntConst(int v, int line, int column) : Expr(line, column), val(v) {}

int IntConst::getValue() const
{
    return val;
}

// CharConst Class Method Implementations

CharConst::CharConst(unsigned char c, int line, int column) : Expr(line, column), val(c) {}

// Lval Class Method Implementations

std::string* Lval::getName() const {
    return name;
}

// StringConst Class Method Implementations

StringConst::StringConst(std::string *v, int line, int column) : Lval(line, column)
{
    name = v;
}

StringConst::~StringConst()
{
    delete name;
}

// BoolConst Class Method Implementations

BoolConst::BoolConst(bool v, int line, int column) : Cond(line, column), val(v) {}

// Id Class Method Implementations

Id::Id(std::string *n, int line, int column) : Lval(line, column)
{
    name = n;
}

Id::~Id()
{
    delete name;
}

// ArrayAccess Class Method Implementations

ArrayAccess::ArrayAccess(std::string *n, Expr *index, int line, int column)
    : Lval(line, column), indexExpr(index)
{
    name = n;
}

ArrayAccess::~ArrayAccess()
{
    delete name;
    delete indexExpr;
}

Expr* ArrayAccess::getIndexExpr() const
{
    return indexExpr;
}

// Let Class Method Implementations

Let::Let(Lval *l, Expr *r, int line, int column) : Stmt(line, column), lexpr(l), rexpr(r) {}

Let::~Let()
{
    delete lexpr;
    delete rexpr;
}

// FuncCall Class Method Implementations

FuncCall::FuncCall(std::string *n, ExprList *e, int line, int column)
    : Expr(line, column), name(n), exprs(e), isNested(false) {
    capturedVars = std::vector<CapturedVar*>();
}

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

// ProcCall Class Method Implementations

ProcCall::ProcCall(FuncCall *f, int line, int column) : Stmt(line, column), funcCall(f) {}

ProcCall::~ProcCall()
{
    delete funcCall;
}

// If Class Method Implementations

If::If(Cond *c, Stmt *t, Stmt *e, int line, int column) : Stmt(line, column), cond(c), thenStmt(t), elseStmt(e) {}

If::~If()
{
    delete cond;
    delete thenStmt;
    if (elseStmt)
    {
        delete elseStmt;
    }
}

// While Class Method Implementations

While::While(Cond *c, Stmt *b, int line, int column) : Stmt(line, column), cond(c), body(b) {}

While::~While()
{
    delete cond;
    delete body;
}

// Return Class Method Implementations

Return::Return(Expr *e, int line, int column) : Stmt(line, column), expr(e) {}

Return::~Return()
{
    delete expr;
}

// Empty Class Method Implementations

Empty::Empty(int line, int column) : Stmt(line, column) {}
