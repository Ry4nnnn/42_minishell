/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:44 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 15:16:15 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_dir(t_mini *mini, char *key, char *value)
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

int	ms_chdir(t_mini *mini, char *path)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, PATH_MAX);
	if (chdir(path) != 0)
		return (-1);
	update_dir(mini, "PWD", getcwd(NULL, PATH_MAX));
	update_dir(mini, "OLDPWD", oldpwd);
	return (0);
}

int	ms_cd_home(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*home;

	home = get_env(mini, "HOME");
	if (home == NULL)
	{
		cmd_error(mini, cmdblock->cmd_argv, NOHOME);
		return (1);
	}
	if (ms_chdir(mini, home) == 0)
		return (0);
	if (access(home, F_OK) == 0)
		cd_error(mini, cmdblock->cmd_argv, NOTDIR);
	else
		cd_error(mini, cmdblock->cmd_argv, NSFD);
	return (1);
}

int	ms_cd_dir(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*home;
	char	*oldpwd;

	home = getenv("HOME");
	oldpwd = get_env(mini, "OLDPWD");
	if (oldpwd && ft_strcmp(cmdblock->cmd_argv[1], "-") == 0)
	{
		ms_chdir(mini, oldpwd);
		ms_pwd();
		return (0);
	}
	if (ft_strcmp(cmdblock->cmd_argv[1], "~") == 0)
		ft_strexpand(&(cmdblock->cmd_argv[1]), home, 0, 1);
	if (ft_strncmp(cmdblock->cmd_argv[1], "~/", 2) == 0)
		ft_strexpand(&(cmdblock->cmd_argv[1]), home, 0, 1);
	if (ms_chdir(mini, cmdblock->cmd_argv[1]) != 0)
	{
		if (access(cmdblock->cmd_argv[1], F_OK) == 0)
			cd_error(mini, cmdblock->cmd_argv, NOTDIR);
		else
			cd_error(mini, cmdblock->cmd_argv, NSFD);
		return (1);
	}
	return (0);
}

// work like normal cd
// (cd) will go to home path
int	ms_cd(t_mini *mini, t_cmdblock *cmdblock)
{
	if (mini->pipes.prep_pipe || mini->pipes.do_pipe
		|| cmdblock->was_in_bracket)
		return (0);
	if (ft_2darrlen((void **)cmdblock->cmd_argv) == 1)
		return (ms_cd_home(mini, cmdblock));
	return (ms_cd_dir(mini, cmdblock) != 0);
}
