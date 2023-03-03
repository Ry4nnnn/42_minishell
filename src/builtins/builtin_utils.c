/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:06:05 by welim             #+#    #+#             */
/*   Updated: 2023/03/03 11:09:28 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_input(char *key)
{
	if (ft_isalpha(*key) == 0 && *key != '_')
		return (0);
	while (*(++key) != '\0')
	{
		if (ft_isalnum(*key) == 0 && *key != '_')
			return (0);
	}
	return (1);
}

//check env var (key) exist
//loops through the linked list and check if theres (key)
//if no then returns a NULL
//if yes then returns the key pointer form env list
t_env	*check_env_var(t_list *env, char *key)
{
	t_env	*env_list;

	while (env != NULL)
	{
		env_list = env->content;
		if (ft_strcmp(key, env_list->key) == 0)
			return (env_list);
		env = env->next;
	}
	return (NULL);
}
