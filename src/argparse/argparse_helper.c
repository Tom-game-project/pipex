#include <stdlib.h>
#include <stdio.h>


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

int ft_isspace(char c)
{
	return (
		c == ' ' ||
		c == '\f' ||
		c == '\n' ||
		c == '\r' ||
		c == '\t' ||
		c == '\v' 
	);
}

/// @brief malloc x 1
/// @param start 
/// @param end 
/// @return 
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

int count_cmd_args(char *str)
{
	int flag;
	int j;

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

char **get_cmd(char *str)
{
	char **rlist;
	char **tmp;
	int flag;
	char *start_ptr;

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
char ***get_cmds(int argc, char *argv[])
{
	int i;
	char ***rlist;

	rlist = (char ***)malloc(sizeof(char **) * (argc - 1));
	if (rlist == NULL)
		return (NULL);
	i = 0;
	while (i + 1 < argc)
	{
		rlist[i] = get_cmd(argv[i + 1]);
		i++;
	}
	return (rlist);
}

/// @brief free all element of cmds
void clear_cmds(int argc, char ***cmds)
{
	int i;
	int j;

	i = 0;
	while (i + 1 < argc)
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

