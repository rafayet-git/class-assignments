#ifndef SHELL_UTIL_H
#define SHELL_UTIL_H

extern char *userdir;
extern char *username;

/**
 * Initialize global values username and userdir with the
 * current user's username and home directory.
 */
void initVals();

/**
 * parse a string into an array of strings with each pointer
 * pointing at each argument
 * 
 * should be deallocated except in the case or an exec family
 * function. the os will free the memory automatically.
 * 
 * @arg line - the line containing the command to parse
 * @return dyanmically allocated array pointing to strings
 */
char** parse_args(char *line);

/**
 * remove extra spaces from the provided cmd.
 * extra spaces are defined as leading and trailing spaces
 * and any additional spaces between words.
 * 
 * 
 * @arg cmd - the string containing the command
 * @returns the string without the extra spaces
 */
char *stripcommand(char *cmd);

/**
 * break line into individual commands and exec each command
 * 
 * @arg cmd - the string containing the command
 */
void *semiColon(char * cmd);

#endif
