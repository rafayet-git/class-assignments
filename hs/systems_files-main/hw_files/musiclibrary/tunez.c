#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tunez.h"

struct song_node* makeNewNode(char *names, char *artists){
	struct song_node *new = malloc(sizeof(struct song_node));
	//Returns error when char*names is bigger than 100
	strcpy(new->name, names);
	strcpy(new->artist, artists);
	new->next = NULL;
	return new;
}

struct song_node * insert_front(struct song_node * front, char * name, char * artist){
  struct song_node * inserted = makeNewNode(name, artist);
  inserted->next = front;
  return inserted;
}

int compareNodes(struct song_node * node1, struct song_node * node2){ //short and sweet
  int k = strcasecmp(node1->artist,node2->artist);
  if (k){
    return k;
  }
  k = strcasecmp(node1->name,node2->name);
  return k;
}

struct song_node * insert_ordered(struct song_node * front, char * names, char * artists){
  struct song_node * inserted = makeNewNode(names, artists);
  struct song_node * frontholder = front;
  if (!front){
    return inserted;
  }
  if (compareNodes(front,inserted)>=0){
    //when the element needs to be inserted in the front
    inserted->next=front;
    return inserted;
  }
  while(front->next && compareNodes(front->next,inserted)<0){
    //move the pointer to the correct location
    front=front->next;
  }
  inserted->next=front->next;
  front->next=inserted;
  return frontholder;
}

void printNode (struct song_node *music){
	printf(" | ");
	for (struct song_node *i=music; i != NULL; i=i->next){
		printf("{%s, %s} | ", i->artist, i->name);
	}
}

int printList(struct song_node * music){
	printf("[ ");
	for (struct song_node *i=music; i != NULL; i=i->next){
		printf("{%s, %s}", i->artist, i->name);
    if (i->next){
      printf(" | ");
    }
	}
	printf(" ]\n");
  return 0;
}

struct song_node* findNodeSpecific(struct song_node *music, char *names, char *artists){
	struct song_node *i = music;
	for(; i != NULL; i=i->next){
		if (strcasecmp(i->artist, artists)==0 && strcasecmp(i->name, names)==0) return i;
	}
	return i;
}

struct song_node* findNodeArtistFirst(struct song_node *music, char *artists){
	struct song_node *i = music;
	for (; i != NULL && strcasecmp(i->artist, artists)!=0; i=i->next);
	return i;
}

struct song_node* removeNode(struct song_node *music, char *names, char *artists){
	struct song_node *back = music;
	// check to see if the first song is the target
	if (strcasecmp(back->artist, artists)==0 && strcasecmp(back->name, names)==0){
		music = music->next;
		free(back);
		return music;
	}
  //all other cases
	for( struct song_node *i = music->next; i != NULL; i=i->next){
		if (strcasecmp(i->artist, artists)==0 && strcasecmp(i->name, names)==0){
			back->next = i->next;
			free(i);
			return music;
		}
		back = i;
	}
	return music;
}

struct song_node * getRandomNode(struct song_node * music){
  struct song_node * front = music;
  int len = 0;
  while (front){ //segment is basically the same as countNode and redundant,
    //but the code in that function gives me a headache to look at, so i'd rather not
    front = front->next;
    len++;
  }
  front = music;
  int j =rand()%len; //not len+1, that'll make it seg fault
  if (j == 0) return front;
  for (int i = 0; i<j ;i++){
    front = front->next;
  }
  return front;
}

int countNode(struct song_node * music){
	int test = 0;
	for (struct song_node *i = music; i !=NULL; i=i->next) test++;
	return test;
}

struct song_node * freelist(struct song_node * front){
  struct song_node * frontholder = front;
  while (front != NULL){
    frontholder=front->next;
    free(front);
    front=frontholder;
  }
  return frontholder;
}
