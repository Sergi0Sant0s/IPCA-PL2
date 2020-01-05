all: clean main.o lex.yy.o grammar.tab.o funcoes.o exec.o
	gcc -o interpetador main.o lex.yy.o grammar.tab.o funcoes.o exec.o -lm

lex.yy.c: lexer.l
	flex lexer.l

grammar.tab.c grammar.tab.h: grammar.y
	bison -d grammar.y

grammar.tab.o: grammar.tab.c funcoes.h

lex.yy.o: lex.yy.c grammar.tab.h funcoes.h

main.o: main.c grammar.tab.h funcoes.h

exec.o: exec.c funcoes.h grammar.tab.h 

funcoes.o: funcoes.c funcoes.h grammar.tab.h 

clean:
	@rm -rf interpetador
	@rm -rf *.o
	@rm -rf grammar.tab.h
	@rm -rf grammar.tab.c
	@rm -rf lex.yy.c