/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:06:03 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/10 17:07:22 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcombine(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;
	size_t	i;

	if (!s2)
		return (s1);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	res = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		res[i] = s1[i];
	i -= 1;
	while (++i < s1_len + s2_len)
		res[i] = s2[i - s1_len];
	res[i] = 0;
	if (s1)
		free(s1);
	return (res);
}

char	**ft_split_line(char *buff)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	res = malloc(2 * sizeof(char *));
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!is_line(buff))
		i--;
	res[0] = malloc((i + 2) * sizeof(char));
	j = -1;
	while (++j < i + 1)
		res[0][j] = buff[j];
	res[0][j] = 0;
	res[1] = NULL;
	if ((ft_strlen(buff) > 1) && is_line(buff))
	{
		res[1] = malloc(ft_strlen(buff + i + 1) + 1);
		j--;
		while (buff[++j])
			res[1][j - i - 1] = buff[j];
		res[1][j - i - 1] = 0;
	}
	return (res);
}
