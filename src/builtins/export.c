/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:34:23 by wxuerui           #+#    #+#             */
/*   Updated: 2023/02/28 22:23:38 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this function is to print the already sorted linked list
void	print_export(t_mini *mini)
{
	// TODO
	t_list	*temp;
	t_env	*smallest_content;
	t_env	*biggest_content;
	t_env	*temp_content;
	int		i;

	temp = mini->envp;
	smallest_content = ((t_env *)temp->content);
	while (temp != NULL)
	{
		if (ft_strcmp(((t_env *)temp->content)->key, smallest_content->key) < 0) // if looping key is smaller than first_content key
			smallest_content = (t_env *)temp->content;
		if (ft_strcmp(((t_env *)temp->content)->key, biggest_content->key) > 0) // if looping key is greater than biggest_content key
			biggest_content = (t_env *)temp->content;
		temp = temp->next;
	} // find the first to print string in the envp list
	printf("declare -x %s=\"%s\"\n", smallest_content->key, smallest_content->value);
	i = ft_lstsize(mini->envp) - 1;
	temp = mini->envp;
	while (--i >= 0)
	{
		temp_content = biggest_content;
		temp = mini->envp;
		while (temp != NULL)
		{
			if (ft_strcmp(((t_env *)temp->content)->key, temp_content->key) < 0
				&& ft_strcmp(((t_env *)temp->content)->key, smallest_content->key) > 0) // if looping key is smaller than temp_content key and temp_content key is greater than first_content key
				temp_content = (t_env *)temp->content;
			temp = temp->next;
		}
		printf("declare -x %s", temp_content->key);
		if (temp_content->value == NULL)
			printf("\n");
		else
			printf("=\"%s\"\n", temp_content->value);
		smallest_content = temp_content;
	}
}

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
	*value = ft_strdup(*value + 1);
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

void	edit_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*envp;

	envp = check_env_var(mini->envp, key);
	if (envp == NULL)// if key doesnt exist in envp (adding new variable)
	{
		printf ("1\n");
		add_envp_var(mini, key, value);
	}
	else// editing variable (envp != NULL)
	{
		printf ("2\n");
		printf ("%p\n", envp->value);
		free(envp->value);
		printf ("value: %s\n", value);
		envp->value = value;							
		free (key);
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
	int	i;

	i = 1;
	//input only export with no paramters
	if (input[i] == NULL)
	{
		print_export(mini);
		return ;
	}
	while (input[i] != NULL)
	{
		get_key_value(input[i], &key, &value);// extracting key and value from input //malloc
		if (valid_input(key) == 0)// invalid input
		{
			printf("export: `%s': not a valid identifier\n", input[i]);
			free (key);
			free (value);
			i++;
			continue ;
		}
		edit_env_var(mini, key, value);// adding key and value to envp or envx
		i++;
	}
}
