/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:23:41 by welim             #+#    #+#             */
/*   Updated: 2023/03/14 16:39:02 by welim            ###   ########.fr       */
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
int	exec_builtins(t_mini *mini, char **cmds, t_cmdblock *cmdblock)
{
	int fd_out;
	int fd_in;

	fd_out = dup(1);
	fd_in = dup(0);
	if (mini->pipes.prep_pipe)
		prepare_pipe(mini);
	if (check_redir_type(mini, cmdblock) == OUT || check_redir_type(mini, cmdblock) == APPEND)
		redir_out(mini, cmdblock); // overwrite the standard output
	if (check_redir_type(mini, cmdblock) == IN)
		redir_in(cmdblock);
	if (ft_strncmp(cmds[0], "exit", 5) == 0)
		ms_exit(mini);
	else if (ft_strncmp(cmds[0], "env", 4) == 0)
		ms_env(mini);
	else if (ft_strncmp(cmds[0], "pwd", 4) == 0)
		ms_pwd();
	else if (ft_strncmp(cmds[0], "unset", 6) == 0)
		ms_unset(mini, cmds);
	else if (ft_strncmp(cmds[0], "export", 7) == 0)
		ms_export(mini, cmds);
	else if (ft_strncmp(cmds[0], "cd", 3) == 0)
		ms_cd(mini, cmds);
	else if (ft_strncmp(cmds[0], "echo", 5) == 0)
		ms_echo(cmds);
	else
		g_errno = 1;
	dup2(fd_out, 1);// change fd back to std output fd
	close(fd_out);
	dup2(fd_in, 0);// change fd back to std input fd
	close(fd_in);
	if (mini->pipes.prep_pipe)
		finish_pipe(mini);
	return (0);
}
