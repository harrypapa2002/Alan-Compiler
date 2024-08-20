#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <vector>
#include <iostream>
#include "types.hpp"

// Enum for symbol types
enum class SymbolType {
    VARIABLE,
    FUNCTION,
    PARAMETER
};

// Enum for parameter types
enum class ParameterType {
    VALUE,
    REFERENCE
};

// Base Symbol class
class Symbol {
public:
    virtual ~Symbol() = default;

    std::string getName() const { return name; }
    Type* getType() const { return type; }
    SymbolType getSymbolType() const { return symbolType; }
    Symbol* getNext() const { return next; }
    void setNext(Symbol* nextSymbol) { next = nextSymbol; }

protected:
    std::string name;
    Type* type;
    Symbol* next;
    SymbolType symbolType;
};

// Derived class for variable symbols
class VariableSymbol : public Symbol {
public:
    VariableSymbol(std::string name, Type* type);
};

// Derived class for parameter symbols
class ParameterSymbol : public Symbol {
public:
    ParameterSymbol(std::string name, Type* type, ParameterType parameterType);
    
    void printOn(std::ostream& out) const;
    ParameterType getParameterType() const;

private:
    ParameterType parameterType;
};

// Overload operator for parameter symbols
inline std::ostream& operator<<(std::ostream& out, const ParameterSymbol& p) {
    p.printOn(out);
    return out;
}

// Derived class for function symbols
class FunctionSymbol : public Symbol {
public:
    FunctionSymbol(std::string name, Type* type);

    const std::vector<ParameterSymbol>& getParameters() const;
    TypeEnum getReturnType() const;

    void addParameter(ParameterSymbol parameter);
    void setReturnType(TypeEnum returnType);
    bool getNeedsReturn() const;
    void setNeedsReturn(bool needsReturn);

private:
    std::vector<ParameterSymbol> parameters;
    TypeEnum returnType;
    bool needsReturn;
    this->returnStatementFound = false;
};

#endif // SYMBOL_HPP