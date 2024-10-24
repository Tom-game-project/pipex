#include "../src/argparse/private_argparse.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	char ***cmds;
	int i;
	int j;
	
	cmds = get_cmds(argc, argv);
	i = 0;
	while (i + 1 < argc)
	{
		j = 0;
		printf("number %d\n", i);
		while (cmds[i][j] != NULL)
		{
			printf("%s\n", cmds[i][j]);
			j++;
		}
		i++;
	}
	clear_cmds(argc, cmds);
	return (0);
}

