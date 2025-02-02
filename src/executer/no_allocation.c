/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_allocation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:49:09 by tmuranak          #+#    #+#             */
/*   Updated: 2025/01/09 19:08:34 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	char_count(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

void	clear_path_list(char **lst)
{
	while (*lst != NULL)
	{
		free(*lst);
		lst++;
	}
}
