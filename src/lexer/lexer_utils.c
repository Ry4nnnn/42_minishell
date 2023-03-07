/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:58:16 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/07 14:32:09 by wxuerui          ###   ########.fr       */
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

void	ft_strremove(char **s, int start, int n)
{
	char	*result;
	int		len;
	int		i;

	if (start > (int)ft_strlen(*s) || start < 0 || n < 0)
		return ;
	if (n > (int)ft_strlen(*s + start))
		n = ft_strlen(*s + start);
	len = ft_strlen(*s) - n;
	result = malloc((len + 1) * sizeof(char));
	result[len] = 0;
	i = -1;
	while (++i < start)
		result[i] = (*s)[i];
	i += n;
	while (i - start < len)
	{
		result[i - start] = (*s)[i];
		i++;
	}
	result[i - start] = 0;
	free(*s);
	*s = result;
}

void	ft_strexpand(char **s, char *insert, int start, int n)
{
	char	*result;
	int		len;
	int		insert_len;
	int		i;

	if (start > (int)ft_strlen(*s) || start < 0 || n < 0)
		return ;
	if (n > (int)ft_strlen(*s + start))
		n = ft_strlen(*s + start);
	insert_len = ft_strlen(insert);
	len = ft_strlen(*s) + insert_len - n;
	result = malloc((len + 1) * sizeof(char));
	result[len] = 0;
	i = -1;
	while (++i < start)
		result[i] = (*s)[i];
	while (++i - start - 1 < insert_len)
		result[i - 1] = insert[i - 1 - start];
	i += n;
	while (++i - 2 - n < len)
		result[i - 2 - n] = (*s)[i - 2 - insert_len];
	free(*s);
	*s = result;
}
