%{
#include <stdio.h>
#include "lexer.h"
%}

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
%token T_char "char"
%token T_lte "<="
%token T_gte ">="
%token T_eq "=="
%token T_neq "!="

%token T_string 
%token T_const 
%token T_id 

%left '&' '|'
%nonassoc T_lte T_gte '<' '>' T_eq T_neq
%left '+' '-' 
%left '*' '/' '%'
%left UNOP

%expect 1

%%

program :
    funcdef 

funcdef : 
    T_id '(' fparlist ')' ':' rtype  localdefs compoundstmt 
|   T_id '(' ')' ':' rtype localdefs compoundstmt 
;
fparlist : 
    fpardef fpardefs 
;
fpardef : 
    T_id ':' T_reference type 
|   T_id ':' type 
;
fpardefs : 
    /* nothing */ 
|   ',' fpardef fpardefs 
;
datatype : 
    T_int 
|   T_byte
; 
type : 
    datatype '[' ']' 
|   datatype 
;
rtype : 
    datatype 
|   T_proc
;
localdef :
    funcdef 
|   vardef
;
localdefs : 
    /* nothing */
|   localdef localdefs 
;
vardef :
    T_id ':' datatype  '[' T_const ']' ';'
|   T_id ':' datatype  ';'
;
stmt :
    ';' 
|   lvalue  '=' expr ';' 
|   compoundstmt  
|   funccall  ';'
|   T_if '(' cond ')' stmt T_else stmt
|   T_if '(' cond ')' stmt
|   T_while '(' cond ')' stmt 
|   T_return expr ';'
|   T_return ';'
;
stmts :
    /* nothing */
|   stmt stmts
;
compoundstmt  : 
    '{' stmts '}'
;
funccall  : 
    T_id '('  exprlist   ')'
|   T_id '(' ')'
;
exprlist : 
    expr exprs
;
expr : 
    T_const  
|   T_char  
|   lvalue  
|   '(' expr ')' 
|   funccall 
|   '+' expr %prec UNOP
|   '-' expr %prec UNOP
|   expr '+' expr
|   expr '-' expr 
|   expr '*' expr 
|   expr '/' expr 
|   expr '%' expr
;
exprs:
    /* nothing */
|   ',' expr exprs
;
lvalue  : 
    T_id '[' expr ']'
|   T_id 
|   T_string 
;
cond : 
    T_true 
|   T_false 
|   '(' cond ')' 
|   '!' cond %prec UNOP
|   expr T_eq expr 
|   expr T_neq expr
|   expr '<' expr 
|   expr '>' expr 
|   expr T_lte expr 
|   expr T_gte expr
|   cond '&' cond 
|   cond '|' cond
;

%%

int main() {
  int result = yyparse();
  if (result == 0) printf("Success.\n");
  return result;
}