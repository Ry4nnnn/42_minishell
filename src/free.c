/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:18 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 18:30:59 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env_var(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (env == NULL)
		return ;
	if (env->key != NULL)
		free(env->key);
	if (env->value != NULL)
		free(env->value);
	free(env);
}

// void	ft_free_cmds(t_mini *mini)
// {
// 	char **temp;

// 	temp = mini->cmds;
// 	while (temp && *temp)
// 	{
// 		free(*temp);
// 		temp++;
// 	}
// 	free (mini->cmds);
// }

//type 1 - free mini.cmds
//type 2 - free mini.prompt
//type 3 - free mini.input
//type 4 - free mini.input && mini.prompt
//type 5 - free mini.cmds && mini.input && mini.prompt
void	ft_free(t_mini *mini, int type)
{
	if (type == 2 || type == 4 || type == 5)
		free (mini->prompt);
	if (type == 3 || type == 4 || type == 5)
		free (mini->input);
}
