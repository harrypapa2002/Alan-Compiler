#include "ast.hpp"
#include "../symbol/symbol_table.hpp"

SymbolTable st;

// StmtList Class Semantic Method Implementation

void StmtList::sem()
{
    for (auto it = stmts.rbegin(); it != stmts.rend(); ++it)
    {
        auto stmt = *it;
        stmt->setExternal(external);
        stmt->sem();
        if (stmt->isReturnStatement())
            st.setReturnStatementFound();
    }
    isReturn = false;
}

// LocalDefList Class Semantic Method Implementation

void LocalDefList::sem()
{
    for (auto it = defs.rbegin(); it != defs.rend(); ++it)
    {
        auto def = *it;
        def->sem();
    }
}

// Fpar Class Semantic Method Implementation

void Fpar::sem()
{
    if (st.findSymbolInCurrentScope(*name))
    {
        semantic_error(this->line, this->column,
            "Parameter '" + *name + "' already declared in the scope of function '" + st.getCurrentFunctionName() + "'");
    }
    else if(parameterType!=ParameterType::REFERENCE && type->getType() == TypeEnum::ARRAY)
    {
        semantic_error(this->line, this->column,
            "Only array reference parameters are allowed.");
    }
    else
    {
        ParameterSymbol *parameterSymbol = new ParameterSymbol(*name, type, parameterType);
        st.addSymbol(*name, parameterSymbol);
        st.getCurrentFunctionContext()->addParameter(parameterSymbol);

        if (type)
        {
            isArray = (type->getType() == TypeEnum::ARRAY);
        }
    }
}

// FparList Class Semantic Method Implementation

void FparList::sem()
{
    for (auto it = fpar.rbegin(); it != fpar.rend(); ++it)
    {
        auto f = *it;
        f->sem();
    }
}

// FuncDef Class Semantic Method Implementation

void FuncDef::sem()
{
    if (st.findSymbolInCurrentScope(*name))
    {
        semantic_error(this->line, this->column,
            "Function name '" + *name + "' already declared in the same scope.");
    }
    else if(!st.getCurrentFunctionContext() && type->getType() != TypeEnum::VOID)
    {
        semantic_error(this->line, this->column,
            "Main function must have a 'proc' return type.");
    }
    else
    {

        FunctionSymbol *funcSymbol = new FunctionSymbol(*name, type);
        st.addSymbol(*name, funcSymbol);
        st.enterFunctionScope(funcSymbol);

        if (fpar)
        {
            
            fpar->sem();
        
        }

        if (localDef)
        {
            localDef->sem();
        }

        if (stmts)
        {
            stmts->setExternal(true);
            stmts->sem();
        }

        if (funcSymbol->getNeedsReturn())
        {
            semantic_warning(this->line, this->column,
                "Non-void function '" + *name + "' does not have a return statement.");
        }

        if (funcSymbol->getReturnStatementFound())
        {
            setReturn();
        }

        for (auto &captured : funcSymbol->getCapturedSymbols())
        {
            if (captured->getSymbolType() == SymbolType::VARIABLE)
            {
                capturedVars.push_back(new CapturedVar(captured->getName(), captured->getType()));
            }
            else
            {
                capturedVars.push_back(new CapturedVar(captured->getName(), captured->getType(), true,
                                                       static_cast<ParameterSymbol *>(captured)->getParameterType()));
            }
        }

        st.exitFunctionScope();
    }
}

// VarDef Class Semantic Method Implementation

void VarDef::sem()
{
    if (st.findSymbolInCurrentScope(*name))
    {
        semantic_error(this->line, this->column,
            "Variable name '" + *name + "' is already declared in the current scope.");
    }
    else if (isArray)
    {
        if (size <= 0)
        {
            semantic_error(this->line, this->column,
                "Array size for variable '" + *name + "' must be greater than 0.");
        }
        else
        {
            type = new ArrayType(type, size);
            st.addSymbol(*name, new VariableSymbol(*name, type));
        }
    }
    else
    {
        st.addSymbol(*name, new VariableSymbol(*name, type));
    }
}

// ExprList Class Semantic Method Implementation

void ExprList::sem()
{
    for (auto it = exprs.rbegin(); it != exprs.rend(); ++it)
    {
        auto expr = *it;
        expr->sem();
    }
}

// UnOp Class Semantic Method Implementation

void UnOp::sem()
{
    expr->sem();

    if (expr->getTypeEnum() != TypeEnum::INT)
    {
        semantic_error(this->line, this->column,
            "Unary operator '" + std::string(1, op) + "' can only be applied to integers, but found type '" +
            typeToString(expr->getTypeEnum()) + "'.");
    }
    else
    {
        type = typeInteger;
    }
}

// BinOp Class Semantic Method Implementation

