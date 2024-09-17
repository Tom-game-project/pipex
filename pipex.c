#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{

    char *argv[] = {"bin/ls", "-l", "-a", "src/", NULL};  // <- argvから割り出すことが可能

    if (execve("/bin/ls", argv, envp) == -1) {
        perror("execve failed");
    }

    return 0;
}

int pipe_child()
{

}