/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:32:39 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/03 19:40:41 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Init the default pipe values
 * 
 * @param mini 
 */
void	init_pipe(t_mini *mini)
{
	mini->pipes.do_pipe = 0;
	mini->pipes.prep_pipe = 0;
	mini->pipes.saved_stdin = dup(STDIN_FILENO);
	mini->pipes.saved_stdout = dup(STDOUT_FILENO);
	mini->pipes.temp_read_fd = -1;
	mini->pipes.is_redir_in = 0;
}

/**
 * @brief Prepare the pipe redirection before every cmdblock is handled
 * 
 * @param mini 
 */
void	prepare_pipe(t_mini *mini)
{
	pipe(mini->pipes.pipe);
	dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
}

/**
 * @brief Do pipe is called when a non-builtin command is executed
 * It reads the input from the pipe read end instead of STDIN.
 * The temp_read_fd is the read end of the pipe created by
 * the cmdblock at the left of the pipe. The purpose of it is to
 * enable multiple pipes at the same time, so if the current cmdblock
 * is also a cmdblock that is at the left of a pipe, it can preserve the
 * previous pipe read end and at the same time pipe for its own use.
 * The -1 checking is not to dup a fd that is not initialized, technically it
 * won't happend but just for safety
 * 
 * @param mini 
 */
void	do_pipe(t_mini *mini)
{
	close(mini->pipes.pipe[WRITE]);
	if (mini->pipes.temp_read_fd != -1 && !mini->pipes.is_redir_in)
		dup2(mini->pipes.temp_read_fd, STDIN_FILENO);
}

/**
 * @brief Close the pipe write end, and the temp_read_fd if the current
 * cmdblock was reading input from it. Restore the do_pipe and prep_pipe value,
 * and reassign the temp_read_fd to the pipe read end for the next cmdblock use
 * Finally dup back the STDOUT and STDIN streams
 * 
 * @param mini 
 */
void	finish_pipe(t_mini *mini)
{
	if (mini->pipes.prep_pipe)
		close(mini->pipes.pipe[WRITE]);
	if (mini->pipes.temp_read_fd != -1)
		close(mini->pipes.temp_read_fd);
	mini->pipes.do_pipe = 0;
	mini->pipes.prep_pipe = 0;
	mini->pipes.temp_read_fd = mini->pipes.pipe[READ];
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	dup2(mini->pipes.saved_stdin, STDIN_FILENO);
}

void	handle_io(int fd, int std_file_no)
{
	dup2(fd, std_file_no);
	close(fd);
}
