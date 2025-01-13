/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:31:06 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/09 19:09:12 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

char	*get_cmd_path(char *cmd, char *envp[]);

int		char_count(char *str, char c);
void	clear_path_list(char **lst);

char	*ft_strclone(char *str);
char	*get_path(char *file, char *envp[]);
char	*get_path2(char *file);

#endif
