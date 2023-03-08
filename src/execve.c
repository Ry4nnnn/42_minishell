/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:26 by welim             #+#    #+#             */
/*   Updated: 2023/03/08 22:17:29 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// gets a list executable paths from envp and split it into a 2d array
// then use access() function to check if input can be found in the list of executable paths
// when found
// this function returns the exec_path for execve() function to execute
char	*get_exec_path(t_mini *mini, char **cmds)
{
	char *plist;
	char **path;
	int j;
	char *temp;
	char *temp2;

	j = 0;
	plist = get_env(mini, "PATH");
	path = ft_split(plist, ':');
	while (path[j] != NULL)
	{
		temp = ft_strjoin(path[j], "/");
		temp2 = ft_strjoin(temp, cmds[0]);
		free (temp);
		if (access (temp2, X_OK) == 0)// if input is found in the List Of Path (break out of the loop)
			break ;
		free(temp2);
		j++;
	}
	if (path[j] == NULL)
	{
		ft_error(mini, cmds, CMD_NF);
		ft_free2darr((void *)path); // free 2d array
		return (NULL);
	}
	ft_free2darr((void *)path); // free 2d array
	// printf ("%s\n", temp2);
	return (temp2);
}

// execute non-builtin inputs
int	exec_non_builtins(t_mini *mini, char **cmds)
{
	pid_t	pid;
	char	*exec_path;
	char	**envp;
	int		estatus;

	exec_path = get_exec_path(mini, cmds);
	if (!exec_path)
		return (127);
	pid = fork();
	if (pid == 0) //this code will only run on child process
	{
		envp = ft_llto2darr(mini->envp, env_to_str);// translate updated linked list env to a 2d array
		if (execve(exec_path, cmds, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmds, CMD_NF); //prints error msg for invalid command
			exit(127);
		}
		exit(errno);
	}
	else
		waitpid(-1, &estatus, 0);
	free (exec_path);
	if (WIFSIGNALED(estatus))
		return (WTERMSIG(estatus));
	return (WEXITSTATUS(estatus));
}

// ./minishell
int	exec_program(t_mini *mini, char **cmds)
{
	pid_t	pid;
	int		estatus;
	char	**envp;

	pid = fork();
	if (pid == 0) //this code will only run on child process
	{
		envp = ft_llto2darr(mini->envp, env_to_str);
		if (execve(cmds[0], cmds, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmds, NSFD); //prints error msg for invalid command
			exit(127);
		}
	}
	else
		waitpid(-1, &estatus, 0);
	return (WEXITSTATUS(estatus));
}
