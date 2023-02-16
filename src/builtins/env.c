#include "minishell.h"

int		ft_env(t_mini *mini)
{
	t_list	*env_list;

	env_list = mini->envp;
	while (env_list->next != NULL)
	{
		t_env *env_node = (t_env *)env_list->content;
		printf ("%s=%s\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
	return (0);
}
