#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[],char *envp[]) {
    int pipe_fd[2];  // ファイルディスクリプタを保存する配列
    char buffer[128];
    char *exe_argv[] = {"bin/ls", "-l", "-a", NULL};  // <- argvから割り出すことが可能

    // パイプを作成
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // 子プロセス: パイプに書き込む
        close(pipe_fd[0]);  // 読み取り側は使わないので閉じる
        char message[] = "Hello from the child process!";
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);  // 書き込みが終わったら閉じる
        write(STDOUT_FILENO, message, strlen(message) + 1);  // パイプに書き込み
    } else {
        // 親プロセス: パイプから読み取る
        close(pipe_fd[1]);  // 書き込み側は使わないので閉じる
        read(pipe_fd[0], buffer, sizeof(buffer));  // パイプから読み取り
        printf("Received from child process: %s\n", buffer);
        close(pipe_fd[0]);  // 読み取りが終わったら閉じる
        wait(NULL);
    }

    return 0;
}
