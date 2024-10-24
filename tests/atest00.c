#include "../src/argparse/private_argparse.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char **a;
	char **tmp;

	for (int i = 1;i < argc; i++)
	{
		printf("count_cmd_args %d \n",count_cmd_args(argv[i]));
		a = get_cmd(argv[i]);
		tmp = a;
		while (*a != NULL)
		{
			printf("\"%s\"\n",*a);
			free(*a);
			a++;
		}
		free(tmp);
	}
	return (0);
}
