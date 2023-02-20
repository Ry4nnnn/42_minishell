#include "minishell.h"


void	ft_free_node(void *s)
{
	t_env	*content;

	content = (t_env *)s;
	free(content->key);
	free(content->value);
}

void	ft_unset(t_mini *mini, char **key)
{
	t_list	*env_list;
	t_env	*env_content;
	t_list	*store_next;
	t_list	*store_prev;


	env_list = mini->envp;
	env_content = (t_env *)env_list->content;
	if (ft_strcmp(key[1], env_content->key) == 0)
	{
		mini->envp = env_list->next;
		ft_lstdelone(env_list, &ft_free_node);
		return ;
	}
	while (env_list->next != NULL)
	{
		env_content = (t_env *)env_list->content;
		if (ft_strcmp(key[1], env_content->key) == 0)
		{
			store_next = env_list->next;;
			ft_lstdelone(env_list, &ft_free_node);
			store_prev->next = store_next;
			return ;
		}
		store_prev = env_list;
		env_list = env_list->next;
	}
}