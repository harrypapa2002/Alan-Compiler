#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>

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

// Base class for different types
class Type
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

// Inline function to print Type objects
inline std::ostream &operator<<(std::ostream &out, const Type &type)
{
    type.printOn(out);
    return out;
}

// Derived class for Void type
class VoidType : public Type
{
public:
    VoidType();

    int getSize() const override;

    void printOn(std::ostream &out) const override;
};

// Derived class for Int type
class IntType : public Type
{
public:
    IntType();

    int getSize() const override;

    void printOn(std::ostream &out) const override;
};

// Derived class for Byte type
class ByteType : public Type
{
public:
    ByteType();

    int getSize() const override;

    void printOn(std::ostream &out) const override;
};

// Derived class for Array type
class ArrayType : public Type
{
public:
    ArrayType(Type *baseType, int size = -1);

    int getSize() const override;

    Type *getBaseType() const override;

    void printOn(std::ostream &out) const override;

private:
    Type *baseType;
    int size;
};

// Derived class for Array Reference type
class ArrayReferenceType : public Type
{
public:
    ArrayReferenceType(Type *baseType);

    int getSize() const override;

    Type *getBaseType() const override;

    void printOn(std::ostream &out) const override;

private:
    Type *baseType;
};

// Function to compare types
inline bool equalTypes(TypeEnum t1, TypeEnum t2)
{
    return t1 == t2;
}

extern Type *typeInteger;
extern Type *typeByte;
extern Type *typeVoid;

#endif // TYPES_HPP