/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:44 by welim             #+#    #+#             */
/*   Updated: 2023/03/31 18:13:13 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function used to update pwd or oldpwd
 * 
 * @param mini 
 * @param key 
 * @param value 
 */
static void	update_dir(t_mini *mini, char *key, char *value)
{
	t_list	*envp;
	t_env	*temp;

	envp = mini->envp;
	while (envp != NULL)
	{
		temp = (t_env *)envp->content;
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (temp->value != NULL)
				free(temp->value);
			temp->value = value;
			break ;
		}
		envp = envp->next;
	}
	if (envp == NULL)
		add_env_var(mini, key, value);
}

/**
 * @brief chdir and update pwd and oldpwd at the same time
 * 
 * @param mini 
 * @param path 
 * @return int 
 */
static int	ms_chdir(t_mini *mini, t_cmdblock *cmdblock, char *path)
{
	char	*oldpwd;

	if (access(path, F_OK) != 0)
		return (-1);
	if (mini->pipes.prep_pipe || mini->pipes.do_pipe)
		return (0);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		free(oldpwd);
		return (-1);
	}
	update_dir(mini, "PWD", getcwd(NULL, 0));
	update_dir(mini, "OLDPWD", oldpwd);
	return (0);
}

/**
 * @brief handle cd
 * 
 * @param mini 
 * @param cmdblock 
 * @return int 
 */
static int	ms_cd_home(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*home;

	home = get_env(mini, "HOME");
	if (home == NULL)
	{
		cmd_error(mini, cmdblock->cmd_argv, NOHOME);
		return (1);
	}
	if (ms_chdir(mini, cmdblock, home) == 0)
		return (0);
	if (access(home, F_OK) == 0)
		cmd_arg_error(mini, cmdblock->cmd_argv, NOTDIR);
	else
		cmd_arg_error(mini, cmdblock->cmd_argv, NSFD);
	return (1);
}

/**
 * @brief handle the cd general case
 * 
 * @param mini 
 * @param cmdblock 
 * @return int 
 */
static int	ms_cd_dir(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*home;
	char	*oldpwd;

	home = getenv("HOME");
	oldpwd = get_env(mini, "OLDPWD");
	if (oldpwd && ft_strcmp(cmdblock->cmd_argv[1], "-") == 0)
	{
		ms_chdir(mini, cmdblock, oldpwd);
		ms_pwd();
		return (0);
	}
	if (ft_strcmp(cmdblock->cmd_argv[1], "~") == 0)
		ft_strexpand(&(cmdblock->cmd_argv[1]), home, 0, 1);
	if (ft_strncmp(cmdblock->cmd_argv[1], "~/", 2) == 0)
		ft_strexpand(&(cmdblock->cmd_argv[1]), home, 0, 1);
	if (ms_chdir(mini, cmdblock, cmdblock->cmd_argv[1]) != 0)
	{
		if (access(cmdblock->cmd_argv[1], F_OK) == 0)
			cmd_arg_error(mini, cmdblock->cmd_argv, NOTDIR);
		else
			cmd_arg_error(mini, cmdblock->cmd_argv, NSFD);
		return (1);
	}
	return (0);
}

/**
 * @brief builtin command cd
 * cd : cd to home, if HOME not set, error
 * cd ~: cd to home, get the global env HOME, so no error
 * cd -: cd to the OLDPWD
 * cd path: cd to path, if path doesn't exist or not a directory, error
 * cd ~/path: cd to HOME/path, if path doesn't exist or not a directory, error
 * 
 * @param mini 
 * @param cmdblock 
 * @return int errno
 */
int	ms_cd(t_mini *mini, t_cmdblock *cmdblock)
{
	if (ft_2darrlen((void **)cmdblock->cmd_argv) == 1)
		return (ms_cd_home(mini, cmdblock));
	return (ms_cd_dir(mini, cmdblock) != 0);
}
