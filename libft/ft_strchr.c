/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:38:26 by welim             #+#    #+#             */
/*   Updated: 2023/02/16 15:54:57 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//finds (c) in a string (s) 
//and return the remaining string after it (including (c))
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
