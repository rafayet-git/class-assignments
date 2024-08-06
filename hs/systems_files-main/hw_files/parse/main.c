#include "parse.h"
#include <unistd.h>
#include <stdlib.h>
int main(){
	char *str="ls -a -l -b -c -d -g";
	char **argue = parse_args(str);
	execvp(argue[0], argue);
	free(argue);
}

