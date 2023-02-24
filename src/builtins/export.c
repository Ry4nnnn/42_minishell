#include "minishell.h"

//duplicates envp to envx
t_list	*ft_lststruct_dup(t_list *lst)
{
	t_list	*new_list = NULL;
	t_list	*last_node = NULL;
	t_list	*new_node;
	t_env *content_dup;
	t_env *converted_env;

	while (lst)
	{
		converted_env = (t_env *)lst->content;
		content_dup = malloc(sizeof(t_env));
		content_dup->key = ft_strdup(converted_env->key);
		content_dup->value = ft_strdup(converted_env->value);
		new_node = ft_lstnew(content_dup);
		if (!new_node)
			return (NULL);
		if (!new_list)
		{
			new_list = new_node;
			last_node = new_node;
		}
		else
		{
			last_node->next = new_node;
			last_node = new_node;
		}
		lst = lst->next;
	}
	return (new_list);
}

//to sort env (declare -x) to ascending order in ascii
//duplicate envp to envx and sort it by ascii
void	sort_env_x(t_mini *mini)
{
	t_list	*env_list;
	t_list	*reset_head;
	t_env	*cur_node;
	t_env	*next_node;
	void	*temp;

	mini->envx = ft_lststruct_dup(mini->envp);// duplicate envp to envx
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

// this function is to print the already sorted linked list
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

// extracting key and value from input
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


//check env var (key) exist
//loops through the linked list and check if theres (key)
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

void	edit_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*env;

	env = check_env_var(mini->envx, key);
	if (env == NULL)// if key doest not exist in env
		add_envx_var(mini, key, value);// adding new key to env
	if (value == NULL)// no value only key (no '=')
	{
		add_envx_var(mini, key, value);
		printf ("check\n");
	}
	//NOT DONE
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
		print_export_x(mini);
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
			// printf ("key: %s | value: %s\n", key, value);
			edit_env_var(mini, key, value);// adding key and value to envp or envx
			i++;
		}
	}
}
