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
		// printf ("value b: %s\n", value);
		key = ft_strndup(*ev, (value - *ev));
		// printf ("key: %s\n", key);
		value = ft_strdup(value + 1);
		// printf ("value: %s\n", value);
		add_env_var(mini, key, value);
		ev++;
	}
	return (0);
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

//get env value by inputing key
char	*get_env(t_mini *mini, char *key)
{
	t_list	*envp;
	t_env	*env_var;

	envp = mini->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(key, env_var->key) == 0)
			return (env_var->value);
		envp = envp->next;
	}
	return (NULL);
}

void	init_prompt(t_mini *mini)
{
	char	*user;
	char	*dir;
	char	*home;
	char	*prompt;

	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	dir = get_env(mini, "PWD");
	home = get_env(mini, "HOME");
	if (home == NULL)
		dir = "🤷";
	else
	{
		if (dir != NULL && ft_strcmp(dir, home) == 0)
			dir = "~";
		else if (dir != NULL)
			dir = ft_strrchr(dir, '/');
		else
			dir = "🤷";
	}
	prompt = ft_strjoin(user, " @ ");
	prompt = ft_strjoin(prompt, dir);
	prompt = ft_strjoin(prompt, " $ ");
	mini->prompt = prompt;
}

// int	lexer(t_mini *mini, char *input)
// {
// 	int i;
// }

int main(int ac, char **av, char **ev)
{
	t_mini	mini;
	char *input;
	char **args;

	(void)ac;
	(void)av;
	glob_errno = 0;
	mini.exit = 0;
	mini.envp = NULL;
	init_env(&mini, ev);
	init_builtins(&mini);
	init_operators(&mini);
	while (!mini.exit)
	{
		init_prompt(&mini);
		input = readline(mini.prompt);
		// printf ("%s\n", input);
		// lexer(&mini, input);
		args = ft_split(input, ' ');
		// if (input == NULL)
		// 	return (0);
		if (!ft_strcmp(input, "env"))
			ft_env(&mini);
		if (!ft_strcmp(input, "exit"))
			ft_exit(&mini);
		if (!ft_strcmp(input, "pwd"))
			ft_pwd();
		if (!ft_strcmp(args[0], "unset"))
			ft_unset(&mini, args);
		if (!ft_strcmp(args[0], "export"))
			ft_export(&mini, args);
		// exec_builtin(&mini, input);
		add_history(input);
	}
	free(args);
	free(mini.prompt);
	return(0);
}