/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:19 by welim             #+#    #+#             */
/*   Updated: 2023/03/04 22:13:33 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int		init_env(t_mini *mini, char **ev)
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

static void	combine_prompt(t_mini *mini, char *user, char *dir)
{
	char	*prompt0;
	char	*prompt1;
	char	*prompt2;
	char	*prompt3;

	prompt0 = ft_strjoin(GREEN , user);
	prompt1 = ft_strjoin(prompt0, " @ ");
	free(prompt0);
	prompt2 = ft_strjoin(prompt1, dir);
	free(prompt1);
	prompt3 = ft_strjoin(prompt2, " $ \033[0;37m");
	free(prompt2);
	mini->prompt = prompt3;
}

//this function is so fucking useless that i have to use one more function
//just to pass norm and displays a prompt that shows the current dir location
//and also to make my minishell looks cooler
void	init_prompt(t_mini *mini)
{
	char	*user;
	char	*dir;
	char	*home;

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
	combine_prompt(mini, user, dir);
}

// check if cmds is a builtin
// returns 1 means its a builtin
//returns 0 means its not a builtin
int	check_builtins(t_mini *mini, char *cmds)
{
	char **builtins;

	builtins = mini->builtins;
	if (cmds == NULL)
		return (0);
	while (*builtins != NULL)
	{
		if (ft_strcmp(*builtins, cmds) == 0)
			return (1);
		builtins++;
	}
	return (0);
}

//this function is to execute the builtins
int		exec_builtins(t_mini *mini, char **cmds)
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
	return(0);
}

// void	check_non_builtins_exist()
// {
// }

// linked list to ascii
// void ltoa ()
// {
	
// }

char	**ft_llto2darr(t_list *list)
{
	int	len;
	int	i;
	char	**arr;
	char	*temp1;
	char	*temp2;

	len = ft_lstsize(list);
	i = -1;
	arr = malloc((len + 1) * sizeof(char *));
	while (++i < len)
	{
		temp1 = ft_strdup(((t_env *)list->content)->key);
		temp2 = ft_strjoin(temp1, "=");
		free(temp1);
		temp1 = ft_strjoin(temp2, ((t_env *)list->content)->value);
		free(temp2);
		arr[i] = temp1;
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	exec_non_builtins(t_mini *mini, char **cmds) //after lexer
{
	char 	*plist;
	char	**path;
	int		j = 0;
	char	*temp;
	char	*temp2;
	char	**envp;
	pid_t	pid;

	plist = get_env(mini, "PATH");
	path = ft_split(plist, ':');
	while (path[j] != NULL)
	{
		temp = ft_strjoin(path[j], "/");
		temp2 = ft_strjoin(temp, cmds[0]);
		free (temp);
		if (access (temp2, X_OK) == 0)// if input is found in the List Of Path (break out of the loop)
			break ;
		free(temp2);
		j++;
	}
	ft_free2darr((void *)path);
	if (path[j] == NULL)
	{
		ft_error(mini, cmds, CMD_NF);
		return ;
	}
	pid = fork();
	if (pid == 0) //this code will only run on child process
	{
		envp = ft_llto2darr(mini->envp);
		printf ("exec: %s\n", temp2);
		if (execve(temp2, cmds, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmds, CMD_NF); //prints error msg for invalid command
			exit(127);
		}
	}
	else
		waitpid(-1, NULL, 0);
	free (temp2);
	return ;
}

void	exec_program(t_mini *mini, char **cmds)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid == 0) //this code will only run on child process
	{
		envp = ft_llto2darr(mini->envp);
		printf ("exec: %s\n", cmds[0]);
		if (execve(cmds[0], cmds, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmds, NSFD); //prints error msg for invalid command
			exit(127);
		}
	}
	else
		waitpid(-1, NULL, 0);
}

int		handle_commands(t_mini *mini, char **cmds)
{
	if (check_builtins(mini, cmds[0]) == 1)// it is a builtin!
	{
		exec_builtins(mini, cmds);
	}
	else if (get_env(mini, "PATH") == NULL)
	{
		ft_error(mini, cmds, NSFD);
	}
	else if (ft_strchr(cmds[0], '/') != NULL)
	{
		exec_program(mini, cmds);
	}
	else // non builtins
	{
		exec_non_builtins(mini, cmds);
	}
	return (0);
}

//expand then tokenize
//lexer, signals, pipes, heredoc, redirection, execve
int main(int ac, char **av, char **ev)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	// glob_errno = 0; (not used yet)
	mini.envp = NULL;
	init_env(&mini, ev);
	init_builtins(&mini);
	// init_operators(&mini); (not used yet)
	while (1)
	{
		init_signal();
		init_prompt(&mini);
		mini.input = readline(mini.prompt);
		if (mini.input == NULL)
			ft_exit(&mini);
		if (mini.input[0] == '\0')
		{
			free (mini.prompt);
			free (mini.input);
			continue ;
		}
		mini.cmds = ft_split(mini.input, ' '); // the budget lexer
		// lexer(&mini);
		handle_commands(&mini, mini.cmds); // this handles all the inputs after getting filtered by lexer
		add_history(mini.input);
		ft_free_cmds(&mini);
		free(mini.prompt);
		free(mini.input);
	}
	return(0);
}

