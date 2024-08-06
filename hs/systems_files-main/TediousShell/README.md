# Tedious Shell

## Features

- Can execute commands and execute programs similarly to Bash
    - Supports bash commands such as `ls`
    - Supports `cd`. `cd ~` is also supported
    - Supports `exit` which should be used to exit the shell
    - Supports aliases with the 'alias' and 'unalias' command
- `SIGINT` are forwarded from the shell to any child processes that are running
    - `ctrl-c` can be used to interrupt any processes that are running
- `SIGINT` does not interrupt the shell similarly to Bash
    - `ctrl-c` in the shell itself reprints the prompt similarly to how Bash functions
    - The `exit` command should be used to exit the shell
- Supports a sequential list of commands using `;` as a separator
    - e.g. `ls -l ; cd ..` 
    - Spaces around the `;` are not necessary
    - Additional spaces around `;` works as well
- The shell provides a prompt displaying the username and the current working directory
- The redirection operators ( `<` , `>`, `>>` ) work
    - `cat < main.c`
    - A command can have more than one type of redirection operators and can have multiple of the same operators as well
    - The last redirection operator of a specific type is performed. `>>` and `>` can overwrite each other
    - e.g. `cat < main.c > test.txt >> test2.txt`. `test2.txt` is valid. `cat` reads from `main.c` and appends the output into `test2.txt`. `test.txt` is not made which does not line up exactly with the functionality provided by Bash.
    - There **MUST** be at least one space padded around the operator. So the following examples would **NOT** be accepted: `ls>test.txt`, `cat<main.c>test.txt`  
- The pipe operator works
    - `cat main.c | grep shell`
    - There can only be **ONE** pipe operator in a given statement
    - Spaces around the `|` is **NOT** required. So the following is accepted: `ls|grep shell`
    - Redirection operators can be used in conjunction with the pipe operator: `cat < shell.c | grep shell > test.txt`
    - Similarly to Bash, the `cd` and `exit` command cannot be executed with the pipe operator
- Aliases work
    - `alias ll="ls -l"`
    - `unalias ll`
    - Quotations are not neccesary, however anything past spaces will not be read , e.g. `alias vim=nvim`
## In Progress


## Known Bugs

- Intermediate redirections are not executed. For example, in `cat < main.c > test.txt >> test2.txt`, the `text.txt` is not created if the file does not exist already. This differs from Bash which would create the file although it would be empty. I consider this to be a minor bug and is a result of how redirection is implemented in the shell.
- Odd (and illogical) formulations using the pipe operators that involves using `>` on the first command or `<` on the second command.
    - e.g. `cat main.c > file.txt | grep shell > file.txt`
    - Unlike to Bash, the `grep shell > file.txt` above would overwrite the previous `cat main.c > file.txt` leaving a empty `file.txt`. In Bash, the `grep shell > file.txt` would not execute due to the lack of input.
    - This is a minor bug because it is unlikely you would write a command similar to the example above. However, Bash syntax allows it, and this shell does not mirror it perfectly. The pipe does work in common use cases, however.
- Spaces around `<`, `>`, and `>>` are required. This differs from Bash where they are optional.
- Aliases are saved per-directory, and new aliases will have to be made when switching directories.

## Function Headers

### [shell.h](./shell.h)

```c
/**
 * splits the current process and executes the provided command
 * in the child process. The parent process will wait until the 
 * child process has finished. Can process one pipe operator and
 * the redirection operators (<, >, >>) as well.
 * 
 * @arg command - the command to execute as a string
 */
void shellexec(char *command);
```

### [shellutil.h](./shellutil.h)

```c
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
```

### [redirect.h](./redirect.h)

```c
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
```

### [alias.h](./alias.h)

```c
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
```
