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
        yyerror(("Parameter '" + *name + "' already declared in the same scope").c_str());
    }
    parameterSymbol = new ParameterSymbol(*name, type, parameterType);
    st.addSymbol(*name, parameterSymbol);

    isArray = (type->getType() == TypeEnum::ARRAY);

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
    if (st.findSymbol(*name))
    {
        yyerror(("Function name '" + *name + "' already declared").c_str());
    }

    funcSymbol = new FunctionSymbol(*name, type);
    st.addSymbol(*name, funcSymbol);

    st.enterFunctionScope(funcSymbol);

    if (fpar)
    {
        fpar->sem();
        for (auto &param : fpar->getParameters())
        {
            funcSymbol->addParameter(*param->getParameterSymbol());
        }
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
        yyerror(("Non-void function '" + *name + "' does not have a return statement").c_str());
    }

    if (funcSymbol->getReturnStatementFound())
    {
        setReturn();
    }

    st.exitFunctionScope();
}

// VarDef Class Semantic Method Implementation

void VarDef::sem()
{
    if (st.findSymbolInCurrentScope(*name))
    {
        yyerror(("Variable name '" + *name + "' already declared").c_str());
    }

    if (isArray)
    {
        if (size <= 0)
        {
            yyerror("Array size must be greater than 0");
        }

        type = new ArrayType(type, size);
    }

    st.addSymbol(*name, new VariableSymbol(*name, type));
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
        yyerror("Unary operator can only be applied to integers");
    }
    type = typeInteger;
}

// BinOp Class Semantic Method Implementation

void BinOp::sem()
{
    left->sem();
    right->sem();

    if (!equalTypes(left->getTypeEnum(), right->getTypeEnum()))
    {
        yyerror("Type mismatch in binary operation");
    }

    if (!equalTypes(left->getTypeEnum(), TypeEnum::INT) && !equalTypes(left->getTypeEnum(), TypeEnum::BYTE))
    {
        yyerror("Binary operator can only be applied to integers or bytes");
    }

    type = left->getType();
}

// CondCompOp Class Semantic Method Implementation

void CondCompOp::sem()
{
    left->sem();
    right->sem();
    TypeEnum t = left->getTypeEnum();
    if (!equalTypes(t, right->getTypeEnum()))
    {
        yyerror("Type mismatch in comparison");
    }
    if (t != TypeEnum::INT && t != TypeEnum::BYTE)
    {
        yyerror("Comparison operator can only be applied to integers or bytes");
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
        yyerror("Variable not declared");
    }

    symbolType = entry->getSymbolType();

    if (symbolType == SymbolType::FUNCTION)
    {
        yyerror("Function cannot be used as a variable");
    }

    type = entry->getType();
}

// ArrayAccess Class Semantic Method Implementation

void ArrayAccess::sem()
{
    indexExpr->sem();
    if (indexExpr->getTypeEnum() != TypeEnum::INT)
    {
        yyerror("Array index must be an integer");
    }

    Symbol *entry = st.findSymbol(*name);
    if (!entry)
    {
        yyerror("Variable not declared");
    }
    if (entry->getSymbolType() == SymbolType::FUNCTION)
    {
        yyerror("Function cannot be used as a variable");
    }
    Type *t = entry->getType();

    if (t->getType() != TypeEnum::ARRAY)
    {
        yyerror("Variable is not an array");
    }

    type = t->getBaseType();
}

// Let Class Semantic Method Implementation

void Let::sem()
{
    lexpr->sem();
    rexpr->sem();

    Symbol *entry = st.findSymbol(*lexpr->getName());
    if (!entry)
    {
        yyerror("Variable not declared");
    }
    SymbolType symbolType = entry->getSymbolType();
    if (symbolType == SymbolType::FUNCTION)
    {
        yyerror("Function cannot be used as a variable");
    }

    if (!equalTypes(lexpr->getTypeEnum(), rexpr->getTypeEnum()))
    {
        yyerror("Type mismatch in assignment");
    }
    isReturn = false;
}

// FuncCall Class Semantic Method Implementation

void FuncCall::sem()
{
    Symbol *entry = st.findSymbol(*name);
    if (!entry)
    {
        yyerror("Function not declared");
    }

    SymbolType symbolType = entry->getSymbolType();
    if (symbolType != SymbolType::FUNCTION)
    {
        yyerror("Variable cannot be used as a function");
    }

    FunctionSymbol *func = static_cast<FunctionSymbol *>(entry);
    if (exprs)
    {
        exprs->sem();
        const std::vector<ParameterSymbol> &params = func->getParameters();
        
        if (exprs->getExprs().size() != params.size())
        {
            yyerror("Number of parameters does not match the function signature");
        }

        for (size_t i = 0; i < exprs->getExprs().size(); ++i)
        {
            TypeEnum exprType = exprs->getExprs()[i]->getTypeEnum();
            TypeEnum paramType = params[i].getType()->getType();

            if (exprType != paramType)
            {
                //std::cout << exprType  << paramType << std::endl;
                yyerror("Type mismatch in function call parameters");
            }

            if (params[i].getParameterType() == ParameterType::REFERENCE) {
                if (dynamic_cast<Lval*>(exprs->getExprs()[i]) == nullptr) {
                    yyerror("Only lvalues can be passed as reference parameters");
                }
            }

            if (exprType == TypeEnum::ARRAY)
            {
                if (params[i].getType()->getBaseType()->getType() != exprs->getExprs()[i]->getType()->getBaseType()->getType())
                {
                    yyerror("Array type mismatch in function call");
                }
            }
        }
    }

    type = func->getType();
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
        yyerror("Return statement not within any function scope.");
        return;
    }

    if (expr)
    {
        expr->sem();

        if (expr->getType()->getType() != expectedReturnType->getType())
        {
            yyerror("Return type does not match the function's return type.");
        }
    }
    else
    {
        if (expectedReturnType->getType() != TypeEnum::VOID)
        {
            yyerror("Missing return value in function expected to return a non-void type.");
        }
    }

    if (external)
        isReturn = true;
}
