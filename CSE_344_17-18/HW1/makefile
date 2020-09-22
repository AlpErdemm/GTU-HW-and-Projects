all: system

system: 151044006_main.o
	gcc -o exe 151044006_main.o

151044006_main.o: 151044006_main.c
	gcc -c 151044006_main.c

run:
	./exe TEST.TIF

clean: 
	-rm *.o exe
