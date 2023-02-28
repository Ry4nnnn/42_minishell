#include "minishell.h"

//adding variable to envp
void	add_envp_var(t_mini *mini, char *key, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (env_var == NULL)
		return ;
	env_var->key = key;
	env_var->value = value;
	ft_lstadd_back(&mini->envp, ft_lstnew(env_var));
}

//take in ev from main func and initialize into a linked list
int init_env(t_mini *mini, char **ev)
{
	char	*key;
	char	*value;

	while (*ev != NULL)
	{
		value = ft_strchr(*ev, '=');
		key = ft_strndup(*ev, (ft_strlen(*ev) - ft_strlen(value)));
		value = ft_strdup(value + 1);
		add_envp_var(mini, key, value);
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

//get env value by inputing key from envp
// returns NULL if could find any
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
	char	*prompt0;
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
	prompt0 = ft_strjoin(GREEN , user);
	prompt1 = ft_strjoin(prompt0, " @ ");
	free(prompt0);
	prompt2 = ft_strjoin(prompt1, dir);
	free(prompt1);
	prompt3 = ft_strjoin(prompt2, " $ \033[0;37m");
	free(prompt2);
	mini->prompt = prompt3;
}

//print error for invalid input || non valid commands
void	ft_error(t_mini *mini, char **cmds)
{
	char *user;

	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	printf("\033[95m%s:\033[0m ", user);
	printf("%s: command not found\n", cmds[0]);
}

int	handle_commands(t_mini *mini, char **cmds)
{
	if (!ft_strncmp(cmds[0], "exit", 5))
		ft_exit(mini);
	else if (!ft_strncmp(cmds[0], "env", 4))
		ft_env(mini);
	else if (!ft_strncmp(cmds[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmds[0], "unset", 6))
		ft_unset(mini, cmds);
	else if (!ft_strncmp(cmds[0], "export", 7))
		ft_export(mini, cmds);
	else if (!ft_strncmp(cmds[0], "cd", 3))
		ft_cd(mini);
	else if (!ft_strncmp(cmds[0], "echo", 5))
		ft_echo(cmds);
	else if (cmds[0] != NULL)
		ft_error(mini, cmds);
	return(0);
}

void	signal_handler(int num)
{
	if (num == SIGINT)
	{
		write(0, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

//expand then tokenize
//lexer, signals, pipes, heredoc, redirection
int main(int ac, char **av, char **ev)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	// glob_errno = 0;
	mini.envp = NULL;
	//test
	// while (*ev != NULL)
	// {
	// 	printf("%s\n", *ev);
	// 	ev++;
	// }
	// return (0);
	init_env(&mini, ev);
	// init_builtins(&mini);
	// init_operators(&mini);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		init_prompt(&mini);
		mini.input = readline(mini.prompt);
		if (mini.input == NULL)
			return (0);
		if (mini.input[0] == '\0')
		{
			free (mini.prompt);
			free (mini.input);
			continue ;
		}
		mini.cmds = ft_split(mini.input, ' ');
		add_history(mini.input);
		// lexer(&mini);
		free(mini.input);
		handle_commands(&mini, mini.cmds);
		ft_free_cmds(&mini);
		free(mini.prompt);
	}
	return(0);
}

