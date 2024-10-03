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
    - `lib.a`: Compiled static library used during linking.
  - **parser/**: Syntax analysis using Bison.
    - `parser.y`: Bison specification for the Alan parser.
  - **symbol/**: Symbol table, type, and scope management.
    - `symbol_table.cpp`, `symbol_table.hpp`, `scope.cpp`, `scope.hpp`, `types.cpp`, `types.hpp`: Implements the symbol table, type system, and scope management for Alan.
  - **Other files**:
    - `alanc`: Script for compiling and running Alan programs.
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

## Usage

Once built, the compiler can be run using the `alanc` script located in the project's main folder. The compiler accepts Alan source files and produces both intermediate code (LLVM IR) and final assembly code.

### Basic Usage
```bash
./alanc <source_file.alan>
```
This will generate the intermediate LLVM code in `<source_file.imm>` and the final assembly in `<source_file.asm>` both located in the same folder as the Alan source file (`<source_file.alan>`). The resulting assembly can be compiled into an executable using Clang and the static runtime library (`lib.a`). 

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

## Bugs

## Running the Compiler Script (`alanc`)

The `alanc` script simplifies the usage of the compiler by handling intermediate and final code generation. It takes care of:
- Invoking `alanc` for generating LLVM IR.
- Compiling the LLVM IR to assembly using `llc`.
- Linking the generated assembly with the static library (`lib.a`) using Clang.

You can specify the output executable name using the `-o` option. For example:
```bash
./alanc -o my_program examples/hello.alan
```

This will generate an executable named `my_program`.
