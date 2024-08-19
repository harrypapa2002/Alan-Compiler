%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.hpp"
#include "lexer.hpp"
#include "../parser/parser.hpp"
#include <string>
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
[\(\)\[\]\{\}\,\:\;\=\+\/\-\*\%\&\|\!] { yylval.op = yytext[0]; return yytext[0]; }
\< {yylval.comp = lt; return yytext[0]; }
\> {yylval.comp = gt; return yytext[0]; }
"<=" { yylval.comp = lte; return T_lte; }
">=" { yylval.comp = gte; return T_gte; }
"==" { yylval.comp = eq; return T_eq; }
"!=" { yylval.comp = neq; return T_neq; }

 /* Constants. Names. Chars. Strings. */
{D}+ { yylval.num = atoi(yytext); return T_const; }
{L}({L}|{D}|_)* { yylval.var = new std::string(yytext); return T_id; }
\'([^\\\'\"]|\\({ESC}|x{H}{H}))\' { yylval.chr = fixChar(yytext+1); return T_char; }
\"(\\({ESC}|x{H}{H})|[^\\\'\"\n])*\"  { yylval.str = new std::string(fixString(yytext+1));  return T_string; }

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

    /* Illegal characters */

. { yyerror("Illegal character"); }

%%


void yyerror(const char *msg) {
    fprintf(stderr, "Error, lexeme %s, line %d: %s\n", yytext, lineno, msg);
    exit(1);
}

int findChar(char c){
    if(c >= '0' && c <= '9') return c - '0';
    else if(c >= 'a' && c <= 'f') return c - 'a' + 10;
    else if(c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

unsigned char fixHex(char *s){
    return findChar(s[0]) * 16 + findChar(s[1]);
}
unsigned char fixChar(char *s){
    if(s[0] != '\\') return s[0];

    else if (s[1] == 'x'){
        return fixHex(s+2);
    }

    else {
        switch(s[1]){
            case 'n': return '\n';
            case 't': return '\t';
            case 'r': return '\r';
            case '0': return '\0';
            case '\'': return '\'';
            case '\"': return '\"';
            case '\\': return '\\';
            default: return s[1];
        }

    }
}

std::string fixString(char *s) {
    std::string res = "";
    for(int i = 0; s[i] != '\"' && s[i] != '\0' ; i++){
        if(s[i] != '\\') res += s[i];
        else {
            switch(s[i+1]){
                case 'n': res += '\n'; break;
                case 't': res += '\t'; break;
                case 'r': res += '\r'; break;
                case '0': res += '\0'; break;
                case '\'': res += '\''; break;
                case '\"': res += '\"'; break;
                case '\\': res += '\\'; break;
                case 'x': res += fixHex(s+i+2); i++; break;
                default: res += s[i+1]; break;
            }
            i++;
        }
    }
    return res;
}
