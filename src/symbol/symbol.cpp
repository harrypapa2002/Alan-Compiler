#include "symbol.hpp"
#include "../ast/ast.hpp"

// Constructor for VariableSymbol
VariableSymbol::VariableSymbol(const std::string& name, Type *type)
{
    this->name = name;
    this->type = type;
    this->symbolType = SymbolType::VARIABLE;
}

// Constructor for ParameterSymbol
ParameterSymbol::ParameterSymbol(const std::string& name, Type *type, ParameterType parameterType)
{
    this->name = name;
    this->type = type;
    this->symbolType = SymbolType::PARAMETER;
    this->parameterType = parameterType;
    this->setIsParameter(true);
}

// Get the parameter type
ParameterType ParameterSymbol::getParameterType() const
{
    return parameterType;
}

// Constructor for FunctionSymbol
FunctionSymbol::FunctionSymbol(const std::string& name, Type *type) : parameters()
{
    this->name = name;
    this->type = type;
    this->symbolType = SymbolType::FUNCTION;
    this->returnType = type->getType();
    this->needsReturn = (returnType != TypeEnum::VOID);
    this->returnStatementFound = false;
}

// Get parameters of the function
const std::vector<ParameterSymbol*> &FunctionSymbol::getParameters() const
{
    return parameters;
}

// Get the return type of the function
TypeEnum FunctionSymbol::getReturnType() const
{
    return returnType;
}

// Add a parameter to the function
void FunctionSymbol::addParameter(ParameterSymbol* parameter)
{
    parameters.push_back(parameter);
}

// Set the return type of the function
void FunctionSymbol::setReturnType(TypeEnum returnType)
{
    this->returnType = returnType;
}

// Check if the function needs a return statement
bool FunctionSymbol::getNeedsReturn() const
{
    return needsReturn;
}

// Set if the function needs a return statement
void FunctionSymbol::setNeedsReturn(bool needsReturn)
{
    this->needsReturn = needsReturn;
}

void FunctionSymbol::setReturnStatementFound()
{
    returnStatementFound = true;
}

bool FunctionSymbol::getReturnStatementFound() const
{
    return returnStatementFound;
}

void FunctionSymbol::addCapturedSymbol(Symbol *symbol)
{
    capturedSymbols.insert(symbol);
}

const std::unordered_set<Symbol*>& FunctionSymbol::getCapturedSymbols() const
{
    return capturedSymbols;
}

FunctionSymbol::~FunctionSymbol() {
    for (ParameterSymbol* param : parameters) {
        delete param;
    }
}