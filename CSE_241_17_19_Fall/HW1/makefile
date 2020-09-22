all: connectfour

connectfour: main.o connectfour.o
	g++ main.o connectfour.o -o exe

main.o: main.cpp
	g++ -c main.cpp

connectfour.o: connectfour.cpp
	g++ -c connectfour.cpp 

clean:
	rm*.o exe

