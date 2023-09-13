all: lex.yy.c
	gcc lex.yy.c -o cstats

lex.yy.c: cstats.l
	flex cstats.l 

clean: 
	rm -f lex.yy.c all ./cstats


