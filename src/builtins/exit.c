/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:08 by welim             #+#    #+#             */
/*   Updated: 2023/03/18 14:53:36 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_num(t_mini *mini, char **cmd_argv)
{
	int	exit_num;

	exit_num = 0;
	if (cmd_argv != NULL && cmd_argv[1] != NULL)
	{
		if (ft_isnumber(cmd_argv[1]) == 0)
		{
			cmd_arg_error(mini, cmd_argv, NONNUMERICARG);
			exit_num = 255;
		}
		else
			exit_num = ft_atoi(cmd_argv[1]);
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
void	ms_exit(t_mini *mini, char **cmd_argv)
{
	int	exit_num;

	if (ft_2darrlen((void **)cmd_argv) > 2)
		return (cmd_error(mini, cmd_argv, TOOMANYARGS));
	if (!mini->pipes.do_pipe && !mini->pipes.prep_pipe)
	{
		rl_clear_history();
		printf("exit 🤍\n");
	}
	exit_num = get_exit_num(mini, cmd_argv);
	g_errno = ((exit_num % 256) + 256) % 256;
	if (mini->pipes.do_pipe == 1 || mini->pipes.prep_pipe == 1)
		return ;
	system("leaks minishell");
	exit(exit_num);
}
