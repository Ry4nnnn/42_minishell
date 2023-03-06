/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:58:16 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/06 10:59:45 by wxuerui          ###   ########.fr       */
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