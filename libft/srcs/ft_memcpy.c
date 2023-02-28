/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:49:49 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/04 16:25:54 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	unsigned const char	*str;

	i = -1;
	dest = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (dst < src && dst + n > src)
		return (dst);
	if (dst > src && src + n > dst)
		return (dst);
	if (dst == src)
		return (dst);
	while (++i < n)
		*(unsigned char *)(dest + i) = *(unsigned char *)(str + i);
	return (dest);
}
