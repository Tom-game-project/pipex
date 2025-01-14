/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:30:44 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/10 19:56:18 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_H
# define BASIC_H

# include <stdbool.h>

char	*copy_string(char *start, char *end);
int		ft_strlen(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		startswith(char *src, char *target);
bool	ft_streq(char *a, char *b);
char	*ft_strclone(char *str);
void	ft_putstr_fd(char *s, int fd);
#endif
