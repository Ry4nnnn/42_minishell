/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:18 by welim             #+#    #+#             */
/*   Updated: 2023/03/18 17:09:39 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function for freeing an env_var, used in ft_lstdelone(), in ms_unset.
 * 
 * @param content 
 */
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

/**
 * @brief Function for freeing a cmdblock, used in ft_lstclear()
 * 
 * @param arg 
 */
void	free_cmdblock(void *arg)
{
	t_cmdblock	*cmdblock;

	if (arg == NULL)
		return ;
	cmdblock = (t_cmdblock *)arg;
	free(cmdblock->input);
	free(cmdblock);
}

/**
 * @brief Free the user input and prompt string.
 * 
 * @param mini 
 */
void	ms_free(t_mini *mini)
{
	free(mini->input);
	free(mini->prompt);
	ft_lstclear(&mini->cmdblock_list, free_cmdblock);
}
