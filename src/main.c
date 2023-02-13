#include "minishell.h"

// int init_env(t_mini *mini, char **env_array)
// {
// 	t_env *env;
// 	t_env *new;
// 	int		i;

// 	if (!(env = malloc(sizeof(t_env))))
// 		return (1);
// 	env->value = NULL;
// 	env->next = NULL;
// 	mini->env = env;
// 	i = 0;
// 	while (env_array && env_array[0] && env_array[i])
// 	{
// 		if (!(new = malloc(sizeof(t_env))))
// 			return (1);
// 		new->value = ft_strdup(env_array[i]);
// 		new->next = NULL;
// 		env->next = new;
// 		env = new;
// 		i++;
// 	}
// 	return (0);
// }

int init_env(t_mini *mini, char **ev)
{
	char	*key;
	char	*value;

	while (*ev != NULL)
	{
		value = ft_strchr(*ev, '=');
		key   = ft_strdup(*ev, (value - *ev));
		value = ft_strdup(value + 1);
		add_env_var(mini, key, value);
		ev++;
	}
}

void init_builtins(t_mini *mini)
{
	char	**builtins;

	builtins = ft_calloc(7 + 1, sizeof(char *));
	builtins[0] = "pwd";
	builtins[1] = "env";
	builtins[2] = "echo";
	builtins[3] = "cd";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = "exit";
	mini->builtins = builtins;
}

void	init_operators(t_mini *mini)
{
	char	**operators;

	operators = ft_calloc(7 + 1, sizeof(char *));
	operators[0] = "|";
	operators[1] = ">>";
	operators[2] = "<<";
	operators[3] = ">";
	operators[4] = "<";
	mini->operators = operators;
}

void	init_minishell(t_mini *mini, char **ev)
{
	glob_errno = 0;
	mini->envp = NULL;
	mini->tokens = NULL;
	mini->cmd = NULL;
}

char	*get_env(t_mini *mini, char *key)
{
	t_list	*envp
}

void	init_prompt(t_mini *mini)
{
	char	*user;
	char	*dir;
	char	*home;
	char	*prompt;

	user = get_env(mini, "USER");

}

int	exec_builtin(t_mini *mini, char *input)
{
	char *path[] = {"ls", NULL};
	if (!ft_strcmp(input, "env"))
		ft_env(mini->env);
	if (!ft_strcmp(input, "pwd"))
		ft_pwd();
	// if (ft_strcmp(input, "echo"))
	// {
	// 	ft_echo(input); 
	// 	printf ("input:%s\n", input);
	// }
	// if (!ft_strcmp(input, "export"))
	// 	ft_pwd();
	if (!ft_strcmp(input, "ls"))
	{
		execve("/bin/ls", path, NULL);
	}
	if (!ft_strcmp(input, "exit"))
	{
		printf ("exit\n");
		exit(0);
	}
	return (0);
}

int main(int ac, char **av, char **ev)
{
	t_mini	mini;
	char *input;

	(void)ac;
	(void)av;
	mini.exit = 0;
	init_minishell(&mini, ev);
	init_env(&mini, ev);
	init_builtins(&mini);
	init_operators(&mini);
	while (!mini.exit)
	{
		init_prompt(&mini);
		input = readline("@minishell> ");
		exec_builtin(&mini, input);
		add_history(input);
	}
	free(mini.env);
	return(0);
}