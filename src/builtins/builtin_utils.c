/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:06:05 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 16:26:42 by wangxuerui       ###   ########.fr       */
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
	t_env	*temp_env;

	while (env != NULL)
	{
		temp_env = env->content;
		if (ft_strcmp(key, temp_env->key) == 0)
			return (temp_env);
		env = env->next;
	}
	return (NULL);
}
