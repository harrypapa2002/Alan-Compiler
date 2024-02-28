%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int lineno = 1;
int is_balanced = 0;

%}

L [a-zA-Z] 
D [0-9]
H [a-fA-F0-9]
W [ \t\r] 
ESC [ntr0\'\"\\] 

%x COMMENT

%%

 /* Keywords */
"byte" { return T_byte; }
"else" { return T_else; }
"false" { return T_false; }
"if" { return T_if; }
"int" { return T_int; }
"proc" { return T_proc; }
"reference" { return T_reference; }
"return" { return T_return; }
"while" { return T_while; }
"true" { return T_true; }

 /* Symbols */
[\(\)\[\]\{\}\,\:\;\=\+\/\-\*\<\>\%\&\|\!] { return yytext[0]; }
"<=" { return T_lte; }
">=" { return T_gte; }
"==" { return T_eq; }
"!=" { return T_neq; }

 /* Constants. Names. Chars. Strings. */
{D}+ { return T_const; }
{L}({L}|{D}|_)* { return T_id; }
\'([^\\\'\"]|\\({ESC}|x{H}{H}))\' { return T_char; }
\"(\\({ESC}|x{H}{H})|[^\\\'\"\n])*\"  { return T_string; }

 /* WhiteSpace */
\n   { ++lineno; }
{W}+ { /* nothing */ }

 /* Comments */
\-\-.*\n? { ++lineno; }
"(*" { BEGIN(COMMENT); }
<COMMENT>"(*" {  ++is_balanced; }
<COMMENT>"*)" {  if(is_balanced) --is_balanced; else { BEGIN(INITIAL);} }
<COMMENT>\n { lineno++; }
<COMMENT>"*" { /* nothing */ }
<COMMENT>"(" { /* nothing */ }
<COMMENT>")" { /* nothing */ }
<COMMENT>[^\(\)*\n]+ { /* nothing */ }
<COMMENT><<EOF>> {yyerror("Unfinished comment"); }


{D}+({L}|_)+ { yyerror("Illegal character"); }

. { yyerror("Illegal character"); }

%%


void yyerror(const char *msg) {
    fprintf(stderr, "Error, lexeme %s, line %d: %s\n", yytext, lineno, msg);
    exit(1);
}