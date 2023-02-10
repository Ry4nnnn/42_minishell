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

int	exec_builtin(t_mini *mini, char *input)
{
	if (!ft_strcmp(input, "env"))
		ft_env(mini->env);
	if (!ft_strcmp(input, "pwd"))
		ft_pwd();
	if (!ft_strcmp(input, "export"))
		ft_pwd();
	if (!ft_strcmp(input, "echo"))
		ft_echo(&input);
	if (!ft_strcmp(input, "exit"))
		exit(0);
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_mini	mini;
	char *input;

	(void)av;
	if (ac != 1)
		return (ERROR);
	init_env(&mini, env);
	while (1)
	{
		// update_prompt(&mini);
		input = readline("@minishell > ");
		exec_builtin(&mini, input);
		add_history(input);
	}
	free(mini.env);
	return(0);
}