#include "minishell.h"

void	free_Llist(t_mini *mini, t_list *env_list)
{
	t_env	*env_node;

	while (env_list != NULL)
	{
		env_node = (t_env *)env_list->content;
		free (env_node->key);
		free (env_node->value);
		free (env_node);
		env_list = env_list->next;
	}
}

void	clear_env_var(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (env == NULL)
		return ;
	if (env->key != NULL)
		free(env->key);
	if (env->value != NULL)
		free(env->value);
	free(env);
}

void	ft_free_cmds(t_mini *mini)
{
	int	i;
	char **temp;

	i = 0;
	temp = mini->cmds;
	while (temp && *temp)
	{
		free(*temp);
		temp++;
	}
	free (mini->cmds);
}