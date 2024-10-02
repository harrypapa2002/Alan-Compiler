#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <stack>
#include <unordered_map>
#include "scope.hpp"

class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable();

    void enterScope();
    void exitScope();
    
    void enterFunctionScope(FunctionSymbol* function);
    void exitFunctionScope();

    Type* getCurrentFunctionReturnType() const;

    void addSymbol(const std::string& name, Symbol* symbol);
    Symbol* findSymbol(const std::string& name);
    Symbol* findSymbolInCurrentScope(const std::string& name);

    void setReturnStatementFound();
    bool getReturnStatementFound() const;

    const std::string& getCurrentFunctionName() const;
    FunctionSymbol* getCurrentFunctionContext() const;

private:
    Symbol* findGlobalSymbol(const std::string& name);

    std::stack<Scope*> scopes;
    std::unordered_map<std::string, Symbol*> globalSymbols;
    std::stack<FunctionSymbol*> currentFunctionContext;
    int currentFunctionNestingLevel;
};

#endif // SYMBOL_TABLE_HPP
