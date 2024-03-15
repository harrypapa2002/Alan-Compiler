CXX=g++
CXXFLAGS=-Wall
lexer: lexer.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ -lfl
lexer.cpp: lexer.l 
	flex -s -o $@ $<
clean:
	$(RM) *.o lexer.cpp core *~
distclean: clean
	$(RM) alanc