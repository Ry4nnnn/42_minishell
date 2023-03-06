/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:58:16 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/06 14:01:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_incharset(char *charset, char c)
{
	int	i;

	i = -1;
	while (charset[++i] != '\0')
	{
		if (c == charset[i])
			return (1);
	}
	return (0);
}

char	*ft_strexpand(char *s, char *insert, int start, int n)
{
	char	*result;
	int		len;
	int		insert_len;
	int		i;

	if (insert == NULL)
		return (s);
	if (start > ft_strlen(s) || start < 0 || n < 0)
		return (NULL);
	if (n > (int)ft_strlen(s + start))
		n = ft_strlen(s + start);
	insert_len = ft_strlen(insert);
	len = ft_strlen(s) + insert_len - n;
	result = malloc((len + 1) * sizeof(char));
	i = -1;
	while (++i < start)
		result[i] = s[i];
	while (++i - start - 1 < insert_len)
		result[i - 1] = insert[i - 1 - start];
	i += n;
	while (++i - 2 - n < len)
		result[i - 2 - n] = s[i - 2 - insert_len];
	result[i - 2] = 0;
	return (result);
}
