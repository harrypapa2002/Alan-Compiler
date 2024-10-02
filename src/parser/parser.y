%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../lexer/lexer.hpp"
#include "../ast/ast.hpp"
#include "../symbol/types.hpp"
#include "../symbol/symbol.hpp"
#include "../symbol/symbol_table.hpp"

int syntax_errors = 0;
extern int lexical_errors;
std::vector<std::string> syntax_error_buffer;  

int semantic_errors = 0;
std::vector<std::string> semantic_error_buffer;

int semantic_warnings = 0; 
std::vector<std::string> semantic_warning_buffer; 

void yyerror(const char *msg);  

Type *typeInteger = new IntType();
Type *typeByte = new ByteType();
Type *typeVoid = new VoidType();

bool optimize = false;

%}

%locations
%error-verbose

%union {
    ExprList *exprlist;
    LocalDefList *localdefs;
    FparList *fparlist;
    StmtList *stmtlist;
    Type *type;
    int num;
    std::string *str;
    unsigned char chr;
    char op;
    compare comp;
    std::string *var;
    AST *ast;
    FuncDef *funcdef;
    VarDef *vardef;
    LocalDef *localdef;
    Fpar *fpardef;
    Stmt *stmt;
    Expr *expr;
    Cond *cond;
    Lval *lvalue;
    FuncCall *fun;
}

// Tokens
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

%token<str> T_string "string"
%token<num> T_const "constant"
%token<str> T_id "identifier"
%token<chr> T_char "char"

%left<op> '&' '|'
%nonassoc<comp> T_lte T_gte '<' '>' T_eq T_neq
%left<op> '+' '-' 
%left<op> '*' '/' '%'
%left UNOP

%expect 1
 
%type <exprlist> exprlist exprs
%type <stmt> stmt 
%type <localdefs> localdefs
%type <fparlist> fparlist fpardefs
%type <stmtlist> stmts compoundstmt
%type <ast> program 
%type <vardef> vardef
%type <fpardef> fpardef
%type <funcdef> funcdef
%type <localdef> localdef
%type <cond> cond
%type <expr> expr 
%type <lvalue> lvalue
%type <type> datatype type rtype
%type <fun> funccall

%%

program :
    funcdef {   
        if (lexical_errors > 0 || syntax_errors > 0) {
            YYABORT; 
        }
        $1->sem();
        if (semantic_errors > 0) {
            YYABORT;
        }
        if (semantic_warnings > 0) {
            for (const std::string &warning : semantic_warning_buffer) {
                fprintf(stderr, "%s\n", warning.c_str());
            }
        }
        $1->llvm_igen(optimize);
    }
;

funcdef : 
    T_id '(' fparlist ')' ':' rtype localdefs compoundstmt {
        $$ = new FuncDef($1, $6, $7, $8, $3, @1.first_line, @1.first_column);
    }
|   T_id '(' ')' ':' rtype localdefs compoundstmt {
        $$ = new FuncDef($1, $5, $6, $7, nullptr, @1.first_line, @1.first_column);
    }
;

fparlist : 
    fpardef fpardefs {
        $2->append($1); $$ = $2;
    }
;

fpardef : 
    T_id ':' T_reference type {
        $$ = new Fpar($1, $4, ParameterType::REFERENCE, @1.first_line, @1.first_column);
    }
|   T_id ':' type {
        $$ = new Fpar($1, $3, ParameterType::VALUE, @1.first_line, @1.first_column);
    }
;

fpardefs : 
    /* nothing */ {
        $$ = new FparList(@$.first_line, @$.first_column);
    }
|   ',' fpardef fpardefs {
        $3->append($2); $$ = $3;
    }
;

datatype : 
    T_int {
        $$ = typeInteger;
    }
|   T_byte {
        $$ = typeByte;
    }
; 

type : 
    datatype '[' ']' {
        $$ = new ArrayType($1);
    }
|   datatype {
        $$ = $1;
    }
;

rtype : 
    datatype {
        $$ = $1;
    }
|   T_proc {
        $$ = typeVoid;
    }
;

localdef :
    funcdef {
        $$ = $1;
    }
|   vardef {
        $$ = $1;
    }
;

localdefs : 
    /* nothing */ {
        $$ = new LocalDefList(@$.first_line, @$.first_column);
    }
|   localdef localdefs {
        $2->append($1); $$ = $2;
    }
;

vardef :
    T_id ':' datatype '[' T_const ']' ';' {
        $$ = new VarDef($1, $3, true, $5, @1.first_line, @1.first_column);
    } 
|   T_id ':' datatype  ';' {
        $$ = new VarDef($1, $3, false, -1, @1.first_line, @1.first_column);
    }
;

stmt :
    ';' {
        $$ = new Empty(@1.first_line, @1.first_column);
    }
|   lvalue  '=' expr ';' {
        $$ = new Let($1, $3, @2.first_line, @2.first_column);
    }
|   compoundstmt  {
        $$ = $1;
    }
|   funccall  ';' {
        $$ = new ProcCall($1, @2.first_line, @2.first_column);
    }
|   T_if '(' cond ')' stmt T_else stmt {
        $$ = new If($3, $5, $7, @1.first_line, @1.first_column);
    }
|   T_if '(' cond ')' stmt {
        $$ = new If($3, $5, nullptr, @1.first_line, @1.first_column);
    }
|   T_while '(' cond ')' stmt {
        $$ = new While($3, $5, @1.first_line, @1.first_column);
    }
|   T_return expr ';' {
        $$ = new Return($2, @1.first_line, @1.first_column);
    }
|   T_return ';' {
        $$ = new Return(nullptr, @1.first_line, @1.first_column);
    }