void BinOp::sem()
{
    left->sem();
    right->sem();

    TypeEnum tLeft = left->getTypeEnum();
    TypeEnum tRight = right->getTypeEnum();

    if (!equalTypes(tLeft, tRight))
    {
        semantic_error(this->line, this->column,
            "Type mismatch in binary operation '" + std::string(1, op) + "': left operand is '" +
            typeToString(tLeft) + "', right operand is '" + typeToString(tRight) + "'.");
    }
    else if (!equalTypes(left->getTypeEnum(), TypeEnum::INT) && !equalTypes(left->getTypeEnum(), TypeEnum::BYTE))
    {
        semantic_error(this->line, this->column,
            "Binary operator '" + std::string(1, op) +
            "' can only be applied to integers or bytes, but found type '" +
            typeToString(left->getTypeEnum()) + "'.");
    }
    else
    {
        type = left->getType();
    }
}

// CondCompOp Class Semantic Method Implementation

void CondCompOp::sem()
{
    left->sem();
    right->sem();
    TypeEnum tLeft = left->getTypeEnum();
    TypeEnum tRight = right->getTypeEnum();

    if (!equalTypes(tLeft, tRight))
    {
        semantic_error(this->line, this->column,
            "Type mismatch in comparison operation '" + compareToString(op) + "': left operand is '" +
            typeToString(tLeft) + "', right operand is '" + typeToString(tRight) + "'.");
    }
    else if (!equalTypes(left->getTypeEnum(), TypeEnum::INT) && !equalTypes(left->getTypeEnum(), TypeEnum::BYTE))
    {
        semantic_error(this->line, this->column,
            "Comparison operator '" + compareToString(op) +
            "' can only be applied to integers or bytes, but found type '" +
            typeToString(left->getTypeEnum()) + "'.");
    }
}

// CondBoolOp Class Semantic Method Implementation

void CondBoolOp::sem()
{
    left->sem();
    right->sem();
}

// CondUnOp Class Semantic Method Implementation

void CondUnOp::sem()
{
    cond->sem();
}

// IntConst Class Semantic Method Implementation

void IntConst::sem()
{
    type = typeInteger;
}

// CharConst Class Semantic Method Implementation

void CharConst::sem()
{
    type = typeByte;
}

// Lval Class Semantic Method Implementation

void Lval::sem()
{
}

// StringConst Class Semantic Method Implementation

void StringConst::sem()
{
    type = new ArrayType(typeByte, name->size() + 1);
}

// BoolConst Class Semantic Method Implementation

void BoolConst::sem()
{
}

// Id Class Semantic Method Implementation

void Id::sem()
{
    Symbol *entry = st.findSymbol(*name);
    if (!entry)
    {
        semantic_error(this->line, this->column,
            "Variable '" + *name + "' is not declared.");
    }
    else
    {
        symbolType = entry->getSymbolType();
        type = entry->getType();
        if (symbolType == SymbolType::FUNCTION)
        {
            semantic_error(this->line, this->column,
                "Function '" + *name + "' cannot be used as a variable.");
        }
    }
}

// ArrayAccess Class Semantic Method Implementation

void ArrayAccess::sem()
{
    indexExpr->sem();

    if (indexExpr->getTypeEnum() != TypeEnum::INT)
    {
        semantic_error(this->line, this->column,
            "Array index must be an integer, but found type '" + typeToString(indexExpr->getTypeEnum()) + "'.");
    }
    else
    {
        Symbol *entry = st.findSymbol(*name);
        if (!entry)
        {
            semantic_error(this->line, this->column,
                "Array '" + *name + "' is not declared.");
        }
        else if (entry->getSymbolType() == SymbolType::FUNCTION)
        {
            semantic_error(this->line, this->column,
                "Variable '" + *name + "' is not an array.");
        }
        else if (Type *t = entry->getType())
        {
            if (t->getType() != TypeEnum::ARRAY)
            {
                semantic_error(this->line, this->column,
                    "Variable '" + *name + "' is not an array.");
            }
            else
            {
                type = t->getBaseType();
            }
        }
    }
}

// Let Class Semantic Method Implementation

void Let::sem()
{
    lexpr->sem();
    rexpr->sem();

    TypeEnum leftType = lexpr->getTypeEnum();
    TypeEnum rightType = rexpr->getTypeEnum();

    if (!equalTypes(leftType, rightType))
    {
        semantic_error(this->line, this->column,
            "Type mismatch in assignment: cannot assign type '" + typeToString(rightType) +
            "' to type '" + typeToString(leftType) + "'.");
    }
    else
    {
        isReturn = false;
    }
}

// FuncCall Class Semantic Method Implementation

