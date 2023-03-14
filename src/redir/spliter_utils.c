/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:13:03 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/14 13:25:33 by codespace        ###   ########.fr       */
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
			{
				printf("%i exited normally\n", (int)curr->pid);
				curr->exit_status = WEXITSTATUS((curr->estatus));
			}
			if (WIFSIGNALED(curr->estatus))
			{
				printf("%i exited abnormally\n", (int)curr->pid);
				curr->exit_status = WTERMSIG(curr->estatus) + 128;
			}
			printf("pid: %i, errno: %i\n", (int)curr->pid, g_errno);
		}
		cmdblocks = cmdblocks->next;
	}
}
