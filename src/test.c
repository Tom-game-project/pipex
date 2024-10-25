
#include "./executer/executor.h"
#include <stdio.h>

#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	char *path;

	if (argc == 2){
	path = get_cmd_path(argv[1], envp);
	printf("cmd %s\n", argv[1]);
	printf("path %s\n", path);
	free(path);
	}
	return (0);
}

