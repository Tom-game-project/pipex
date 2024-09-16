#include <unistd.h>
#include <stdio.h>

int main() {
    char *argv[] = {"bin/ls", "-l", "-a", "src/", NULL};  // 実行するプログラムと引数
    char *envp[] = {NULL};  // 環境変数

    if (execve("/bin/ls", argv, envp) == -1) {
        perror("execve failed");
    }

    return 0;
}

