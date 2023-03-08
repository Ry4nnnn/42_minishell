/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:28:00 by welim             #+#    #+#             */
/*   Updated: 2023/03/08 22:39:49 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	printf ("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_errno = 1;
}

void	init_signal(void)
{
	struct termios	termios_current;

	if (tcgetattr(STDIN_FILENO, &termios_current) == -1)
	{
		perror("Tcgetattr failed\n");
		exit(g_errno);
	}
	termios_current.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_current) == -1)
	{
		perror("Tcsetattr failed\n");
		exit(g_errno);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
