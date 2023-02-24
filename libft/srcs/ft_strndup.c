/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:09:18 by wxuerui           #+#    #+#             */
/*   Updated: 2023/02/24 19:23:15 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*res;
	int		i;

	if (str == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (n + 1));
	i = -1;
	while (++i < n)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}
