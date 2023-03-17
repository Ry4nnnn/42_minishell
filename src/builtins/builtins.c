/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:23:41 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 15:49:59 by wangxuerui       ###   ########.fr       */
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
int	exec_builtins(t_mini *mini, t_cmdblock *cmdblock)
{
	int	errnum;

	errnum = 0;
	if (mini->pipes.prep_pipe)
		prepare_pipe(mini);
	if (check_redir_type(mini, cmdblock) != 0)
		call_redir(mini, cmdblock);
	if (ft_strncmp(cmdblock->cmd_argv[0], "exit", 5) == 0)
		ms_exit(mini);
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
		errnum = ms_echo(cmdblock->cmd_argv);
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	dup2(mini->pipes.saved_stdin, STDIN_FILENO);
	if (mini->pipes.prep_pipe)
		finish_pipe(mini);
	return (errnum);
}
