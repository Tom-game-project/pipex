/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:03:17 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/09 19:05:27 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../basic/basic.h"
#include "executor.h"
#include <stdlib.h>
#include <unistd.h>

/// 実行可能なファイルのパスを返す、無い場合はNULLを返却するもの
char	*get_cmd_path(char *cmd, char *envp[])
{
	char	*file;
	char	*p;

	if (startswith(cmd, "/") || startswith(cmd, "."))
	{
		p = get_path2(cmd);
		return (p);
	}
	else
	{
		file = ft_strjoin("/", cmd);
		p = get_path(file, envp);
		free(file);
		return (p);
	}
}
