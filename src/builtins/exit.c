/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:08 by welim             #+#    #+#             */
/*   Updated: 2023/04/08 15:52:38 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get exit_num,
 * rint error if the exit_num is non_numeric and return 255
 * 
 * @param mini 
 * @param cmd_argv 
 * @return int 
 */
static int	get_exit_num(t_mini *mini, t_cmdblock *cmdblock)
{
	int	exit_num;

	exit_num = 0;
	if (cmdblock && cmdblock->cmd_argv && cmdblock->cmd_argv[1])
	{
		if (ft_isnumber(cmdblock->cmd_argv[1]) == 0)
		{
			cmd_arg_error(mini, cmdblock->cmd_argv, NONNUMERICARG);
			return (255);
		}
		exit_num = ft_atoi(cmdblock->cmd_argv[1]);
	}
	return (exit_num);
}

/**
 * @brief exit should work without args or with one any numerical values,
 * Non numerical values or too many arguments should output error,
 * exit doesn't execute in pipes, but still outputs the error messages
 * 
 * @param mini 
 * @param cmd_argv 
 */
int	ms_exit(t_mini *mini, t_cmdblock *cmdblock)
{
	int	exit_num;

	if (!mini->pipes.do_pipe && !mini->pipes.prep_pipe)
		printf("exit 🤍\n");
	if (cmdblock && ft_2darrlen((void **)cmdblock->cmd_argv) > 2)
	{
		cmd_error(mini, cmdblock->cmd_argv, TOOMANYARGS);
		return (ERROR);
	}
	rl_clear_history();
	exit_num = get_exit_num(mini, cmdblock);
	g_errno = ((exit_num % 256) + 256) % 256;
	if (mini->pipes.do_pipe == 1 || mini->pipes.prep_pipe == 1)
		return (((exit_num % 256) + 256) % 256);
	system("leaks -q minishell");
	exit(exit_num);
}
