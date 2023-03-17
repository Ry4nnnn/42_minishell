/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:31:42 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 22:47:34 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_childs(t_list *cmdblocks)
{
	t_cmdblock	*curr;

	while (cmdblocks != NULL)
	{
		curr = (t_cmdblock *)cmdblocks->content;
		if (curr->need_wait)
		{
			waitpid(curr->pid, &curr->estatus, WUNTRACED);
			if (WIFEXITED((curr->estatus)))
				curr->exit_status = WEXITSTATUS((curr->estatus));
			if (WIFSIGNALED(curr->estatus))
				curr->exit_status = WTERMSIG(curr->estatus) + 128;
		}
		cmdblocks = cmdblocks->next;
	}
}
