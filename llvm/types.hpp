#ifndef TYPES_HPP
#define TYPES_HPP
//#include "lexer.hpp"

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

inline std::ostream &operator<<(std::ostream &out, const Type &type)
{
    type.printOn(out);
    return out;
}


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
    ArrayType(Type *baseType, int size = -1 ) : baseType(baseType), size(size)
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


inline bool equalTypes(TypeEnum t1, TypeEnum t2) {
    return t1 == t2;
}

extern Type *typeInteger;
extern Type *typeByte;
extern Type *typeVoid;

#endif // TYPES_HPP