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

// void	update_prompt(t_mini *mini)
// {
// 	char	*pwd;
// 	char	*prompt;
// 	char	*user;

	
// 	pwd = getcwd(NULL, 1024);
// 	user = get_env(&mini->env, "USER");
// 	prompt = ft_strdup(user);

// }

int main(int ac, char **av, char **env)
{
	t_mini	mini;
	char *cwd;
	char *buff;

	(void)av;
	if (ac != 1)
		return (ERROR);
	init_env(&mini, env);
	cwd = getcwd(NULL, 1024);
	// ft_strlcat(cwd, "@minihell> ", 1024 + 12);
	// while (1)
	// {
	// 	update_prompt(&mini);
		buff = readline(cwd);
	// }
	// printf("%s\n", buff);
	// ft_pwd();
	// ft_env(mini.env);
	// ft_export();
	// free(mini.env);
	return(0);
}