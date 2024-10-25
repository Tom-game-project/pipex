#include <stdio.h>
#include <string.h>

/*
int main()
{
	char *a;

	a = strerror(127);
	printf("strerror %s\n", a);
}

int main()
{
	char *a;

	a = strerror(127);
	perror("pipex");
	return (0);
}
*/

#include <stdio.h>

int main(void) {
    FILE *fp;
    fp = fopen("test3.txt", "r");
    
    if (fp == NULL) {
        perror("エラーが発生しました");
        return 0;
    } else {
        printf("ファイルが開きました");
    }

    fclose(fp);
    return 0;
}
