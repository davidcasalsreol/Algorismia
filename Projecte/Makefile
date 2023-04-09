all: programa

programa: graf.o localsearch.o State.o
	g++ -o programa.out graf.o localsearch.o State.o

graf.o: Part1/graf.cpp
	g++ -c Part1/graf.cpp

localsearch.o: Part2/localsearch.cpp
	g++ -c Part2/localsearch.cpp

State.o: Part2/State.cpp Part1/difusioIC.cpp
	g++ -c Part2/State.cpp

clear:
	rm *.o programa.out