#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include "tunez.h"
#include "songlist.h"

struct songlist *newList(){ //just to make initializing a bit easier
	struct songlist *new = calloc(1,sizeof(struct songlist));
	for (int i=0; i<27; i++){
	  (new->lib)[i]=NULL;
	}
	return new;
}
struct songlist *addSong(struct songlist *library, char* name, char* artist){
	char letter = toupper(artist[0]);
	if (isalpha(letter)==0){
		(library->count)[26]++;
		(library->lib)[26] = insert_ordered((library->lib)[26], name, artist);
		return library;
	}
	letter = letter-65;
	(library->count)[letter]++;
	(library->lib)[letter] = insert_ordered((library->lib)[letter], name, artist);
	return library;
}

struct song_node * findSong(struct songlist *library, char* name, char* artist){
	char letter = toupper(artist[0]);
	if (!isalpha(letter)){
		return findNodeSpecific((library->lib)[26], name, artist);
	}
	letter = letter-65;
	return findNodeSpecific((library->lib)[letter], name, artist);
}

struct song_node * findArtist(struct songlist *library, char * artist){
	char letter = toupper(artist[0]);
	if (!isalpha(letter)){
		return findNodeArtistFirst((library->lib)[26], artist);
	}
	letter = letter-65;
	return findNodeArtistFirst((library->lib)[letter], artist);
}

void printLetter(struct songlist *library, char letter ){
	letter = toupper(letter);
	if (isalpha(letter)==0){
		printList((library->lib)[26]);
	} else {
		printList((library->lib)[letter-65]);
	}
}

int printArtist(struct songlist * library, char * artist){
	struct song_node * p = findArtist(library,artist);
	printf("[");
	while (p && !strcasecmp(p->artist,artist)){ //while p isn't null and still has the same artist
		printf(" {%s, %s} ", p->artist, p->name);
		if (p->next && !strcasecmp(p->next->artist,artist)){
			printf("|");
		}
		p=p->next;
	}
	printf("]\n");
	return 0;
}

void printFullList(struct songlist *library){
	for (int i = 0; i < 27; i++){
		if ((library->count)[i]){
			if (i!=26){
				printf("%c: ", i+'a');
			} else {
				printf("other: ");
			}
			printList((library->lib)[i]);
		}
	}
}

struct songlist * deleteSong(struct songlist * library, char * name, char * artist){
	//i'm not sure if i want it to return the removed song or the list itelf
	//so i'll do the latter, even though there's no chance of the pointer to the songlist changing
	char letter = toupper(artist[0]);
	struct song_node * p;
	if (!isalpha(letter)){
		(library->lib)[26] = removeNode((library->lib)[26], name, artist);
		(library->count)[26]--; //make sure the count of how many songs are under each letter stays constant
		return library;
	}
	letter = toupper(letter)-65; //for some reason, replacing the 65 with 'a' causes a seg fault
	(library->lib)[letter] = removeNode((library->lib)[letter], name, artist);
	(library->count)[letter]--;
	return library;
}

struct songlist * clear(struct songlist * library){
	for (int i=0; i<27; i++){
    (library->lib)[i]=freelist((library->lib)[i]);
		(library->lib)[i]=NULL;
		(library->count)[i]=0;
  }
	return library;
}

struct songlist * shuffle(struct songlist * library){
	int spice = rand()%3; //so the amount in a shuffle isn't always the same
	int totalcount;
	struct song_node ** shuffleholder = calloc(5+spice,sizeof(struct song_node*));
	for (int i=0; i<5+spice; i++){
		totalcount=0;
		for (int j=0; j<27; j++){
			totalcount+=(library->count)[j]; //with this, we find the total number of elements still in the library/songlist
		}
		int randomnum = rand()%totalcount;
		for (int j=0;j<27;j++){
			//printf("%d randomnum: %d totalcount: %d items: %d\n",j,randomnum,totalcount,(library->count)[j]);
			if (randomnum < (library->count)[j]){
				struct song_node * g = getRandomNode((library->lib)[j]);
				shuffleholder[i]=makeNewNode(g->name,g->artist);
				printf("{%s, %s}\n", g->artist, g->name);
				deleteSong(library,g->name,g->artist); //deleting to avoid repeat selections
				j=28;
			}
			randomnum-=(library->count)[j];
		}
	}
	for (int j=0; j<(5+spice); j++){
		addSong(library,shuffleholder[j]->name,shuffleholder[j]->artist);
		free(shuffleholder[j]);
	}
	free(shuffleholder);
	return library;
}
