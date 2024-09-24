%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../lexer/lexer.hpp"
#include "../ast/ast.hpp"
#include "../symbol/types.hpp"
#include "../symbol/symbol.hpp"
#include "../symbol/symbol_table.hpp"

// Track error state
int syntax_errors = 0;
extern int lexical_errors;
std::vector<std::string> syntax_error_buffer;  

int semantic_errors = 0;
std::vector<std::string> semantic_error_buffer;

int semantic_warnings = 0; 
std::vector<std::string> semantic_warning_buffer; 


// Global line and column tracking
extern int lineno;
extern int column;

// Token position tracking
extern int token_start_line;
extern int token_start_column;

void yyerror(const char *msg);  

Type *typeInteger = new IntType();
Type *typeByte = new ByteType();
Type *typeVoid = new VoidType();
%}

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
        $1->llvm_igen();
    }
;

funcdef : 
    T_id '(' fparlist ')' ':' rtype localdefs compoundstmt { $$ = new FuncDef($1, $6, $7, $8, $3); }
|   T_id '(' ')' ':' rtype localdefs compoundstmt { $$ = new FuncDef($1, $5, $6, $7); }
;

fparlist : 
    fpardef fpardefs { $2->append($1); $$ = $2; }
;

fpardef : 
    T_id ':' T_reference type { $$ = new Fpar($1, $4, ParameterType::REFERENCE); }
|   T_id ':' type { $$ = new Fpar($1, $3, ParameterType::VALUE); }
;

fpardefs : 
    /* nothing */ { $$ = new FparList(); }
|   ',' fpardef fpardefs { $3->append($2); $$ = $3; }
;

datatype : 
    T_int { $$ = typeInteger; }
|   T_byte { $$ = typeByte; }
; 

type : 
    datatype '[' ']' {  $$ = new ArrayType($1);}
|   datatype { $$ = $1; }
;

rtype : 
    datatype { $$ = $1; }
|   T_proc { $$ = typeVoid; }
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
    T_id ':' datatype '[' T_const ']' ';' { $$ = new VarDef($1, $3, true, $5); } 
|   T_id ':' datatype  ';' { $$ = new VarDef($1, $3, false); }
;

stmt :
    ';' { $$ = new Empty();}
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
    /* nothing */ { $$ = new StmtList(); }
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

    if (semantic_warnings > 0) {
        for (const std::string &warning : semantic_warning_buffer) {
            fprintf(stderr, "%s\n", warning.c_str());
        }
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

    std::string error_message = "Error at line " + std::to_string(token_start_line) +
                                ", column " + std::to_string(token_start_column) + ": " + processed_msg;
    

    syntax_error_buffer.push_back(error_message);
}

void semantic_error(const std::string &msg) {
    char error_message[512];

    snprintf(error_message, sizeof(error_message),
             "Semantic Error at line %d, column %d: %s",
             token_start_line, token_start_column, msg.c_str());

    semantic_error_buffer.push_back(error_message);
    semantic_errors++;
}


void semantic_warning(const std::string &msg) {
    char warning_message[512];

    snprintf(warning_message, sizeof(warning_message),
             "Semantic Warning at line %d, column %d: %s",
             token_start_line, token_start_column, msg.c_str());

    semantic_warning_buffer.push_back(warning_message);
    semantic_warnings++;
}