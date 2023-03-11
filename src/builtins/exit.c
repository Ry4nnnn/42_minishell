/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:08 by welim             #+#    #+#             */
/*   Updated: 2023/03/11 13:43:49 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(t_mini *mini)
{
	if (mini->pipes.do_pipe == 1)
		return ;
	rl_clear_history();
	system("leaks minishell");
	printf("exit 🤍\n");
	exit(0);
}
