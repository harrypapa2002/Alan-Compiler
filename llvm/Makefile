.PHONY: clean distclean default

LLVM-CONFIG=llvm-config-15

CXX=clang++
CXXFLAGS=-Wall -g `$(LLVM-CONFIG) --cxxflags`
LDFLAGS=`$(LLVM-CONFIG) --ldflags --system-libs --libs all`

default: alanc

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

lexer.o: lexer.cpp lexer.hpp parser.hpp ast.hpp symbol.hpp types.hpp

parser.hpp parser.cpp: parser.y
	bison -dv -o parser.cpp parser.y

parser.o: parser.cpp lexer.hpp ast.hpp symbol.hpp types.hpp

alanc: lexer.o parser.o ast.o
	$(CXX) $(CXXFLAGS) -o alanc $^ $(LDFLAGS)

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o

distclean: clean
	$(RM) alanc