;

stmts :
    /* nothing */ {
        $$ = new StmtList(@$.first_line, @$.first_column);
    }
|   stmt stmts {
        $2->append($1); $$ = $2;
    }
;

compoundstmt : 
    '{' stmts '}' {
        $$ = $2;
    }
;

funccall : 
    T_id '('  exprlist   ')' {
        $$ = new FuncCall($1, $3, @1.first_line, @1.first_column);
    }
|   T_id '(' ')' {
        $$ = new FuncCall($1, nullptr, @1.first_line, @1.first_column);
    }
;

exprlist : 
    expr exprs {
        $2->append($1); $$ = $2;
    }
;

expr : 
    T_const {
        $$ = new IntConst($1, @1.first_line, @1.first_column);
    }
|   T_char  {
        $$ = new CharConst($1, @1.first_line, @1.first_column);
    }
|   lvalue  {
        $$ = $1;
    }
|   '(' expr ')' {
        $$ = $2;
    }
|   funccall {
        $$ = $1;
    }
|   '+' expr %prec UNOP {
        $$ = new UnOp('+', $2, @1.first_line, @1.first_column);
    }
|   '-' expr %prec UNOP {
        $$ = new UnOp('-', $2, @1.first_line, @1.first_column);
    }
|   expr '+' expr {
        $$ = new BinOp($1, '+', $3, @2.first_line, @2.first_column);
    }
|   expr '-' expr  {
        $$ = new BinOp($1, '-', $3, @2.first_line, @2.first_column);
    }
|   expr '*' expr  {
        $$ = new BinOp($1, '*', $3, @2.first_line, @2.first_column);
    }
|   expr '/' expr  {
        $$ = new BinOp($1, '/', $3, @2.first_line, @2.first_column);
    }
|   expr '%' expr {
        $$ = new BinOp($1, '%', $3, @2.first_line, @2.first_column);
    }
;

exprs:
    /* nothing */ {
        $$ = new ExprList(@$.first_line, @$.first_column);
    }
|   ',' expr exprs {
        $3->append($2); $$ = $3;
    }
;

lvalue : 
    T_id '[' expr ']' {
        $$ = new ArrayAccess($1, $3, @1.first_line, @1.first_column);
    }
|   T_id {
        $$ = new Id($1, @1.first_line, @1.first_column);
    }
|   T_string {
        $$ = new StringConst($1, @1.first_line, @1.first_column);
    }
;

cond : 
    T_true {
        $$ = new BoolConst(true, @1.first_line, @1.first_column);
    }
|   T_false {
        $$ = new BoolConst(false, @1.first_line, @1.first_column);
    }
|   '(' cond ')' {
        $$ = $2;
    }
|   '!' cond %prec UNOP {
        $$ = new CondUnOp('!', $2, @1.first_line, @1.first_column);
    }
|   expr T_eq expr {
        $$ = new CondCompOp($1, eq, $3, @2.first_line, @2.first_column);
    }
|   expr T_neq expr {
        $$ = new CondCompOp($1, neq, $3, @2.first_line, @2.first_column);
    }
|   expr '<' expr {
        $$ = new CondCompOp($1, lt, $3, @2.first_line, @2.first_column);
    }
|   expr '>' expr {
        $$ = new CondCompOp($1, gt, $3, @2.first_line, @2.first_column);
    }
|   expr T_lte expr {
        $$ = new CondCompOp($1, lte, $3, @2.first_line, @2.first_column);
    }
|   expr T_gte expr {
        $$ = new CondCompOp($1, gte, $3, @2.first_line, @2.first_column);
    }
|   cond '&' cond {
        $$ = new CondBoolOp($1, '&', $3, @2.first_line, @2.first_column);
    }
|   cond '|' cond {
        $$ = new CondBoolOp($1, '|', $3, @2.first_line, @2.first_column);
    }
;

%%

int main(int argc, char **argv) {

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-O") == 0) {
            optimize = true;
        }
    }

    int result = yyparse();
    
    if (lexical_errors > 0) {
        for (const std::string &error : error_buffer) {
            fprintf(stderr, "%s\n", error.c_str());
        }
        return 1;
    }

    if (syntax_errors > 0) {
        for (const std::string &error : syntax_error_buffer) {
            fprintf(stderr, "%s\n", error.c_str());
        }
        return 1;
    }

    if (semantic_errors > 0) {
        for (const std::string &error : semantic_error_buffer) {
            fprintf(stderr, "%s\n", error.c_str());
        }
        return 1;
    }

    return result;
}

void yyerror(const char *msg) {
    syntax_errors++;

    std::string processed_msg(msg);

    size_t pos = processed_msg.find("$end");
    if (pos != std::string::npos) {
        processed_msg.replace(pos, 4, "end of input");
    }

    std::string error_message = "Error at line " + std::to_string(yylloc.first_line) +
                                ", column " + std::to_string(yylloc.first_column) + ": " + processed_msg;
    

    syntax_error_buffer.push_back(error_message);
}

void semantic_error(int line, int column, const std::string &msg) {
    char error_message[512];

    snprintf(error_message, sizeof(error_message),
             "Semantic Error at line %d, column %d: %s",
             line, column, msg.c_str());

    semantic_error_buffer.push_back(error_message);
    semantic_errors++;
}

void semantic_warning(int line, int column, const std::string &msg) {
    char warning_message[512];
    snprintf(warning_message, sizeof(warning_message),
             "Semantic Warning at line %d, column %d: %s",
             line, column, msg.c_str());

    semantic_warning_buffer.push_back(warning_message);
    semantic_warnings++;
}
