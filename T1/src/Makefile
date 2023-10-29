Main: Main.o Verification.o Automaton.o Lex.o Parsing.o
	g++ -g Main.o Verification.o Automaton.o Lex.o Parsing.o -o Main

Main.o: Main.cpp
	g++ -c Main.cpp

Verification.o: Verification.cpp
	g++ -c Verification.cpp

Automaton.o: Automaton.cpp
	g++ -c Automaton.cpp

Lex.o: ./Lexical/Lex.cpp
	g++ -c ./Lexical/Lex.cpp

Parsing.o: ./Parsing/Parsing.cpp
	g++ -c ./Parsing/Parsing.cpp
	
clean: 
	rm *.o Main 