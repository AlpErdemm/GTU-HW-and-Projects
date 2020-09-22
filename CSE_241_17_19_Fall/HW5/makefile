all: main

main: main.o
	g++ -std=c++11 main.o cell.o cfabstract.o connectfourplus.o connectfourdiag.o connectfourplusundo.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp cell.cpp cfabstract.cpp connectfourplus.cpp connectfourdiag.cpp connectfourplusundo.cpp

clean:
	rm *.o exe
