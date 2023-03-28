/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 06:25:51 by welim             #+#    #+#             */
/*   Updated: 2023/03/28 15:09:44 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	done_redir(t_mini *mini)
{
	// DEV remove this
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	if (mini->pipes.do_pipe)
		dup2(mini->pipes.pipe[READ], STDIN_FILENO);
	else
		dup2(mini->pipes.saved_stdin, STDIN_FILENO);
}

void	redir_out(t_mini *mini, char* file, int type)
{
	int flags;
	if (type == OUT)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	if (type == APPEND)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	if (mini->fd_out == -1)
		close (mini->fd_out);
	mini->fd_out = ms_open(file, flags, 0644);
	handle_io(mini->fd_out, STDOUT_FILENO);
}

void	redir_in(t_mini *mini, t_cmdblock *cmdblock, char* file, int type)
{
	if (type == IN)
	{
		if (mini->fd_in == -1)
			close (mini->fd_in);
		mini->fd_in = ms_open(file, O_RDONLY, 0644);
		handle_io(mini->fd_in, STDIN_FILENO);
	}
	if (type == HEREDOC)
	{
		if (mini->fd_in == -1)
			close (mini->fd_in);
		done_redir(mini);
		pipe(mini->pipes.pipe);
		cmdblock->pid = fork();
		if (cmdblock->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
    		signal(SIGQUIT, SIG_DFL);
			mini->fd_in = heredoc(mini, cmdblock);
			exit(0);
		}
		if (mini->pipes.prep_pipe == 0 || cmdblock->was_in_bracket)
			waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
		dup2(mini->pipes.pipe[READ], STDIN_FILENO);
		close(mini->pipes.pipe[WRITE]);
	}
}

int get_iofile(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	if (cmdblock->cmd_argv[i] == NULL)
		return (ERROR);
	if (check_for_redir(mini, cmdblock->cmd_argv[i]) == 0)
	{
		i++;
		cmdblock->file_name = cmdblock->cmd_argv[i];
		while ((cmdblock->cmd_argv[i + 1]) && check_for_redir(mini, cmdblock->cmd_argv[i + 1]) == 1)// there a non redir after a filename
		{
			cmdblock->file_name = cmdblock->cmd_argv[i + 1];
			i++;
		}
	}
	return (SUCCESS);
}

int	exec_redir(t_mini *mini, t_cmdblock *cmdblock)
{
	mini->fd_in = 0;
	mini->fd_out = 0;
	int i = 0;

	if (redir_error(mini, cmdblock) == ERROR)
		return (ERROR);
	while (cmdblock->cmd_argv[i])
	{
		get_iofile(mini, cmdblock, i + 1); // to get the current file name
		if (ft_strcmp(cmdblock->cmd_argv[i], ">") == 0)
			redir_out(mini, cmdblock->file_name, OUT);
		if (ft_strcmp(cmdblock->cmd_argv[i], ">>") == 0)
			redir_out(mini,cmdblock->file_name, APPEND);
		if (ft_strcmp(cmdblock->cmd_argv[i], "<") == 0)
			redir_in(mini, cmdblock, cmdblock->file_name, IN);
		if (ft_strcmp(cmdblock->cmd_argv[i], "<<") == 0)
			redir_in(mini, cmdblock, cmdblock->file_name, HEREDOC);
		i++;
	}
	
	if (mini->fd_out == -1)
		handle_io(mini->fd_out, STDOUT_FILENO);
	if (mini->fd_in == -1)
		handle_io(mini->fd_in, STDIN_FILENO);
	if (mini->fd_out == -1 || mini->fd_in == -1)
		return (ERROR);
	return (SUCCESS);
}
