.PHONY: clean distclean default

LLVM-CONFIG = llvm-config

CXX = clang++
CXXFLAGS = `$(LLVM-CONFIG) --cxxflags`
LDFLAGS = `$(LLVM-CONFIG) --ldflags`
LDLIBS = `$(LLVM-CONFIG) --libs --system-libs core`

# Directories
LEXER_DIR = lexer
PARSER_DIR = parser
AST_DIR = ast
SYMBOL_DIR = symbol
CODEGEN_DIR = codegen

# Source files
LEXER_SRCS = $(LEXER_DIR)/lexer.cpp
PARSER_SRCS = $(PARSER_DIR)/parser.cpp
AST_SRCS = $(AST_DIR)/ast.cpp $(AST_DIR)/semantic.cpp $(AST_DIR)/igen.cpp
SYMBOL_SRCS = $(SYMBOL_DIR)/scope.cpp $(SYMBOL_DIR)/symbol.cpp $(SYMBOL_DIR)/symbol_table.cpp $(SYMBOL_DIR)/types.cpp
CODEGEN_SRS = $(CODEGEN_DIR)/codegen.cpp

# Object files
LEXER_OBJS = $(LEXER_SRCS:$(LEXER_DIR)/%.cpp=$(LEXER_DIR)/%.o)
PARSER_OBJS = $(PARSER_SRCS:$(PARSER_DIR)/%.cpp=$(PARSER_DIR)/%.o)
AST_OBJS = $(AST_SRCS:$(AST_DIR)/%.cpp=$(AST_DIR)/%.o)
SYMBOL_OBJS = $(SYMBOL_SRCS:$(SYMBOL_DIR)/%.cpp=$(SYMBOL_DIR)/%.o)
CODEGEN_OBJS = $(CODEGEN_SRS:$(CODEGEN_DIR)/%.cpp=$(CODEGEN_DIR)/%.o)

# All object files
OBJS = $(LEXER_OBJS) $(PARSER_OBJS) $(AST_OBJS) $(SYMBOL_OBJS) $(CODEGEN_OBJS)

# Default target
default: alanc

# Generate lexer.cpp from lexer.l using Flex
$(LEXER_DIR)/lexer.cpp: $(LEXER_DIR)/lexer.l
	flex -s -o $@ $<

# Compile lexer.cpp into lexer.o
$(LEXER_DIR)/lexer.o: $(LEXER_DIR)/lexer.cpp $(LEXER_DIR)/lexer.hpp $(PARSER_DIR)/parser.hpp $(AST_DIR)/ast.hpp $(SYMBOL_DIR)/symbol.hpp $(SYMBOL_DIR)/types.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generate parser.hpp and parser.cpp from parser.y using Bison
$(PARSER_DIR)/parser.hpp $(PARSER_DIR)/parser.cpp: $(PARSER_DIR)/parser.y
	bison -dv -o $(PARSER_DIR)/parser.cpp $(PARSER_DIR)/parser.y

# Compile parser.cpp into parser.o
$(PARSER_DIR)/parser.o: $(PARSER_DIR)/parser.cpp $(LEXER_DIR)/lexer.hpp $(AST_DIR)/ast.hpp $(SYMBOL_DIR)/symbol.hpp $(SYMBOL_DIR)/types.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile AST and Semantic source files into object files
$(AST_DIR)/%.o: $(AST_DIR)/%.cpp $(AST_DIR)/ast.hpp $(SYMBOL_DIR)/symbol.hpp $(SYMBOL_DIR)/types.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile Symbol source files into object files
$(SYMBOL_DIR)/%.o: $(SYMBOL_DIR)/%.cpp $(SYMBOL_DIR)/symbol.hpp $(SYMBOL_DIR)/symbol_table.hpp $(SYMBOL_DIR)/scope.hpp $(SYMBOL_DIR)/types.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile Codegen source files into object files
$(CODEGEN_DIR)/%.o: $(CODEGEN_DIR)/%.cpp $(CODEGEN_DIR)/codegen.hpp $(AST_DIR)/ast.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all object files to create the final executable
alanc: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Clean up intermediate files
clean:
	$(RM) $(LEXER_DIR)/*.cpp $(LEXER_DIR)/*.o $(PARSER_DIR)/*.cpp $(PARSER_DIR)/*.hpp $(PARSER_DIR)/*.output $(PARSER_DIR)/*.o $(AST_DIR)/*.o $(SYMBOL_DIR)/*.o $(CODEGEN_DIR)/*.o
# Clean up everything including the executable
distclean: clean
	$(RM) alanc
