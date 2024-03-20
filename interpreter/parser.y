%{
#include <stdio.h>
#include <stdlib.h>
#include "lexer.hpp"
#include "ast.hpp"

%}


%union {
    ExprList *exprlist;
    LocalDefList *localdefs;
    FparList *fparlist;
    Type *type;
    int num;
    std::string *str;
    char chr;
    char op;
    compare comp;
    std::string *var;
    AST *ast;
    FuncDef *funcdef;
    VarDef *vardef;
    LocalDef *localdef;
    Fpar *fpardef;
    Stmt *stmt;
    //StmtList *stmtlist;
    Expr *expr;
    Cond *cond;
}

%token T_byte "byte"
%token T_else "else"
%token T_false "false"
%token T_if "if"
%token T_int "int"
%token T_proc "proc"
%token T_reference "reference"
%token T_return "return"
%token T_while "while"
%token T_true "true"
%token T_lte "<="
%token T_gte ">="
%token T_eq "=="
%token T_neq "!="

%token<str> T_string 
%token<num> T_const 
%token<str> T_id 
%token<str> T_char 

%left<op> '&' '|'
%nonassoc<comp> T_lte T_gte '<' '>' T_eq T_neq
%left<op> '+' '-' 
%left<op> '*' '/' '%'
%left UNOP

%expect 1
 
%type <exprlist> exprlist exprs
%type <stmt> stmt stmts compoundstmt
%type <localdefs> localdefs
%type <fparlist> fparlist fpardefs
%type <ast> program 
%type <vardef> vardef
%type <fpardef> fpardef
%type <funcdef> funcdef
%type <localdef> localdef
%type <cond> cond
%type <expr> expr funccall lvalue
%type <type> datatype type rtype


%%

program :
    funcdef { std::cout << *$1 << std::endl; }

funcdef : 
    T_id '(' fparlist ')' ':' rtype localdefs compoundstmt { $$ = new FuncDef($1, $6, $7, $8, $3); }
|   T_id '(' ')' ':' rtype localdefs compoundstmt { $$ = new FuncDef($1, $5, $6, $7); }
;
fparlist : 
    fpardef fpardefs { $2->append($1); $$ = $2; }
;
fpardef : 
    T_id ':' T_reference type { $$ = new Fpar($1, $4, true); }
|   T_id ':' type { $$ = new Fpar($1, $3, false);}
;
fpardefs : 
    /* nothing */ { $$ = new FparList(); }
|   ',' fpardef fpardefs { $3->append($2); $$ = $3; }
;
datatype : 
    T_int { $$ = new Type("int"); }
|   T_byte { $$ = new Type("byte"); }
; 
type : 
    datatype '[' ']' { $1->array(); $$ = $1; }
|   datatype { $$ = $1; }
;
rtype : 
    datatype { $$ = $1; }
|   T_proc { $$ = new Type("proc"); }
;
localdef :
    funcdef { $$ = $1; }
|   vardef { $$ = $1; }
;
localdefs : 
    /* nothing */ { $$ = new LocalDefList(); }
|   localdef localdefs { $2->append($1); $$ = $2; }
;
vardef :
    T_id ':' datatype '[' T_const ']' ';' { $$ = new VarDef($1, $3, $5); } 
|   T_id ':' datatype  ';' { $$ = new VarDef($1, $3); }
;
stmt :
    ';' { $$ = new Stmt(); }
|   lvalue  '=' expr ';' { $$ = new Let($1, $3); }
|   compoundstmt  { $$ = $1; }
|   funccall  ';' { $$ = new ProcCall($1); }
|   T_if '(' cond ')' stmt T_else stmt { $$ = new If($3, $5, $7); }
|   T_if '(' cond ')' stmt { $$ = new If($3, $5); }
|   T_while '(' cond ')' stmt { $$ = new While($3, $5); }
|   T_return expr ';' { $$ = new Return($2); }
|   T_return ';' { $$ = new Return(); }
;
stmts :
    /* nothing */ { $$ = new Stmt(); }
|   stmt stmts { $2->append($1); $$ = $2; }
;
compoundstmt : 
    '{' stmts '}' { $$ = $2; }
;
funccall : 
    T_id '('  exprlist   ')' { $$ = new FuncCall($1, $3);}
|   T_id '(' ')' { $$ = new FuncCall($1); }
;
exprlist : 
    expr exprs { $2->append($1); $$ = $2; }
;
expr : 
    T_const { $$ = new IntConst($1); }
|   T_char  { $$ = new CharConst($1); }
|   lvalue  { $$ = $1;}
|   '(' expr ')' { $$ = $2;}
|   funccall { $$ = $1;}
|   '+' expr %prec UNOP { $$ = new UnOp($1, $2); }
|   '-' expr %prec UNOP { $$ = new UnOp($1, $2); }
|   expr '+' expr { $$ = new BinOp($1, $2, $3); }
|   expr '-' expr  { $$ = new BinOp($1, $2, $3);  }
|   expr '*' expr  { $$ = new BinOp($1, $2, $3);  }
|   expr '/' expr  { $$ = new BinOp($1, $2, $3); }
|   expr '%' expr { $$ = new BinOp($1, $2, $3);  }
;
exprs:
    /* nothing */ { $$ = new ExprList(); }
|   ',' expr exprs { $3->append($2); $$ = $3; }
;
lvalue : 
    T_id '[' expr ']' { $$ = new ArrayAccess($1, $3); }
|   T_id { $$ = new Id($1); }
|   T_string { $$ = new StringConst($1); }
;
cond : 
    T_true { $$ = new BoolConst(true); }
|   T_false { $$ = new BoolConst(false);}
|   '(' cond ')' { $$ = $2; }
|   '!' cond %prec UNOP { $$ = new CondUnOp('!',$2); }
|   expr T_eq expr { $$ = new CondCompOp($1, $2, $3); }
|   expr T_neq expr { $$ = new CondCompOp($1, $2, $3); }
|   expr '<' expr { $$ = new CondCompOp($1, $2, $3); }
|   expr '>' expr { $$ = new CondCompOp($1, $2, $3); }
|   expr T_lte expr { $$ = new CondCompOp($1, $2, $3); }
|   expr T_gte expr { $$ = new CondCompOp($1, $2, $3); }
|   cond '&' cond { $$ = new CondBoolOp($1, $2, $3); }
|   cond '|' cond { $$ = new CondBoolOp($1, $2, $3); }
;

%%

int main() {
  int result = yyparse();
  if (result == 0) printf("Success.\n");
  return result;
}