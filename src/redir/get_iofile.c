/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_iofile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:14:42 by welim             #+#    #+#             */
/*   Updated: 2023/04/04 21:48:12 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_infile(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	cmdblock->infile = cmdblock->cmd_argv[i + 1];
	while (cmdblock->cmd_argv[i + 1]
		&& check_for_redir(mini, cmdblock->cmd_argv[i + 1]) == SUCCESS)
	{
		cmdblock->infile = cmdblock->cmd_argv[i + 1];
		i++;
	}
}

static void	get_outfile(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	(void)mini;
	cmdblock->outfile = cmdblock->cmd_argv[i + 1];
}

/**
 * @brief to get the file name depending if its a in or out redirection
 * it will also get the delimiters for heredoc
 * 
 * @param mini struct
 * @param cmdblock struct
 * @param i
 * 
 * @return int
 */
int	get_iofile(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	if (cmdblock->cmd_argv[i + 1] == NULL)
		return (ERROR);
	if ((ft_strcmp(cmdblock->cmd_argv[i], S_IN) == 0)
		|| (ft_strcmp(cmdblock->cmd_argv[i], S_HEREDOC) == 0))
	{
		get_infile(mini, cmdblock, i);
	}
	if ((ft_strcmp(cmdblock->cmd_argv[i], S_OUT) == 0)
		|| (ft_strcmp(cmdblock->cmd_argv[i], S_APPEND) == 0))
	{
		get_outfile(mini, cmdblock, i);
	}
	return (SUCCESS);
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
