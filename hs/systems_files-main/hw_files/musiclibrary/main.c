#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tunez.h"
#include "songlist.h"

int main(){

  srand(time(NULL));
/* i was testing how different things work as booleans
  if (0 && 1==1){
    printf("0 and true\n");
  }
  if (1 && 1==1){
    printf("1 and true\n");
  }
  if (56 && 1==1){
    printf("56 and true\n");
  }
  if (1 && 1==7){
    printf("1 nd false\n");
  }
  if (1 && 7) {
    printf("1 and 7\n");
  }
  if (0){
    printf("0\n");
  }
  if (NULL){
    printf("null\n");
  }
*/
  struct song_node * a = NULL;

printf("LINKED LIST TESTS\n");
printf("====================================\n\n");

printf("Testing insert_ordered:\n");
a = insert_ordered(a, "bites the dust", "queen");
a = insert_ordered(a, "sheer heart attack", "queen");
a = insert_ordered(a, "american idiot", "greenday");
a = insert_ordered(a, "holiday", "greenday");
a = insert_ordered(a, "release the kraken", "nsp");
a = insert_ordered(a, "peppermint", "jack stauber");
a = insert_ordered(a, "smooth", "jack stauber");

printf("Testing print_list\n");
printList(a);
printf("====================================\n\n");

//printf("Testing print_node\n", );
printf("Testing findNodeSpecific: \n");
printf("looking for [%s : %s]\n","greenday","holiday");
struct song_node * b = findNodeSpecific(a,"holiday","greenday");
if (b){
  printf("node found: { %s | %s }\n",b->artist,b->name);
} else{
  printf("node not found\n");
}
printf("looking for [%s : %s]\n","queen","bites the dust");
b = findNodeSpecific(a,"bites the dust","queen");
if (b){
  printf("node found: { %s | %s }\n",b->artist,b->name);
} else{
  printf("node not found\n");
}
printf("looking for [%s : %s]\n","beatles","come together");
b = findNodeSpecific(a,"come together","beatles");
if (b){
  printf("node found: { %s | %s }\n",b->artist,b->name);
} else{
  printf("node not found\n");
}
printf("====================================\n\n");

printf("Testing findNodeArtistFirst:\n");
char * author = "nsp";
printf("looking for: %s\n", author);
b = findNodeArtistFirst(a,author);
if (b){
  printf("artist found: ");
  printList(b); //printing it this way since thst's how it is on the website
} else {
  printf("artist not found\n");
}
author = "greenday";
printf("looking for: %s\n", author);
b = findNodeArtistFirst(a,author);
if (b){
  printf("artist found: ");
  printList(b);
} else {
  printf("artist not found\n");
}
author = "your mom";
printf("looking for: %s\n", author);
b = findNodeArtistFirst(a,author);
if (b){
  printf("artist found: ");
  printList(b);
} else {
  printf("artist not found\n");
}
printf("====================================\n\n");

printf("Testing compareNodes:\n");
char *artist1,*artist2,*song1,*song2;
artist1="greenday";
artist2="greenday";
song1 = "holiday";
song2 = "holiday";
printf("comparing [%s,%s] to [%s,%s]\n", artist1,song1,artist2,song2);
printf("%d\n",compareNodes(findNodeSpecific(a,song1,artist1),findNodeSpecific(a,song2,artist2)) );
artist1="greenday";
artist2="greenday";
song1 = "holiday";
song2 = "american idiot";
printf("comparing [%s,%s] to [%s,%s]\n", artist1,song1,artist2,song2);
printf("%d\n",compareNodes(findNodeSpecific(a,song1,artist1),findNodeSpecific(a,song2,artist2)) );
artist1="queen";
artist2="greenday";
song1 = "bites the dust";
song2 = "holiday";
printf("comparing [%s,%s] to [%s,%s]\n", artist1,song1,artist2,song2);
printf("%d\n",compareNodes(findNodeSpecific(a,song1,artist1),findNodeSpecific(a,song2,artist2)) );
artist1="greenday";
artist2="queen";
song1 = "holiday";
song2 = "bites the dust";
printf("comparing [%s,%s] to [%s,%s]\n", artist1,song1,artist2,song2);
printf("%d\n",compareNodes(findNodeSpecific(a,song1,artist1),findNodeSpecific(a,song2,artist2)) );
printf("====================================\n\n");

printf("Testing randomNode:\n");
for (int i =0; i<5; i++){
  b = getRandomNode(a);
  printf("{%s,%s}\n",b->artist,b->name);
}
printf("====================================\n\n");

printf("Testing removeNode:\n");
printf("removing [greenday: american idiot]\n");
if (findNodeSpecific(a,"american idiot","greenday")){ //is the removeNode supposed to do part of this on it's own?
  a = removeNode(a,"american idiot","greenday");
  printf("node found! ");
  printList(a);
} else {
  printf("node not found\n");
}
printf("removing [queen: killer queen]\n");
if (findNodeSpecific(a,"killer queen","queen")){ //is the removeNode supposed to do part of this on it's own?
  a = removeNode(a,"killer queen","queen");
  printf("node found! ");
  printList(a);
} else {
  printf("node not found\n");
}
printf("removing [nsp: release the kraken]\n");
if (findNodeSpecific(a,"release the kraken","nsp")){ //is the removeNode supposed to do part of this on it's own?
  a = removeNode(a,"release the kraken","nsp");
  printf("node found! ");
  printList(a);
} else {
  printf("node not found\n");
}
printf("removing [batta: chase]\n");
if (findNodeSpecific(a,"chase","batta")){ //is the removeNode supposed to do part of this on it's own?
  a = removeNode(a,"chase","batta");
  printf("node found! ");
  printList(a);
} else {
  printf("node not found\n");
}

printf("====================================\n\n");
printf("Testing freelist:\n");
a = freelist(a);
printf("list after freelist:\n");
printList(a);

printf("\n\nMUSIC LIBRARY TESTS\n====================================\n\n");

printf("initializing music library\n");
struct songlist * walkman = newList();

printf("Testing printLetter:\n");
printLetter(walkman,'a');
printLetter(walkman,'z'+1);
printf("====================================\n\n");

printf("Testing printFullList:\n");
printFullList(walkman);
printf("====================================\n\n");

printf("filling the library\n");
walkman = addSong(walkman,"bites the dust", "queen");
walkman = addSong(walkman,"sheer heart attack", "queen");
walkman = addSong(walkman,"american idiot", "greenday");
walkman = addSong(walkman,"holiday", "greenday");
walkman = addSong(walkman,"release the kraken", "nsp");
walkman = addSong(walkman,"peppermint", "jack stauber");
walkman = addSong(walkman,"smooth", "jack stauber");
walkman = addSong(walkman,"i love you","1direction"); //not a real song, just to test with

printf("Testing printFullList:\n");
printFullList(walkman);
printf("====================================\n\n");

printf("Testing findSong (find song by name and author):\n");
printf("looking for [%s : %s]\n","greenday","holiday");
b = findSong(walkman,"holiday","greenday");
if (b){
  printf("node found: { %s | %s }\n",b->artist,b->name);
} else{
  printf("node not found\n");
}
printf("looking for [%s : %s]\n","queen","bites the dust");
b = findSong(walkman,"bites the dust","queen");
if (b){
  printf("node found: { %s | %s }\n",b->artist,b->name);
} else{
  printf("node not found\n");
}
printf("looking for [%s : %s]\n","beatles","come together");
b = findSong(walkman,"come together","beatles");
if (b){
  printf("node found: { %s | %s }\n",b->artist,b->name);
} else{
  printf("node not found\n");
}
printf("====================================\n\n");

printf("Testing findArtist: \n");
author = "nsp";
printf("looking for %s\n", author);
b = findArtist(walkman,author);
if (b){
  printf("artist found: ");
  printList(b); //printing it this way since thst's how it is on the website
} else {
  printf("artist not found\n");
}
author = "greenday";
printf("looking for %s\n", author);
b = findArtist(walkman,author);
if (b){
  printf("artist found: ");
  printList(b);
} else {
  printf("artist not found\n");
}
author = "your mom";
printf("looking for %s\n", author);
b = findArtist(walkman,author);
if (b){
  printf("artist found: ");
  printList(b);
} else {
  printf("artist not found\n");
}
printf("====================================\n\n");

printf("Testing printArtist (prints a list of songs of the specified artist):\n");
author = "nsp";
printf("%s: ",author);
printArtist(walkman,author);
author = "greenday";
printf("%s: ",author);
printArtist(walkman,author);
author = "your mom";
printf("%s: ",author);
printArtist(walkman,author);
printf("====================================\n\n");

printf("Testing printLetter with elements in the list:\n");
printf("letters where i have elements:\n");
printLetter(walkman,'q');
printLetter(walkman,'1');
printf("letters where i don't:\n");
printLetter(walkman,'w');
printf("====================================\n\n");

printf("Testing deleteSong:\n");
printf("removing: [%s, %s] \n","greenday","american idiot");
walkman = deleteSong(walkman,"american idiot","greenday");
printFullList(walkman);
printf("removing: [%s, %s] \n","queen","bites the dust");
walkman = deleteSong(walkman,"bites the dust","queen");
printFullList(walkman);
printf("removing: [%s, %s] \n","nsp","release the kraken");
walkman = deleteSong(walkman,"release the kraken","nsp");
printFullList(walkman);
printf("removing: [%s, %s] \n","jack stauber","peppermint");
walkman = deleteSong(walkman,"peppermint","jack stauber");
printFullList(walkman);
printf("====================================\n\n");

printf("Testing clear (library-clearing method):\n");
walkman = clear(walkman);
printf("====================================\n\n");

printf("Testing printFullList:\n");
printFullList(walkman);
printf("====================================\n\n");

printf("Adding a few elements back to the empty songlist:\n");
walkman = addSong(walkman,"chase","batta");
walkman = addSong(walkman,"boulevard of broken dreams","greenday");
walkman = addSong(walkman,"it's bedtime","nsp");
walkman = addSong(walkman,"bites the dust", "queen");
walkman = addSong(walkman,"sheer heart attack", "queen");
walkman = addSong(walkman,"american idiot", "greenday");
walkman = addSong(walkman,"holiday", "greenday");
walkman = addSong(walkman,"release the kraken", "nsp");
walkman = addSong(walkman,"peppermint", "jack stauber");
walkman = addSong(walkman,"smooth", "jack stauber");

printf("Testing printFullList:\n");
printFullList(walkman);
printf("====================================\n\n");

printf("Testing printLetter:\n");
printf("g:\n");
printLetter(walkman,'g');
printf("other:\n");
printLetter(walkman,'1');
printf("====================================\n\n");

printf("Testing shuffle:\n");
shuffle(walkman);

printf("List after Shuffle:\n");
printFullList(walkman);

  return 0;
}
