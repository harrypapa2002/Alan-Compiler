#ifndef __LEXER_HPP__
#define __LEXER_HPP__
#include <string>


int yylex();
void yyerror(const char *msg);
unsigned char fixChar(char *c);
unsigned char fixHex(char *s);
unsigned char findChar(char *c);
std::string fixString(char *s);

enum compare { lt, gt, lte, gte, eq, neq};

#endif
