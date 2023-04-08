/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:01:14 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/04/08 17:01:33 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**insert_arr_to_2darr(char **insert, char **arr, int *index)
{
	char	**new;
	int		i;

	if (ft_2darrlen((void *)insert) == 1)
	{
		ft_free2darr((void **)insert);
		return (arr);
	}
	new = malloc(sizeof(char *)
			* (ft_2darrlen((void **)arr) + ft_2darrlen((void **)insert)));
	i = -1;
	while (++i < *index)
		new[i] = arr[i];
	i--;
	while (++i < *index + ft_2darrlen((void **)insert))
		new[i] = insert[i - *index];
	new[i] = NULL;
	free(arr[*index]);
	*index += ft_2darrlen((void **)insert) - 1;
	free(insert);
	free(arr);
	return (new);
}

/**
 * @brief Similar to handle_cmdblocks,
 * But doesn't do pipes, since the whole cmdblocks_list
 * is treated as a single command
 * 
 * @param mini 
 * @param cmdblocks_list 
 * @return int 
 */
int	handle_bracket_cmdblock(t_mini *mini, t_list *cmdblocks_list)
{
	pid_t		pid;
	int			estatus;

	pid = fork();
	if (pid == 0)
		exit(handle_cmdblocks(mini, cmdblocks_list));
	waitpid(pid, &estatus, 0);
	ft_lstclear(&cmdblocks_list, free_cmdblock);
	return (WEXITSTATUS(estatus));
}

/**
 * @brief Handle an individual cmdblock
 * 
 * @param mini 
 * @param prev_cmdblock 
 * @param cmdblock 
 * @return int 
 */
int	handle_cmdblock(t_mini *mini, t_cmdblock *cmdblock)
{
	int	i;

	if (cmdblock->in_bracket)
		return (handle_bracket_cmdblock(mini,
				split_cmdblocks(cmdblock->input, 1)));
	cmdblock->cmd_argv = tokenize_cmd(mini, cmdblock->input);
	i = -1;
	while (cmdblock->cmd_argv[++i] != NULL)
	{
		if (expand_input(mini, &cmdblock->cmd_argv[i]) != 0)
			cmdblock->cmd_argv = insert_arr_to_2darr(
					tokenize_cmd(mini, cmdblock->cmd_argv[i]),
					cmdblock->cmd_argv, &i);
	}
	cmdblock->exit_status = executor(mini, cmdblock);
	done_redir(mini, 0);
	g_errno = cmdblock->exit_status;
	ft_free2darr((void **)cmdblock->cmd_argv);
	mini->pipes.is_redir_in = 0;
	return (cmdblock->exit_status);
}

/**
 * @brief Handle the cmdblock in the cmdblocks_list one by one
 * First of all check syntax error, if invalid syntax then return 258.
 * Loop through the linked list, first prepare handling (pipes),
 * then handle the cmdblock if should_execute, assign the correct exit_status,
 * lastly wrap up by finish_pipe.
 * After all wait for the child processes and return the overall exit status.
 * 
 * @param mini 
 * @param cmdblocks_list 
 * @return int 
 */
int	handle_cmdblocks(t_mini *mini, t_list *cmdblocks_list)
{
	t_list		*temp;
	t_cmdblock	*prev_cmdblock;
	t_cmdblock	*cmdblock;

	temp = cmdblocks_list;
	prev_cmdblock = NULL;
	if (check_syntax(mini, cmdblocks_list) == 0)
		return (258);
	while (temp != NULL)
	{
		cmdblock = (t_cmdblock *)temp->content;
		prepare_handling(mini, temp, cmdblock);
		if (should_execute(prev_cmdblock, cmdblock))
			cmdblock->exit_status = handle_cmdblock(mini, cmdblock);
		else
			cmdblock->exit_status = 0;
		if (mini->pipes.do_pipe || mini->pipes.prep_pipe)
			finish_pipe(mini);
		prev_cmdblock = cmdblock;
		temp = temp->next;
	}
	wait_childs(cmdblocks_list);
	return (get_exit_status(cmdblocks_list));
}
