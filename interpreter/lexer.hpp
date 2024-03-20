#ifndef __LEXER_HPP__
#define __LEXER_HPP__

int yylex();
void yyerror(const char *msg);
enum compare { lt, gt, lte, gte, eq, neq};



#endif
