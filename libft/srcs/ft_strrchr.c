/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:53:21 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/04 17:21:21 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	c %= 256;
	if (c == 0)
		return ((char *)s + ft_strlen((char *)s));
	while (s[i])
		i++;
	while (--i >= 0)
		if (s[i] == c)
			return ((char *)s + i);
	return (NULL);
}
