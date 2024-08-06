#ifndef songlist_h
#define songlist_h
struct songlist{
	struct song_node * lib[27];
	int count[27];
};
struct songlist *newList();
struct songlist *addSong(struct songlist *aa, char *nam, char *art);
void printLetter(struct songlist *lib, char let);
void printFullList(struct songlist *library);
struct song_node * findSong(struct songlist *library, char* name, char* artist);
struct song_node * findArtist(struct songlist *library, char * artist);
int printArtist(struct songlist * library, char * artist);
struct songlist * deleteSong(struct songlist * library, char * name, char * artist);
struct songlist * clear(struct songlist * library);
struct songlist * newList();
struct songlist * shuffle(struct songlist * library);
#endif
