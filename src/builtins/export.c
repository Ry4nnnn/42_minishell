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
			if (valid_input(input[i]) == 0)
			{
				printf("export: `%s': not a valid identifier\n", input[i]);
				return ;
				// continue ;
			}
			i++;
		}
	}
}
