#ifndef ALIAS_H
#define ALIAS_H

struct alias
{
	char name[100];
	char cmd[255];
};

/* Removes an alias from the .aliases save file, if it exists
 * 
 * @arg nname - the alias entry provided by the shell
 * @return nonzero if an error occurs, zero if successful
 */
int removeAlias(char *nname);

/* Prints all aliases saved in .aliases
 */
void printAliasi();

/* Adds an alias by appending to the .alias save file,
 * if the alias already exists it gets replaced by 
 * first removing it through removeAlias();
 *
 * @arg alname - the alias entry provided by the shell
 * @return nonzero if error occurs, zero if successful
 */
int addAlias(char *alname);

/* Looks for the first work in the entered command if 
 * it is an alias, which would then be replaced with
 * the cooresponding directory.
 *
 * @arg cmd - full command entered by user
 *@return the command string with proper aliases replaced
 */
 char *replaceAlias(char *cmd);
#endif

