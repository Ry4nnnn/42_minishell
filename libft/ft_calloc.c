/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:19:20 by welim             #+#    #+#             */
/*   Updated: 2022/04/18 15:47:59 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;

	if (nmemb > 4294967295 || size > 4294967295)
		return (NULL);
	res = malloc(nmemb * size);
	if (!res)
		return (0);
	ft_bzero(res, (nmemb * size));
	return (res);
}
