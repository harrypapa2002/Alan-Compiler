#include "scope.hpp"
#include "../lexer/lexer.hpp"

// Destructor for Scope class
Scope::~Scope() {
    for (auto& symbolPair : symbols) {
        delete symbolPair.second;
    }
}

// Add a symbol to the scope
void Scope::addSymbol(std::string name, Symbol* symbol) {
    if (symbols.find(name) != symbols.end()) {
        yyerror("Symbol already defined");
        return;
    }
    symbols[name] = symbol;
}

// Find a symbol in the scope
Symbol* Scope::findSymbol(std::string name) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return it->second;
    }
    return nullptr;
}

// Get all symbols in the scope
const std::unordered_map<std::string, Symbol*>& Scope::getSymbols() const {
    return symbols;
}