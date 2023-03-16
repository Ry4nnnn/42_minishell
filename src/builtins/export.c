/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:34:23 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/16 21:13:25 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				&& ft_strcmp(((t_env *)temp->content)->key, smallest->key) > 0) // if looping key is smaller than temp_content key and temp_content key is greater than first_content key
				temp_content = (t_env *)temp->content;
			temp = temp->next;
		}
		smallest = temp_content;
	}
}

// this function is to print the already sorted linked list
void	print_export(t_mini *mini)
{
	t_list	*temp;
	t_env	*smallest_content;
	t_env	*biggest_content;

	temp = mini->envp;
	smallest_content = ((t_env *)temp->content);
	biggest_content = ((t_env *)temp->content);
	while (temp != NULL)
	{
		if (ft_strcmp(((t_env *)temp->content)->key, smallest_content->key) < 0) // if looping key is smaller than first_content key
			smallest_content = (t_env *)temp->content;
		if (ft_strcmp(((t_env *)temp->content)->key, biggest_content->key) > 0) // if looping key is greater than biggest_content key
			biggest_content = (t_env *)temp->content;
		temp = temp->next;
	}
	show_export(smallest_content, biggest_content, mini->envp);
}



// extracting key and value from input
void	get_key_value(char *arg, char **key, char **value)
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


// (adding \ changing) key and value to envp
void	edit_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*envp;

	envp = check_env_var(mini->envp, key);
	if (envp == NULL) // if key doesnt exist in envp (adding new variable)
	{
		add_env_var(mini, key, value);
	}
	else if (value != NULL) // editing variable (envp != NULL)
	{
		free(envp->value);
		envp->value = value;
		free (key);
	}
	else
		free (key);
}

//if export with no '=' only add to export(envx)
//if export with = add to both export(envx) and env(envp)
void	ms_export(t_mini *mini, char **input, t_cmdblock *cmdblock)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	if (input[i] == NULL || check_redir_type(mini, cmdblock) != 0) //when input is only export with no paramters
	{
		print_export(mini);
		return ;
	}
	if (mini->pipes.do_pipe)
		return ;
	while (input[i] != NULL)
	{
		get_key_value(input[i], &key, &value); // extracting key and value from input //malloc
		if (!ft_strcmp(key, "_")) // ignore export _
		{
			free (key);
			if (value)
				free (value);
			return ;
		}
		if (valid_input(key) == 0) // invalid input
		{
			printf("export: `%s': not a valid identifier\n", input[i]);
			free (key);
			free (value);
			i++;
			continue ;
		}
		edit_env_var(mini, key, value); // adding key and value to envp or envx
		i++;
	}
}
