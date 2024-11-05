#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "./basic/basic.h"
#include "./argparse/private_argparse.h"
#include "./pipeline/pipeline.h"

// for test
#include <stdio.h>

/*
char *cmd1[] = {"cat", NULL};
char *cmd2[] = {"head", NULL};
char *cmd3[] = {"grep", "char", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};
int cmd_n = 3;
*/

int main(int argc, char *argv[], char *envp[])
{
	char ***cmds;
	pid_t pid;
	t_input *inp;
	int cmd_n;
	int exit_status;
	int status;

	(void) envp;

	exit_status = 0;
	inp = (t_input*) malloc(sizeof(t_input));
	if (inp == NULL)
		return (1);
	inp -> infile = argv[1];
	cmds = get_cmds(argc, argv);
	cmd_n = argc - 2 - 1;
	inp -> cmds = cmds;
	inp -> cmdlen = cmd_n;
	inp -> outfile = argv[argc - 1];
	// printf("infile %s \n",inp -> infile);
	// fork
	pid = fork(); // if error pid == -1
	if (pid == 0) // if child
		 run_pipes(cmd_n - 1, inp, envp);
	else if (pid == -1)
	{
		// pass;
	}
	else // if parent
	     {
		waitpid(pid, &status, WUNTRACED);
		        if (WIFEXITED(status)) {
            // 子プロセスが正常終了した場合
            exit_status = WEXITSTATUS(status);
            printf("Child process exited with status: %d\n", exit_status);
        } else if (WIFSIGNALED(status)) {
            // 子プロセスがシグナルで終了した場合
            int signal_num = WTERMSIG(status);
            printf("Child process terminated by signal: %d\n", signal_num);
        } else {
            printf("Child process did not terminate normally.\n");
        }
			
	     }
	// ===== free all =====
	clear_cmds(argc, cmds);
	free(inp);
	return (exit_status);
}

