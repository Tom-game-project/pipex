#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <errno.h>
#include <stdio.h>

#include <fcntl.h>
#include "../basic/basic.h"
#include "../argparse/private_argparse.h"
#include "../executer/executor.h"

#include "pipeline.h"

// macros
#define READ 0
#define WRITE 1

// error msgs
#define CMD_NOT_FOUND "command not found\n"

static int origin_proc(int d, t_input *ti, char *envp[]);
static int child_proc(int d, int pipe_fd[2], t_input *ti, char *envp[]);
static int parent_proc(int d, int pipe_fd[2], t_input *ti, char *envp[]);
static void out_proc(int d, int pipe_fd[2], t_input *ti, char *envp[]);

int run_pipes(int d, t_input *ti, char *envp[])
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
		else if (pid == -1)
			perror("pipex");
		else if (ti -> cmdlen - 1== d)
		{
			out_proc(d, pipe_fd, ti, envp);
		}
		else 
			parent_proc(d, pipe_fd, ti, envp);
	}
	return (1);
}

void executor(char *file,char *argv[], char *envp[])
{
	char *path;

	path = get_cmd_path(file, envp);
	if (path == NULL)
	{
		// command not found
		write(STDERR_FILENO, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND));
		exit (127);
	}
	execve(path, argv, envp);
	free(path);
	perror("pipex");
	exit (1);
}

static int origin_proc(int d, t_input *ti, char *envp[])
{
	int fd;

	fd = open(ti -> infile, O_RDONLY);
	if (fd == -1) // some error occured
	{
		perror(ti -> infile);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	executor(ti -> cmds[d][0], ti -> cmds[d], envp);
	return (1);
}

static int child_proc(int d, int pipe_fd[2], t_input *ti, char *envp[])
{
	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close(pipe_fd[WRITE]);
	run_pipes(d - 1, ti, envp);
	return (1);
}

static int parent_proc(int d, int pipe_fd[2], t_input *ti, char *envp[])
{
	close(pipe_fd[WRITE]);
	dup2(pipe_fd[READ], STDIN_FILENO);
	close(pipe_fd[READ]);
	executor(ti -> cmds[d][0],ti -> cmds[d], envp);
	return (1);
}

static void out_proc(int d, int pipe_fd[2], t_input *ti, char *envp[])
{
	int fd;

	fd = open(ti -> outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1) // some error occured
	{
		perror(ti -> outfile);
		exit(1);
	}
	close(pipe_fd[WRITE]);
	dup2(pipe_fd[READ], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipe_fd[READ]);
	close(fd);
	executor(ti -> cmds[d][0],ti -> cmds[d], envp);
}

