Main: Main.o verification.o
	g++ Main.o verification.o -o Main

Main.o: Main.cpp
	g++ -c Main.cpp

verification.o: verification.cpp
	g++ -c verification.cpp

clean: 
	rm *.o Main 