#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();  // 子プロセスを作成
    int pipe_fd[2];
    char buffer[1024];

    if (pipe(pipe_fd) == -1){
        perror("something wrong with pipe");
        exit(1);
    }

    if (pid == 0) {
        // 子プロセス内の処理
        printf("子プロセスが開始されました。\n");

        // execveで新しいプログラムを実行
        char *argv[] = {"/bin/ls", "-l", NULL};  // 実行するプログラムと引数
        char *envp[] = {NULL};  // 環境変数
        close(pipe_fd[0]); // 読み込み側を閉じる
        dup2(pipe_fd[1], STDIN_FILENO);
        close(pipe_fd[1]); // 書き込み側を閉じる
        if (execve("/bin/ls", argv, envp) == -1) {
            perror("execve failed");
        }
        
        // execveが成功すると、この行は実行されません
        printf("これは表示されないはずです。\n");

    } else if (pid > 0) {
        // 親プロセス内の処理
        int status;
        wait(&status);  // 子プロセスが終了するのを待機
        close(pipe_fd[1]);// 書き込み側を閉じる
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("子プロセスが終了しました。%s\n", buffer);
        close(pipe_fd[0]); // 読み込み側を閉じる
    } else {
        // forkの失敗
        perror("fork failed");
    }

    return 0;
}
