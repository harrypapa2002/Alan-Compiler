#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <unordered_map>
#include <string>
#include "symbol.hpp"

// Scope class to manage symbols
class Scope {
public:
    ~Scope();

    void addSymbol(const std::string& name, Symbol* symbol);
    Symbol* findSymbol(const std::string& name);
    const std::unordered_map<std::string, Symbol*>& getSymbols() const;

private:
    std::unordered_map<std::string, Symbol*> symbols;
};

#endif // SCOPE_HPP
