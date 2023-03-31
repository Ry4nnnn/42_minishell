/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:10:02 by welim             #+#    #+#             */
/*   Updated: 2023/03/31 08:15:44 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** @brief Find the redir type
* return 0 if input does not contain any redir
* return 1 if contain >
* return 2 if contain >> (append)
* return 3 if contain <
* return 4 if contain << (heredoc)
**/
int	check_redir_type(t_mini *mini, t_cmdblock *cmdblock)
{
	char	**redir;
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = cmdblock->cmd_argv;
	redir = mini->redir;
	if (args == NULL)
		return (0);
	while (args[j] != NULL)
	{
		i = 0;
		while (redir[i] != 0)
		{
			if (ft_strcmp(redir[i], args[j]) == 0)
				return (i + 1);
			i++;
		}
		j++;
	}
	return (0);
}

int	ms_open(char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (fd);
}

//check in the str is a redir
// return 0 if true 
int	check_for_redir(t_mini *mini, char *str)
{
	int		i;

	i = 0;
	while (mini->redir[i])
	{
		if (ft_strcmp(str, mini->redir[i]) == 0)
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

// if (cmdblock->cmd_argv[i + 1] == NULL)
// theres redir at the end of the token
//
// if (check_for_redir(mini, cmdblock->cmd_argv[i + 1]) == 0)
// theres a redir after a redir
static int	check_redir_error(t_mini *mini, char *cmd_argv)
{
	char	*token;

	if (cmd_argv == NULL)
	{
		token = ft_strdup("newline");
		syntax_error(mini, UNEXPECTED_TOKEN, token);
		return (ERROR);
	}
	if ((cmd_argv[0] == '>') || (cmd_argv[0] == '<'))
	{
		token = ft_strndup(cmd_argv, 1);
		syntax_error(mini, UNEXPECTED_TOKEN, token);
		return (ERROR);
	}
	return (SUCCESS);
}

// to check if input ends with a redir
// if true it prints error msg
int	redir_error(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;
	int		j;

	i = 0;
	while (cmdblock->cmd_argv[i])
	{
		j = 0;
		while (mini->redir[j])
		{
			if (ft_strcmp(cmdblock->cmd_argv[i], mini->redir[j]) == 0)
			{
				if (check_redir_error(mini, cmdblock->cmd_argv[i + 1]) == ERROR)
					return (ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
