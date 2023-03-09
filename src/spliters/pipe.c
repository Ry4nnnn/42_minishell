/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:32:39 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/09 15:30:24 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(t_mini *mini)
{
	mini->pipes.do_pipe = 0;
	mini->pipes.prep_pipe = 0;
	mini->pipes.saved_stdin = dup(STDIN_FILENO);
	mini->pipes.saved_stdout = dup(STDOUT_FILENO);
}

void	prepare_pipe(t_mini *mini)
{
	pipe(mini->pipes.pipe);
	dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	mini->pipes.prep_pipe = 0;
}

void	do_pipe(t_mini *mini)
{
	close(mini->pipes.pipe[WRITE]);
	dup2(mini->pipes.pipe[READ], STDIN_FILENO);
}

void	finish_pipe(t_mini *mini)
{
	close(mini->pipes.pipe[WRITE]);
	mini->pipes.do_pipe = 0;
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	dup2(mini->pipes.saved_stdin, STDIN_FILENO);
}