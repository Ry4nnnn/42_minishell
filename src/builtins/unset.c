#include "minishell.h"

// void	ft_unset(t_mini *mini, char **key)
// {
// 	t_list	*env_list;
// 	t_env	*env_content;
// 	t_list	*store_next;
// 	t_list	*store_prev;

// 	env_list = mini->envx;
// 	env_content = (t_env *)env_list->content;
// 	if (!key[1])
// 		return ;
// 	if (ft_strcmp(key[1], env_content->key) == 0)
// 	{
// 		mini->envp = env_list->next;
// 		ft_lstdelone(env_list, &clear_env_var);
// 		return ;
// 	}
// 	while (env_list->next != NULL)
// 	{
// 		env_content = (t_env *)env_list->content;
// 		if (ft_strcmp(key[1], env_content->key) == 0)
// 		{
// 			store_next = env_list->next;;
// 			ft_lstdelone(env_list, &clear_env_var);
// 			store_prev->next = store_next;
// 			return ;
// 		}
// 		store_prev = env_list;
// 		env_list = env_list->next;
// 	}
// }

static void	del_env_var(t_mini *ms, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;

	curr = ms->envp;
	if (curr->content == env)
	{
		ms->envp = curr->next;
		clear_env_var(env);
		free(curr);
		return ;
	}
	while (curr->next != NULL)
	{
		if (curr->next->content == env)
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			clear_env_var(env);
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
}

static void	del_envx_var(t_mini *ms, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;

	curr = ms->envx;
	if (curr->content == env)
	{
		ms->envx = curr->next;
		clear_env_var(env);
		free(curr);
		return ;
	}
	while (curr->next != NULL)
	{
		if (curr->next->content == env)
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			clear_env_var(env);
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
}

void	ft_unset(t_mini *mini, char **key)
{
	t_env	*env;
	t_env	*envx;
	int	i;

	i = 1;
	if (key[i] == NULL)
		return ;
	while (key[i] != NULL)
	{
		if (valid_input(key[i]) == 0)
		{
			printf("unset: `%s': not a valid identifier\n", key[i]);
		}
		env = check_env_var(mini->envp, key[i]);
		envx = check_env_var(mini->envx, key[i]);
		if (!env && !envx)//if key does not exits in both
		{
			printf ("0\n");
			i++;
			continue;
		}
		else if (!env)//if key does not exits in env
		{
			printf ("1\n");
			del_envx_var(mini, envx);
		}
		else if (!envx)//if key does not exits in env
		{
			printf ("2\n");
			del_env_var(mini, env);
		}
		else // both env and envx has key
		{
			printf ("3\n");
			del_env_var(mini, env);
			del_envx_var(mini, envx);
		}
		i++;
	}
}