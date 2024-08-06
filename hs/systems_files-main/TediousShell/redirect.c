#include "redirect.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

#include "shell.h"
#include "shellutil.h"

void process_cmd_env(struct cmd_env *cond, char *command)
{
    cond->flag = 0;
    cond->core_command[0] = '\0';

    int tok_len = 1;
    size_t command_len = strlen(command);
    for (int i = 0; command[i]; ++i, tok_len += command[i] == ' ') {} // counts number of tokens
    char **tok_arr = malloc(tok_len * sizeof(char *));
    for (int i = 0; i < tok_len; ++i)
    {
        tok_arr[i] = strsep(&command, " "); // sep to tokens
    }

    for (int i = 0; i < tok_len; ++i)
    {
        if (strcmp(tok_arr[i], "<") == 0 && i + 1 < tok_len)
        {
            cond->flag |= cmd_in;
            strcpy(cond->in, tok_arr[i + 1]);
            ++i;
        }
        else if (strcmp(tok_arr[i], ">") == 0 && i + 1 < tok_len)
        {
            cond->flag |= cmd_out;
            cond->flag &= ~cmd_append; // turn append off
            strcpy(cond->out, tok_arr[i + 1]);
            ++i;
        }
        else if (strcmp(tok_arr[i], ">>") == 0 && i + 1 < tok_len)
        {
            cond->flag |= cmd_out | cmd_append;
            strcpy(cond->out, tok_arr[i + 1]);
            ++i;
        }
        else
        {
            cond->flag |= cmd_has_command;
            strcat(cond->core_command, tok_arr[i]);
            strcat(cond->core_command, " "); // add space back
        }
    }

    for (int i = 0; i < command_len; ++i) // restore to original
    {
        if (tok_arr[0][i] == '\0') // note tok_arr[0] should be the the beginning of the original string
        {
            tok_arr[0][i] = ' '; // replace back to space
        }
    }

    free(tok_arr);
}

void print_cmd_env(struct cmd_env *cond)
{
    printf("core_command: %s\n", cond->flag & cmd_has_command ? cond->core_command : "NULL");
    printf("in: %s\n", cond->flag & cmd_in ? cond->in : "STDIN");
    printf("out: %s\n", cond->flag & cmd_out ? cond->out : "STDOUT");
    printf("append: %s\n", cond->flag & cmd_append ? "True" : "False");
}

void exec_cmd(struct cmd_env *cond)
{
    if (cond->flag & cmd_has_command)
    {
        int backup_stdin = dup(STDIN_FILENO);
        int backup_stdout = dup(STDOUT_FILENO);

        if (cond->flag & cmd_in)
        {
            int infd = open(cond->in, O_RDONLY);
            if (infd == -1) {
                printf("Input file does not exist\n");
                close(backup_stdin);
                close(backup_stdout);
                return; 
            }
            dup2(infd, STDIN_FILENO);
        }
        if (cond->flag & cmd_out)
        {
            int outfd;
            if (cond->flag & cmd_append) outfd = open(cond->out, O_CREAT | O_WRONLY | O_APPEND, 0644);
            else outfd = open(cond->out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (outfd == -1)
            {
                printf("ERROR - %s\n", strerror(errno));
                close(backup_stdin);
                close(backup_stdout);
                return;
            }
            dup2(outfd, STDOUT_FILENO);
        }

        char **args = parse_args(stripcommand(cond->core_command));
        execvp(args[0], args);

        if (errno == ENOENT)
        {
            printf("No such command.\n");
            exit(EXIT_SUCCESS);
	    }
        else
        {
            printf("ERROR - %s\n", strerror(errno));
	        exit(EXIT_FAILURE);
        }

        // cleanup
        dup2(backup_stdin, STDIN_FILENO);
        dup2(backup_stdout, STDOUT_FILENO);
    }
    else
    {
        printf("NO COMMAND SPECIFIED\n");
    }
}

void process_pipe_cmd_env(char *command, struct cmd_env *cond1, struct cmd_env *cond2)
{
    char *pipe_ptr = strchr(command, '|');
    *pipe_ptr = '\0';
    char *second_cmd = pipe_ptr + (pipe_ptr[1] == ' ' ? 2 : 1);
    char *first_cmd = command;

    process_cmd_env(cond1, first_cmd);
    process_cmd_env(cond2, second_cmd);

    if (!(cond1->flag & cmd_out) && !(cond2->flag & cmd_in)) // if out and in is not set
    {
        cond1->flag |= cmd_out;
        cond2->flag |= cmd_in;

        strcpy(cond1->out, "PIPE_FILE");
        strcpy(cond2->in, "PIPE_FILE");
    }
    else if (!(cond2->flag & cmd_in))
    {
        cond2->flag |= cmd_in;
        strcpy(cond2->in, "/dev/null");
    }

    *pipe_ptr = '|';
}

void pipe_exec(char *command)
{
    stripcommand(command);
    pid_t parent_pid = getpid();

    struct cmd_env first, second;
    process_pipe_cmd_env(command, &first, &second);

    pid_t exec_one_pid = fork();
    if (exec_one_pid == -1) printf("ERROR - %s\n", strerror(errno));
    else if (exec_one_pid)
    {
        int status;
        pid_t wait_res = waitpid(exec_one_pid, &status, 0);
        if (wait_res == -1)
        {
            printf("ERROR - %s\n", strerror(errno));
            return;
        }

        pid_t exec_two_pid = fork();
        if (exec_two_pid == -1) printf("ERROR - %s\n", strerror(errno));
        else if (exec_two_pid)
        {
            wait_res = waitpid(exec_two_pid, &status, 0);
            if (wait_res == -1)
            {
                printf("ERROR - %s\n", strerror(errno));
                return;
            }
            // cleanup
            if (strcmp(second.in, "PIPE_FILE") == 0)
            {
                remove("PIPE_FILE");
            }
        }
        else
        {
            exec_cmd(&second);
            if (errno == ENOENT)
            {
                printf("Command not found.\n");
                exit(0);
            }
            else
            {
                printf("ERROR - %s\n", strerror(errno));
                exit(3);
            }    
        }
    }
    else
    {
        exec_cmd(&first);
        if (errno == ENOENT)
        {
            printf("Command not found.\n");
            exit(0);
	    }
        else
        {
            printf("ERROR - %s\n", strerror(errno));
            exit(3);
        }        
    }
}