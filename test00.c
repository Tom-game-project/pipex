#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];  // ファイルディスクリプタを保存する配列
    char buffer[128];

    // パイプを作成
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // 子プロセス: パイプに書き込む
        close(fd[0]);  // 読み取り側は使わないので閉じる
        char message[] = "Hello from the child process!";
        write(fd[1], message, strlen(message) + 1);  // パイプに書き込み
        close(fd[1]);  // 書き込みが終わったら閉じる
    } else {
        // 親プロセス: パイプから読み取る
        close(fd[1]);  // 書き込み側は使わないので閉じる
        read(fd[0], buffer, sizeof(buffer));  // パイプから読み取り
        printf("Received from child process: %s\n", buffer);
        close(fd[0]);  // 読み取りが終わったら閉じる
    }

    return 0;
}
