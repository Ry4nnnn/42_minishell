#include "minishell.h"

int	ft_export(t_mini *mini, char **key)
{
	t_list	*env_list;
	t_env	*env_node;

	env_list = mini->envp;
	while (env_list->next != NULL)
	{
		env_node = (t_env *)env_list->content;
		printf ("declare -x ");
		printf ("%s=\"%s\"\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
	return (0);
}
