# Alan Compiler

This project is a compiler for the **Alan** programming language, created as part of the Compilers course at the **School of Electrical and Computer Engineering** at **NTUA** (National Technical University of Athens). This repository contains the complete source code and examples of the Alan language, which supports basic types, functions, and simple control structures similar to Pascal.

## Authors
- **Konstantinos Katsikopoulos** (el20103@mail.ntua.gr)
- **Charidimos Papadakis** (el20022@mail.ntua.gr)

## Project Structure

The project has two main directories:

- `src/`: Contains the core compiler implementation, broken down into the following components:
  - **ast/**: Abstract Syntax Tree (AST) generation.
    - `ast.cpp`, `ast.hpp`: Core AST classes and functions.
    - `igen.cpp`: Intermediate code generation (LLVM).
    - `semantic.cpp`: Semantic analysis for the Alan language.
  - **codegen/**: Code generation.
    - `codegen.cpp`, `codegen.hpp`: Code generation data structures and classes for LLVM.
  - **lexer/**: Lexical analysis using Flex.
    - `lexer.l`: The Flex specification for lexical analysis.
    - `lexer.hpp`: Header file for the lexer.
  - **lib/**: Contains the Alan runtime library.
    - `lib.c`: C source file for standard runtime functions (input/output, string handling).
  - **parser/**: Syntax analysis using Bison.
    - `parser.y`: Bison specification for the Alan parser.
  - **symbol/**: Symbol table, type, and scope management.
    - `symbol_table.cpp`, `symbol_table.hpp`, `scope.cpp`, `scope.hpp`, `types.cpp`, `types.hpp`: Implements the symbol table, type system, and scope management for Alan.
  - **Other files**:
    - `alanc`: Script for compiling and running Alan programs (located inside project's root folder).
    - `Makefile`: Located inside the `src/` folder, it defines the build process for the compiler.
  
- `lib/`: Contains the runtime library source code and its corresponding Makefile.
    - `Makefile`: Located inside the `lib/` folder, it defines the build process for creating the `lib.a` static library.

- `examples/`: Contains example programs written in the Alan language.

## Installation

### Requirements
- **LLVM** (version 15 or later)
- **Flex** (version 2.6 or later) and **Bison** (version 2.3 or later) for lexical and syntactic analysis.
- **Clang** for compiling the C++ source code and linking.
- **Make** for building the project.

### Steps
1. Clone the repository:
    ```bash
    git clone git@github.com:kostiscpp/compilers.git
    ```
2. Navigate to the project directory:
    ```bash
    cd compilers
    ```
3. Build the compiler and the library using `make`:
    ```bash
    cd src
    make
    cd ../lib
    make
    ```
   This will compile the compiler (`alanc`) inside `src/` and create the static library (`lib.a`) inside `lib/`.

4. Clean build artifacts (optional):
    ```bash
    cd src
    make clean
    cd ../lib
    make clean
    ```

### Adding the Compiler to Your PATH

To make the `alanc` compiler available system-wide, add the project's directory to your `PATH` environment variable. You can do this by modifying your shell configuration file (e.g., `~/.zshrc` or `~/.bashrc`).

1. Open your shell configuration file in a text editor:
    ```bash
    vim ~/.zshrc
    ```

2. Add the following line at the end of the file:
    ```bash
    export PATH="/path/to/compilers:$PATH"
    ```

3. Save the file and reload the shell configuration:
    ```bash
    source ~/.zshrc
    ```

4. Verify that the `alanc` compiler is accessible:
    ```bash
    which alanc
    ```
   This should output the path to the `alanc` binary.

## Usage

Once built, the compiler can be run using the `alanc` script located in the project's main folder. The compiler accepts Alan source files and produces both intermediate code (LLVM IR) and final assembly code.

### Basic Usage
```bash
./alanc <source_file.alan>
```
This will generate the intermediate LLVM code in `<source_file.imm>` and the final assembly in `<source_file.asm>`, both located in the same folder as the Alan source file (`<source_file.alan>`). The resulting assembly can be compiled into an executable using Clang and the static runtime library (`lib.a`).

### Options
- `-O`: Enable code optimization.
- `-f`: Read Alan source code from standard input and output the final assembly code to standard output. **Note:** When using this option, the final executable is not produced.
- `-i`: Read Alan source code from standard input and output the intermediate LLVM IR to standard output. **Note:** When using this option, the final executable is not produced.
- `-o <executable>`: Specify the name of the output executable file. **Note:** The `-o` option cannot be used simultaneously with `-i` or `-f`. If no `-o` option is provided, the executable will be named `a.out` and will be created in the current working directory.

### Example
You can find example programs in the `examples/` directory. To compile the `hello.alan` example and specify the output executable name:
```bash
./alanc -o hello examples/hello.alan
```
This will produce an executable named `hello`.

## Limitations and Known Issues

## Assumptions
- **Type Sizes**: 
   - The `int` type is 4 bytes (32 bits).
   - The `byte` type is 1 byte (8 bits).
  
- **Main Function**: 
   - The outer function can have any name but must be specified as `proc`. However, it is handled in code generation as a function returning an `int`, indicating whether the program executed successfully. 
   - In the LLVM IR, the main function returns `0` (32-bit integer) upon successful execution or a different value upon error.

- **Nested Functions**:
   - Nested functions can use parameters and variables declared in their outer functions. Any changes made to these variables within the nested functions are reflected back to the outer functions where they were declared.
   - It is possible to have nested procedures with the same name as an outer one. However, **static scoping** rules apply to procedure calls, meaning the closest (most recently declared) scope will be used for resolving names.

- **Non-Proc Functions**: 
   - Non-`proc` functions must always return a value consistent with the declared return type. Failing to return a value matching the return type will result in an error, not just a warning.

## Library Documentation

The Alan runtime library provides the following functions for input/output, string manipulation, and type conversion.

### I/O Functions

```alan
writeInteger (n : int) : proc
```
- Prints an integer.

```alan
writeByte (b : byte) : proc
```
- Prints a byte as an integer (arithmetic value).

```alan
writeChar (b : byte) : proc
```
- Prints a character corresponding to the ASCII code of the byte.

```alan
writeString (s : reference byte []) : proc
```
- Prints a string of bytes.

```alan
readInteger () : int
```
- Reads and returns an integer from input.

```alan
readByte () : byte
```
- Reads and returns a byte (interpreted as an integer).

```alan
readChar () : byte
```
- Reads and returns a single character (as a byte).

```alan
readString (n : int, s : reference byte []) : proc
```
- Reads up to `n` characters into the byte array `s`.

### Type Conversion Functions

```alan
extend (b : byte) : int
```
- Converts a byte to an integer (extension).

```alan
shrink (i : int) : byte
```
- Converts an integer to a byte (shrinking).

### String Functions

```alan
strlen (s : reference byte []) : int
```
- Returns the length of the string `s`.

```alan
strcmp (s1 : reference byte [], s2 : reference byte []) : int
```
- Compares two strings lexicographically:
  - Returns `0` if they are equal.
  - Returns `-1` if `s1` is lexicographically smaller than `s2`.
  - Returns `1` if `s1` is lexicographically larger than `s2`.

```alan
strcpy (trg : reference byte [], src : reference byte []) : proc
```
- Copies the string from `src` to `trg`.

```alan
strcat (trg : reference byte [], src : reference byte []) : proc
```
- Concatenates the string `src` to `trg`.
