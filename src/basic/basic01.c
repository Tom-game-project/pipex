/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:55:30 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/10 19:56:53 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"
#include <stdbool.h>
#include <unistd.h>

/// 同じ文字列かどうかを判定する
bool	ft_streq(char *a, char *b)
{
	if (ft_strlen(a) != ft_strlen(b))
		return (false);
	else
	{
		while (*a != '\0')
		{
			if (*a != *b)
				return (false);
			a++;
			b++;
		}
		return (true);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}
