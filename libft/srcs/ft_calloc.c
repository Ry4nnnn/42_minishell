/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 09:47:41 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/05 10:35:14 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;
	size_t	i;

	if (size == SIZE_MAX || count == SIZE_MAX)
		return (NULL);
	temp = malloc(count * size);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		*(unsigned char *)(temp + i) = 0;
		i++;
	}
	return (temp);
}
