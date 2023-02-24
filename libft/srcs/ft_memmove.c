/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:00:22 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/04 15:31:48 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dest;
	unsigned const char	*str;

	i = -1;
	dest = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (dst < src)
		while (++i < len)
			*(unsigned char *)(dest + i) = *(unsigned char *)(str + i);
	else if (dst > src)
		while (len-- > 0)
			*(unsigned char *)(dest + len) = *(unsigned char *)(str + len);
	return (dest);
}
