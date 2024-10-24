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
		if (flag && *str == ' ')
		{
			j++;
			flag = 0;
		}
		else if (!flag && *str != ' ')
			flag = 1;
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
		if (flag && *str == ' ')
		{
			flag = 0;
			*rlist++ = copy_string(start_ptr, str);
		}
		else if (!flag && *str != ' ')
		{
			flag = 1;
			start_ptr = str;
		}
		str++;
	}
	*rlist = NULL;
	return (tmp);
}

/*
/// @brief 
/// 	[
/// 		[(char *), ...],
/// 		[...],
/// 		...
/// 	]
char ***get_cmds(int argc, char *argv[])
{
	int i;

	i = 0;
	while (++i < argc)
	{

	}
}
*/
