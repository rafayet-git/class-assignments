#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

static void sighandler(int signo){
	if (signo == SIGINT){
		printf("Program exited due to SIGINT");
	}
	if (signo == SIGUSR1){
		printf("\n ---> The PID is %d \n\n", getpid());
	}
}

int main(){
	int i = 0;
	signal(SIGINT,sighandler);
	signal(SIGUSR1,sighandler);
	while(i>=0){
		printf("%d!! PID:%d PPID:%d\n", i,getpid(), getppid());
		i++;
		sleep(1);
	}
}
