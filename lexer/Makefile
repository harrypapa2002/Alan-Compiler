CC=gcc
CFLAGS=-Wall
alanc: lexer.o 
	$(CC) $(CFLAGS) -o $@ $^ -lfl
lexer.c: lexer.l 
	flex -s -o $@ $<
clean:
	$(RM) *.o lexer.c core *~
distclean: clean
	$(RM) alanc