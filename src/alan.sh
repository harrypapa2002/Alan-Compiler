#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Function to display usage information
usage() {
    echo "Usage: $0 <source-file>"
    exit 1
}

# Check if a source file is provided
if [ $# -lt 1 ]; then
    usage
fi

SRC_FILE="$1"

# Compile the Alan source file into LLVM IR
echo "Compiling $SRC_FILE..."
./alanc < "$SRC_FILE" > a.ll
compiler_status=$?

# Check if the compiler succeeded
if [ $compiler_status -ne 0 ]; then
    echo "Compilation failed."
    exit $compiler_status
fi

# Compile LLVM IR to assembly
echo "Generating assembly from LLVM IR..."
llc -o a.s a.ll
llc_status=$?

# Check if llc succeeded
if [ $llc_status -ne 0 ]; then
    echo "LLVM compilation failed."
    exit $llc_status
fi

# Link the assembly with the static library to produce the executable
echo "Linking to create executable..."
clang -o a.out a.s lib/lib.a 
clang_status=$?

# Check if clang succeeded
if [ $clang_status -ne 0 ]; then
    echo "Linking failed."
    exit $clang_status
fi

echo "Compilation and linking succeeded. Executable 'a.out' generated."
