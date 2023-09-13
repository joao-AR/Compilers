all: lex.yy.c
	gcc lex.yy.c -o lex

lex.yy.c: lex.l
	flex lex.l 

clean: 
	rm -f lex.yy.c all ./lex


