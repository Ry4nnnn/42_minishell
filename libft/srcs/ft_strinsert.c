/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:44:47 by codespace         #+#    #+#             */
/*   Updated: 2023/03/06 13:45:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *s, char *insert, int start)
{
	char	*result;
	int		len;
	int		insert_len;
	int		i;

	if (insert == NULL)
		return (s);
	if (start > (int)ft_strlen(s) || start < 0)
		return (NULL);
	insert_len = ft_strlen(insert);
	len = ft_strlen(s) + insert_len;
	result = malloc((len + 1) * sizeof(char));
	i = -1;
	while (++i < start)
		result[i] = s[i];
	while (++i - start - 1 < insert_len)
		result[i - 1] = insert[i - 1 - start];
	while (++i - 2 < len)
		result[i - 2] = s[i - 2 - insert_len];
	result[i - 2] = 0;
	return (result);
}
