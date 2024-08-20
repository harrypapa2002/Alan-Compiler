#include "symbol.hpp"
#include "../ast/ast.hpp"

// Constructor for VariableSymbol
VariableSymbol::VariableSymbol(std::string name, Type* type) {
    this->name = name;
    this->type = type;
    this->symbolType = SymbolType::VARIABLE;
}

// Constructor for ParameterSymbol
ParameterSymbol::ParameterSymbol(std::string name, Type* type, ParameterType parameterType) {
    if (parameterType != ParameterType::REFERENCE && type->getType() == TypeEnum::ARRAY) {
        yyerror("Only array reference parameters are allowed");
    }
    this->name = name;
    this->type = type;
    this->symbolType = SymbolType::PARAMETER;
    this->parameterType = parameterType;
}

// Method to print parameter symbol details
void ParameterSymbol::printOn(std::ostream& out) const {
    out << "Parameter: " << name << " " << *type;
    out << " " << (parameterType == ParameterType::VALUE ? "value" : "reference");
}

// Get the parameter type
ParameterType ParameterSymbol::getParameterType() const { 
    return parameterType; 
}

// Constructor for FunctionSymbol
FunctionSymbol::FunctionSymbol(std::string name, Type* type) : parameters() {
    this->name = name;
    this->type = type;
    this->symbolType = SymbolType::FUNCTION;
    this->returnType = type->getType();
    this->needsReturn = (returnType != TypeEnum::VOID);
}

// Get parameters of the function
const std::vector<ParameterSymbol>& FunctionSymbol::getParameters() const { 
    return parameters; 
}

// Get the return type of the function
TypeEnum FunctionSymbol::getReturnType() const { 
    return returnType; 
}

// Add a parameter to the function
void FunctionSymbol::addParameter(ParameterSymbol parameter) { 
    parameters.push_back(parameter); 
}

// Set the return type of the function
void FunctionSymbol::setReturnType(TypeEnum returnType) { 
    this->returnType = returnType; 
}

// Check if the function needs a return statement
bool FunctionSymbol::getNeedsReturn() const { 
    return needsReturn; 
}

// Set if the function needs a return statement
void FunctionSymbol::setNeedsReturn(bool needsReturn) { 
    this->needsReturn = needsReturn; 
}

void FunctionSymbol::setReturnStatementFound() {
    returnStatementFound = true;
}

bool FunctionSymbol::getReturnStatementFound() const {
    return returnStatementFound;
}