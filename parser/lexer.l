%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int lineno = 1;
int is_balanced = 0;

%}

L [A-Za-z] 
hex [a-f0-9]
D [0-9]
W [ \t\r] 

%x COMMENT
%x STRING

%%


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


{L}({L}|{D})* { return T_id; }
{D}+ { return T_const; }
{W}+ { /* nothing */ }
\'([^\\\'\"\n]|\\x{hex}{hex}|\\n|\\t|\\r|\\0|\\\\|\\\'|\\\")\' { return T_char; }

[\(\)\[\]\{\}\,\:\;\=\+\/\-\*\<\>\%\&\|] { return yytext[0]; }
\<\= { return T_lte; }
\>\= { return T_gte; }
\=\= { return T_eq; }
\!\= { return T_neq; }

\" { BEGIN(STRING); }
<STRING>\" { BEGIN(INITIAL); return T_string; BEGIN(INITIAL);}
<STRING>(\\x{hex}{hex}|\\n|\\t|\\r|\\\'|\\\"|\\\0|\\\\) { /* nothing */ }
<STRING>[^\n\\\"]+ { /* nothing */ }
<STRING>\n { lineno++; yyerror("Changed line in unfinished string"); }
<STRING><<EOF>> { yyerror("Unfinished string"); }
<STRING>. { yyerror("Illegal character in string"); }

\n { lineno++; }
\-\-.*\n? { /* nothing */ }
"(*" {++is_balanced; BEGIN(COMMENT); }
<COMMENT>"(*" { ++is_balanced; }
<COMMENT>"*)" { --is_balanced; if(is_balanced == 0) { BEGIN(INITIAL);} }
<COMMENT>\n { lineno++; }
<COMMENT>"*" { /* nothing */ }
<COMMENT>"(" { /* nothing */ }
<COMMENT>")" { /* nothing */ }
<COMMENT>[^\(\)*\n]+ { /* nothing */ }
<COMMENT><<EOF>> { yyerror("Unfinished comment"); }

. { yyerror("Illegal character"); }

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Error, lexeme %s, line %d: %s\n", yytext, lineno, msg);
    exit(1);
}