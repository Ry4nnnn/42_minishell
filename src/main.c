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
	char	*prompt1;
	char	*prompt2;
	char	*prompt3;

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
	prompt1 = ft_strjoin(user, " @ ");
	prompt2 = ft_strjoin(prompt1, dir);
	free(prompt1);
	prompt3 = ft_strjoin(prompt2, " $ ");
	free(prompt2);
	mini->prompt = prompt3;
}

int	handle_commands(t_mini *mini, char **cmds)
{
	if (!ft_strncmp(cmds[0], "exit", 5))
	{
		ft_exit(mini);
		exit(1);
	}
	else if (!ft_strncmp(cmds[0], "env", 4))
		ft_env(mini);
	else if (!ft_strncmp(cmds[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmds[0], "unset", 6))
		ft_unset(mini, cmds);
	else if (!ft_strncmp(cmds[0], "export", 7))
		ft_export(mini, cmds);
	else if (cmds[0] != NULL)
		printf("welim: %s: command not found\n", cmds[0]);
	return(0);
}


void	free_Llist(t_mini *mini)
{
	t_list	*env_list;
	t_env	*env_node;

	env_list = mini->envx;
	while (env_list != NULL)
	{
		env_node = (t_env *)env_list->content;
		free (env_node->key);
		free (env_node->value);
		printf ("%s=\"%s\"\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
}

void	free_Llist2(t_mini *mini)
{
	t_list	*env_list;
	t_env	*env_node;

	env_list = mini->envp;
	while (env_list != NULL)
	{
		env_node = (t_env *)env_list->content;
		free (env_node->key);
		free (env_node->value);
		printf ("%s=\"%s\"\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
}

void	clear_env_var(void *content)
{
	t_env	*env;

	env = content;
	free(env->key);
	free(env->value);
	free(env);
}

// void	free_cmds(char **cmds)
// {
// 	while (!*cmds)
// 	{
// 		free (*cmds);
// 		*cmds
// 	}
// }


//lexer, signals, pipes, heredoc, redirection
int main(int ac, char **av, char **ev)
{
	t_mini	mini;
	char *input;
	char **cmds;

	(void)ac;
	(void)av;
	glob_errno = 0;
	mini.exit = 0;
	mini.envp = NULL;
	init_env(&mini, ev);
	// init_builtins(&mini);
	// init_operators(&mini);
	while (1)
	{
		int i = 0;
		init_prompt(&mini);
		input = readline(mini.prompt);
		// lexer(&mini, input);
		if (input == NULL)
			return (0);
		if (input[0] == '\0')
			continue ;
		mini.cmds = ft_split(input, ' ');
		// printf ("cmds: %s\n", cmds[0]);
		handle_commands(&mini, mini.cmds);
		// free(mini.cmds[i++]);
		add_history(input);
		free(mini.prompt);
		// ft_free_cmds(&mini);
	}
	return(0);
}

