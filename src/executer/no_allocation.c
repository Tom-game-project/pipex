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
