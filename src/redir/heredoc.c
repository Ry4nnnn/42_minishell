/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:39:01 by welim             #+#    #+#             */
/*   Updated: 2023/04/06 22:49:07 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal_handler(int signo)
{
	(void)signo;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit(SIGINT);
}

/**
 * @brief execute heredoc
 * 
 * @param mini struct
 * @param cmdblock struct
 * 
 * @return int
 */
int	heredoc(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*rl;
	char	*delimiter;

	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	rl = readline("> ");
	expand_input(mini, &rl);
	dup2(mini->pipes.h_pipe[WRITE], STDOUT_FILENO);
	delimiter = cmdblock->infile;
	while (rl && ft_strncmp(rl, delimiter, ft_strlen(delimiter) + 1))
	{
		write(mini->pipes.h_pipe[WRITE], rl, ft_strlen(rl));
		write(mini->pipes.h_pipe[WRITE], "\n", 1);
		free(rl);
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
		rl = readline("> ");
		if (rl == NULL)
		{
			// ft_putchar_fd('\b', STDOUT_FILENO);
		}
		expand_input(mini, &rl);
		dup2(mini->pipes.h_pipe[WRITE], STDOUT_FILENO);
	}
	free(rl);
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	close(mini->pipes.h_pipe[WRITE]);
	return (mini->pipes.h_pipe[READ]);
}
