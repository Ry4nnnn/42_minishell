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
		// printf ("key=%s\n", env_content->key);
		// free(env_content->key);
		// printf ("value=%s\n", env_content->value);
		// free(env_content->value);
		// free(env_list);
		ft_lstdelone(env_list, &ft_free_node);
		return ;
	}
	while (env_list->next != NULL)
	{
		env_content = (t_env *)env_list->content;
		if (ft_strcmp(key[1], env_content->key) == 0)
		{
			//if env->list == mini->envp this is first content
			// mini->envp = env->list->next 
			// free(env->content)
			store_next = env_list->next;
			// printf ("key=%s\n", env_content->key);
			// free(env_content->key);
			// printf ("value=%s\n", env_content->value);
			// free(env_content->value);
			ft_lstdelone(env_list, &ft_free_node);
			store_prev->next = store_next;
			return ;
		}
		store_prev = env_list;
		env_list = env_list->next;
	}
}