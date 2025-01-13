/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:32:16 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/09 18:49:45 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./argparse/private_argparse.h"
#include "./pipeline/pipeline.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// for test
#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

int	usage(void)
{
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 [cmd3[...]] outfile\n",
		STDERR_FILENO);
	ft_putstr_fd("behave like :`< infile cmd1 | cmd2 | cmd3 ... > outfile`\n",
		STDERR_FILENO);
	ft_putstr_fd("requires at least 4 arguments\n", 1);
	exit(1);
}

t_input	*create_input_structure(int argc, char *argv[])
{
	char	***cmds;
	t_input	*inp;

	inp = (t_input *)malloc(sizeof(t_input));
	if (inp == NULL)
		return (NULL);
	inp->infile = argv[1];
	cmds = get_cmds(argc, argv);
	inp->cmds = cmds;
	inp->cmdlen = argc - 2 - 1;
	inp->outfile = argv[argc - 1];
	return (inp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_input	*inp;
	int		exit_status;

	if (argc < 5)
		usage();
	exit_status = 0;
	inp = create_input_structure(argc, argv);
	exit_status = exec_pipe(inp, envp);
	clear_cmds(argc, inp->cmds);
	free(inp);
	return (exit_status);
}
