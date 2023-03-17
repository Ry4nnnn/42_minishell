/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:12 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 18:22:56 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_env_var(t_mini *ms, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;

	curr = ms->envp;
	if (curr->content == env)
	{
		ms->envp = curr->next;
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
 * 
 * @param mini 
 * @param cmd_argv 
 */
void	ms_unset(t_mini *mini, char **cmd_argv)
{
	t_env	*envp;
	int		i;

	i = 0;
	if (cmd_argv[1] == NULL || mini->pipes.do_pipe || mini->pipes.prep_pipe)
		return ;
	while (cmd_argv[++i] != NULL)
	{
		if  (!ft_strcmp(cmd_argv[i], "_")) // ignore unset _
			return ;
		if (valid_input(cmd_argv[i]) == 0)
			printf("unset: `%s': not a valid identifier\n", cmd_argv[i]);
		envp = check_env_var(mini->envp, cmd_argv[i]);
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
