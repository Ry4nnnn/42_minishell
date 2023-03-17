/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:49:06 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/18 02:04:15 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *input)
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

int	ms_echo(char **input)
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
		if (!ft_strncmp(input[i], "<", 2)
			|| !ft_strncmp(input[i], "<<", 3)
			|| !ft_strncmp(input[i], ">", 2)
			|| !ft_strncmp(input[i], ">>", 3))
			break ;
		printf("%s", input[i]);
		if (input[i] != NULL)
			printf(" ");
		i++;
	}
	if (option == 0)
		printf("\n");
	return (0);
}