void FuncCall::sem()
{
    Symbol *entry = st.findSymbol(*name);
    if (!entry)
    {
        semantic_error(this->line, this->column,
            "Function '" + *name + "' is not declared.");
    }
    else
    {
        SymbolType symbolType = entry->getSymbolType();

        if (symbolType != SymbolType::FUNCTION)
        {
            semantic_error(this->line, this->column,
                "Variable '" + *name + "' is not a function.");
        }
        else
        {
            FunctionSymbol *func = static_cast<FunctionSymbol *>(entry);
            const std::vector<ParameterSymbol*> &params = func->getParameters();
            size_t numParams = params.size();

            if (exprs)
            {
                exprs->sem();
                size_t numArgs = exprs->getExprs().size();

                if (numParams != numArgs)
                {
                    semantic_error(this->line, this->column,
                        "Function '" + *name + "' expects " + std::to_string(numParams) +
                        " parameters, but " + std::to_string(numArgs) + " were provided.");
                }
                else
                {
                    for (size_t i = 0; i < numArgs; ++i)
                    {
                        size_t paramIndex = numParams - i - 1; 

                        TypeEnum exprType = exprs->getExprs()[i]
                                                ? exprs->getExprs()[i]->getTypeEnum()
                                                : TypeEnum::ERROR;
                        TypeEnum paramType = params[paramIndex]->getType()
                                                 ? params[paramIndex]->getType()->getType()
                                                 : TypeEnum::ERROR;

                        if (exprType != paramType)
                        {
                            semantic_error(this->line, this->column,
                                "Type mismatch for parameter " + std::to_string(paramIndex + 1) +
                                " in function call to '" + *name + "'. Expected '" +
                                typeToString(paramType) + "', but found '" + typeToString(exprType) + "'.");
                        }
                        else if (params[paramIndex]->getParameterType() == ParameterType::REFERENCE)
                        {
                            if (dynamic_cast<Lval *>(exprs->getExprs()[i]) == nullptr)
                            {
                                semantic_error(this->line, this->column,
                                    "Reference parameter " + std::to_string(paramIndex + 1) +
                                    " in function call to '" + *name + "' must be an lvalue.");
                            }
                        }
                        else if (exprType == TypeEnum::ARRAY)
                        {
                            TypeEnum paramBaseType = params[paramIndex]->getType()->getBaseType()->getType();
                            TypeEnum exprBaseType = exprs->getExprs()[i]->getType()->getBaseType()->getType();

                            if (paramBaseType != exprBaseType)
                            {
                                semantic_error(this->line, this->column,
                                    "Array type mismatch for parameter " + std::to_string(paramIndex + 1) +
                                    " in function call to '" + *name + "'. Expected base type '" +
                                    typeToString(paramBaseType) + "', but found '" + typeToString(exprBaseType) + "'.");
                            }
                        }
                    }
                }
            }
            else if (numParams != 0)
            {
                semantic_error(this->line, this->column,
                    "Function '" + *name + "' expects " + std::to_string(numParams) +
                    " parameters, but none were provided.");
            }

            type = func->getType();

            for (auto &captured : func->getCapturedSymbols())
            {
                if (captured->getSymbolType() == SymbolType::VARIABLE)
                {
                    capturedVars.push_back(new CapturedVar(captured->getName(), captured->getType()));
                }
                else
                {
                    capturedVars.push_back(new CapturedVar(captured->getName(), captured->getType(), true,
                                                           static_cast<ParameterSymbol *>(captured)->getParameterType()));
                }
            }

            if (func->getNestingLevel() > 1)
            {
                isNested = true;
            }
        }
    }
}


// ProcCall Class Semantic Method Implementation

void ProcCall::sem()
{
    funcCall->sem();
}

// If Class Semantic Method Implementation

void If::sem()
{
    cond->sem();
    thenStmt->setExternal(elseStmt && external);
    thenStmt->sem();

    if (elseStmt)
    {
        elseStmt->setExternal(external);
        elseStmt->sem();

        if (thenStmt->isReturnStatement() && elseStmt->isReturnStatement())
        {
            st.setReturnStatementFound();
        }
    }
}

// While Class Semantic Method Implementation

void While::sem()
{
    cond->sem();
    body->setExternal(false);
    body->sem();
}

// Return Class Semantic Method Implementation

void Return::sem()
{
    Type *expectedReturnType = st.getCurrentFunctionReturnType();
    if (!expectedReturnType)
    {
        semantic_error(this->line, this->column,
            "Return statement not allowed outside of a function.");
    }
    else if (expr)
    {
        expr->sem();

        if (expectedReturnType->getType() == TypeEnum::VOID)
        {
            semantic_error(this->line, this->column,
                "Void function '" + st.getCurrentFunctionName() + "' should not return a value.");
        }
        else if (expr->getType() && expr->getType()->getType() != expectedReturnType->getType())
        {
            semantic_error(this->line, this->column,
                "Return type does not match the function's return type.");
        }
    }
    else if (expectedReturnType->getType() != TypeEnum::VOID)
    {
        semantic_warning(this->line, this->column,
            "Non-void function '" + st.getCurrentFunctionName() + "' should return a value.");
    }

    if (external)
    {
        isReturn = true;
    }
}
