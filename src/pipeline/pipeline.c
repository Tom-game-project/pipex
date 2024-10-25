#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../basic/basic.h"
#include "../argparse/private_argparse.h"

#include "pipeline.h"

// macros
#define READ 0
#define WRITE 1

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

