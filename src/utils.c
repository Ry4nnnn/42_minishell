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
	*value = ft_strdup(*value + 1);
}

//to sort env (declare -x) to ascending order in ascii
// env_list = reset_head; < this line is to reset the linked list and 
//go back to the first node and compare again
void	sort_env_x(t_mini *mini)
{
	t_list	*env_list;
	t_list	*reset_head;
	t_env	*cur_node;
	t_env	*next_node;
	void	*temp;

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
			env_list = reset_head;
		}
		else
			env_list = env_list->next;
	}
	env_list = reset_head;
}
