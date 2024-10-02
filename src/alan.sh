#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Function to display usage information
usage() {
    echo "Usage: $0 [-O] [-i | -f] [-o <executable>] [<source-file>]"
    echo "-O: enable optimization"
    echo "-i: output intermediate (LLVM IR) code to stdout"
    echo "-f: output final assembly code to stdout"
    echo "-o <executable>: specify output executable name"
    exit 1
}

# Default values for flags and options
OPTIMIZATION=false
EXECUTABLE="a.out"
OUTPUT_IR=false
OUTPUT_ASM=false
USE_STDIN=false
TEMP_FILE_CREATED=false  # Track if we created a temp file

# Parse the command-line options
while getopts ":Oifo:" opt; do
    case ${opt} in
        O )
            OPTIMIZATION=true
            ;;
        i )
            if [ "$OUTPUT_ASM" = true ]; then
                echo "Error: -i and -f cannot be used together."
                usage
                exit 1
            fi
            OUTPUT_IR=true
            USE_STDIN=true  
            ;;
        f )
            if [ "$OUTPUT_IR" = true ]; then
                echo "Error: -i and -f cannot be used together."
                usage
                exit 1
            fi
            OUTPUT_ASM=true
            USE_STDIN=true 
            ;;
        o )
            if [ "$OUTPUT_IR" = true ] || [ "$OUTPUT_ASM" = true ]; then
                echo "Error: -o cannot be used with -i or -f options."
                usage
                exit 1
            fi
            EXECUTABLE=$OPTARG
            ;;
        \? )
            usage
            ;;
    esac
done

# Move to the next argument after options
shift $((OPTIND -1))

# Ensure the presence of exactly one source file or read from stdin
if [ $# -gt 1 ]; then
    echo "Error: Too many arguments provided."
    usage
    exit 1
elif [ $# -eq 1 ]; then
    # Check if the file exists before proceeding
    if [ ! -f "$1" ]; then
        echo "Error: Source file '$1' not found."
        usage
        exit 1
    fi
    SRC_FILE="$1"
else
    if ! $USE_STDIN; then
        echo "Error: No input provided. A source file or stdin input is required."
        usage
        exit 1
    fi
fi

# If using stdin, read into a temporary file
if $USE_STDIN; then
    SRC_FILE=$(mktemp /tmp/alan_src.XXXXXX)
    TEMP_FILE_CREATED=true  
    cat > "$SRC_FILE"
fi

# Determine the output file paths based on the source file location
BASENAME=$(basename "$SRC_FILE" .alan)
DIRNAME=$(dirname "$SRC_FILE")
IMM_FILE="$DIRNAME/$BASENAME.imm"
ASM_FILE="$DIRNAME/$BASENAME.asm"

# Compile the Alan source file into LLVM IR, pass the optimize flag
if $OPTIMIZATION; then
    ./alanc -O < "$SRC_FILE" > "$IMM_FILE"
else
    ./alanc < "$SRC_FILE" > "$IMM_FILE"
fi
compiler_status=$?

# Check if the compiler succeeded
if [ $compiler_status -ne 0 ]; then
    echo "Compilation failed."
    [ $TEMP_FILE_CREATED = true ] && rm -f "$SRC_FILE"  # Remove the temp file if created
    exit $compiler_status
fi

# If intermediate (LLVM IR) output is requested, print and exit
if $OUTPUT_IR; then
    cat "$IMM_FILE"
    rm -f "$IMM_FILE"
    [ $TEMP_FILE_CREATED = true ] && rm -f "$SRC_FILE"  
    exit 0
fi

# Compile LLVM IR to assembly
llc -o "$ASM_FILE" "$IMM_FILE"
llc_status=$?

# Check if llc succeeded
if [ $llc_status -ne 0 ]; then
    echo "LLVM compilation failed."
    [ $TEMP_FILE_CREATED = true ] && rm -f "$SRC_FILE"  
    exit $llc_status
fi

# If final assembly output is requested, print and exit
if $OUTPUT_ASM; then
    cat "$ASM_FILE"
    rm -f "$IMM_FILE" "$ASM_FILE"
    [ $TEMP_FILE_CREATED = true ] && rm -f "$SRC_FILE"  
    exit 0
fi

# Link the assembly with the static library to produce the executable
clang -o "$EXECUTABLE" "$ASM_FILE" lib/lib.a 
clang_status=$?

# Check if clang succeeded
if [ $clang_status -ne 0 ]; then
    echo "Linking failed."
    [ $TEMP_FILE_CREATED = true ] && rm -f "$SRC_FILE"  # Remove the temp file if created
    exit $clang_status
fi

# Cleanup after successful execution
[ $TEMP_FILE_CREATED = true ] && rm -f "$SRC_FILE"  # Remove the temp file if created

exit 0
