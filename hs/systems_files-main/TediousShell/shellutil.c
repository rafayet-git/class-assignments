#include "shellutil.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

#include "shell.h"
#include "alias.h"

#define MAX_ARGS 10

char *userdir;
char *username;

void initVals()
{
	struct passwd *p;
	p = getpwuid(getuid());
	userdir = p->pw_dir;
	username = p->pw_name;
}

char** parse_args(char *line)
{
    char *newCmd = replaceAlias(line);
    int i = 0;
    char **args = (char**) malloc(sizeof(void* ) * MAX_ARGS + 1);

    char *ptr;
    while (i < MAX_ARGS && (ptr = strsep(&newCmd, " ")))
    {
        args[i++] = ptr;
    }

    args[i] = NULL;
    free(newCmd);
    return args;
}

char *stripcommand(char *cmd)
{
    int j = 0;
    for (int i = 0; cmd[i]; ++i)
    {
        if (cmd[i] != ' ' || (i > 0 && cmd[i - 1] != ' '))
        {
            cmd[j++] = cmd[i];
        }
    }
    cmd[j] = '\0';
    if (cmd[strlen(cmd) - 1] == ' ')
    {
        cmd[strlen(cmd) - 1] = '\0';
    }
    return cmd;
}

void *semiColon(char * cmd) {
    char *token = strsep(&cmd, ";");
    while (token != NULL) {
        int i = 0;
        if (token[i] == ' ') {
            token = token + 1;
        }
        token[strlen(token)] = '\0';
        stripcommand(token);
        shellexec(token);
        token = strsep(&cmd, ";");
    }
}
