/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:31:38 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/09 18:58:49 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// macros
#define READ 0
#define WRITE 1

// run_pipe2
int	run_pipe(int d, t_input *ti, char *envp[], int input_fd);

int	last_cmd(int d, t_input *ti, char *envp[], int input_fd)
{
	pid_t	pid;
	int		fd;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
			close((dup2(input_fd, STDIN_FILENO), input_fd));
		if (ti->outfile)
		{
			fd = open(ti->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				exit((perror("open output file"), 1));
			close((dup2(fd, STDOUT_FILENO), fd));
		}
		executor(ti->cmds[d][0], ti->cmds[d], envp);
		exit((perror("executor"), 1));
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	waitpid(pid, &status, WUNTRACED);
	return (WEXITSTATUS(status));
}

int	middle_cmd(int d, t_input *ti, char *envp[], int input_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		last_status;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		(close(pipe_fd[WRITE]), close(pipe_fd[READ]));
		if (input_fd != STDIN_FILENO)
			close((dup2(input_fd, STDIN_FILENO), input_fd));
		executor(ti->cmds[d][0], ti->cmds[d], envp);
		exit((perror("executor"), 1));
	}
	close(pipe_fd[WRITE]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	last_status = run_pipe(d + 1, ti, envp, pipe_fd[READ]);
	return ((waitpid(pid, &status, WUNTRACED), last_status));
}

int	run_pipe(int d, t_input *ti, char *envp[], int input_fd)
{
	if (d == ti->cmdlen - 1)
		return (last_cmd(d, ti, envp, input_fd));
	return (middle_cmd(d, ti, envp, input_fd));
}

int	exec_pipe(t_input *ti, char *envp[])
{
	int	fd;

	fd = open(ti->infile, O_RDONLY);
	if (fd == -1)
	{
		perror(ti->infile);
		return (1);
	}
	return (run_pipe(0, ti, envp, fd));
}
