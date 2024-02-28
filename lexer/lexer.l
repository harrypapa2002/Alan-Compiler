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
    int is_balanced = 0;
    void ERROR(const char msg []) {
        fprintf(stderr, "Error, line %d: %s\n", lineno, msg);
        exit(1);
    }
%}

L [A-Za-z] 
hex [a-f0-9]
D [0-9]
W [ \t\r] 

%x COMMENT
%x STRING
%x ICOMMENT

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
<STRING>\n { lineno++; ERROR("Changed line in unfinished string"); }
<STRING><<EOF>> { ERROR("Unfinished string"); }
<STRING>. { ERROR("Illegal character in string"); }

\n { lineno++; }
\-\-.*\n? { /* nothing */ }

"(*" {++is_balanced;  BEGIN(COMMENT); }
<COMMENT>"(*" {  ++is_balanced; }
<COMMENT>"*)" {  --is_balanced; if(is_balanced == 0) { BEGIN(INITIAL);} }
<COMMENT>\n { lineno++; }
<COMMENT>"*" { /* nothing */ }
<COMMENT>"(" { /* nothing */ }
<COMMENT>")" { /* nothing */ }
<COMMENT>[^\(\)*\n]+ { printf("%s\n", yytext);/* nothing */ }
<COMMENT><<EOF>> { ERROR("Unfinished comment"); }

. { ERROR("Illegal character"); }

%%

int main () {
  int token;
  do {
    token = yylex();
    printf("token=%d, lexeme=\"%s\"\n", token, yytext);
  } while (token != T_eof);
    return 0;
}