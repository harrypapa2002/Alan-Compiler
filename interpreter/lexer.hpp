#ifndef __LEXER_HPP__
#define __LEXER_HPP__

int yylex();
void yyerror(const char *msg);
unsigned char fixChar(char *c);
unsigned char fixHex(char *s);
unsigned char findChar(char *c);

enum compare { lt, gt, lte, gte, eq, neq};



#endif
