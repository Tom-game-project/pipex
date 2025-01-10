#include "basic.h"
#include <stdbool.h>

/// 同じ文字列かどうかを判定する
bool ft_streq(char *a, char *b)
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

