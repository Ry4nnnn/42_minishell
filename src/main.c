/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:19 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 23:32:10 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	g_errno = 0;
	ms_init(&mini, envp);
	while (true)
	{
		ms_loop_init(&mini);
		mini.input = readline(mini.prompt);
		if (mini.input == NULL)
			ms_exit(&mini);
		mini.input = trim_input(mini.input);
		if (mini.input[0] == '\0')
		{
			ms_free(&mini);
			continue ;
		}
		mini.cmdblock_list = split_cmdblocks(mini.input, 0);
		g_errno = handle_cmdblocks(&mini, mini.cmdblock_list);
		add_history(mini.input);
		ms_free(&mini);
	}
	return (0);
}
