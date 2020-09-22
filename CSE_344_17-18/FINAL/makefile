all: server client

server: server.o
	gcc -o exe1 server.o -pthread -lm

server.o: server.c
	gcc -c server.c -pthread

client: client.o
	gcc -o exe2 client.o -pthread

client.o: client.c
	gcc -c client.c

clean: 
	-rm *.o exe

