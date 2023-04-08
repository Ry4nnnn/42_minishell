/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 06:25:51 by welim             #+#    #+#             */
/*   Updated: 2023/04/08 16:13:53 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	done_redir(t_mini *mini, int heredoc)
{
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	if (mini->pipes.do_pipe && !heredoc)
		dup2(mini->pipes.temp_read_fd, STDIN_FILENO);
	else
		dup2(mini->pipes.saved_stdin, STDIN_FILENO);
}

int	redir_out(t_mini *mini, char *file, int type)
{
	int		flags;

	if (type == OUT)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	if (type == APPEND)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	mini->fd_out = ms_open(mini, file, flags, 0644);
	if (mini->fd_out == -1)
	{
		close (mini->fd_out);
		return (-1);
	}
	handle_io(mini->fd_out, STDOUT_FILENO);
	return (0);
}

int	redir_in(t_mini *mini, t_cmdblock *cmdblock, char *file, int type)
{
	mini->pipes.is_redir_in = 1;
	if (type == IN)
	{
		mini->fd_in = ms_open(mini, file, O_RDONLY, 0644);
		if (mini->fd_in == -1)
			return (-1);
		handle_io(mini->fd_in, STDIN_FILENO);
	}
	if (type == HEREDOC)
	{
		done_redir(mini, 1);
		pipe(mini->pipes.h_pipe);
		cmdblock->h_pid = fork();
		if (cmdblock->h_pid == 0)
			heredoc(mini, cmdblock);
		waitpid(cmdblock->h_pid, &mini->pipes.hd_estatus, 0);
		close(mini->pipes.h_pipe[WRITE]);
		if (WEXITSTATUS(mini->pipes.hd_estatus) == SIGINT)
		{
			close(mini->pipes.h_pipe[READ]);
			return (-1);
		}
		dup2(mini->pipes.h_pipe[READ], STDIN_FILENO);
	}
	return (0);
}

static int	select_and_exec(t_mini *mini, t_cmdblock *cmdblock, char *cmd_argv)
{
	if (ft_strcmp(cmd_argv, S_OUT) == 0)
		return (redir_out(mini, cmdblock->outfile, OUT));
	if (ft_strcmp(cmd_argv, S_APPEND) == 0)
		return (redir_out(mini, cmdblock->outfile, APPEND));
	if (ft_strcmp(cmd_argv, S_IN) == 0)
		return (redir_in(mini, cmdblock, cmdblock->infile, IN));
	if (ft_strcmp(cmd_argv, S_HEREDOC) == 0)
		return (redir_in(mini, cmdblock, cmdblock->infile, HEREDOC));
	return (0);
}

/**
 * @brief execute redirection
 * 
 * @param mini struct
 * @param cmdblock struct
 * 
 * @return int
 */
int	exec_redir(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;
	int		option;

	i = 0;
	option = 0;
	cmdblock->infile = NULL;
	cmdblock->outfile = NULL;
	mini->pipes.is_redir_in = 0;
	if (check_for_redir(mini, cmdblock->cmd_argv[0]) == SUCCESS)
		option = 1;
	while (cmdblock->cmd_argv[i] != NULL)
	{
		if (option == 1)
			get_iofile(mini, cmdblock, i);
		else
			get_iofile(mini, cmdblock, i + 1);
		if (select_and_exec(mini, cmdblock, cmdblock->cmd_argv[i]) == -1)
			return (-1);
		i++;
	}
	return (SUCCESS);
}
