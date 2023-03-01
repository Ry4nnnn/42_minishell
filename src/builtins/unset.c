/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:12 by welim             #+#    #+#             */
/*   Updated: 2023/03/01 21:24:02 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env_var(t_mini *ms, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;

	curr = ms->envp;
	if (curr->content == env)
	{
		ms->envp = curr->next;
		clear_env_var(env);
		free(curr);
		return ;
	}
	while (curr->next != NULL)
	{
		if (curr->next->content == env)
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			clear_env_var(env);
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
}

// delete var from linked list
void	ft_unset(t_mini *mini, char **key)
{
	t_env	*envp;
	int	i;

	i = 1;
	if (key[i] == NULL)
		return ;
	while (key[i] != NULL)
	{
		if (valid_input(key[i]) == 0)
			printf("unset: `%s': not a valid identifier\n", key[i]);
		envp = check_env_var(mini->envp, key[i]);
		if (!envp)//if key does not exits in both
		{
			i++;
			continue;
		}
		else // deleting node
			del_env_var(mini, envp);
		i++;
	}
}
