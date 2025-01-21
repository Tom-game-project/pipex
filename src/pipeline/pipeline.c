/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:31:38 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/21 17:00:16 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "../basic/basic.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int	run_pipe(int d, t_input *ti, char *envp[], int input_fd);

void	write_outfile(char *filename)
{
	int	fd;

	if (filename)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(filename);
			exit(1);
		}
		close((dup2(fd, STDOUT_FILENO), fd));
	}
}

int	last_cmd(int d, t_input *ti, char *envp[], int input_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
			close((dup2(input_fd, STDIN_FILENO), input_fd));
		write_outfile(ti->outfile);
		executor(ti->cmds[d][0], ti->cmds[d], envp);
		exit((perror("executor"), 1));
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	waitpid(pid, &status, WUNTRACED);
	return (WEXITSTATUS(status));
}

bool	read_infile(int *input_fd, char *filename)
{
	if (filename)
	{
		*input_fd = (close(*input_fd), open(filename, O_RDONLY));
		if (*input_fd == -1)
			(perror(filename), exit(1));
	}
	return (true);
}

void	connect_pipe(int d, int input_fd, char *filename)
{
	if (input_fd != STDIN_FILENO)
	{
		if (d == 0)
			read_infile(&input_fd, filename);
		close((dup2(input_fd, STDIN_FILENO), input_fd));
	}
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
		connect_pipe(d, input_fd, ti->infile);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		(close(pipe_fd[WRITE]), close(pipe_fd[READ]));
		executor(ti->cmds[d][0], ti->cmds[d], envp);
		exit((perror("executor"), 1));
	}
	close(pipe_fd[WRITE]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	last_status = run_pipe(d + 1, ti, envp, pipe_fd[READ]);
	return ((waitpid(pid, &status, WUNTRACED), last_status));
}
