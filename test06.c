#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t cpid = fork();
    if (cpid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        // 子プロセス: 標準出力をパイプの書き込み側にリダイレクト
        close(pipefd[0]);  // 読み取り側を閉じる
        dup2(pipefd[1], STDOUT_FILENO);  // 標準出力をパイプにリダイレクト
        close(pipefd[1]);  // 書き込み側を閉じる

        // 実行するコマンドを設定 (例: ls -l)
        char *cmd = "/bin/ls";
        char *args[] = {cmd, "-l", NULL};

        // execve で新しいプログラムを実行
        if (execve(cmd, args, NULL) == -1) {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // 親プロセス: パイプの書き込み側を閉じ、読み取り側からデータを読む
        close(pipefd[1]);  // 書き込み側を閉じる

        char buffer[1024];
        ssize_t count;
        
        // パイプからデータを読み取る
        while ((count = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[count] = '\0';  // 読み取ったデータを文字列として扱う
            printf("Received output:\n%s", buffer);  // 標準出力に表示
        }

        close(pipefd[0]);  // 読み取り側を閉じる
        wait(NULL);  // 子プロセスの終了を待つ
    }

    return 0;
}
