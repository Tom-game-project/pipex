/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:30:09 by tmuranak          #+#    #+#             */
/*   Updated: 2024/11/07 19:38:54 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../basic/basic.h"

int	ft_isspace(char c)
{
	return (
		c == ' ' || \
		c == '\f' || \
		c == '\n' || \
		c == '\r' || \
		c == '\t' || \
		c == '\v'
	);
}

int	count_cmd_args(char *str)
{
	int	flag;
	int	j;

	flag = 0;
	j = 0;
	while (*str != '\0')
	{
		if (flag && ft_isspace(*str))
			j++;
		flag = !ft_isspace(*str);
		str++;
	}
	if (flag)
		j++;
	return (j);
}

char	**get_cmd(char *str)
{
	char	**rlist;
	char	**tmp;
	int		flag;
	char	*start_ptr;

	rlist = (char **)malloc(sizeof(char *) * (count_cmd_args(str) + 1));
	if (rlist == NULL)
		return (NULL);
	tmp = rlist;
	flag = 0;
	while (*str != '\0')
	{
		if (flag && ft_isspace(*str))
			*rlist++ = copy_string(start_ptr, str);
		else if (!flag && !ft_isspace(*str))
			start_ptr = str;
		flag = !ft_isspace(*str);
		str++;
	}
	if (flag)
		*rlist++ = copy_string(start_ptr, str);
	*rlist = NULL;
	return (tmp);
}

/// @brief 
/// 	[
/// 		[(char *), ...],
/// 		[...],
/// 		...
/// 	]
char	***get_cmds(int argc, char *argv[])
{
	int		i;
	char	***rlist;

	rlist = (char ***)malloc(sizeof(char **) * (argc - 1 - 2));
	if (rlist == NULL)
		return (NULL);
	i = 0;
	while (i + 2 < argc - 1)
	{
		rlist[i] = get_cmd(argv[i + 2]);
		i++;
	}
	return (rlist);
}

/// @brief free all element of cmds
void	clear_cmds(int argc, char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i + 2 < argc - 1)
	{
		j = 0;
		while (cmds[i][j] != NULL)
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
