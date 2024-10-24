#include "../src/argparse/private_argparse.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	for (int i = 1;i < argc; i++)
	{
		printf("count_cmd_args %d \n",count_cmd_args(argv[i]));
	}
	return (0);
}
