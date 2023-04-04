/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:19 by welim             #+#    #+#             */
/*   Updated: 2023/04/04 22:55:05 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the input string, if input is NULL (ctrl-d) then exit.
 * If the input is not command, then make the commanded variable 0,
 * so the next prompt will be just an arrow, without the long annoying line.
 * 
 * @param mini 
 * @param commanded 
 * @return int 1 for valid line, 0 for empty input
 */
int	get_input(t_mini *mini, int *commanded)
{
	if (*commanded)
		mini->input = readline(mini->prompt);
	else
		mini->input = readline(BBLUE" ↪ "RESET);
	if (mini->input == NULL)
		ms_exit(mini, NULL);
	mini->input = trim_input(mini->input);
	if (mini->input[0] == '\0')
	{
		ms_free(mini);
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
