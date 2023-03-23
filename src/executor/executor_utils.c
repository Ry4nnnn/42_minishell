/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:06:46 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/03/23 22:30:42 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief env to string castng.
 * E.g.: key=A, value=abc => A=abc
 * Used by ft_llto2darr (linked list to 2d array)
 * 
 * @param arg 
 * @return char* 
 */
char	*env_to_str(void *arg)
{
	t_env	*env_t;
	char	*temp;
	char	*output;

	env_t = (t_env *)arg;
	temp = ft_strjoin(env_t->key, "=");
	output = ft_strjoin(temp, env_t->value);
	free(temp);
	return (output);
}

/**
 * @brief Try if a path joined with cmd is valid
 * 
 * @param path 
 * @param cmd 
 * @return char* NULL for invalid and cmd_path if valid
 */
static char	*try_cmd_path(char *path, char *cmd)
{
	char	*cmd_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin_free(temp, cmd);
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

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

int	get_exec_argv_sz(t_mini *mini, t_cmdblock *cmdblock)
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

//get the input in 2d array and check if theres a redir
//and remove the args after the redir including the redir
void	get_exec_argv(t_mini *mini, t_cmdblock *cmdblock)
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
	cmdblock->redir_argv = res;
}
