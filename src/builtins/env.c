/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:06 by welim             #+#    #+#             */
/*   Updated: 2023/03/11 13:40:39 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(t_mini *mini)
{
	t_list	*env_list;
	t_env	*env_node;

	env_list = mini->envp;
	while (env_list != NULL)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->value != NULL)
			printf ("%s=%s\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
	return (0);
}
