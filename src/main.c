/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:19 by welim             #+#    #+#             */
/*   Updated: 2023/03/06 11:59:20 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//take in ev from main func and add it into a linked list
int		init_env(t_mini *mini, char **ev)
{
	char	*key;
	char	*value;

	while (*ev != NULL)
	{
		value = ft_strchr(*ev, '=');
		key = ft_strndup(*ev, (ft_strlen(*ev) - ft_strlen(value)));
		value = ft_strdup(value + 1);
		add_env_var(mini, key, value);
		ev++;
	}
	return (0);
}

// to initialize all the builtins
// dont have to NULL the last one (calloc alrdy did it)
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
//lexer, pipes, heredoc, redirection
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
		// mini.cmds = ft_split(mini.input, ' '); // the budget lexer
		lexer(&mini);
		return (0);
		handle_commands(&mini, mini.cmds); // this handles all the inputs after getting filtered by lexer
		add_history(mini.input);
		ft_free_cmds(&mini);
		free(mini.prompt);
		free(mini.input);
	}
	return(0);
}

