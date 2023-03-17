/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:44 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 15:01:35 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_chdir(t_mini *mini, char *path)
{
	t_list	*envp;

	envp = mini->envp;
	if (chdir(path) != 0)
		return (-1);
	while (envp != NULL)
	{
		if (ft_strcmp((char *)((t_env *)envp->content)->key, "PWD") == 0)
		{
			if ((char *)((t_env *)envp->content)->value != NULL)
				free(((t_env *)envp->content)->value);
			((t_env *)envp->content)->value = getcwd(NULL, PATH_MAX);
			break ;
		}
		envp = envp->next;
	}
	if (envp == NULL)
		add_env_var(mini, "PWD", getcwd(NULL, PATH_MAX));
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

	home = getenv("HOME");
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
