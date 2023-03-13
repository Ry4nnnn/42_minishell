/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:31:52 by welim             #+#    #+#             */
/*   Updated: 2023/03/13 11:21:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//print error for invalid input || non valid commands
void	ft_error(t_mini *mini, char **cmds, char *msg)
{
	char *user;

	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	if (cmds != NULL)
		printf("\033[95m%s: \033[0m%s: %s", user, cmds[0], msg);
	else
		printf("\033[95m%s: \033[0m: %s", user, msg);
}

void	syntax_error(t_mini *mini, char *err_msg, char *token)
{
	char *user;

	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	if (token != NULL)
	{
		printf("\033[95m%s:\033[0m %s `%s'\n", user, err_msg, token);
		free(token);
	}
	else
		printf("\033[95m%s:\033[0m %s\n", user, err_msg);
}