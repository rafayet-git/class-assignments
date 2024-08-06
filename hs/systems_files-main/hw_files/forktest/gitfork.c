#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	printf("Forking 2 child process\n");
	int fork1 = fork();
	if(fork1){
		int fork2 = fork();
		if (fork2){
			int wat;
			int wrt = wait(&wat);
			int secSlept  = WEXITSTATUS(wat);
			printf ("%d sleeped for %d seconds\n", wrt, secSlept);	
			return 0;
		}
	}
	int newP = getpid();
	srand(newP);
	int rnd = (rand()%4)+2;
	printf("%d %dsec\n",newP, rnd);
	sleep(rnd);
	printf("%d finished\n", newP);

	return rnd;	

}
