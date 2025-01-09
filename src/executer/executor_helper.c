/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:31:15 by tmuranak          #+#    #+#             */
/*   Updated: 2024/11/07 19:36:32 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../basic/basic.h"
#include "executor.h"

// test
#include <stdio.h>

int	get_path_index(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (startswith(envp[i], "PATH="))
			return (i);
		i++;
	}
	return (-1);
}

char	**split_path_string(char *str)
{
	char	**rlist;
	char	**tmp;
	int		rlen;
	char	*start_ptr;

	rlen = char_count(str, ':');
	rlist = (char **)malloc(sizeof(char *) * (rlen + 1 + 1));
	tmp = rlist;
	if (rlist == NULL)
		return (NULL);
	start_ptr = str;
	while (*str != '\0')
	{
		if (*str == ':')
		{
			*rlist++ = copy_string(start_ptr, str);
			start_ptr = str + 1;
		}
		str++;
	}
	*rlist++ = copy_string(start_ptr, str);
	*rlist = NULL;
	return (tmp);
}

/// 環境変数を格納した、リストVec<String>を返却する
char	**get_all_path(char *envp[])
{
	char	**rlist;
	char	*str;

	str = envp[get_path_index(envp)];
	str += 5;
	rlist = split_path_string(str);
	return (rlist);
}

char	*get_path(char *file, char *envp[])
{
	char	*joined;
	char	*rtmp;	
	char	**rlist;
	char	**rlist_tmp;

	rlist = get_all_path(envp);
	rtmp = NULL;
	rlist_tmp = rlist;
	while (*rlist != NULL)
	{
		joined = ft_strjoin(*rlist, file);
		if (access(joined, X_OK) == 0 && rtmp == NULL)
			rtmp = joined;
		else
			free(joined);
		rlist++;
	}
	clear_path_list(rlist_tmp);
	free(rlist_tmp);
	return (rtmp);
}

char	*ft_strclone(char *str)
{
	char *rstr;
	char *rstr_tmp;

	rstr = (char *) malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (rstr == NULL)
		return (NULL);
	rstr_tmp = rstr;
	while (*str != '\0')
	{
		*rstr = *str;
		rstr++;
		str++;
	}
	*rstr = '\0';
	return (rstr_tmp);
}

/// 絶対パスでコマンドが指定されていそうな場合
/// 正直この中のmalloc失敗をキャッチする
char	*get_path2(char *file)
{
	char	*rtmp;

	if (access(file, X_OK) == 0)
		rtmp = ft_strclone(file);
	else
		rtmp = NULL;
	return (rtmp);
}

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
