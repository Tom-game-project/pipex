#include "../src/argparse/private_argparse.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *a = "hello world";
	char *b = copy_string(a, a + 5);
	printf("%s\n", b);
	free(b);
}

