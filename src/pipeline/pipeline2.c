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

void	executor(char *file, char *argv[], char *envp[])
{
	char	*path;

	path = get_cmd_path(file, envp);
	if (path == NULL)
	{
		write(STDERR_FILENO, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND));
		free(path);
		exit (127);
	}
	execve(path, argv, envp);
	free(path);
	perror("pipex");
	exit (1);
}
