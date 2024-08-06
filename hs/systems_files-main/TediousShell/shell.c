#include "shell.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>

#include "shellutil.h"
#include "redirect.h"
#include "alias.h"

char *getWorkDir();

void shellexec(char *command)
{
    pid_t parent_pid = getpid();

    if (strchr(command, '|'))
    {
        pipe_exec(command);
    }
    else
    {
        stripcommand(command);

        if (strncmp(command, "cd", 2) == 0)
        {
            char path[255];
            int has_path = sscanf(command, "cd %s", path);
            if (!has_path) path[0] = '\0';

            char *argument = path;
            char *newArg = malloc(strlen(path) + strlen(userdir) + 1);
            if (path[0] == '~')
            {
                strcpy(newArg, userdir);
                int i = 1;
                for (; i < strlen(path); i++)
                {
                    newArg[i + strlen(userdir) - 1] = path[i];
                }
                newArg[i + strlen(userdir) - 1] = '\0';
                argument = newArg;
            }

            if (chdir(argument))
            {
                printf("Invalid directory: %s\n", path);
                free(newArg);
                return;
            }

            getWorkDir();
            free(newArg);
            return;
        }
        else if (strncmp(command, "exit", 4) == 0)
        {
            printf("Bye!\n");
            exit(0);
        }
	else if (strncmp(command, "alias", 5) == 0)
	{
		if (command[5] == '\0')
		{
			printAliasi();
			return;
		}
		if (command[5] == ' '){
			addAlias(command+6);
			return;
   		}
	}
	else if (strncmp(command, "unalias", 7) == 0)
	{
		if (command[7] == ' '){
			removeAlias(command+8);
			return;
		}
	}

        pid_t child_pid = fork();
        if (child_pid == -1)
        {
            printf("ERROR - %s\n", strerror(errno));
        }
        else if (child_pid)
        {
            int status;
            pid_t wait_res = waitpid(child_pid, &status, 0);
            if (wait_res == -1)
            {
                printf("ERROR - %s\n", strerror(errno));
            }
        }
        else
        {
            struct cmd_env cond;
            process_cmd_env(&cond, command);
            exec_cmd(&cond);

            if (errno == ENOENT)
            {
                printf("Command not found.\n");
                exit(errno);
            }
            else
            {
                printf("ERROR - %s\n", strerror(errno));
                exit(errno);
            }
        }
    }
}
