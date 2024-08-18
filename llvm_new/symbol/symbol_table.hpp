#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <stack>
#include <unordered_map>
#include "scope.hpp"

// SymbolTable class to manage multiple scopes
class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable();

    void enterScope();
    void exitScope();
    
    void enterFunctionScope(FunctionSymbol* function);
    void exitFunctionScope();

    Type* getCurrentFunctionReturnType() const;

    void addSymbol(std::string name, Symbol* symbol);
    Symbol* findSymbol(std::string name);
    Symbol* findSymbolInCurrentScope(std::string name);

    void setReturnStatementFound();
    bool getReturnStatementFound() const;

private:
    Symbol* findGlobalSymbol(std::string name);

    std::stack<Scope*> scopes;
    std::unordered_map<std::string, Symbol*> globalSymbols;
    std::stack<FunctionSymbol*> currentFunctionContext;
};

#endif // SYMBOL_TABLE_HPP
