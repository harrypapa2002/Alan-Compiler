# Compiler
CC = clang

# Compiler flags
CFLAGS = -c -O2 -fno-builtin

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

# Clean up the object files only
clean:
	rm -f $(OBJ)

# Clean up the object files and the static library
distclean: clean
	rm -f $(TARGET)

.PHONY: all clean distclean
