/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:44 by welim             #+#    #+#             */
/*   Updated: 2023/03/08 21:10:55 by wxuerui          ###   ########.fr       */
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

	oldpwd = get_env(mini, "OLDPWD");
	if (!ft_strcmp(cmds[1], "-")) // if args is only "-"
	{
		if (!oldpwd) // if oldpwd is empty
			printf ("cd: OLDPWD not set\n");
		else
		{
			oldpwd = get_env(mini, "PWD");
			chdir(get_env(mini, "OLDPWD")); // change to oldpwd address
			update_pwd(mini, "PWD"); // pwd will be updated
			update_oldpwd(mini, oldpwd); //oldpwd will be updated
			printf ("%s\n", get_env(mini, "PWD"));
		}
	}
	else
	{
		if (chdir(cmds[1])) // if input is not valid
			printf ("cd: %s: No such file or directory\n", cmds[1]);
		update_pwd(mini, "PWD");
		update_oldpwd(mini, oldpwd);
	}
}

// work like normal cd
// (cd) will go to home path
// (cd -) will switch between PWD and OLDPWD
void	ft_cd(t_mini *mini, char **cmds)
{
	char	*home;

	home = get_env(mini, "HOME");
	if (!cmds[1] || (!ft_strcmp(cmds[1], "~"))) // if only cd or cd ~
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
	else if (cmds[1] != NULL) // if cd got args
		ft_cd_args(mini, cmds);
}
