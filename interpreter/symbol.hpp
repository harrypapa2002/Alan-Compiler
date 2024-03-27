#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "ast.hpp"
#include "types.hpp"
#include <stack>

enum class SymbolType
{
    VARIABLE,
    FUNCTION,
    PARAMETER
};

enum class ParameterType
{
    VALUE,
    REFERENCE
};  





class Symbol
{
public:

    virtual ~Symbol() = default;

    std::string getName() const { return name; }
    Type *getType() const { return type; }
    SymbolType getSymbolType() const { return symbolType; }
    Symbol *getNext() const { return next; }
    void setNext(Symbol *nextSymbol) { next = nextSymbol; }




protected:
    std::string name;
    Type *type;
    Symbol *next;
    SymbolType symbolType;
};


class VariableSymbol : public Symbol {
public:
    VariableSymbol(std::string name, Type *type) {
        this->name = name;
        this->type = type;
        this->symbolType = SymbolType::VARIABLE;
    }
    
};

class ParameterSymbol : public Symbol {
public:
    ParameterSymbol(std::string name, Type *type, ParameterType parameterType) {
        if (parameterType != ParameterType::REFERENCE && type->getType() == TypeEnum::ARRAY)
        {
            yyerror("Only array reference parameters are allowed");
        }
        this->name = name;
        this->type = type;
        this->symbolType = SymbolType::PARAMETER;
        this->parameterType = parameterType;
    }
    
    ParameterType getParameterType() const { return parameterType; }

private:
    ParameterType parameterType;
};

class FunctionSymbol : public Symbol {
public:
    FunctionSymbol(std::string name, Type *type, std::vector<ParameterSymbol *> parameters, TypeEnum returnType) {
        this->name = name;
        this->type = type;
        this->symbolType = SymbolType::FUNCTION;
        this->parameters = parameters;
        this->returnType = returnType;
    }

    std::vector<ParameterSymbol *> getParameters() const { return parameters; }
    TypeEnum getReturnType() const { return returnType; }

    void addParameter(ParameterSymbol *parameter) {
        parameters.push_back(parameter);
    }

    void setReturnType(TypeEnum returnType) {
        this->returnType = returnType;
    }

private:
    std::vector<ParameterSymbol *> parameters;
    TypeEnum returnType;
    
};



class Scope
{
public:
    void addSymbol(std::string name, Symbol *symbol)
    {
        if (symbols.find(name) != symbols.end())
        {
            yyerror("Symbol already defined");
            return;
        }
        symbols[name] = symbol;
    }

    Symbol *findSymbol(std::string name)
    {
        auto it = symbols.find(name);
        if (it != symbols.end())
            return it->second;
        return nullptr;
    }
    std::unordered_map<std::string, Symbol *> getSymbols()
    {
        return symbols;
    }

private:
    std::unordered_map<std::string, Symbol *> symbols;
};

class SymbolTable
{

public:
    SymbolTable()
    {
        enterScope();
    }

    ~SymbolTable()
    {
        while (!scopes.empty())
        {
            exitScope();
        }
    }

    void enterScope()
    {
        scopes.push(new Scope());
    }

    void exitScope()
    {
        Scope *scope = scopes.top();
        auto symbols = scope->getSymbols();
        for (auto &symbolPair : symbols)
        {
            globalSymbols[symbolPair.first] = symbolPair.second->getNext();
        }
        delete scope;
        scopes.pop();
    }

    void addSymbol(std::string name, Symbol *symbol)
    {
        symbol->setNext(findGlobalSymbol(name));
        globalSymbols[name] = symbol;
        scopes.top()->addSymbol(name, symbol);
    }

    Symbol *findSymbol(std::string name)
    {
        return findGlobalSymbol(name);
    }

private:
    Symbol *findGlobalSymbol(std::string name)
    {
        auto it = globalSymbols.find(name);
        if (it != globalSymbols.end())
            return it->second;
        return nullptr;
    }
    std::stack<Scope *> scopes;
    std::unordered_map<std::string, Symbol *> globalSymbols; // Tracks the most recent symbols by name
};

extern SymbolTable st;

#endif // SYMBOL_HPP