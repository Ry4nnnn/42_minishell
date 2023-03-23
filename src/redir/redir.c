/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 06:25:51 by welim             #+#    #+#             */
/*   Updated: 2023/03/23 15:34:34 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	redir_in(t_mini *mini, t_cmdblock *cmdblock, char* file, int type, int i)
{
	if (type == IN)
	{
		if (mini->fd_out == -1)
			close (mini->fd_in);
		mini->fd_in = ms_open(file, O_RDONLY, 0644);
	}
	if (type == HEREDOC)
	{
		if (mini->fd_out == -1)
			close (mini->fd_in);
		mini->fd_in = heredoc(mini, cmdblock, i);
	}
	handle_io(mini->fd_in, STDIN_FILENO);
}

//check in the str is a redir
// return 0 if true 
int check_for_redir(t_mini *mini, char *str)
{
	int i;

	i = 0;
	while (mini->redir[i])
	{
		if (ft_strcmp(str, mini->redir[i]) == 0)
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

int get_iofile(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	char *err_token;

	// printf ("argv:%s\n", cmdblock->cmd_argv[i]);
	if (check_for_redir(mini, cmdblock->cmd_argv[i]) == 0)
	{
		i += 1;
		if (check_for_redir(mini, cmdblock->cmd_argv[i]) == 0) // theres a redir after a redir
		{
			err_token = ft_strdup(cmdblock->cmd_argv[i]);
			syntax_error(mini, UNEXPECTED_TOKEN, err_token);
			return (ERROR);
		}
		else
			cmdblock->file_name = cmdblock->cmd_argv[i];
	}
	return (SUCCESS);
}

int	exec_redir(t_mini *mini, t_cmdblock *cmdblock)
{
	mini->fd_in = 0;
	mini->fd_out = 0;
	int i = 0;
	int	saved_fd;

	if (redir_error(mini, cmdblock) == ERROR)
		return (ERROR);
	while (cmdblock->cmd_argv[i])
	{
		saved_fd = dup(STDIN_FILENO);
		if (get_iofile(mini, cmdblock, i + 1) == ERROR) // to get the current file name
			return (ERROR);
		if (ft_strcmp(cmdblock->cmd_argv[i], ">") == 0)
		{
			redir_out(mini, cmdblock->file_name, OUT);
		}
		if (ft_strcmp(cmdblock->cmd_argv[i], ">>") == 0)
		{
			redir_out(mini,cmdblock->file_name, APPEND);
		}
		if (ft_strcmp(cmdblock->cmd_argv[i], "<") == 0)
		{
			redir_in(mini, cmdblock, cmdblock->file_name, IN, i);
		}
		if (ft_strcmp(cmdblock->cmd_argv[i], "<<") == 0)
		{
			dup2(saved_fd, STDIN_FILENO);
			close(saved_fd);
			write(2, "ABOUT TO LOOP HEREDOC\n", 22);
			redir_in(mini, cmdblock, cmdblock->file_name, HEREDOC, i);
		}
		i++;
	}
	// write(2, "LOOP ENDED\n", 11);
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
