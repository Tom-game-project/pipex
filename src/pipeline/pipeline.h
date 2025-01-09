/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:31:27 by tmuranak          #+#    #+#             */
/*   Updated: 2024/11/07 19:42:06 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

typedef struct s_input
{
	char	*infile;
	char	***cmds;
	int		cmdlen;
	char	*outfile;
}			t_input;

// int parent_proc(int d, int pipe_fd[2], t_input *ti);
// int		run_pipes(int d, t_input *ti, char *envp[]);
// for execute user command
void		executor(char *file, char *argv[], char *envp[]);

int			exec_pipe(t_input *ti, char *envp[]);
#endif
