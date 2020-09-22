all: system

system: 151044006_main.o
	g++ -o exe 151044006_main.o -lm

151044006_main.o: 151044006_main.cpp
	g++ -c -std=c++11 151044006_main.cpp

run:
	./exe

clean: 
	-rm *.o exe
