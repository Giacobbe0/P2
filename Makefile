FLAGS= -Wall -pedantic -std=c++14 -iquote inc

___start__: program
	./program
program:Graf.o Funkcje.o main.cpp
	g++ -o program Graf.o Funkcje.o main.cpp

Graf.o:Graf.cpp
	g++ -c ${FLAGS}  Graf.cpp
	
Funkcje.o:Funkcje.cpp
	g++ -c ${FLAGS}  Funkcje.cpp

clean:
	rm -f Graf.o Funkcje.o program
