#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*res;
	int		i;

	res = (char)malloc(sizeof(char) * (n + 1));
	i = -1;
	while (++i < n)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}
