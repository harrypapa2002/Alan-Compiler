#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>
#include <string>

enum class TypeEnum
{
    INT,
    BYTE,
    VOID,
    ARRAY,
    ERROR
};

// Base class for different types
class Type
{
public:
    virtual ~Type() {};

    virtual Type *getBaseType() const { return nullptr; }

    TypeEnum getType() const { return type; }

protected:
    TypeEnum type;
};


// Derived class for Void type
class VoidType : public Type
{
public:
    VoidType();
};

// Derived class for Int type
class IntType : public Type
{
public:
    IntType();
};

// Derived class for Byte type
class ByteType : public Type
{
public:
    ByteType();
};

// Derived class for Array type
class ArrayType : public Type
{
public:
    ArrayType(Type *baseType, int size = -1);
    Type *getBaseType() const override;
    int getSize() const;

private:
    Type *baseType;
    int size;
};

// Function to compare types
inline bool equalTypes(TypeEnum t1, TypeEnum t2)
{
    return t1 == t2;
}
std::string typeToString(TypeEnum type);
extern Type *typeInteger;
extern Type *typeByte;
extern Type *typeVoid;

#endif // TYPES_HPP