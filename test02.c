#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // 子プロセスを作成

    if (pid == 0) {
        // 子プロセス内の処理
        printf("子プロセスが開始されました。\n");

        // execveで新しいプログラムを実行
        char *argv[] = {"/bin/ls", "-l", NULL};  // 実行するプログラムと引数
        char *envp[] = {NULL};  // 環境変数
        
        if (execve("/bin/ls", argv, envp) == -1) {
            perror("execve failed");
        }
        
        // execveが成功すると、この行は実行されません
        printf("これは表示されないはずです。\n");

    } else if (pid > 0) {
        // 親プロセス内の処理
        int status;
        wait(&status);  // 子プロセスが終了するのを待機
        printf("子プロセスが終了しました。\n");
    } else {
        // forkの失敗
        perror("fork failed");
    }

    return 0;
}
