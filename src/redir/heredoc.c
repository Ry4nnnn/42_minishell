/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:39:01 by welim             #+#    #+#             */
/*   Updated: 2023/03/29 16:51:23 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*rl;
	char	*delimiter;

	rl = readline("> ");
	delimiter = cmdblock->infile;
	while (rl && ft_strncmp(rl, delimiter, ft_strlen(delimiter) + 1))
	{
		write(mini->pipes.pipe[WRITE], rl, ft_strlen(rl));
		write(mini->pipes.pipe[WRITE], "\n", 1);
		free(rl);
		rl = readline("> ");
	}
	free(rl);
	close(mini->pipes.pipe[WRITE]);
	return (mini->pipes.pipe[READ]);
}
