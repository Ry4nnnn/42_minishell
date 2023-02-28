/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:45:39 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/04 15:59:02 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	i = ft_strlen(dst);
	j = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (dstsize <= ft_strlen(dst))
		return (src_len + dstsize);
	while (src[j] != 0 && i < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (dest_len + src_len);
}
