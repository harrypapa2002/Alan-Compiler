#include "scope.hpp"
#include "../lexer/lexer.hpp"

// Destructor for Scope class
Scope::~Scope() {
    for (auto& symbolPair : symbols) {
       if(!symbolPair.second->getIsParameter())
       {
           delete symbolPair.second;
       }
    }
}

// Add a symbol to the scope
void Scope::addSymbol(const std::string& name, Symbol* symbol) {
    symbols[name] = symbol;
}

// Find a symbol in the scope
Symbol* Scope::findSymbol(const std::string& name) {
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