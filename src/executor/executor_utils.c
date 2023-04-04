/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:06:46 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/04/04 17:21:37 by welim            ###   ########.fr       */
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
char	*try_cmd_path(char *path, char *cmd)
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

int	get_program_permission(t_mini *mini, t_cmdblock *cmdblock)
{
	struct stat	file_stat;

	if (stat(cmdblock->cmd_argv[0], &file_stat) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, NSFD);
		return (127);
	}
	if (S_ISDIR(file_stat.st_mode) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, ISDIR);
		return (126);
	}
	else if (access(cmdblock->cmd_argv[0], X_OK) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, PERMISSION_DENIED);
		return (126);
	}
	return (0);
}
