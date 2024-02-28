CC=gcc
CFLAGS=-Wall
alanc: lexer.o parser.o 
	$(CC) $(CFLAGS) -o $@ $^ -lfl
lexer.c: lexer.l parser.h
	flex -s -o $@ $<
parser.c parser.h: parser.y
	bison -dv -o $@ $<
clean:
	$(RM) *.o parser.c parser.h lexer.c core *~
distclean: clean
	$(RM) alanc