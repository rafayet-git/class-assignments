compile: accounts.o main.o
	gcc -o accounts.out main.o accounts.o

run:
	./accounts.out

main.o: main.c accounts.h
	gcc -c main.c

structs.o: accounts.c accounts.h
	gcc -c accounts.c

clear: 
	rm *.o
	rm *.out
