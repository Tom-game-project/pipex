/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:31:27 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/16 17:44:47 by tmuranak         ###   ########.fr       */
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

void		executor(char *file, char *argv[], char *envp[]);

int			exec_pipe(t_input *ti, char *envp[]);

int			last_cmd(int d, t_input *ti, char *envp[], int input_fd);

int			middle_cmd(int d, t_input *ti, char *envp[], int input_fd);

#endif
