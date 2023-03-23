/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 06:25:51 by welim             #+#    #+#             */
/*   Updated: 2023/03/23 11:40:51 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_out(t_mini *mini, t_cmdblock *cmdblock)
{
	int		flags;

	if (check_redir_type(mini, cmdblock) == OUT)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	if (check_redir_type(mini, cmdblock) == APPEND)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	if (mini->fd_out == -1)
		close (mini->fd_out);
	mini->fd_out = ms_open(cmdblock->file_name, flags, 0644);
	handle_io(mini->fd_out, STDOUT_FILENO);
}

void	redir_in(t_mini *mini, t_cmdblock *cmdblock)
{
	if (check_redir_type(mini, cmdblock) == IN)
	{
		if (mini->fd_out == -1)
			close (mini->fd_in);
		mini->fd_in = ms_open(cmdblock->file_name, O_RDONLY, 0644);
	}
	if (check_redir_type(mini, cmdblock) == HEREDOC)
	{
		if (mini->fd_out == -1)
			close (mini->fd_in);
		mini->fd_in = heredoc(mini, cmdblock);
	}
	handle_io(mini->fd_in, STDIN_FILENO);
}

void	done_redir(t_mini *mini)
{
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	if (mini->pipes.do_pipe)
		dup2(mini->pipes.pipe[READ], STDIN_FILENO);
	else
		dup2(mini->pipes.saved_stdin, STDIN_FILENO);
}

int	exec_redir(t_mini *mini, t_cmdblock *cmdblock)
{
	mini->fd_in = 0;
	mini->fd_out = 0;
	int i = 0;

	if (redir_error(mini, cmdblock) == ERROR)
		return (ERROR);
	// while (cmdblock->cmd_argv[i])
	// {
	// 	get_iofile(cmdblock);
	// 	if (ft_strcmp(cmdblock->cmd_argv[i], ">") == 0)
	// 	{
	// 		redir_out(mini, cmdblock->file_name);
	// 	}
	// 	if (ft_strcmp(cmdblock->cmd_argv[i], ">>") == 0)
	// 	{
			
	// 	}
	// 	if (ft_strcmp(cmdblock->cmd_argv[i], "<") == 0)
	// 	{
			
	// 	}
	// 	if (ft_strcmp(cmdblock->cmd_argv[i], "<<") == 0)
	// 	{
			
	// 	}
	// 	i++;
	// }
	if (check_redir_type(mini, cmdblock) == OUT
		|| check_redir_type(mini, cmdblock) == APPEND)
		redir_out(mini, cmdblock);
	if (check_redir_type(mini, cmdblock) == IN
		|| check_redir_type(mini, cmdblock) == HEREDOC)
		redir_in(mini, cmdblock);
	if (mini->fd_out == -1 || mini->fd_in == -1)
		return (ERROR);
	if (mini->fd_out == -1)
	{
		handle_io(mini->fd_out, STDOUT_FILENO);
	}
	if (mini->fd_in == -1)
		handle_io(mini->fd_in, STDIN_FILENO);
	return (SUCCESS);
}
