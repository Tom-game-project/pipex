/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:30:54 by tmuranak          #+#    #+#             */
/*   Updated: 2024/11/07 19:30:56 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>


char *copy_string(char *start, char *end)
{
    int len;
    char *rstr;
    char *tmp;

    len = end - start + 1;
    rstr = (char *)malloc(len * sizeof(char));
    if (rstr==NULL)
        return (NULL);
    tmp = rstr;
    while (start < end)
        *rstr++= *start++;
    *rstr = '\0';
    return (tmp);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (*str != '\0')
    {
        str++;
        i++;
    }
    return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	char	*tmp1;
	char	*tmp2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	tmp1 = (char *) s1;
	tmp2 = (char *) s2;
	buf = malloc((ft_strlen(tmp1) + ft_strlen(tmp2) + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	i = 0;
	while (*tmp1)
		*(buf + i++) = *tmp1++;
	while (*tmp2)
		*(buf + i++) = *tmp2++;
	*(buf + i) = '\0';
	return (buf);
}

int startswith(char *src, char *target)
{
	while (*target != '\0')
	{
		if (*src != *target)
			return (0);
		target++;
		src++;
	}
	return (1);
}

