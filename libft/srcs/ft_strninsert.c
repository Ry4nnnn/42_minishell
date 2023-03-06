/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strninsert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:40:00 by codespace         #+#    #+#             */
/*   Updated: 2023/03/06 13:43:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strninsert(char *s, char *insert, int start, int n)
{
	char	*result;
	int		len;
	int		i;

	if (insert == NULL)
		return (s);
	if (start > (int)ft_strlen(s) || start < 0 || n < 0)
		return (NULL);
	if (n > (int)ft_strlen(insert))
		n = ft_strlen(insert);
	len = ft_strlen(s) + n;
	result = malloc((len + 1) * sizeof(char));
	i = -1;
	while (++i < start)
		result[i] = s[i];
	while (++i - start - 1 < n)
		result[i - 1] = insert[i - 1 - start];
	while (++i - 2 < len)
		result[i - 2] = s[i - 2 - n];
	result[i - 2] = 0;
	return (result);
}
