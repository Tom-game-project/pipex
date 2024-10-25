#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "./basic/basic.h"
#include "./argparse/private_argparse.h"

#include <stdio.h>


#define READ 0
#define WRITE 1

/*
char *cmd1[] = {"cat", NULL};
char *cmd2[] = {"head", NULL};
char *cmd3[] = {"grep", "char", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};
int cmd_n = 3;
*/

typedef struct s_input
{
	char *infile;
	char ***cmds;
	char *outfile;
}	 t_input;

int origin_proc(int d, t_input *ti);
int child_proc(int d, int pipe_fd[2], t_input *ti);
int parent_proc(int d, int pipe_fd[2], t_input *ti);

void run_pipes(int d, t_input *ti)
{
	pid_t pid;
	int pipe_fd[2];

	pipe(pipe_fd);
	if (d == 0)
		origin_proc(d, ti);
	else
	{
		pid = fork();
		if (pid == 0)
			child_proc(d, pipe_fd, ti);
		else 
			parent_proc(d, pipe_fd, ti);
	}
}

int origin_proc(int d, t_input *ti)
{
	int fd;
	char ***cmds;
	char *infile;

	cmds = ti -> cmds;
	infile = ti -> infile;
	fd = open(infile, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	execvp(cmds[d][0], cmds[d]);
	return (0);
}

int child_proc(int d, int pipe_fd[2], t_input *ti)
{
	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close(pipe_fd[WRITE]);
	run_pipes(d - 1, ti);
	return (0);
}

int parent_proc(int d, int pipe_fd[2], t_input *ti)
{
	char ***cmds;

	// env d
	cmds = ti -> cmds;
	close(pipe_fd[WRITE]);
	dup2(pipe_fd[READ], STDIN_FILENO);
	close(pipe_fd[READ]);
	execvp(cmds[d][0], cmds[d]);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	char ***cmds;
	pid_t pid;
	t_input *inp;
	int cmd_n;

	(void) envp;

	inp = (t_input*) malloc(sizeof(inp));
	if (inp == NULL)
		return (1);
	inp -> infile = argv[1];
	cmds = get_cmds(argc, argv);
	cmd_n = argc - 2 - 1;
	inp -> cmds = cmds;
	inp -> outfile = argv[argc - 1];
	printf("infile %s \n",inp -> infile);
	// fork
	pid = fork(); // if error pid == -1
	if (pid == 0) // if child
		run_pipes(cmd_n - 1, inp);
	else if (pid == -1)
	{
		// pass;
	}
	else // if parent
		wait(NULL);
	// ===== free all =====
	clear_cmds(argc, cmds);
	free(inp);
	return (0);
}

