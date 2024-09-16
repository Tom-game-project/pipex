#include <stdlib.h>

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
char *copy_string(char *start,char *end)
{
    int len;
    char *rstr;
    int i;

    len = end - start + 1;
    rstr = malloc(len * sizeof(char));
    i = 0;
    if (rstr==NULL)
        return (NULL);
    while (start < end)
    {
        rstr[i] = *start;
        start++;
        i++;
    }
    rstr[len - 1] = '\0';
    return (rstr);
}
