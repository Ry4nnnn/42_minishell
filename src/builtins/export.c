#include "minishell.h"

//to sort env (declare -x) to ascending order in ascii
//duplicate envp to envx and sort it by ascii
void	sort_env_x(t_mini *mini)
{
	t_list	*env_list;
	t_list	*reset_head;
	t_env	*cur_node;
	t_env	*next_node;
	void	*temp;

	mini->envx = ft_struct_dup(mini->envp);// duplicate envp to envx
	// init_envx(mini);
	reset_head = mini->envx;
	env_list = mini->envx;
	while (env_list->next != NULL)
	{
		cur_node = (t_env *)env_list->content;
		next_node = (t_env *)env_list->next->content;
		if (ft_strcmp(cur_node->key, next_node->key) > 0)
		{
			temp = env_list->content;
			env_list->content = env_list->next->content;
			env_list->next->content = temp;
			env_list = reset_head;//reset and go back to the first node and compare again
		}
		else
			env_list = env_list->next;// shift to next node
	}
	env_list = reset_head;
}

void	print_export_x(t_mini *mini)
{
	t_list	*env_list;
	t_env	*env_node;

	env_list = mini->envx;
	while (env_list != NULL)
	{
		env_node = (t_env *)env_list->content;
		printf ("declare -x ");
		printf ("%s=\"%s\"\n", env_node->key, env_node->value);
		env_list = env_list->next;
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

static void	get_key_value(char *arg, char **key, char **value)
{
	*value = ft_strchr(arg, '=');
	if (*value == NULL)
	{
		*key = ft_strdup(arg);
		return ;
	}
	*key = ft_strndup(arg, *value - arg);
	*value = ft_strdup(*value + 1);
}

// loops through the linked list and check if theres (key)
//if no then returns a NULL
//if yes then returns the key itself
t_env	*check_env_var(t_list *envx, char *key)
{
	t_env	*env_list;

	while (envx != NULL)
	{
		env_list = envx->content;
		if (ft_strcmp(key, env_list->key) == 0)
			return (env_list);
		envx = envx->next;
	}
	return (NULL);
}

void	edit_env_var(t_mini *ms, char *key, char *value)
{
	t_env	*env;

	env = check_env_var(ms->envx, key);
	if (env == NULL)
		add_env_var(ms, key, value);// adding new key to env
	else if (value == NULL && env->value != NULL)
	{
		free(value);
		free(key);
	}
	else
	{
		free(env->value);
		env->value = value;
		free(key);
	}
}

//if export with no '=' only add to export(envx)
//if export with = add to both export(envx) and env(envp)
void	ft_export(t_mini *mini, char **input)
{
	char	*key;
	char	*value;
	int	i;

	i = 1;
	sort_env_x(mini);// duplicate envp to envx and sort it by ascii
	if (input[i] == NULL)//input only export with no paramters
	{
		print_export_x(mini);
		ft_lstclear(&mini->envx, clear_env_var);// free duplicated llist (envx)
	}
	else
	{
		while (input[i] != NULL)
		{
			get_key_value(input[i], &key, &value);// extracting key and value from input
			if (valid_input(key) == 0)// invalid input
			{
				printf("export: `%s': not a valid identifier\n", input[i]);
				free (key);
				free (value);
				// continue ;
			}
			printf ("key: %s | value: %s\n", key, value);
			edit_env_var(mini, key, value);// adding key and value to envp or envx
			i++;
		}
		ft_lstclear(&mini->envx, clear_env_var);// free duplicated llist (envx)
	}
}
