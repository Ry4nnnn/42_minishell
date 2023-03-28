/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:12 by welim             #+#    #+#             */
/*   Updated: 2023/03/28 18:17:19 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Deletes variable from the (linked-list)envp
 * 
 * @param mini sturct
 * @param env linked list
 * @return void
 */
static void	rm_env_var(t_mini *mini, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;

	if (mini->pipes.do_pipe || mini->pipes.prep_pipe)
		return ;
	curr = mini->envp;
	if (curr->content == env)
	{
		mini->envp = curr->next;
		ft_lstdelone(curr, clear_env_var);
		return ;
	}
	while (curr->next != NULL)
	{
		if (curr->next->content == env)
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			ft_lstdelone(tmp, clear_env_var);
			return ;
		}
		curr = curr->next;
	}
}

/**
 * @brief Builtin command unset
 * unset env var, if invalid identifier then output error
 * unset _ : should do nothing
 * 
 * @param mini 
 * @param cmd_argv 
 * @return void
 */
void	ms_unset(t_mini *mini, char **cmd_argv)
{
	t_env	*envp;
	int		i;

	i = 0;
	if (cmd_argv[1] == NULL)
		return ;
	while (cmd_argv[++i] != NULL)
	{
		envp = check_env_var(mini->envp, cmd_argv[i]);
		if (ft_strcmp(cmd_argv[i], "_") == 0)
			continue ;
		if (valid_input(cmd_argv[i]))
		{
			envp = check_env_var(mini->envp, cmd_argv[i]);
			if (envp != NULL)
				rm_env_var(mini, envp);
		}
		else
			identifier_error(mini, cmd_argv, i, INVALID_IDENTIFIER);
	}
}
