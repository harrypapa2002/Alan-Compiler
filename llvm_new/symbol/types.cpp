#include "types.hpp"
#include "../lexer/lexer.hpp"
#include <iostream>

// Implementation of VoidType constructor
VoidType::VoidType()
{
    type = TypeEnum::VOID;
}

// Implementation of getSize for VoidType
int VoidType::getSize() const
{
    yyerror("Void type has no size");
    return -1;
}

// Implementation of printOn for VoidType
void VoidType::printOn(std::ostream &out) const
{
    out << "proc";
}

// Implementation of IntType constructor
IntType::IntType()
{
    type = TypeEnum::INT;
}

// Implementation of getSize for IntType
int IntType::getSize() const
{
    return INT_SIZE;
}

// Implementation of printOn for IntType
void IntType::printOn(std::ostream &out) const
{
    out << "int";
}

// Implementation of ByteType constructor
ByteType::ByteType()
{
    type = TypeEnum::BYTE;
}

// Implementation of getSize for ByteType
int ByteType::getSize() const
{
    return BYTE_SIZE;
}

// Implementation of printOn for ByteType
void ByteType::printOn(std::ostream &out) const
{
    out << "byte";
}

// Implementation of ArrayType constructor
ArrayType::ArrayType(Type *baseType, int size) : baseType(baseType), size(size)
{
    if (baseType->getType() == TypeEnum::VOID)
        yyerror("Array cannot have void type");
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

// Implementation of printOn for ArrayType
void ArrayType::printOn(std::ostream &out) const
{
    out << "array of " << *baseType << "[" << size << "]";
}

// Implementation of ArrayReferenceType constructor
ArrayReferenceType::ArrayReferenceType(Type *baseType) : baseType(baseType)
{
    if (baseType->getType() == TypeEnum::VOID)
        yyerror("Array cannot have void type");
    type = TypeEnum::REFERENCE;
}

// Implementation of getSize for ArrayReferenceType
int ArrayReferenceType::getSize() const
{
    return INT_SIZE;
}

// Implementation of getBaseType for ArrayReferenceType
Type *ArrayReferenceType::getBaseType() const
{
    return baseType;
}

// Implementation of printOn for ArrayReferenceType
void ArrayReferenceType::printOn(std::ostream &out) const
{
    out << "reference to array of " << *baseType;
}

