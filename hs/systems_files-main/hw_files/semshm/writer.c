#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#define SEMKEY 25565999
#define SHMKEY 25566999

int main(){
  printf("Waiting for semaphore...\n");
  int semd = semget(SEMKEY, 1,0);
  if (semd == -1){
    printf("ERROR - %s\n", strerror(errno));
    exit(errno);
  }
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(semd, &sb, 1);
  char *lastLine;
  int shmd = shmget(SHMKEY, 0, 0);
  lastLine = shmat(shmd, 0, 0);
  FILE *file = fopen("writeFile.txt", "a");
  if (file == NULL){
    printf("ERROR - %s\n", strerror(errno));
    exit(errno);
  }
  printf("Last line on file: %sEnter line to append: ", lastLine);
  fgets(lastLine, 255, stdin);
  fputs(lastLine, file);
  fclose(file);
  printf("Appended new line to file writeFile.txt\n");
  shmdt(lastLine);
  sb.sem_op = 1;
  semop(semd, &sb, 1);
  return 0;
}
