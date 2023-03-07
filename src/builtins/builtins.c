/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:23:41 by welim             #+#    #+#             */
/*   Updated: 2023/03/07 16:24:35 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if cmds is a builtin
// returns 1 means its a builtin
//returns 0 means its not a builtin
int	check_builtins(t_mini *mini, char *cmds)
{
	char **builtins;

	builtins = mini->builtins;
	if (cmds == NULL)
		return (0);
	while (*builtins != NULL)
	{
		if (ft_strcmp(*builtins, cmds) == 0)
			return (1);
		builtins++;
	}
	return (0);
}

//this function is to execute the builtins
int	exec_builtins(t_mini *mini, char **cmds)
{
	if (ft_strncmp(cmds[0], "exit", 5) == 0)
		ft_exit(mini);
	else if (ft_strncmp(cmds[0], "env", 4) == 0)
		ft_env(mini);
	else if (ft_strncmp(cmds[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmds[0], "unset", 6) == 0)
		ft_unset(mini, cmds);
	else if (ft_strncmp(cmds[0], "export", 7) == 0)
		ft_export(mini, cmds);
	else if (ft_strncmp(cmds[0], "cd", 3) == 0)
		ft_cd(mini);
	else if (ft_strncmp(cmds[0], "echo", 5) == 0)
		ft_echo(cmds);
	else
		g_errno = 1;
	return (0);
}
