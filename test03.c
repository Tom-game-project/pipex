#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    int pipefd[2];
    pid_t pid;
    char buffer[1024];
    ssize_t nbytes;

    // パイプを作成
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // 子プロセスを生成
    pid = fork();

    if (pid == -1) {
        // forkが失敗した場合
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // 子プロセス
        // パイプの読み取り側を閉じる
        close(pipefd[0]);

        // 標準出力をパイプの書き込み側にリダイレクト
        dup2(pipefd[1], STDOUT_FILENO);

        // パイプの書き込み側を閉じる
        close(pipefd[1]);

        // 実行するプログラムと引数を準備
        char *argv_command[] = {"/bin/ls","-la", NULL};
        // char *envp[] = {NULL};

        // execveで新しいプログラムを実行
        execve(argv_command[0], argv_command, envp);

        // execveが失敗した場合
        perror("execve failed");
        exit(EXIT_FAILURE);
    } else {
        // 親プロセス
        // パイプの書き込み側を閉じる
        close(pipefd[1]);

        // 子プロセスの標準出力をパイプから読み取る
        while ((nbytes = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[nbytes] = '\0';  // 文字列の終端を追加
            printf("Received from child: %s", buffer);
        }

        // パイプの読み取り側を閉じる
        close(pipefd[0]);

        // 子プロセスの終了を待つ
        wait(NULL);
    }

    return 0;
}
