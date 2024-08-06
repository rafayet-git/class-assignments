compile: main.o tunez.o songlist.o
	gcc -o ipod main.o tunez.o songlist.o

run: ipod
	./ipod

main.o: main.c songlist.h tunez.h

tunez.o: tunez.c tunez.h
	gcc -c tunez.c

songlist.o: songlist.c songlist.h tunez.h
	gcc -c songlist.c

clear:
	rm *.o ipod
