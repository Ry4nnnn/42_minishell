/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:40:50 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/04/08 16:38:19 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Init the builtin commands array
 * 
 * @param mini 
 */
static void	init_builtins(t_mini *mini)
{
	mini->builtins[0] = "pwd";
	mini->builtins[1] = "env";
	mini->builtins[2] = "echo";
	mini->builtins[3] = "cd";
	mini->builtins[4] = "unset";
	mini->builtins[5] = "export";
	mini->builtins[6] = "exit";
	mini->builtins[7] = NULL;
}

/**
 * @brief Init the redirection types array
 * 
 * @param mini 
 */
static void	init_redir(t_mini *mini)
{
	mini->redir[0] = "\1";
	mini->redir[1] = "\1\1";
	mini->redir[2] = "\3";
	mini->redir[3] = "\3\3";
	mini->redir[4] = NULL;
}

/**
 * @brief Init the envp linked list
 * 
 * @param mini 
 * @param envp 
 */
static void	init_env(t_mini *mini, char **envp)
{
	char	*key;
	char	*value;

	while (*envp != NULL)
	{
		value = ft_strchr(*envp, '=');
		key = ft_strndup(*envp, (ft_strlen(*envp) - ft_strlen(value)));
		value = ft_strdup(value + 1);
		add_env_var(mini, key, value);
		envp++;
	}
}

/**
 * @brief Init g_errno to 0, and call the 3 init functions above
 * 
 * @param mini 
 * @param envp 
 */
void	ms_init(t_mini *mini, char **envp)
{
	g_errno = 0;
	mini->envp = NULL;
	mini->cmdblock_list = NULL;
	init_env(mini, envp);
	init_builtins(mini);
	init_redir(mini);
}

/**
 * @brief
 * Restore the signal handler, prompt string, and pipes before every command.
 * 
 * @param mini 
 */
void	ms_loop_init(t_mini *mini)
{
	init_signal();
	init_prompt(mini);
	init_pipe(mini);
}
