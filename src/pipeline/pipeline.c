/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:31:38 by tmuranak          #+#    #+#             */
/*   Updated: 2024/11/07 19:40:58 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// #include <errno.h>
#include <stdio.h>

#include <fcntl.h>
// #include "../basic/basic.h"
// #include "../argparse/private_argparse.h"
// #include "../executer/executor.h"

#include "pipeline.h"

// macros
#define READ 0
#define WRITE 1

//static int	origin_proc(int d, t_input *ti, char *envp[]);
//static int	child_proc(int d, int pipe_fd[2], t_input *ti, char *envp[]);
//static int	parent_proc(int d, int pipe_fd[2], t_input *ti, char *envp[]);
//static void	out_proc(int d, int pipe_fd[2], t_input *ti, char *envp[]);

// run_pipe2
int	run_pipe2(int d, t_input *ti, char *envp[], int input_fd);

int last_cmd(int d, t_input *ti, char *envp[], int input_fd)
{
	pid_t pid;
	int fd;

	pid = fork();
	if (pid == -1) // エラーのとき
		return (perror("fork"),1);
	if (pid == 0)
	{
		// 子プロセスのとき
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (ti -> outfile)
		{
			fd = open(ti->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open output file");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		// 最後のコマンドを実行
		executor(ti->cmds[d][0], ti->cmds[d], envp);
		perror("execvp");
		exit(1);
	}
	// 親プロセスのとき
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	waitpid(pid, NULL, 0);
	return (0);
}


int middle_cmd(int d, t_input *ti, char *envp[], int input_fd)
{
	int pipe_fd[2];
	pid_t pid;
	int result;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		// エラーのとき
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		// 子プロセスのとき
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		close(pipe_fd[READ]);

		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		
		executor(ti->cmds[d][0], ti->cmds[d], envp);
		perror("execvp");
		exit(1);
	}
	// 親プロセスのとき
	close(pipe_fd[WRITE]);
	if (input_fd != STDIN_FILENO)
	{
		close(input_fd);
	}
	result = run_pipe2(d + 1, ti, envp, pipe_fd[READ]);
	waitpid(pid, NULL, 0);
	return (result);
}

int	run_pipe2(int d, t_input *ti, char *envp[], int input_fd)
{
	// 最後のコマンドを実行したとき
	if (d == ti->cmdlen - 1)
	{
		return (last_cmd(d, ti, envp, input_fd));
	}
	return (middle_cmd(d, ti, envp, input_fd));
}

int exec_pipe(t_input *ti, char *envp[])
{
	int fd;

	// printf("infile \"%s\"\n", ti->infile);
	fd = open(ti -> infile, O_RDONLY);
	if (fd == -1)
	{
		perror(ti -> infile);
		return (1);
	}
	return (run_pipe2(0, ti, envp, fd));
}

