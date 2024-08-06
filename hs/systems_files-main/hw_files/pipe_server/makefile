all: clientcompile servercompile

client: client.out
	./client.out
server: server.out
	./server.out
	
clientcompile: basic_client.o pipe_networking.o
	gcc -o client.out basic_client.o pipe_networking.o

servercompile: basic_server.o pipe_networking.o
	gcc -o server.out basic_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm -f *.o
	rm -f *.out

