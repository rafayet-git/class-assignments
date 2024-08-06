#ifndef SHELL_H
#define SHELL_H

/**
 * splits the current process and executes the provided command
 * in the child process. The parent process will wait until the 
 * child process has finished. Can process one pipe operator and
 * the redirection operators (<, >, >>) as well.
 * 
 * @arg command - the command to execute as a string
 */
void shellexec(char *command);

#endif
