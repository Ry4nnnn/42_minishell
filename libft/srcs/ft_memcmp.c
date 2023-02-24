/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:35:56 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/04 17:47:22 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	size_t	cmp;

	i = 0;
	cmp = 0;
	while (!cmp && i < n)
	{
		cmp = *(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i);
		i++;
	}
	return ((int)cmp);
}
