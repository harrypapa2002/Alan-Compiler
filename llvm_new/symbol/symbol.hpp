#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include "types.hpp"

// Enum for symbol types
enum class SymbolType
{
    VARIABLE,
    FUNCTION,
    PARAMETER
};

// Enum for parameter types
enum class ParameterType
{
    VALUE,
    REFERENCE
};

// Base Symbol class
class Symbol
{
public:
    virtual ~Symbol() = default;

    const std::string& getName() const { return name; }
    Type *getType() const { return type; }
    SymbolType getSymbolType() const { return symbolType; }
    Symbol *getNext() const { return next; }
    void setNext(Symbol *nextSymbol) { next = nextSymbol; }
    int getNestingLevel() const { return nestingLevel; }
    void setNestingLevel(int nestingLevel) { this->nestingLevel = nestingLevel; }

protected:
    std::string name;
    Type *type;
    Symbol *next;
    SymbolType symbolType;
    int nestingLevel;
};

// Derived class for variable symbols
class VariableSymbol : public Symbol
{
public:
    VariableSymbol(const std::string& name, Type *type);
};

// Derived class for parameter symbols
class ParameterSymbol : public Symbol
{
public:
    ParameterSymbol(const std::string& name, Type *type, ParameterType parameterType);
    ParameterType getParameterType() const;

private:
    ParameterType parameterType;
};

// Derived class for function symbols
class FunctionSymbol : public Symbol
{
public:
    FunctionSymbol(const std::string& name, Type *type);

    const std::vector<ParameterSymbol> &getParameters() const;
    TypeEnum getReturnType() const;

    void addParameter(ParameterSymbol parameter);
    void setReturnType(TypeEnum returnType);
    bool getNeedsReturn() const;
    void setNeedsReturn(bool needsReturn);
    void setReturnStatementFound();
    bool getReturnStatementFound() const;
    void addCapturedSymbol(Symbol *symbol);
    const std::unordered_set<Symbol*>& getCapturedSymbols() const;

private:
    std::vector<ParameterSymbol> parameters;
    std::unordered_set<Symbol*> capturedSymbols;    
    TypeEnum returnType;
    bool needsReturn;
    bool returnStatementFound;
};



#endif // SYMBOL_HPP