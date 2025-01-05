/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:32:16 by tmuranak          #+#    #+#             */
/*   Updated: 2024/11/07 19:42:20 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "./basic/basic.h"
#include "./argparse/private_argparse.h"
#include "./pipeline/pipeline.h"

// for test
#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	Usage(void)
{
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 [cmd3[...]] outfile\n", 1);
	ft_putstr_fd("behave like :`< infile cmd1 | cmd2 | cmd3 ... > outfile`\n", 1);
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
	inp -> infile = argv[1];
	cmds = get_cmds(argc, argv);
	inp -> cmds = cmds;
	inp -> cmdlen = argc - 2 - 1;
	inp -> outfile = argv[argc - 1];
	return (inp);
}

int	main(int argc, char *argv[], char *envp[])
{
	//pid_t	pid;
	t_input	*inp;
	int		exit_status;
	// int		status;

	if (argc < 5)
		Usage();
	exit_status = 0;
	inp = create_input_structure(argc, argv);
	// run_pipes(0, inp, envp);
	exec_pipe(inp, envp);
	//	pid = fork();
	//	if (pid == 0)
	//	else if (pid == -1)
	//	{
	//	}
	//	else
	//	{
	//		waitpid(pid, &status, WUNTRACED);
	//		exit_status = WEXITSTATUS(status);
	//	}
	clear_cmds(argc, inp -> cmds);
	free(inp);
	return (exit_status);
}
