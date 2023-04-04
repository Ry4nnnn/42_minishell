/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:25:29 by welim             #+#    #+#             */
/*   Updated: 2023/04/04 22:00:08 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the program path by joining the cmds[0] with the paths list
 * and try until got a valid one.
 * If has tried all paths and still no valid program path, return NULL.
 * 
 * @param mini
 * @param cmds
**/
char	*get_exec_path(t_mini *mini, char **cmds)
{
	char	*plist;
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	plist = get_env(mini, "PATH");
	paths = ft_split(plist, ':');
	cmd_path = NULL;
	while (paths[i] != NULL)
	{
		cmd_path = try_cmd_path(paths[i], cmds[0]);
		if (cmd_path != NULL)
			break ;
		i++;
	}
	ft_free2darr((void *)paths);
	if (cmd_path == NULL)
		cmd_error(mini, cmds, CMD_NF);
	return (cmd_path);
}

static int	get_exec_argv_sz(t_mini *mini, t_cmdblock *cmdblock)
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
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

static void	get_redir_argv(t_cmdblock *cmdblock)
{
	char	**res;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (check_is_redir(cmdblock->cmd_argv[0]) == 1)
	{
		while (cmdblock->cmd_argv[i] != NULL
			&& check_is_redir(cmdblock->cmd_argv[i]))
			i += 2;
		res = (char **)malloc(sizeof(char *)
				* (ft_2darrlen((void **)cmdblock->cmd_argv) - i + 1));
		while (cmdblock->cmd_argv[i])
		{
			res[k++] = ft_strdup(cmdblock->cmd_argv[i]);
			i++;
		}
		res[k] = NULL;
		ft_free2darr((void **)cmdblock->cmd_argv);
		cmdblock->cmd_argv = res;
	}
}

static void	get_redir2_argv(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	k = 0;
	i = get_exec_argv_sz(mini, cmdblock);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	while (i--)
	{
		j = 0;
		res[k] = malloc(sizeof(char) * (ft_strlen(cmdblock->cmd_argv[k]) + 1));
		while (cmdblock->cmd_argv[k][j])
		{
			res[k][j] = cmdblock->cmd_argv[k][j];
			j++;
		}
		res[k][j] = '\0';
		k++;
	}
	res[k] = NULL;
	ft_free2darr((void **)cmdblock->cmd_argv);
	cmdblock->cmd_argv = res;
}

//get the input in 2d array and check if theres a redir
//and remove the args after the redir including the redir
/**
 * @brief gets the redir argument for execve
 * gets the input in 2d array and check if theres a redir
 * removes the args after the redir including the redir
 * 
 * @param mini struct
 * @param cmdblock struct
 */
void	get_exec_argv(t_mini *mini, t_cmdblock *cmdblock)
{
	get_redir_argv(cmdblock);
	if (check_redir_type(mini, cmdblock) != 0)
		get_redir2_argv(mini, cmdblock);
}
