#include "minishell.h"

//to sort env (declare -x) to ascending order in ascii
void	sort_env_x(t_mini *mini)
{
	t_list	*env_list;
	t_list	*reset_head;
	t_env	*cur_node;
	t_env	*next_node;
	void	*temp;

	mini->envx = ft_lstdup(mini->envp);// duplicate envp to envx
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

	// init_envx(mini);
	sort_env_x(mini);
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

void	add_to_envx()
{
	printf ("check\n");
}

void	edit_env_var(t_mini *mini, char *key, char *value)
{
	if (!value)// if no '='
	{
		printf ("check\n");
		add_envx_var(mini, key, value);//add to envx //NOT WORKING
	}
	else
	{
		add_env_var(mini, key, value);//add to envp //NOT WORKING
		add_envx_var(mini, key, value);//add to envx
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
	if (input[i] == NULL)
		return (print_export_x(mini));
	else
	{
		while (input[i] != NULL)
		{
			get_key_value(input[i], &key, &value);// extracting key and value from input
			if (valid_input(key) == 0)
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
	}
}
