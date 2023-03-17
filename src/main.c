/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:19 by welim             #+#    #+#             */
/*   Updated: 2023/03/18 00:20:37 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input(t_mini *mini, int *commanded)
{
	if (*commanded)
		mini->input = readline(mini->prompt);
	else
		mini->input = readline(BBLUE" ↪ "RESET);
	if (mini->input == NULL)
		ms_exit(mini);
	mini->input = trim_input(mini->input);
	if (mini->input[0] == '\0')
	{
		ms_free(&mini);
		*commanded = 0;
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	int		commanded;

	(void)ac;
	(void)av;
	commanded = 1;
	ms_init(&mini, envp);
	while (true)
	{
		ms_loop_init(&mini);
		if (get_input(&mini, &commanded) == 0)
			continue ;
		mini.cmdblock_list = split_cmdblocks(mini.input, 0);
		g_errno = handle_cmdblocks(&mini, mini.cmdblock_list);
		add_history(mini.input);
		ms_free(&mini);
		commanded = 1;
	}
	return (0);
}
