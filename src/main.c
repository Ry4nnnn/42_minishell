#include "minishell.h"

int init_env(t_mini *mini, char **env_array)
{
	t_env *env;
	t_env *new;
	int		i;

	if (!(env = malloc(sizeof(t_env))))
		return (1);
	env->value = NULL;
	env->next = NULL;
	mini->env = env;
	i = 0;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;

	init_env(&mini, env);
	ft_enev(mini.env);
	free(mini.env);
	return(0);
}