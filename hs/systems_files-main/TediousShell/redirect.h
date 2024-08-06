#ifndef REDIRECT_H
#define REDIRECT_H

/**
 * struct containing data about the environment in which a command
 * will run. 
 * 
 * flag & cmd_has_command HAS TO BE TRUE FOR THE ENV TO BE EXECUTED BY
 * THE SHELL
 * 
 * contains a bitset that marks if in, out, append, or core_command are set
 * core_command - the command that will run without the redirection operators 
 * and arguments
 * in and out - the file in which the command will read from and output to
 */
struct cmd_env
{
    char flag; // 0 0 0 0 - [has_command][append_out?][set_out?][set_in?]
    char in[255];
    char out[255];
    char core_command[255];
};

// bit flags
static const char cmd_in = 1 << 0;
static const char cmd_out = 1 << 1;
static const char cmd_append = 1 << 2;
static const char cmd_has_command = 1 << 3;

/**
 * parses a command string and sets cmd_env with appropriate values.
 * sets the input, output, and the command that will be executed.
 * 
 * @arg cond - the cmd_env to write to with the appropriate data
 * from parsing command
 * @arg command - the full command string including <, >, >> 
 */
void process_cmd_env(struct cmd_env *cond, char *command);

/**
 * executes a command environment settings the appropriate input
 * and output streams. 
 * 
 * @arg cond - the command environment that is set appropriately
 * from parsing a command string
 */
void exec_cmd(struct cmd_env *cond);

/**
 * prints command environment. Used for debugging
 * 
 * @arg cond - the command environment to be printed
 */
void print_cmd_env(struct cmd_env *cond);

/**
 * parses a string containing the pipe and assigns the cmd_envs to
 * perform the piping. Also parses the redirection operators ( <, >, >>)
 * and sets the cmd_envs appropriately.
 * 
 * @arg command - the complete string that MUST contain a pipe operator
 * @arg cond1 - the environment of the first command that will be modified
 * @arg cond2 - the environment of the second command that will be modified
 */
void process_pipe_cmd_env(char *command, struct cmd_env *cond1, struct cmd_env *cond2);

/**
 * executes a string that contains only ONE pipe operator.
 * 
 * @arg command - the command string containing the one pipe operator to execute.
 */
void pipe_exec(char *command);

#endif