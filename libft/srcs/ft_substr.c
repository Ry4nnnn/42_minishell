/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:09:42 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/05 11:22:24 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if (s_len <= start)
		substr = malloc(1 * sizeof(char));
	else if (s_len - start > len)
		substr = malloc((len + 1) * sizeof(char));
	else
		substr = malloc((s_len - start + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (start < s_len && i < len)
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	substr[i] = 0;
	return (substr);
}
