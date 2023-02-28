/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:12 by welim             #+#    #+#             */
/*   Updated: 2023/02/28 21:03:10 by welim            ###   ########.fr       */
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

void	del_envx_var(t_mini *ms, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;

	curr = ms->envx;
	if (curr->content == env)
	{
		ms->envx = curr->next;
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

// freeing shit that is not malloced
void	ft_unset(t_mini *mini, char **key)
{
	t_env	*envp;
	t_env	*envx;
	int	i;

	i = 1;
	if (key[i] == NULL)
		return ;
	while (key[i] != NULL)
	{
		if (valid_input(key[i]) == 0)
		{
			printf("unset: `%s': not a valid identifier\n", key[i]);
		}
		envp = check_env_var(mini->envp, key[i]);
		envx = check_env_var(mini->envx, key[i]);
		if (!envp && !envx)//if key does not exits in both
		{
			printf ("0\n");
			i++;
			continue;
		}
		else if (!envp)//if key does not exits in env
		{
			printf ("1\n");
			del_envx_var(mini, envx);
		}
		else if (!envx)//if key does not exits in env
		{
			printf ("2\n");
			del_env_var(mini, envp);
		}
		else // both env and envx has key
		{
			printf ("3\n");
			del_env_var(mini, envp);// both freeing something
			del_envx_var(mini, envx);// causing double free
		}
		i++;
	}
}