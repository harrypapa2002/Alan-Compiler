#include "../symbol/symbol_table.hpp"
#include "../ast/ast.hpp"
#include "../symbol/types.hpp"

SymbolTable::SymbolTable() : currentFunctionNestingLevel(0) {
    enterScope();

    FunctionSymbol* writeInteger = new FunctionSymbol("writeInteger", typeVoid);
    writeInteger->addParameter(new ParameterSymbol("n", typeInteger, ParameterType::VALUE));
    addSymbol("writeInteger", writeInteger);

    FunctionSymbol* writeByte = new FunctionSymbol("writeByte", typeVoid);
    writeByte->addParameter(new ParameterSymbol("b", typeByte, ParameterType::VALUE));
    addSymbol("writeByte", writeByte);

    FunctionSymbol* writeChar = new FunctionSymbol("writeChar", typeVoid);
    writeChar->addParameter(new ParameterSymbol("b", typeByte, ParameterType::VALUE));
    addSymbol("writeChar", writeChar);

    FunctionSymbol* writeString = new FunctionSymbol("writeString", typeVoid);
    writeString->addParameter(new ParameterSymbol("s", new ArrayType(typeByte), ParameterType::REFERENCE));
    addSymbol("writeString", writeString);

    FunctionSymbol* readInteger = new FunctionSymbol("readInteger", typeInteger);
    addSymbol("readInteger", readInteger);

    FunctionSymbol* readByte = new FunctionSymbol("readByte", typeByte);
    addSymbol("readByte", readByte);

    FunctionSymbol* readChar = new FunctionSymbol("readChar", typeByte);
    addSymbol("readChar", readChar);

    FunctionSymbol* readString = new FunctionSymbol("readString", typeVoid);
    readString->addParameter(new ParameterSymbol("s", new ArrayType(typeByte), ParameterType::REFERENCE));
    readString->addParameter(new ParameterSymbol("n", typeInteger, ParameterType::VALUE));
    addSymbol("readString", readString);

    FunctionSymbol* extend = new FunctionSymbol("extend", typeInteger);
    extend->addParameter(new ParameterSymbol("b", typeByte, ParameterType::VALUE));
    addSymbol("extend", extend);

    FunctionSymbol* shrink = new FunctionSymbol("shrink", typeByte);
    shrink->addParameter(new ParameterSymbol("i", typeInteger, ParameterType::VALUE));
    addSymbol("shrink", shrink);

    FunctionSymbol* strlen = new FunctionSymbol("strlen", typeInteger);
    strlen->addParameter(new ParameterSymbol("s", new ArrayType(typeByte), ParameterType::REFERENCE));
    addSymbol("strlen", strlen);

    FunctionSymbol* strcmp = new FunctionSymbol("strcmp", typeInteger);
    strcmp->addParameter(new ParameterSymbol("s2", new ArrayType(typeByte), ParameterType::REFERENCE));
    strcmp->addParameter(new ParameterSymbol("s1", new ArrayType(typeByte), ParameterType::REFERENCE));

    addSymbol("strcmp", strcmp);

    FunctionSymbol* strcpy = new FunctionSymbol("strcpy", typeVoid);
    strcpy->addParameter(new ParameterSymbol("src", new ArrayType(typeByte), ParameterType::REFERENCE));
    strcpy->addParameter(new ParameterSymbol("trg", new ArrayType(typeByte), ParameterType::REFERENCE));
    addSymbol("strcpy", strcpy);

    FunctionSymbol* strcat = new FunctionSymbol("strcat", typeVoid);
    strcat->addParameter(new ParameterSymbol("src", new ArrayType(typeByte), ParameterType::REFERENCE));
    strcat->addParameter(new ParameterSymbol("trg", new ArrayType(typeByte), ParameterType::REFERENCE));

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
    currentFunctionNestingLevel++;
}

// Exit a function scope
void SymbolTable::exitFunctionScope() {
    if (!currentFunctionContext.empty()) {
        currentFunctionContext.pop();
    }
    exitScope();
    currentFunctionNestingLevel--;
}

// Get the current function's return type
Type* SymbolTable::getCurrentFunctionReturnType() const {
    if (currentFunctionContext.empty()) return nullptr;
    return currentFunctionContext.top()->getType();
}

// Add a symbol to the current scope
void SymbolTable::addSymbol(const std::string& name, Symbol* symbol) {
    symbol->setNext(findGlobalSymbol(name));
    globalSymbols[name] = symbol;
    scopes.top()->addSymbol(name, symbol);
    symbol->setNestingLevel(currentFunctionNestingLevel);
}

// Find a symbol in the global scope
Symbol* SymbolTable::findSymbol(const std::string& name) {
    Symbol* symbol = findGlobalSymbol(name);

    if (symbol) {

        if (symbol->getSymbolType() == SymbolType::FUNCTION) {
            return symbol;
        }


        int symbolFunctionNestingLevel = symbol->getNestingLevel();
        if (symbolFunctionNestingLevel < currentFunctionNestingLevel) {
            int levelDifference = currentFunctionNestingLevel - symbolFunctionNestingLevel - 1;

            std::stack<FunctionSymbol*> tempStack = currentFunctionContext;

            while (levelDifference >= 0) {
                FunctionSymbol* currentFunction = tempStack.top();
                currentFunction->addCapturedSymbol(symbol);
                tempStack.pop();
                --levelDifference;
            }

        }
    }
    return symbol;
}

// Find a symbol in the current scope
Symbol* SymbolTable::findSymbolInCurrentScope(const std::string& name) {
    return scopes.top()->findSymbol(name);
}

// Mark the current function's return statement as found
void SymbolTable::setReturnStatementFound() {
    if (!currentFunctionContext.empty()) {
        currentFunctionContext.top()->setNeedsReturn(false);
        currentFunctionContext.top()->setReturnStatementFound();
    }
}

bool SymbolTable::getReturnStatementFound() const {
    if (currentFunctionContext.empty()) return false;
    return currentFunctionContext.top()->getReturnStatementFound();
}

// Find a symbol in the global symbol map
Symbol* SymbolTable::findGlobalSymbol(const std::string& name) {
    auto it = globalSymbols.find(name);
    if (it != globalSymbols.end()) return it->second;
    return nullptr;
}

// Get the name of the current function
const std::string& SymbolTable::getCurrentFunctionName() const {
    return currentFunctionContext.top()->getName();
}

FunctionSymbol* SymbolTable::getCurrentFunctionContext() const {
    if(!currentFunctionContext.empty())
    {
        return currentFunctionContext.top();
    }
    return nullptr;
}