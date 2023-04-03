/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:06:53 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/04/03 19:40:50 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the overall exit status of a cmdblock_list
 * 1. If there is a OR logic and successed, return 0.
 * 2. If now is a AND logic and exit_status is 0, namely all previous
 * 		commands are success, then set exit_status to the current exit_status.
 * 3. Else, like PIPE or the opposite case of 1 and 2, set exit_status to
 * 		the current one (the latest one).
 * 
 * @param cmdblock_list 
 * @return int 
 */
int	get_exit_status(t_list *cmdblock_list)
{
	t_cmdblock	*cmdblock;
	int			exit_status;

	exit_status = 0;
	while (cmdblock_list != NULL)
	{
		cmdblock = (t_cmdblock *)cmdblock_list->content;
		if (cmdblock->spliter_type == OR && cmdblock->exit_status == 0)
			return (0);
		else if (cmdblock->spliter_type == AND)
		{
			if ((cmdblock->exit_status == 0 && exit_status == 0)
				|| (cmdblock->exit_status != 0))
				exit_status = cmdblock->exit_status;
		}
		else
			exit_status = cmdblock->exit_status;
		cmdblock_list = cmdblock_list->next;
	}
	return (exit_status);
}

/**
 * @brief Prepare the do_pipe and prep_pipe variables and prepare pipe
 * before handling commands.
 * 
 * Procedures:
 * 1.If current cmdblock is piping (spliter is PIPE), set do_pipe to 1.
 * 2. If the next cmdblock is pipeing (spliter is PIPE), set prep_pipe to 1.
 * 3. If need prep pipe, prepare the pipe.
 * 
 * @param mini 
 * @param curr_node 
 * @param cmdblock 
 */
void	prepare_handling(t_mini *mini, t_list *curr_node, t_cmdblock *cmdblock)
{
	t_cmdblock	*next_cmdblock;

	next_cmdblock = NULL;
	if (curr_node->next != NULL)
		next_cmdblock = (t_cmdblock *)curr_node->next->content;
	if (cmdblock->spliter_type == PIPE)
		mini->pipes.do_pipe = 1;
	if (next_cmdblock != NULL && next_cmdblock->spliter_type == PIPE)
		mini->pipes.prep_pipe = 1;
	if (mini->pipes.prep_pipe)
		prepare_pipe(mini);
}

/**
 * @brief Check if a cmdblock should execute
 * If in a And logic and the previous failed, return 0;
 * Else if in a OR logic and previous command successed, return 0 as well.
 * 
 * @param prev_cmdblock 
 * @param cmdblock 
 * @return int 1 for true 0 for false
 */
int	should_execute(t_cmdblock *prev_cmdblock, t_cmdblock *cmdblock)
{
	if (prev_cmdblock != NULL)
	{
		if (cmdblock->spliter_type == AND && prev_cmdblock->exit_status != 0)
			return (0);
		else if (cmdblock->spliter_type == OR
			&& prev_cmdblock->exit_status == 0)
			return (0);
	}
	return (1);
}
