%option noyywrap

%{
    #define T_eof 0
    #define T_const 1000
    #define T_id 1001
    #define T_byte 1002
    #define T_else 1003
    #define T_false 1004
    #define T_if 1005
    #define T_int 1006
    #define T_proc 1007
    #define T_reference 1008
    #define T_return 1009
    #define T_while 1010
    #define T_true 1011
    #define T_char 1012
    #define T_lte 1013
    #define T_gte 1014
    #define T_eq 1015
    #define T_neq 1016
    #define T_string 1017
    int lineno = 1;
    int nested_comment = 0;

    void yyerror(const char msg []) {
        fprintf(stderr, "Error, line %d: %s\n", lineno, msg);
        exit(1);
    }
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
<COMMENT>"(*" { ++nested_comment; }
<COMMENT>"*)" { if (nested_comment) --nested_comment; else BEGIN(INITIAL); }
<COMMENT>\n { ++lineno; }
 /* Stars not followed by stars or parenthesis */
<COMMENT>"*"+[^*)\n]* { /* nothing */ }
 /* Parenthesis not followed by star */
<COMMENT>"("+[^*\n]*  { /* nothing */ }
 /* Anything that is not a star or parentesis */
<COMMENT>[^(*\n]+     { /* nothing */ }
<COMMENT><<EOF>> { yyerror("Unfinished comment"); }

{D}+({L}|_)+ { yyerror("Illegal character"); }

. { yyerror("Illegal character"); }

%%

int main () {
  int token;
  do {
    token = yylex();
    printf("Line %d: token=%d, lexeme=\"%s\"\n", lineno, token, yytext);
  } while (token != T_eof);
  return 0;
}

