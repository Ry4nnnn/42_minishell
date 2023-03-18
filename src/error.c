/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:31:52 by welim             #+#    #+#             */
/*   Updated: 2023/03/18 14:26:36 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	identifier_error(t_mini *mini, char **cmds, int i, char *msg)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	printf(YELLOW"%s: \033[0m%s: `%s': %s", user, cmds[0], cmds[i], msg);
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

void	cmd_arg_error(t_mini *mini, char **cmds, char *msg)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	printf(YELLOW"%s: \033[0m%s: %s: %s", user, cmds[0], cmds[1], msg);
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

void	cmd_error(t_mini *mini, char **cmds, char *msg)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	if (cmds != NULL)
		printf(YELLOW"%s: \033[0m%s: %s", user, cmds[0], msg);
	else
		printf(YELLOW"%s: \033[0m: %s", user, msg);
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

int	syntax_error(t_mini *mini, char *err_msg, char *token)
{
	char	*user;

	if (token == NULL)
		return (1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	if (token != NULL)
	{
		printf(YELLOW"%s:\033[0m %s `%s'\n", user, err_msg, token);
		free(token);
	}
	else
		printf(YELLOW"%s:\033[0m %s\n", user, err_msg);
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	g_errno = 258;
	return (0);
}
