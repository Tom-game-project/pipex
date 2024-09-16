#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];  // パイプ用のファイルディスクリプタ (pipefd[0] が読み込み側, pipefd[1] が書き込み側)
    pid_t pid;
    char buffer[1024];  // 親プロセスで子プロセスの出力を読み込むためのバッファ

    // パイプの作成
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 子プロセスの作成
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    printf("hello pid %d\n", pid);

    if (pid == 0) {
        // 子プロセスの処理

        printf("子プロセス 開始\n");
        // 標準出力をパイプの書き込み側にリダイレクト
        close(pipefd[0]);  // パイプの読み込み側を閉じる
        dup2(pipefd[1], STDOUT_FILENO);  // 標準出力をパイプの書き込み側に複製
        close(pipefd[1]);  // パイプの書き込み側を閉じる

        // 実行するプログラム（/bin/ls）の設定
        char *argv[] = {"/bin/ls", NULL};
        char *envp[] = {NULL};  // 環境変数

        // execveで新しいプログラムを実行
        execve("/bin/ls", argv, envp);

        // エラー処理 (execveが失敗した場合)
        perror("execve failed");
        exit(EXIT_FAILURE);
    } else {
        // 親プロセスの処理
        printf("親プロセス 開始\n");
        close(pipefd[1]);  // パイプの書き込み側を閉じる

        // パイプの読み込み側からデータを読み取る
        ssize_t count;
        while ((count = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[count] = '\0';  // バッファを文字列に変換
            printf("%s", buffer);  // 子プロセスの出力を表示
        }

        close(pipefd[0]);  // パイプの読み込み側を閉じる

        // 子プロセスの終了を待機
        wait(NULL);
    }

    return 0;
}
