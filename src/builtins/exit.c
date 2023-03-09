/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:08 by welim             #+#    #+#             */
/*   Updated: 2023/03/09 18:40:00 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_mini *mini)
{
	(void)mini;
	rl_clear_history();
	system("leaks minishell");
	printf("exit 🤍\n");
	exit(0);
}
