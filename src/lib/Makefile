# Makefile for compiling a static library from lib.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -c -O2

# Target library name
TARGET = lib.a

# Source file
SRC = lib.c

# Object file
OBJ = $(SRC:.c=.o)

# Rule to build the static library
all: $(TARGET)

# Rule to compile the object file from the source
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

# Rule to create the static library from the object file
$(TARGET): $(OBJ)
	ar rcs $@ $^

# Clean up the object files and the library
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

