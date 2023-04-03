/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:34:23 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/03 19:30:26 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print env from smallest to biggest, and add a declare -x in front
 * The inner loop is used to find the current smallest key
 * First assign temp_content to biggest, and gradualy find the smallest
 * 
 * @param smallest 
 * @param biggest 
 * @param envp 
 */
static void	show_export(t_env *smallest, t_env *biggest, t_list *envp)
{
	t_env	*temp_content;
	t_list	*temp;
	int		i;

	i = ft_lstsize(envp);
	temp_content = smallest;
	while (--i >= 0)
	{
		temp = envp;
		printf("declare -x %s", temp_content->key);
		if (temp_content->value == NULL)
			printf("\n");
		else
			printf("=\"%s\"\n", temp_content->value);
		temp_content = biggest;
		while (temp != NULL)
		{
			if (ft_strcmp(((t_env *)temp->content)->key, temp_content->key) < 0
				&& ft_strcmp(((t_env *)temp->content)->key, smallest->key) > 0)
				temp_content = (t_env *)temp->content;
			temp = temp->next;
		}
		smallest = temp_content;
	}
}

/**
 * @brief First find the smallest and biggest key by ascii value,
 * then use show_export function to print out the env
 * 
 * @param mini 
 * @return int 
 */
int	print_export(t_mini *mini)
{
	t_list	*temp;
	t_env	*smallest_content;
	t_env	*biggest_content;

	temp = mini->envp;
	smallest_content = ((t_env *)temp->content);
	biggest_content = ((t_env *)temp->content);
	while (temp != NULL)
	{
		if (ft_strcmp(((t_env *)temp->content)->key, smallest_content->key) < 0)
			smallest_content = (t_env *)temp->content;
		if (ft_strcmp(((t_env *)temp->content)->key, biggest_content->key) > 0)
			biggest_content = (t_env *)temp->content;
		temp = temp->next;
	}
	show_export(smallest_content, biggest_content, mini->envp);
	return (0);
}

// extracting key and value from input
static void	get_key_value(char *arg, char **key, char **value)
{
	*value = ft_strchr(arg, '=');
	if (*value == NULL)
	{
		*key = ft_strdup(arg);
		return ;
	}
	*key = ft_strndup(arg, ft_strlen(arg) - ft_strlen(*value));
	if ((*value + 1)[0] == '"' || (*value + 1)[0] == '\'')
		*value = ft_strndup(*value + 2, ft_strlen(*value + 2) - 1);
	else
		*value = ft_strdup(*value + 1);
}

/**
 * @brief Edit env var, if not exist then add to the envp list
 * Notice that export _ will be ignored
 * 
 * @param mini 
 * @param key 
 * @param value 
 */
void	edit_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*envp;

	if (ft_strcmp(key, "_") == 0)
	{
		free (key);
		if (value)
			free (value);
		return ;
	}
	envp = check_env_var(mini->envp, key);
	if (envp == NULL)
		add_env_var(mini, key, value);
	else
	{
		if (value != NULL)
		{
			free(envp->value);
			envp->value = value;
		}
		free (key);
	}
}

/**
 * @brief Builtin command export
 * export: print env including the ones with no value, with declare -x in front
 * export KEY : export the key with no value
 * export KEY= : export the key with no value but with =
 * export KEY=VALUE : like normal export
 * export _ : ignore (should not change the env variable)
 * 
 * @param mini 
 * @param input 
 * @param cmdblock 
 * @return int 
 */
int	ms_export(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*key;
	char	*value;
	int		i;
	int		errnum;

	i = 0;
	errnum = 0;
	if (cmdblock->cmd_argv[1] == NULL || check_redir_type(mini, cmdblock) != 0)
		return (print_export(mini));
	while (cmdblock->cmd_argv[++i] != NULL)
	{
		if (mini->pipes.do_pipe || mini->pipes.prep_pipe)
			continue ;
		get_key_value(cmdblock->cmd_argv[i], &key, &value);
		if (valid_input(key))
			edit_env_var(mini, key, value);
		else
		{
			identifier_error(mini, cmdblock->cmd_argv, i, INVALID_IDENTIFIER);
			errnum = 1;
			free (key);
			free (value);
		}
	}
	return (errnum);
}
