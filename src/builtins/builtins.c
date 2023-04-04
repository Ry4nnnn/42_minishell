/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:23:41 by welim             #+#    #+#             */
/*   Updated: 2023/04/04 22:48:32 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if param cmds is a builtin
 * compares the string (cmds) with the redir in the struct
 * returns 1 - cmds is a builtin
 * returns 0 - cmds is not a builtin
 * 
 * @param mini struct
 * @param cmds string
 * @return int 
 */
int	check_builtins(t_mini *mini, char *cmds)
{
	char	**builtins;

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

/**
 * @brief Choose the corresponding command and execute
 * 
 * @param mini struct
 * @param cmdblock struct
 * @return int 
 */
static int	choose_and_exec(t_mini *mini, t_cmdblock *cmdblock)
{
	int	errnum;

	errnum = 0;
	if (ft_strncmp(cmdblock->cmd_argv[0], "exit", 5) == 0)
		errnum = ms_exit(mini, cmdblock);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "env", 4) == 0)
		ms_env(mini);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "pwd", 4) == 0)
		ms_pwd();
	else if (ft_strncmp(cmdblock->cmd_argv[0], "unset", 6) == 0)
		ms_unset(mini, cmdblock->cmd_argv);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "export", 7) == 0)
		errnum = ms_export(mini, cmdblock);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "cd", 3) == 0)
		errnum = ms_cd(mini, cmdblock);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "echo", 5) == 0)
		errnum = ms_echo(mini, cmdblock->cmd_argv);
	return (errnum);
}

/**
 * @brief execute builtin functions
 * 
 * @param mini 
 * @param cmdblock 
 * @return int errnum
 */
int	exec_builtins(t_mini *mini, t_cmdblock *cmdblock)
{
	int	errnum;

	errnum = choose_and_exec(mini, cmdblock);
	done_redir(mini, 0);
	return (errnum);
}
