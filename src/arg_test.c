#include "./argparse/private_argparse.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_input
{
	char *infile;
	char ***cmds;
	char *outfile;
}	 t_input;

int main(int argc, char *argv[])
{
	t_input *inp;
	char ***cmds;
	int i;
	int j;

	inp = (t_input*) malloc(sizeof(inp));
	if (inp == NULL)
		return (1);
	inp -> infile = argv[1];
	cmds = get_cmds(argc, argv);
	inp -> outfile = argv[argc - 1];
	printf("infile %s \n",inp -> infile);
	i = 0;
	while (i + 2 < argc - 1)
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
	printf("outfile %s \n",inp -> outfile);
	clear_cmds(argc, cmds);
	free(inp);
	return (1);
}

