#ifndef tunez_h
#define tunez_h
struct song_node{
  char name[100];
  char artist[100];
  struct song_node *next;
};
struct song_node* makeNewNode(char *names, char *artists);
struct song_node * insert_front(struct song_node * front, char * name, char * artist);
int compareNodes(struct song_node * node1, struct song_node * node2);
struct song_node * insert_ordered(struct song_node * front, char * name, char * artist);
struct song_node * freelist(struct song_node * front);
int printList(struct song_node *music);
void printNode(struct song_node *music);
struct song_node* findNodeSpecific(struct song_node *music, char *name, char *artist);
struct song_node* findNodeArtistFirst(struct song_node *music, char *artist);
struct song_node * getRandomNode(struct song_node * front);
struct song_node* removeNode(struct song_node *music, char *name, char *artist);
int countNode(struct song_node * music);
#endif
