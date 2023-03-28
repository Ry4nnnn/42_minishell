/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:49:06 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/28 17:59:48 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief builtin command cd
 * 
 * @param input each token
 * @return int
 */
static int	is_option(char *input)
{
	int		i;

	i = 1;
	if (input[0] != '-')
		return (0);
	while (input[i] == 'n')
		i++;
	if (input[i] == '\0')
		return (i);
	return (0);
}

/**
 * @brief builtin command echo
 * echo with -n flag does not print a newline (`\n') character
 * echo will stop printing on it sees a redir
 *
 * @param mini struct
 * @param input 2d array of the command input
 * @return int
 */
int	ms_echo(t_mini *mini, char **input)
{
	int		i;
	int		option;

	i = 1;
	option = 0;
	if (input[i] == NULL)
		return (printf("\n"));
	while (input[i] != NULL && is_option(input[i]) > 1)
	{
		option = 1;
		i++;
	}
	while (input[i] != NULL)
	{
		if (check_for_redir(mini, input[i]) == 0)
			break ;
		write (1, input[i], ft_strlen(input[i]));
		if (input[i] != NULL)
			write (1, " ", 1);
		i++;
	}
	if (option == 0)
		write(1, "\n", 1);
	return (0);
}
