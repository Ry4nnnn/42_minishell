/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:51:11 by welim             #+#    #+#             */
/*   Updated: 2023/04/08 16:38:19 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief goes through the user input in the struct
 * 			finds the first redir in the input
 * 
 * @param mini struct
 * @param cmdblock struct
 * 
 * @return int
 * return 0 if input does not contain any redir
 * return 1 if is > (redir out)
 * return 2 if is >> (append)
 * return 3 if is < (redir in)
 * return 4 if is << (heredoc)
 */
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

/**
 * @brief goes through the str and search for redir
 * 
 * @param mini struct
 * @param str string
 * 
 * @return int
 * return 0 if true
 * return 1 if false
 */
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

int	check_is_redir(char *str)
{
	if (ft_strcmp("\1", str) == 0)
		return (1);
	if (ft_strcmp("\1\1", str) == 0)
		return (1);
	if (ft_strcmp("\3", str) == 0)
		return (1);
	if (ft_strcmp("\3\3", str) == 0)
		return (1);
	else
		return (0);
}

int	ms_open(t_mini *mini, char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		cmd_error(mini, &filename, NSFD);
		g_errno = 1;
		return (-1);
	}
	return (fd);
}
