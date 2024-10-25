#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../basic/basic.h"
#include "../argparse/private_argparse.h"
#include "../executer/executor.h"

#include "pipeline.h"

#include <stdio.h>

// macros
#define READ 0
#define WRITE 1

static int origin_proc(int d, t_input *ti, char *envp[]);
static int child_proc(int d, int pipe_fd[2], t_input *ti, char *envp[]);
static int parent_proc(int d, int pipe_fd[2], t_input *ti, char *envp[]);

void run_pipes(int d, t_input *ti, char *envp[])
{
	pid_t pid;
	int pipe_fd[2];

	pipe(pipe_fd);
	if (d == 0)
		origin_proc(d, ti, envp);
	else
	{
		pid = fork();
		if (pid == 0)
			child_proc(d, pipe_fd, ti, envp);
		else 
			parent_proc(d, pipe_fd, ti, envp);
	}
}

int executor(char *file,char *argv[], char *envp[])
{
	char *path;
	
	// printf("file \"%s\"\n", file);
	path = get_cmd_path(file, envp);
	printf("path %s\n", path);
	execve(path, argv, envp);
	free(path);
	return (0);
}

static int origin_proc(int d, t_input *ti, char *envp[])
{
	int fd;

	fd = open( ti -> infile, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	// execvp(ti -> cmds[d][0], ti -> cmds[d]);
	executor(ti -> cmds[d][0], ti -> cmds[d], envp);
	return (0);
}

static int child_proc(int d, int pipe_fd[2], t_input *ti, char *envp[])
{
	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close(pipe_fd[WRITE]);
	run_pipes(d - 1, ti, envp);
	return (0);
}

static int parent_proc(int d, int pipe_fd[2], t_input *ti, char *envp[])
{
	// env d
	close(pipe_fd[WRITE]);
	dup2(pipe_fd[READ], STDIN_FILENO);
	close(pipe_fd[READ]);
	// execvp(cmds[d][0], cmds[d]);
	executor(ti -> cmds[d][0],ti -> cmds[d], envp);
	return (0);
}

