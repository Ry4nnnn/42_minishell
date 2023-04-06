/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:28:00 by welim             #+#    #+#             */
/*   Updated: 2023/04/06 22:05:19 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_exec(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("^C\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("^\\Quit: ", STDERR_FILENO);
		ft_putnbr_fd(signo, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

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
		exit(0);
	}
	termios_current.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_current) == -1)
	{
		perror("Tcsetattr failed\n");
		exit(0);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
