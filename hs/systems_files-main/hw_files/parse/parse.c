#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char ** parse_args (char * line){
	char **args = malloc(11 * sizeof(char *));
	char i = 0;
	char *cpy = strdup(line);
	char *tk = strsep(&cpy, " ");
	while (tk != NULL){
		args[i] = strdup(tk);
		i++;
		tk = strsep(&cpy, " ");
	}
	return args;
}

