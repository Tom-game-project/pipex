#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMANDS 10

typedef struct {
    char **commands[MAX_COMMANDS];
    int cmd_count;
    char *input_file;
    char *output_file;
} Pipeline;

int execute_pipeline_recursive(Pipeline *pipeline, int cmd_index, int input_fd);

int last_cmd(Pipeline *pipeline, int cmd_index, int input_fd)
{
        // 子プロセスを作成
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {  // 子プロセス
            // 前のコマンドからの入力を設定
            if (input_fd != STDIN_FILENO) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            // 出力リダイレクトの設定
            if (pipeline->output_file) {
                int fd = open(pipeline->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("open output file");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            // 最後のコマンドを実行
            execvp(pipeline->commands[cmd_index][0], pipeline->commands[cmd_index]);
            perror("execvp");
            exit(1);
        }

        // 親プロセスは入力FDを閉じて子プロセスの終了を待つ
        if (input_fd != STDIN_FILENO) {
            close(input_fd);
        }
        waitpid(pid, NULL, 0);
        return 0;
}

int middle_cmd(Pipeline *pipeline, int cmd_index, int input_fd)
{
    // 再帰ケース：中間コマンドの実行
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {  // 子プロセス
        // パイプの書き込み端を標準出力に設定
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);  // 読み込み端は使わない

        // 前のコマンドからの入力を設定
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        // 現在のコマンドを実行
        execvp(pipeline->commands[cmd_index][0], pipeline->commands[cmd_index]);
        perror("execvp");
        exit(1);
    }

    // 親プロセスは使わないファイルディスクリプタを閉じる
    close(pipefd[1]);
    if (input_fd != STDIN_FILENO) {
        close(input_fd);
    }

    // 次のコマンドを再帰的に実行
    int result = execute_pipeline_recursive(pipeline, cmd_index + 1, pipefd[0]);

    // 子プロセスの終了を待つ
    waitpid(pid, NULL, 0);
    return result;
}

// 再帰的にパイプラインを実行する関数
int execute_pipeline_recursive(Pipeline *pipeline, int cmd_index, int input_fd) 
{
    // 基底ケース：最後のコマンドの実行
    if (cmd_index == pipeline->cmd_count - 1) {
	    return (last_cmd(pipeline, cmd_index, input_fd));
    }
    return (middle_cmd(pipeline, cmd_index, input_fd)); // 再帰
}

// パイプラインの実行を開始する関数
int execute_pipeline(Pipeline *pipeline) {
    // 入力リダイレクトの設定
    int input_fd = STDIN_FILENO;
    if (pipeline->input_file) {
        input_fd = open(pipeline->input_file, O_RDONLY);
        if (input_fd == -1) {
            perror("open input file");
            return 1;
        }
    }

    // 再帰的な実行を開始
    return execute_pipeline_recursive(pipeline, 0, input_fd);
}

// 使用例
int main() {
    Pipeline pipeline = {0};
    
    // "< input.txt ls -l | grep test | wc -l > output.txt" を実行する例
    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"grep", "test", NULL};
    char *cmd3[] = {"wc", "-l", NULL};
    
    pipeline.commands[0] = cmd1;
    pipeline.commands[1] = cmd2;
    pipeline.commands[2] = cmd3;
    pipeline.cmd_count = 3;
    pipeline.input_file = "input.txt";
    pipeline.output_file = "output.txt";
    
    execute_pipeline(&pipeline);
    return 0;
}
