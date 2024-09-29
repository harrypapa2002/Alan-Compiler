#ifndef __LEXER_HPP__
#define __LEXER_HPP__
#include <string>


int yylex();
void yyerror(const char *s);
void semantic_error(int line, int column, const std::string &msg);
void semantic_warning(int line, int column, const std::string &msg);
unsigned char fixChar(char *c);
unsigned char fixHex(char *s);
unsigned char findChar(char *c);
std::string fixString(char *s);
extern std::vector<std::string> error_buffer; 
extern int semantic_errors;
extern std::vector<std::string> semantic_error_buffer;
extern int semantic_warnings;
extern std::vector<std::string> semantic_warning_buffer;
enum compare { lt, gt, lte, gte, eq, neq};
std::string compareToString(compare op);

#endif
