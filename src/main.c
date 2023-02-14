#include "minishell.h"

void	add_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (env_var == NULL)
		return ;
	env_var->key = key;
	env_var->value = value;
	ft_lstadd_back(&mini->envp, ft_lstnew(env_var));
}

int init_env(t_mini *mini, char **ev)
{
	char	*key;
	char	*value;

	while (*ev != NULL)
	{
		value = ft_strchr(*ev, '=');
		key = ft_strndup(*ev, (value - *ev));
		// printf ("key: %s\n", key);
		value = ft_strdup(value + 1);
		// printf ("value: %s\n", value);
		add_env_var(mini, key, value);
		ev++;
	}
	return (0);
}

// void init_builtins(t_mini *mini)
// {
// 	char	**builtins;

// 	builtins = ft_calloc(7 + 1, sizeof(char *));
// 	builtins[0] = "pwd";
// 	builtins[1] = "env";
// 	builtins[2] = "echo";
// 	builtins[3] = "cd";
// 	builtins[4] = "unset";
// 	builtins[5] = "export";
// 	builtins[6] = "exit";
// 	mini->builtins = builtins;
// }

// void	init_operators(t_mini *mini)
// {
// 	char	**operators;

// 	operators = ft_calloc(7 + 1, sizeof(char *));
// 	operators[0] = "|";
// 	operators[1] = ">>";
// 	operators[2] = "<<";
// 	operators[3] = ">";
// 	operators[4] = "<";
// 	mini->operators = operators;
// }

void	init_minishell(t_mini *mini, char **ev)
{
	glob_errno = 0;
	mini->envp = NULL;
	mini->tokens = NULL;
	mini->cmd = NULL;
}

// char	*get_env(t_mini *mini, char *key)
// {
// 	t_list	*envp;
// 	t_env	*env_var;

// 	envp = mini->envp;
// 	while (envp != NULL)
// 	{
// 		env_var = envp->content;
// 		if (ft_strcmp(key, env_var->key) == 0)
// 			return (env_var->value);
// 		envp = envp->next;
// 	}
// 	return (NULL);
// }

// void	init_prompt(t_mini *mini)
// {
// 	char	*user;
// 	char	*dir;
// 	char	*home;
// 	char	*prompt;

// 	user = get_env(mini, "USER");

// }

// int	exec_builtin(t_mini *mini, char *input)
// {
// 	if (!ft_strcmp(input, "env"))
// 		ft_env(mini->envp);
// 	if (!ft_strcmp(input, "pwd"))
// 		ft_pwd();
// 	if (!ft_strcmp(input, "exit"))
// 	{
// 		printf ("exit\n");
// 		exit(0);
// 	}
// 	return (0);
// }

int main(int ac, char **av, char **ev)
{
	t_mini	mini;
	char *input;

	(void)ac;
	(void)av;
	mini.exit = 0;
	init_minishell(&mini, ev);
	init_env(&mini, ev);
	// init_builtins(&mini);
	// init_operators(&mini);
	// while (!mini.exit)
	// {
	// 	// init_prompt(&mini);
	// 	input = readline("@minishell> ");
	// 	exec_builtin(&mini, input);
	// 	add_history(input);
	// }
	// free(mini.envp);
	return(0);
}