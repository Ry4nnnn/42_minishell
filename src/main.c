/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:19 by welim             #+#    #+#             */
/*   Updated: 2023/04/05 15:38:10 by welim            ###   ########.fr       */
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

/**
 * @brief print welcome banner when launch ./minishell
 * 
 * @param void 
 */
static void	print_banner(void)
{
	printf (BGREEN);
	printf(" _____ ______   ___  ________   ___  ___");
	printf("_____  ___  ___  _______   ___       ___\n");
	printf("|\\   _ \\  _   \\|\\  \\|\\   ___  \\|\\  \\|\\   ");
	printf ("____\\|\\  \\|\\  \\|\\  ____\\ |\\  \\     |\\  \\\n");
	printf("\\ \\  \\\\\\__\\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\");
	printf (" \\  \\___|\\ \\  \\\\\\  \\ \\  \\__|_\\ \\  \\    \\ \\  \\\n");
	printf(" \\ \\  \\\\|__| \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\ \\");
	printf ("_____  \\ \\   __  \\ \\   ___\\\\ \\  \\    \\ \\  \\\n");
	printf("  \\ \\  \\    \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\|__");
	printf ("__|\\  \\ \\  \\ \\  \\ \\  \\__|_\\ \\  \\____\\ \\  \\____\n");
	printf("   \\ \\__\\    \\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\__");
	printf ("\\\\________\\ \\__\\ \\__\\ \\______\\\\ \\_______\\ \\_______\\\n");
	printf("    \\|__|     \\|__|\\|__|\\|__| \\|__|\\|__|");
	printf (" |_______| |__|\\|__|\\|_______|\\|_______|\\|_______|\n");
	printf (BCYAN);
	printf ("						created by: Ryan | welim & Ray | wxuerui\n");
	printf (RESET);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	int		commanded;

	(void)ac;
	(void)av;
	commanded = 1;
	print_banner();
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
