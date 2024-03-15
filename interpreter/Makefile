CXX=g++
CXXFLAGS=-Wall
alanc: lexer.o parser.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ -lfl
lexer.cpp: lexer.l parser.hpp
	flex -s -o $@ $<
parser.cpp parser.hpp: parser.y
	bison -dv -o $@ $<
clean:
	$(RM) *.o parser.cpp parser.hpp lexer.cpp core *~
distclean: clean
	$(RM) alanc