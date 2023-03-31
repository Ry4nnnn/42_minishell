/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 06:25:51 by welim             #+#    #+#             */
/*   Updated: 2023/03/31 08:08:18 by welim            ###   ########.fr       */
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

void	redir_out(t_mini *mini, char *file, int type)
{
	int		flags;

	if (type == OUT)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	if (type == APPEND)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	if (mini->fd_out == -1)
		close (mini->fd_out);
	mini->fd_out = ms_open(file, flags, 0644);
	handle_io(mini->fd_out, STDOUT_FILENO);
}

void	redir_in(t_mini *mini, t_cmdblock *cmdblock, char *file, int type)
{
	if (type == IN)
	{
		mini->fd_in = ms_open(file, O_RDONLY, 0644);
		handle_io(mini->fd_in, STDIN_FILENO);
	}
	if (type == HEREDOC)
	{
		done_redir(mini);
		pipe(mini->pipes.h_pipe);
		cmdblock->h_pid = fork();
		if (cmdblock->h_pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			mini->fd_in = heredoc(mini, cmdblock);
			exit(0);
		}
		waitpid(cmdblock->h_pid, NULL, 0);
		dup2(mini->pipes.h_pipe[READ], STDIN_FILENO);
		close(mini->pipes.h_pipe[WRITE]);
	}
}

static int	select_and_exec(t_mini *mini, t_cmdblock *cmdblock, char *cmd_argv)
{
	if (ft_strcmp(cmd_argv, S_OUT) == 0)
		redir_out(mini, cmdblock->outfile, OUT);
	if (ft_strcmp(cmd_argv, S_APPEND) == 0)
		redir_out(mini, cmdblock->outfile, APPEND);
	if (ft_strcmp(cmd_argv, S_IN) == 0)
		redir_in(mini, cmdblock, cmdblock->infile, IN);
	if (ft_strcmp(cmd_argv, S_HEREDOC) == 0)
		redir_in(mini, cmdblock, cmdblock->infile, HEREDOC);
	return (0);
}

int	exec_redir(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;
	int		option;

	i = 0;
	option = 0;
	cmdblock->infile = NULL;
	cmdblock->outfile = NULL;
	if (check_for_redir(mini, cmdblock->cmd_argv[0]) == SUCCESS)
		option = 1;
	while (cmdblock->cmd_argv[i] != NULL)
	{
		if (option == 1)
			get_iofile(mini, cmdblock, i);
		else
			get_iofile(mini, cmdblock, i + 1);
		select_and_exec(mini, cmdblock, cmdblock->cmd_argv[i]);
		i++;
	}
	if (option == 1)
		return (1);
	return (SUCCESS);
}
