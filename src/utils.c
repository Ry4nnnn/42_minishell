/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:31:42 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 21:37:56 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//get env value by inputing key from envp
// returns NULL if could find any
char	*get_env(t_mini *mini, char *key)
{
	t_list	*envp;
	t_env	*env_var;

	envp = mini->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(key, env_var->key) == 0)
			return (env_var->value);
		envp = envp->next;
	}
	return (NULL);
}

//adding variable to envp
void	add_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (env_var == NULL)
		return ;
	env_var->key = key;
	env_var->value = value;
	ft_lstadd_back(&mini->envp, ft_lstnew(env_var));
}

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
