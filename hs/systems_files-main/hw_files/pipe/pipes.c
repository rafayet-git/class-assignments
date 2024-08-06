#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define READ 0
#define WRITE 1

char *invertCase(char *str){
  for(int i = 0; i < strlen(str); i++){
    if (islower(str[i])){
      str[i]-=32;
    }else if (isupper(str[i])){
      str[i]+=32;
    }
  }
  return str;
}

char *lowerCase(char *str){
  for(int i = 0; i < strlen(str); i++){
    if (isupper(str[i])){
      str[i]+=32;
    }
  }
  return str;
}
char *upperCase(char *str){
  for(int i = 0; i < strlen(str); i++){
    if (islower(str[i])){
      str[i]-=32;
    }
  }
  return str;
}

char *revertString(char *str){
	char tmp;
	int len = strlen(str);
	for(int i = 0; i < len/2; i++){
		tmp = str[i];
	  str[i] = str[len-2-i];
		str[len-2-i] = tmp;
  }
	return str;
}

int main(){
  srand(time(NULL));
	mkfifo("steel", 0777);
	int pipes[4][2];
	int forkamt = (int)((rand() % 3)+2);
  pid_t currentPID = getpid();
  pid_t childPID;
  char buff[256];
  char currStr[256];
	int chiPipe;
	int i = 0;
	for(; i < forkamt; i++){
    		if(getpid()==currentPID){
      			pipe(pipes[i]);
      			if (fork()){ //parent
        			close(pipes[i][READ]);
      			}else{ // child
				      chiPipe = i;
              childPID = getpid();
        			close(pipes[i][WRITE]);
      			}
    		}
	}
	int parpipe;
	if(getpid() == currentPID){
    printf("Numchildren %d\n", forkamt);
		while(1){
			printf("Enter string:\n");
			fgets(currStr,255,stdin);
      for(int j = 0; j < strlen(currStr); j++){
        if (currStr[j]=='\n') currStr[j]='\0';
      }
			for(i=0;i<forkamt;i++){
				write(pipes[i][WRITE], currStr, 255);
      }
      for(i=0;i<forkamt;i++){
        parpipe = open("steel",O_RDONLY);
				printf("Test\n");
        read(parpipe, buff, 255);
        read(parpipe, &childPID, sizeof(pid_t));
				close(parpipe);
				printf("Result from process %d is \'%s\'\n", childPID, buff);
      }

			
		}
	}else{
    double sleepTime;
		while(1){
      read(pipes[chiPipe][READ], buff,255);
      for(i=0; i <= chiPipe; i++) sleepTime = (rand()%3000001)+1000000;
      printf("Child %d waiting.. %f seconds\n", childPID, sleepTime/1000000);
      usleep(sleepTime);
			switch(chiPipe){
				case 0:
					invertCase(buff);
					break;
				case 1:
					lowerCase(buff);
					break;
				case 2:
					upperCase(buff);
					break;
				case 3:
					revertString(buff);
					break;
			}
			parpipe = open("steel", O_WRONLY);
			write(parpipe, buff, 255);
      write(parpipe, &childPID, sizeof(pid_t));
			close(parpipe);
		}
	}

	return 0;
}
