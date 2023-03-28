/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:54:10 by welim             #+#    #+#             */
/*   Updated: 2023/03/28 16:05:34 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (cmdblock->cmd_argv[i + 1] == NULL)
// theres redir at the end of the token
//
// if (check_for_redir(mini, cmdblock->cmd_argv[i + 1]) == 0)
// theres a redir after a redir
static int	check_redir_error(t_mini *mini, char *cmd_argv)
{
	char	*token;

	if (cmd_argv == NULL)
	{
		token = ft_strdup("newline");
		syntax_error(mini, UNEXPECTED_TOKEN, token);
		return (ERROR);
	}
	if (check_for_redir(mini, cmd_argv) == 0)
	{
		token = ft_strdup(cmd_argv);
		syntax_error(mini, UNEXPECTED_TOKEN, token);
		return (ERROR);
	}
	return (SUCCESS);
}

// to check if input ends with a redir
// if true it prints error msg
int	redir_error(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;
	int		j;

	i = 0;
	while (cmdblock->cmd_argv[i])
	{
		j = 0;
		while (mini->redir[j])
		{
			if (ft_strcmp(cmdblock->cmd_argv[i], mini->redir[j]) == 0)
			{
				if (check_redir_error(mini, cmdblock->cmd_argv[i + 1]) == ERROR)
					return (ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
