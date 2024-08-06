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

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

void createSem(){
	int semd = semget(SEMKEY, 1 , IPC_CREAT | IPC_EXCL | 0644);
  if (semd==-1 ){
    printf("ERROR - %s\n", strerror(errno));
  } else{
    union semun su;
    su.val = 1;
    int r = semctl(semd, 0, SETVAL, su);
  }
  int file = open("writeFile.txt", O_RDWR | O_TRUNC | O_CREAT, 0777);
  if (file ==-1 ){
    printf("ERROR - %s\n", strerror(errno));
    exit(errno);
  }
  close(file);
  int shmd = shmget(SHMKEY, sizeof(char)*256, IPC_CREAT | 0644);
  printf("done\n");

}

void removeSem(){
  int semd = semget(SEMKEY, 1, 0);
  if (semd==-1 ){
    printf("ERROR - %s\n", strerror(errno));
  }else{
    semctl(semd, IPC_RMID, 0);
  }
  int shmd = shmget(SHMKEY, 0, 0);
  shmctl(shmd, IPC_RMID, 0);
  printf("removed semaphore and shared mem\n ---Reading writeFile.txt--- \n");
  FILE *file = fopen("writeFile.txt", "r");
  if (file == NULL){
    printf("ERROR - %s\n", strerror(errno));
  }else{
    for (char c = fgetc(file); c != EOF; c = fgetc(file)){
      printf("%c", c);
    }
    printf("\n");
  }
  fclose(file);
}

void viewSem(){
  printf(" ---Reading writeFile.txt--- \n");
  FILE *file = fopen("writeFile.txt", "r");
  if (file == NULL){
    printf("ERROR - %s\n", strerror(errno));
    exit(errno);
  }else{
    for (char c = fgetc(file); c != EOF; c = fgetc(file)){
      printf("%c", c);

    }
    printf("\n");
  }
  fclose(file);
}

int main(int argc, char *argv[]){
	if (argc != 2){
		printf("No argument specified\n");
		return 0;
	} else if (strcasecmp(argv[1], "-create")==0){
		createSem();
		return 0;
	} else if (strcasecmp(argv[1], "-remove")==0){
		removeSem();
		return 0;
	} else if (strcasecmp(argv[1], "-view")==0){
		viewSem();
		return 0;
	}
	printf("No argument specified\n");
	return 0;
}
