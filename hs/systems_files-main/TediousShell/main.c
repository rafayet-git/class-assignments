#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "shell.h"
#include "shellutil.h"
#include "redirect.h"

#define LINE_BUFFER_SIZE 256

static char currentDir[LINE_BUFFER_SIZE];

/* Signal interrupt for the shell itself
*
* @arg signo - the signal number given by signal()
*/
   static void sigmain(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n\033[1m%s\033[0m %s -> ", username, currentDir);
		fflush(stdout);
	}
}
/* Signal interrupt for the child processes
*If a program is running, it will not print the header.
*
* @arg signo - the signal number given by signal()
*/
static void sigchd(int signo) 
{ 
	if (signo == SIGINT)
	{
		printf("\n");
		fflush(stdout);
	}
}

/* Get the working directory for the shell and 
* saves to static variable currentDir
* Replaces home directory with '~' if found
*/
char *getWorkDir()
{
	getcwd(currentDir, LINE_BUFFER_SIZE);
	if (!strncmp(currentDir, userdir, strlen(userdir)))
    	{
		char temp[LINE_BUFFER_SIZE];
		temp[0] = '~';
		int i = strlen(userdir);
		for (; i < strlen(currentDir); i++)
        	{
			temp[i - strlen(userdir) + 1] = currentDir[i];
		}
		temp[i - strlen(userdir) + 1] = 0;
		strcpy(currentDir, temp);
	}
}

int main()
{
	signal(SIGINT, sigmain);
	initVals();
	getWorkDir();
	printf("\033[1m%s\033[0m %s -> ", username, currentDir);

	char *line = malloc(LINE_BUFFER_SIZE);
	while (fgets(line, LINE_BUFFER_SIZE, stdin)) 
	{
        	signal(SIGINT,sigchd);	
        	if (strstr(line, " ; ") || strstr(line, "; ") || strstr(line, " ;")) 
        	{
        		line[strlen(line) - 1] = '\0';
        		semiColon(line);
        	} else {
            		line[strlen(line) - 1] = '\0';
            		stripcommand(line);
            		shellexec(line);
        	}
	    	signal(SIGINT,sigmain);
	    	printf("\033[1m%s\033[0m %s -> ", username, currentDir);
	}  
}   
