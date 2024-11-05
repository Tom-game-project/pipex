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
                exit_status = WEXITSTATUS(status);
	     }
	// ===== free all =====
	clear_cmds(argc, cmds);
	free(inp);
	return (exit_status);
}

