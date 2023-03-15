/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:44 by welim             #+#    #+#             */
/*   Updated: 2023/03/15 21:37:53 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_mini *mini, char *key)
{
	t_list	*envp;
	t_env	*env_var;

	envp = mini->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(key, env_var->key) == 0)
		{
			if (env_var->value)
				free (env_var->value);
			env_var->value = getcwd(NULL, PATH_MAX);
			return ;
		}
		envp = envp->next;
	}
}

void	update_oldpwd(t_mini *mini, char *old_path)
{
	t_list	*envp;
	t_env	*env_var;

	envp = mini->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp("OLDPWD", env_var->key) == 0)
		{
			if (env_var->value)
				free(env_var->value);
			env_var->value = ft_strdup(old_path);
		}
		envp = envp->next;
	}
}

void	ft_cd_args(t_mini *mini, char **cmds)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = get_env(mini, "OLDPWD");
	pwd = get_env(mini, "PWD");
	if (ft_strcmp(cmds[1], "-") == 0) // if args is only "-"
	{
		if (!oldpwd) // if oldpwd is empty
			printf ("cd: OLDPWD not set\n");
		else
		{
			chdir(get_env(mini, "OLDPWD")); // change to oldpwd address
			update_oldpwd(mini, pwd); //oldpwd will be updated
			update_pwd(mini, "PWD"); // pwd will be updated
			printf ("%s\n", get_env(mini, "PWD"));
		}
	}
	else
	{
		if (chdir(cmds[1]) != 0) // if input is not valid
			printf ("cd: %s: No such file or directory\n", cmds[1]);
		else
		{
			update_oldpwd(mini, pwd);
			update_pwd(mini, "PWD");
		}
	}
}

// work like normal cd
// (cd) will go to home path
// (cd -) will switch between PWD and OLDPWD
void	ms_cd(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*home;

	if (mini->pipes.prep_pipe || mini->pipes.do_pipe || cmdblock->was_in_bracket)
		return ;
	home = get_env(mini, "HOME");
	if (!cmdblock->cmd_argv[1] || (!ft_strcmp(cmdblock->cmd_argv[1], "~"))) // if only cd or cd ~
	{
		if (!home)
			printf ("cd: HOME not set\n");
		else
		{
			update_pwd(mini, "OLDPWD"); // will change oldpwd to cur path
			chdir(home); // change pwd to home path
			update_pwd(mini, "PWD"); // will change cur pwd to home path
		}
	}
	else if (cmdblock->cmd_argv[1] != NULL) // if cd got args
		ft_cd_args(mini, cmdblock->cmd_argv);
}
