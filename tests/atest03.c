#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int get_path_index(char *envp[])
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (startswith(envp[i], "PATH="))
			return (i);
		i++;
	}
	return (-1);
}

int char_count(char *str,char c)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

char **split_path_string(char *str)
{
	char **rlist;
	char **tmp;
	int rlen;
	char *start_ptr;

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
			*rlist++=copy_string(start_ptr, str);
			start_ptr = str + 1;
		}
		str++;
	}
	*rlist++=copy_string(start_ptr, str);
	*rlist = NULL;
	return (tmp);
}

void clear_path_list(char **lst)
{
	char **tmp;

	tmp = lst;
	while (*lst != NULL)
	{
		free(*lst);
		lst++;
	}
}

char **get_all_path(char *envp[])
{
	char **rlist;
	char *str;

	str = envp[get_path_index(envp)];
	str += 5;
	rlist = split_path_string(str);
	return (rlist);
}

char *get_path(char *file, char *envp[])
{
	char *joined;
	char *rtmp;	
	char **rlist;
	char **rlist_tmp;
       
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


int main(int argc, char *argv[], char *envp[])
{
	char *p;

	p = get_path("/ls", envp);
	printf("match! %s\n", p);
	free(p);
	return (0);
}

