#include "../symbol/symbol_table.hpp"
#include "../ast/ast.hpp"
#include "../symbol/types.hpp"

// Constructor for SymbolTable
SymbolTable::SymbolTable() {
    enterScope();
    // Adding predefined functions
    FunctionSymbol* writeInteger = new FunctionSymbol("writeInteger", typeVoid);
    writeInteger->addParameter(ParameterSymbol("n", typeInteger, ParameterType::VALUE));
    addSymbol("writeInteger", writeInteger);

    FunctionSymbol* writeByte = new FunctionSymbol("writeByte", typeVoid);
    writeByte->addParameter(ParameterSymbol("b", typeByte, ParameterType::VALUE));
    addSymbol("writeByte", writeByte);

    FunctionSymbol* writeChar = new FunctionSymbol("writeChar", typeVoid);
    writeChar->addParameter(ParameterSymbol("b", typeByte, ParameterType::VALUE));
    addSymbol("writeChar", writeChar);

    FunctionSymbol* writeString = new FunctionSymbol("writeString", typeVoid);
    writeString->addParameter(ParameterSymbol("s", new ArrayType(typeByte), ParameterType::REFERENCE));
    addSymbol("writeString", writeString);

    FunctionSymbol* readInteger = new FunctionSymbol("readInteger", typeInteger);
    addSymbol("readInteger", readInteger);

    FunctionSymbol* readByte = new FunctionSymbol("readByte", typeByte);
    addSymbol("readByte", readByte);

    FunctionSymbol* readChar = new FunctionSymbol("readChar", typeByte);
    addSymbol("readChar", readChar);

    FunctionSymbol* readString = new FunctionSymbol("readString", typeVoid);
    readString->addParameter(ParameterSymbol("s", new ArrayType(typeByte), ParameterType::REFERENCE));
    readString->addParameter(ParameterSymbol("n", typeInteger, ParameterType::VALUE));
    addSymbol("readString", readString);

    FunctionSymbol* extend = new FunctionSymbol("extend", typeInteger);
    extend->addParameter(ParameterSymbol("b", typeByte, ParameterType::VALUE));
    addSymbol("extend", extend);

    FunctionSymbol* shrink = new FunctionSymbol("shrink", typeByte);
    shrink->addParameter(ParameterSymbol("i", typeInteger, ParameterType::VALUE));
    addSymbol("shrink", shrink);

    FunctionSymbol* strlen = new FunctionSymbol("strlen", typeInteger);
    strlen->addParameter(ParameterSymbol("s", new ArrayType(typeByte), ParameterType::REFERENCE));
    addSymbol("strlen", strlen);

    FunctionSymbol* strcmp = new FunctionSymbol("strcmp", typeInteger);
    strcmp->addParameter(ParameterSymbol("s2", new ArrayType(typeByte), ParameterType::REFERENCE));
    strcmp->addParameter(ParameterSymbol("s1", new ArrayType(typeByte), ParameterType::REFERENCE));

    addSymbol("strcmp", strcmp);

    FunctionSymbol* strcpy = new FunctionSymbol("strcpy", typeVoid);
    strcpy->addParameter(ParameterSymbol("src", new ArrayType(typeByte), ParameterType::REFERENCE));
    strcpy->addParameter(ParameterSymbol("trg", new ArrayType(typeByte), ParameterType::REFERENCE));
    addSymbol("strcpy", strcpy);

    FunctionSymbol* strcat = new FunctionSymbol("strcat", typeVoid);
    strcat->addParameter(ParameterSymbol("src", new ArrayType(typeByte), ParameterType::REFERENCE));
    strcat->addParameter(ParameterSymbol("trg", new ArrayType(typeByte), ParameterType::REFERENCE));

    addSymbol("strcat", strcat);
}

// Destructor for SymbolTable
SymbolTable::~SymbolTable() {
    while (!scopes.empty()) {
        exitScope();
    }
}

// Enter a new scope
void SymbolTable::enterScope() {
    scopes.push(new Scope());
}

// Exit the current scope
void SymbolTable::exitScope() {
    Scope* scope = scopes.top();
    auto symbols = scope->getSymbols();
    for (auto& symbolPair : symbols) {
        globalSymbols[symbolPair.first] = symbolPair.second->getNext();
    }
    scopes.pop();
    delete scope;
}

// Enter a function scope
void SymbolTable::enterFunctionScope(FunctionSymbol* function) {
    currentFunctionContext.push(function);
    enterScope();
}

// Exit a function scope
void SymbolTable::exitFunctionScope() {
    if (!currentFunctionContext.empty()) {
        currentFunctionContext.pop();
    }
    exitScope();
}

// Get the current function's return type
Type* SymbolTable::getCurrentFunctionReturnType() const {
    if (currentFunctionContext.empty()) return nullptr;
    return currentFunctionContext.top()->getType();
}

// Add a symbol to the current scope
void SymbolTable::addSymbol(std::string name, Symbol* symbol) {
    symbol->setNext(findGlobalSymbol(name));
    globalSymbols[name] = symbol;
    scopes.top()->addSymbol(name, symbol);
}

// Find a symbol in the global scope
Symbol* SymbolTable::findSymbol(std::string name) {
    return findGlobalSymbol(name);
}

// Find a symbol in the current scope
Symbol* SymbolTable::findSymbolInCurrentScope(std::string name) {
    return scopes.top()->findSymbol(name);
}

// Mark the current function's return statement as found
void SymbolTable::setReturnStatementFound() {
    if (!currentFunctionContext.empty()) {
        currentFunctionContext.top()->setNeedsReturn(false);
    }
    returnStatementFound = true;

}

bool FunctionSymbol::getReturnStatementFound() const {
    return returnStatementFound;
}

// Find a symbol in the global symbol map
Symbol* SymbolTable::findGlobalSymbol(std::string name) {
    auto it = globalSymbols.find(name);
    if (it != globalSymbols.end()) return it->second;
    return nullptr;
}
