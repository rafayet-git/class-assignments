#include "alias.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

/* parses the string after the "alias" keyword, separating into
 * the alias name and the command as the struct alias. Will be 
 * used by removeAlias and parseAlias.
 *
 * @arg str - the alias entry provided by the shell
 * @return the struct of the name and command.
 */
static struct alias *parseAlias(char *str){
	struct alias *new = malloc(sizeof(struct alias));
	int i = 0;

	while(str[i] != '=' && str[i] != '\0' && str[i] != ' ')
	{
		(new->name)[i] = str[i];
		i++;
	}
	new->name[i] = 0;
	i++;
	int j = 0;
	if (str[i] == '\"' || str[i] == '\'')
	{
		i++;
		while(str[i] != '\"' && str[i] != '\'')
		{
			new->cmd[j] = str[i];
			i++;
			j++;
		}

	}else{
		while(str[i] != '\0' && str[i] != ' ')
		{
			new->cmd[j] = str[i];
			i++;
			j++;
		}
	}
	new->cmd[j] = 0;

	return new;

}

int removeAlias(char *nname){
	struct alias *newAlias = parseAlias(nname);
	if (newAlias->name[0] == 0)
	{
		free(newAlias);
		return 0;
	}
	int aliasFile = open(".aliases", O_RDONLY | O_CREAT, 0777);
	int tempFile = open(".shelltmp", O_WRONLY | O_CREAT, 0777);
	if (aliasFile == -1)
	{
		printf("ERROR - %s\n", strerror(errno));
		return -1;
	}
	struct alias temp;
	struct stat data;
	stat(".aliases", &data);
	int aliasCount = (data.st_size / sizeof(struct alias));
	for(int i = 1; i <=aliasCount; i++)
	{
		read(aliasFile, &temp, sizeof(struct alias));
		if(strcmp(newAlias->name, temp.name))
		{
			write(tempFile,&temp,sizeof(struct alias));
		}
	}
	close(aliasFile);
	close(tempFile);
	remove(".aliases");
	rename(".shelltmp", ".aliases");
	free(newAlias);
	return 0;
}

void printAliasi()
{
	int savefile = open(".aliases", O_RDONLY | O_CREAT, 0777);
	if (savefile == -1)
	{
		printf("ERROR - %s\n", strerror(errno));
	}
	else {
		struct alias temp;
		struct stat data;
		stat(".aliases",&data);
		int aliasCount = (data.st_size / sizeof(struct alias));
		for(int i = 1; i<=aliasCount; i++)
		{
			read(savefile, &temp, sizeof(struct alias));
			printf("%s=\'%s\'\n", temp.name, temp.cmd);
		}
		close(savefile);
	}
}

int addAlias(char *alname)
{
	removeAlias(alname);
	struct alias *newAlias = parseAlias(alname);
	int savefile = open(".aliases", O_WRONLY | O_APPEND);
	if (savefile == -1){
		printf("ERROR - %s\n", strerror(errno));
		return -1;
	}
	write(savefile, newAlias, sizeof(struct alias));
	close(savefile);
	free(newAlias);
	return 0;
}

char *replaceAlias(char *cmd)
{
	char *fullCmd = malloc(256);
	char aliasName[100];
	char aliasCmd[255];
	int savefile = open(".aliases", O_RDONLY);
	if (savefile == -1)
	{
		fullCmd = strcpy(fullCmd, cmd);
		return fullCmd;
	}
	int i = 0;
	while(cmd[i] != '\0' && cmd[i] != ' ')
	{
		aliasName[i] = cmd[i];
		i++;
	}
	aliasName[i] = 0;

	struct alias temp;
	struct stat data;
	stat(".aliases",&data);
	int aliasCount = (data.st_size / sizeof(struct alias));
	for(int i = 1; i<=aliasCount; i++)
	{
		read(savefile, &temp, sizeof(struct alias));
		if (strcmp(temp.name, aliasName) == 0){
			strcpy(aliasCmd, temp.cmd);
			break;
		}
	}
	close(savefile);
	if (aliasCmd[0] == 0)
	{
		fullCmd = strcpy(fullCmd, cmd);
		return fullCmd;
	}
	fullCmd = strcpy(fullCmd, aliasCmd);
	if (cmd[i] == ' ')
	{
		strcat(fullCmd, strchr(cmd, ' '));
	}
	return fullCmd;
	

}



