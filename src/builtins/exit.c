/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:08 by welim             #+#    #+#             */
/*   Updated: 2023/03/14 13:16:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(t_mini *mini)
{
	if (mini->pipes.do_pipe == 1 || mini->pipes.prep_pipe == 1)
		return ;
	rl_clear_history();
	# ifndef __linux__
		system("leaks minishell")
	# endif
	printf("exit 🤍\n");
	exit(0);
}
