/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:18 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 23:22:47 by wangxuerui       ###   ########.fr       */
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

void	free_cmdblock(void *arg)
{
	t_cmdblock	*cmdblock;

	if (arg == NULL)
		return ;
	cmdblock = (t_cmdblock *)arg;
	free(cmdblock->input);
	free(cmdblock);
}

void	ms_free(t_mini *mini)
{
	free(mini->input);
	free(mini->prompt);
}
