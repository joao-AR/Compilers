Main: Main.o Verification.o Automaton.o
	g++ -g Main.o Verification.o Automaton.o -o Main

Main.o: Main.cpp
	g++ -c Main.cpp

verification.o: Verification.cpp
	g++ -c Verification.cpp

Automaton.o: Automaton.cpp
	g++ -c Automaton.cpp

clean: 
	rm *.o Main 