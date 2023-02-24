/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:41:37 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/05 13:43:28 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_start(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen((char *)s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

size_t	get_end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen((char *)s1);
	while (i > 0)
	{
		if (ft_strchr(set, s1[i - 1]) == 0)
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*temp;

	if (!s1 || !set)
		return (NULL);
	start = get_start(s1, set);
	end = get_end(s1, set);
	if (start >= end)
	{
		temp = malloc(1 * sizeof(char));
		temp[0] = 0;
		return (temp);
	}
	temp = malloc((end - start + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, s1 + start, end - start + 1);
	return (temp);
}
