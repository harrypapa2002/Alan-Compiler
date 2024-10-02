%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h> 
#include <vector>
#include "../ast/ast.hpp"
#include "../parser/parser.hpp"
#include "lexer.hpp"

enum LexicalErrorType {
    ILLEGAL_CHARACTER,
    UNFINISHED_COMMENT
};

int lineno = 1;       
int column = 1;        
int lexical_errors = 0; 
std::vector<std::string> error_buffer; 
int is_balanced = 0;  
void trackLexicalError(LexicalErrorType errorType);

int comment_start_line = 0;
int comment_start_column = 0;

#define SET_YYLLOC \
    yylloc.first_line = lineno; \
    yylloc.first_column = column; \
    yylloc.last_line = lineno; \
    yylloc.last_column = column + yyleng - 1;

%}

L [a-zA-Z] 
D [0-9]
H [a-fA-F0-9]
W [ \t\r] 
ESC [ntr0\'\"\\] 

%x COMMENT

%%

 /* Keywords */
"byte"    { SET_YYLLOC; column += yyleng; return T_byte; }
"else"    { SET_YYLLOC; column += yyleng; return T_else; }
"false"   { SET_YYLLOC; column += yyleng; return T_false; }
"if"      { SET_YYLLOC; column += yyleng; return T_if; }
"int"     { SET_YYLLOC; column += yyleng; return T_int; }
"proc"    { SET_YYLLOC; column += yyleng; return T_proc; }
"reference" { SET_YYLLOC; column += yyleng; return T_reference; }
"return"  { SET_YYLLOC; column += yyleng; return T_return; }
"while"   { SET_YYLLOC; column += yyleng; return T_while; }
"true"    { SET_YYLLOC; column += yyleng; return T_true; }

 /* Symbols */
[\(\)\[\]\{\}\,\:\;\=\+\/\-\*\%\&\|\!] {
    SET_YYLLOC;
    column += yyleng; 
    yylval.op = yytext[0]; 
    return yytext[0]; 
}
\< { SET_YYLLOC; column += yyleng; yylval.comp = lt; return yytext[0]; }
\> { SET_YYLLOC; column += yyleng; yylval.comp = gt; return yytext[0]; }
"<=" { SET_YYLLOC; column += yyleng; yylval.comp = lte; return T_lte; }
">=" { SET_YYLLOC; column += yyleng; yylval.comp = gte; return T_gte; }
"==" { SET_YYLLOC; column += yyleng; yylval.comp = eq; return T_eq; }
"!=" { SET_YYLLOC; column += yyleng; yylval.comp = neq; return T_neq; }

 /* Constants. Names. Chars. Strings. */
{D}+ { 
    SET_YYLLOC; 
    column += yyleng; 
    yylval.num = atoi(yytext); 
    return T_const; 
}
{L}({L}|{D}|_)* { 
    SET_YYLLOC; 
    column += yyleng; 
    yylval.var = new std::string(yytext); 
    return T_id; 
}
\'([^\\\'\"]|\\({ESC}|x{H}{H}))\' { 
    SET_YYLLOC; 
    column += yyleng; 
    yylval.chr = fixChar(yytext+1); 
    return T_char; 
}
\"(\\({ESC}|x{H}{H})|[^\\\'\"\n])*\"  { 
    SET_YYLLOC; 
    column += yyleng; 
    yylval.str = new std::string(fixString(yytext+1)); 
    return T_string; 
}

 /* WhiteSpace */
\n   { 
    lineno++; 
    column = 1; 
}
{W}+ { 
    column += yyleng;  
}

 /* Comments */
\-\-.*\n? { 
    column = 1; 
    lineno++; 
}
"(*" { 
    comment_start_line = lineno;        
    comment_start_column = column;     
    BEGIN(COMMENT); 
    is_balanced = 0; 
}
<COMMENT>"(*" { 
    column += yyleng; 
    ++is_balanced; 
}
<COMMENT>"*)" { 
    column += yyleng; 
    if(is_balanced) --is_balanced; 
    else { BEGIN(INITIAL); } 
}
<COMMENT>\n { 
    lineno++; 
    column = 1; 
}
<COMMENT>"*" { 
    column += yyleng; 
}
<COMMENT>"(" { 
    column += yyleng; 
}
<COMMENT>")" { 
    column += yyleng; 
}
<COMMENT>[^\(\)*\n]+ { 
    column += yyleng; 
}
<COMMENT><<EOF>> { 
    trackLexicalError(UNFINISHED_COMMENT);
    BEGIN(INITIAL);
}

 /* Illegal characters */
. { 
    SET_YYLLOC;
    trackLexicalError(ILLEGAL_CHARACTER); 
    column += yyleng;
}

%%

void trackLexicalError(LexicalErrorType errorType) {
    char error_message[256];

    switch (errorType) {
        case ILLEGAL_CHARACTER:
            if (isprint(yytext[0])) {
                snprintf(error_message, sizeof(error_message),
                         "Illegal character '%s' encountered at line %d, column %d.",
                         yytext, lineno, column);
            } else {
                snprintf(error_message, sizeof(error_message),
                         "Illegal non-printable character (ASCII code %d) encountered at line %d, column %d.",
                         (int)yytext[0], lineno, column);
            }
            break;

        case UNFINISHED_COMMENT:
            snprintf(error_message, sizeof(error_message),
                     "Unfinished comment starting at line %d, column %d. Make sure all comments are properly closed.",
                     comment_start_line, comment_start_column);
            break;

        default:
            snprintf(error_message, sizeof(error_message),
                     "Lexical error at line %d, column %d.", lineno, column);
            break;
    }

    error_buffer.push_back(error_message);
    lexical_errors++;
}

int findChar(char c) {
    if(c >= '0' && c <= '9') return c - '0';
    else if(c >= 'a' && c <= 'f') return c - 'a' + 10;
    else if(c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

unsigned char fixHex(char *s) {
    return findChar(s[0]) * 16 + findChar(s[1]);
}

unsigned char fixChar(char *s) {
    if(s[0] != '\\') return s[0];
    else if (s[1] == 'x') {
        return fixHex(s+2);
    } else {
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
    for(int i = 0; s[i] != '\"' && s[i] != '\0' ; i++) {
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
