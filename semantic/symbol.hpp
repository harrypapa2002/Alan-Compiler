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
    void printOn(std::ostream &out) const {
        out << "Parameter: " << name << " " << *type;
        out << " " << (parameterType == ParameterType::VALUE ? "value" : "reference");
    }
    ParameterType getParameterType() const { return parameterType; }

private:
    ParameterType parameterType;
};

inline std::ostream &operator<<(std::ostream &out,ParameterSymbol p)
{
    p.printOn(out);
    return out;
}

class FunctionSymbol : public Symbol {
public:
    FunctionSymbol(std::string name, Type *type) : parameters(){
        this->name = name;
        this->type = type;
        this->symbolType = SymbolType::FUNCTION;
        this->returnType = type->getType();
    }

    const std::vector<ParameterSymbol> &getParameters() const { return parameters; }
    TypeEnum getReturnType() const { return returnType; }

    void addParameter(ParameterSymbol parameter) {
        parameters.push_back(parameter);
    }

    void setReturnType(TypeEnum returnType) {
        this->returnType = returnType;
    }
    

private:
    std::vector<ParameterSymbol> parameters;
    TypeEnum returnType;
    
};



class Scope
{
public:

    ~Scope()
    {
        for (auto &symbolPair : symbols)
        {
            delete symbolPair.second;
        }
    }

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
    const std::unordered_map<std::string, Symbol *> &getSymbols() const
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
        FunctionSymbol *writeInteger = new FunctionSymbol(std::string("writeInteger"), typeVoid);
        writeInteger->addParameter(ParameterSymbol(std::string("n"), typeInteger, ParameterType::VALUE));
        addSymbol(std::string("writeInteger"), writeInteger);
        FunctionSymbol *writeByte = new FunctionSymbol(std::string(std::string("writeByte")), typeVoid);
        writeByte->addParameter(ParameterSymbol(std::string("b"), typeByte, ParameterType::VALUE));
        addSymbol(std::string("writeByte"), writeByte);
        FunctionSymbol *writeChar = new FunctionSymbol(std::string("writeChar"), typeVoid);
        writeChar->addParameter(ParameterSymbol(std::string("b"), typeByte, ParameterType::VALUE));
        addSymbol(std::string("writeChar"), writeChar);
        FunctionSymbol *writeString = new FunctionSymbol(std::string("writeString"), typeVoid);
        writeString->addParameter(ParameterSymbol(std::string("s"), new ArrayType(typeByte), ParameterType::REFERENCE));
        addSymbol(std::string("writeString"), writeString);
        FunctionSymbol *readInteger = new FunctionSymbol(std::string("readInteger"), typeInteger);
        addSymbol(std::string("readInteger"), readInteger);
        FunctionSymbol *readByte = new FunctionSymbol(std::string("readByte"), typeByte);
        addSymbol(std::string("readByte"), readByte);
        FunctionSymbol *readChar = new FunctionSymbol(std::string("readChar"), typeByte);
        addSymbol(std::string("readChar"), readChar);
        FunctionSymbol *readString = new FunctionSymbol(std::string("readString"), typeVoid);
        readString->addParameter(ParameterSymbol(std::string("n"), typeInteger, ParameterType::VALUE));
        readString->addParameter(ParameterSymbol(std::string("s"), new ArrayType(typeByte), ParameterType::REFERENCE));
        addSymbol(std::string("readString"), readString);
        /*
        extend (b : byte) : int {}
        shrink (i : int) : byte {}
        strlen (s : reference byte []) : int {}
        strcmp (s1 : reference byte [], s2 : reference byte []) : int {}
        strcpy (trg : reference byte [], src : reference byte []) : proc {}
        strcat (trg : reference byte [], src : reference byte []) : proc {}
        */
        FunctionSymbol *extend = new FunctionSymbol(std::string("extend"), typeInteger);
        extend->addParameter(ParameterSymbol(std::string("b"), typeByte, ParameterType::VALUE));
        addSymbol(std::string("extend"), extend);
        FunctionSymbol *shrink = new FunctionSymbol(std::string("shrink"), typeByte);
        shrink->addParameter(ParameterSymbol(std::string("i"), typeInteger, ParameterType::VALUE));
        addSymbol(std::string("shrink"), shrink);
        FunctionSymbol *strlen = new FunctionSymbol(std::string("strlen"), typeInteger);
        strlen->addParameter(ParameterSymbol(std::string("s"), new ArrayType(typeByte), ParameterType::REFERENCE));
        addSymbol(std::string("strlen"), strlen);
        FunctionSymbol *strcmp = new FunctionSymbol(std::string("strcmp"), typeInteger);
        strcmp->addParameter(ParameterSymbol(std::string("s1"), new ArrayType(typeByte), ParameterType::REFERENCE));
        strcmp->addParameter(ParameterSymbol(std::string("s2"), new ArrayType(typeByte), ParameterType::REFERENCE));
        addSymbol(std::string("strcmp"), strcmp);
        FunctionSymbol *strcpy = new FunctionSymbol(std::string("strcpy"), typeVoid);
        strcpy->addParameter(ParameterSymbol(std::string("trg"), new ArrayType(typeByte), ParameterType::REFERENCE));
        strcpy->addParameter(ParameterSymbol(std::string("src"), new ArrayType(typeByte), ParameterType::REFERENCE));
        addSymbol(std::string("strcpy"), strcpy);
        FunctionSymbol *strcat = new FunctionSymbol(std::string("strcat"), typeVoid);
        strcat->addParameter(ParameterSymbol(std::string("trg"), new ArrayType(typeByte), ParameterType::REFERENCE));
        strcat->addParameter(ParameterSymbol(std::string("src"), new ArrayType(typeByte), ParameterType::REFERENCE));
        addSymbol(std::string("strcat"), strcat);
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
        scopes.pop();
        delete scope;
        
    }

    void enterFunctionScope(FunctionSymbol* function) {
        currentFunctionContext.push(function);
        enterScope(); 
    }

    void exitFunctionScope() {
        if (!currentFunctionContext.empty()) {
            currentFunctionContext.pop();
        }
        exitScope();
    }

    Type* getCurrentFunctionReturnType() const {
        if (currentFunctionContext.empty()) return nullptr;
        return currentFunctionContext.top()->getType();
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

    Symbol *findSymbolInCurrentScope(std::string name)
    {
        return scopes.top()->findSymbol(name);
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
    std::stack<FunctionSymbol*> currentFunctionContext; // Track the current function context

};




extern SymbolTable st;

#endif // SYMBOL_HPP