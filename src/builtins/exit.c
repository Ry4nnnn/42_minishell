/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:08 by welim             #+#    #+#             */
/*   Updated: 2023/03/18 14:29:32 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(t_mini *mini, char **cmd_argv)
{
	int	exit_num;

	if (mini->pipes.do_pipe == 1 || mini->pipes.prep_pipe == 1)
		return ;
	if (ft_2darrlen((void **)cmd_argv) > 2)
		return (cmd_error(mini, cmd_argv, TOOMANYARGS));
	exit_num = 0;
	rl_clear_history();
	printf("exit 🤍\n");
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
	system("leaks minishell");
	exit(exit_num);
}
