/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:31:52 by welim             #+#    #+#             */
/*   Updated: 2023/03/22 18:04:55 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Identifier error
 * Output the command and the identifier of the ith argument, and the err_msg
 * All error messages are outputed to the STDERR stream.
 * 
 * @param mini 
 * @param cmds 
 * @param i 
 * @param msg 
 */
void	identifier_error(t_mini *mini, char **cmds, int i, char *msg)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	printf(YELLOW"%s: \033[0m%s: `%s': %s", user, cmds[0], cmds[i], msg);
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

/**
 * @brief Command error with argument
 * Output the command and its first argument, and the error message.
 * All error messages are outputed to the STDERR stream.
 * 
 * @param mini 
 * @param cmds 
 * @param msg 
 */
void	cmd_arg_error(t_mini *mini, char **cmds, char *msg)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	printf(YELLOW"%s: \033[0m%s: %s: %s", user, cmds[0], cmds[1], msg);
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

/**
 * @brief Command error
 * Output just the command and the error message. 
 * All error messages are outputed to the STDERR stream.
 * 
 * @param mini 
 * @param cmds 
 * @param msg 
 */
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
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

/**
 * @brief Output syntax error message with or without unexpected token
 * All error messages are outputed to the STDERR stream.
 * 
 * @param mini 
 * @param err_msg 
 * @param token 
 * @return int 
 */
int	syntax_error(t_mini *mini, char *err_msg, char *token)
{
	char	*user;

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
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	g_errno = 258;
	return (0);
}
