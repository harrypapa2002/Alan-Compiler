#ifndef TYPES_HPP
#define TYPES_HPP
#include "ast.hpp"
#include "lexer.hpp"

#define INT_SIZE 4
#define BYTE_SIZE 1

enum class TypeEnum
{
    INT,
    BYTE,
    VOID,
    ARRAY,
    REFERENCE
};

class Type : public AST
{
public:
    virtual ~Type() {};

    virtual int getSize() const = 0;

    virtual Type *getBaseType() const { return nullptr; }

    virtual void printOn(std::ostream &out) const = 0;

    TypeEnum getType() const { return type; }

protected:
    TypeEnum type;
};

class VoidType : public Type
{
public:
    VoidType() { type = TypeEnum::VOID; }

    int getSize() const override
    {
        yyerror("Void type has no size");
        return -1;
    }

    void printOn(std::ostream &out) const override { out << "proc"; }
};

class IntType : public Type
{
public:
    IntType() { type = TypeEnum::INT; }

    int getSize() const override { return INT_SIZE; }

    void printOn(std::ostream &out) const override { out << "int"; }
};

class ByteType : public Type
{
public:
    ByteType() { type = TypeEnum::BYTE; }

    int getSize() const override { return BYTE_SIZE; }

    void printOn(std::ostream &out) const override { out << "byte"; }
};

class ArrayType : public Type
{
public:
    ArrayType(Type *baseType, int size) : baseType(baseType), size(size)
    {
        if (baseType->getType() == TypeEnum::VOID)
            yyerror("Array cannot have void type");
        type = TypeEnum::ARRAY;
    }

    int getSize() const override { return size; }

    Type *getBaseType() const override { return baseType; }

    void printOn(std::ostream &out) const override
    {
       out << "array of " << *baseType << "[" << size << "]";
    }

private:
    Type *baseType;
    int size;
};

class ArrayReferenceType : public Type
{
public:
    ArrayReferenceType(Type *baseType) : baseType(baseType)
    {
        if (baseType->getType() == TypeEnum::VOID)
            yyerror("Array cannot have void type");
        type = TypeEnum::REFERENCE;
    }

    int getSize() const override { return INT_SIZE; }

    Type *getBaseType() const override { return baseType; }

    void printOn(std::ostream &out) const override
    {
        out << "reference to array of " << *baseType;
    }

private:
    Type *baseType;
};


#endif // TYPES_HPP