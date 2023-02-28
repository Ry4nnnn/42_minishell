/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:10 by welim             #+#    #+#             */
/*   Updated: 2023/02/28 19:44:17 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this function is to sort and print linked list
void	print_export_x(t_mini *mini)
{
	t_list	*env_list;
	t_env	*env_node;

	sort_env_x(mini);
	env_list = mini->envx;
	while (env_list != NULL)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->value == NULL)
			ft_printf("declare -x %s\n", env_node->key);
		else if (env_node->value[0] == '\0')
			ft_printf("declare -x %s=\"\"\n", env_node->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
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

// (adding \ changing) key and value to envp
void	edit_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*envp;

	envp = check_env_var(mini->envp, key);
	if (envp == NULL) // if key doesnt exist in envp (adding new variable)
	{
		if (value != NULL)
			add_envp_var(mini, key, value);
		else
			free (key);
	}
	else // editing variable (envp != NULL)
	{
		free(envp->value);
		envp->value = value;
		free (key);
	}
}

// (adding \ changing) key and value to envx
void	edit_envx_var(t_mini *mini, char *keyx, char *valuex)
{
	t_env	*envx;

	envx = check_env_var(mini->envx, keyx);
	if (envx == NULL) // if key doesnt exist in envx (adding new variable)
		add_envx_var(mini, keyx, valuex);
	else // editing variable
	{
		free(envx->value);
		envx->value = valuex;
		free(keyx);
	}
}

//if export with no '=' only add to export(envx)
//if export with = add to both export(envx) and env(envp)
void	ft_export(t_mini *mini, char **input)
{
	char	*key;
	char	*value;
	char	*keyx;
	char	*valuex;
	int		i;

	i = 1;
	if (input[i] == NULL) //input only export with no paramters
		print_export_x(mini);
	else
	{
		while (input[i] != NULL)
		{
			get_key_value(input[i], &key, &value);
			get_key_value(input[i], &keyx, &valuex);
			if (valid_input(key) == 0) // invalid input
			{
				printf("export: `%s': not a valid identifier\n", input[i]);
				free (key);
				free (value);
				i++;
				continue ;
			}
			edit_env_var(mini, key, value);
			edit_envx_var(mini, keyx, valuex);
			i++;
		}
	}
}
