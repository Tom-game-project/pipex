/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:31:38 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/16 16:56:55 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
int	run_pipe(int d, t_input *ti, char *envp[], int input_fd)
{
	if (d == ti->cmdlen - 1)
		return (last_cmd(d, ti, envp, input_fd));
	return (middle_cmd(d, ti, envp, input_fd));
}

int	exec_pipe(t_input *ti, char *envp[])
{
	return (run_pipe(0, ti, envp, -1));
}
