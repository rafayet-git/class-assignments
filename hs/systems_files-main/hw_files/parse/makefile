compile: main.o parse.o
	gcc -o testr main.o parse.o 
run: testr
	./testr

main.o: main.c parse.h
	gcc -c main.c
parse.o: parse.c parse.h
	gcc -c parse.c
