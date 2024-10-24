#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

// 再帰的にコマンドを実行する関数
void execute_pipeline(char ***cmds, int n, int write_to_file) {
    if (n == 0) {
        // 終了条件: 最後のコマンドを実行する

        // ファイルに出力する場合
        if (write_to_file) {
            int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (file_fd == -1) {
                perror("open failed");
                exit(EXIT_FAILURE);
            }

            // 標準出力をファイルにリダイレクト
            dup2(file_fd, STDOUT_FILENO);
            close(file_fd);
        }

        // コマンドを実行
        if (execve(cmds[0][0], cmds[0], NULL) == -1) {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    }

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
        // 子プロセス: 次のコマンドを実行
        close(pipefd[1]);  // 書き込み側を閉じる
        dup2(pipefd[0], STDIN_FILENO);  // 標準入力をパイプの読み取り側にリダイレクト
        close(pipefd[0]);

        // 次のコマンドに再帰的に処理を渡す
        execute_pipeline(cmds + 1, n - 1, write_to_file);
    } else {
        // 親プロセス: 現在のコマンドを実行
        close(pipefd[0]);  // 読み取り側を閉じる
        dup2(pipefd[1], STDOUT_FILENO);  // 標準出力をパイプの書き込み側にリダイレクト
        close(pipefd[1]);

        // 現在のコマンドを実行
        if (execve(cmds[0][0], cmds[0], NULL) == -1) {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    // コマンド列の定義
    char *ls[] = {"/bin/ls", NULL};
    char *grep[] = {"/bin/grep", "something", NULL};
    char *wc[] = {"/usr/bin/wc", "-l", NULL};
    char **cmds[] = {ls, grep, wc, NULL};

    // コマンド列の長さを取得
    int n = 0;
    while (cmds[n] != NULL) n++;

    // 最後のコマンドの出力をファイルに書き込む
    execute_pipeline(cmds, n, 1);

    // 子プロセスの終了を待つ
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}
