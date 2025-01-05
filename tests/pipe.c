#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// 単純なパイプの実装: command1 | command2 の形式
int create_pipe(char *cmd1[], char *cmd2[]) {
    int pipefd[2];  // パイプの読み書き用のファイルディスクリプタ
    pid_t pid1, pid2;

    // パイプの作成
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // 最初のコマンド用の子プロセスを作成
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {  // 子プロセス1
        // 標準出力をパイプの書き込み端点に複製
        dup2(pipefd[1], STDOUT_FILENO);
        
        // パイプの両端を閉じる
        close(pipefd[0]);
        close(pipefd[1]);

        // コマンド1を実行
        execvp(cmd1[0], cmd1);
        perror("execvp cmd1");
        exit(1);
    }

    // 二番目のコマンド用の子プロセスを作成
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {  // 子プロセス2
        // 標準入力をパイプの読み込み端点に複製
        dup2(pipefd[0], STDIN_FILENO);
        
        // パイプの両端を閉じる
        close(pipefd[0]);
        close(pipefd[1]);

        // コマンド2を実行
        execvp(cmd2[0], cmd2);
        perror("execvp cmd2");
        exit(1);
    }

    // 親プロセスでパイプの両端を閉じる
    close(pipefd[0]);
    close(pipefd[1]);

    // 両方の子プロセスの終了を待つ
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

// 使用例
int main() {
    // "ls -l | grep test" を実行する例
    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"grep", "test", NULL};
    
    create_pipe(cmd1, cmd2);
    return 0;
}
