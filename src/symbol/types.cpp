#include "types.hpp"
#include "../lexer/lexer.hpp"
#include <iostream>
#include <string>

// Implementation of VoidType constructor
VoidType::VoidType()
{
    type = TypeEnum::VOID;
}

// Implementation of IntType constructor
IntType::IntType()
{
    type = TypeEnum::INT;
}

// Implementation of ByteType constructor
ByteType::ByteType()
{
    type = TypeEnum::BYTE;
}

// Implementation of ArrayType constructor
ArrayType::ArrayType(Type *baseType, int size) : baseType(baseType), size(size)
{
    type = TypeEnum::ARRAY;
}

// Implementation of getSize for ArrayType
int ArrayType::getSize() const
{
    return size;
}

// Implementation of getBaseType for ArrayType
Type *ArrayType::getBaseType() const
{
    return baseType;
}

// Implementation of typeToString
std::string typeToString(TypeEnum type)
{
    switch(type)
    {
        case TypeEnum::INT:
            return "int";
        case TypeEnum::BYTE:
            return "byte";
        case TypeEnum::VOID:
            return "void";
        case TypeEnum::ARRAY:
            return "array";
        case TypeEnum::ERROR:
            return "undefined";
        default:
            return "unknown";
    }
}
