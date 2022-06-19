a.out: game.o main.o
	g++ -Wall -pedantic game.o main.o

game.o: game.cpp game.h
	g++ -Wall -pedantic game.h
	g++ -Wall -pedantic -c game.cpp

main.o: main.cpp
	g++ -Wall -pedantic -c main.cpp

clear:
	rm *.o