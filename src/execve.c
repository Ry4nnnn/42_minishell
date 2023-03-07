/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:26 by welim             #+#    #+#             */
/*   Updated: 2023/03/06 20:00:53 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//converts linked list to 2d array
char	**ft_llto2darr(t_list *list)
{
	int	len;
	int	i;
	char	**arr;
	char	*temp1;
	char	*temp2;

	len = ft_lstsize(list);
	i = -1;
	arr = malloc((len + 1) * sizeof(char *));
	while (++i < len)
	{
		temp1 = ft_strdup(((t_env *)list->content)->key);
		temp2 = ft_strjoin(temp1, "=");
		free(temp1);
		temp1 = ft_strjoin(temp2, ((t_env *)list->content)->value);
		free(temp2);
		arr[i] = temp1;
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
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
	ft_free2darr((void *)path); // free 2d array
	if (path[j] == NULL)
	{
		ft_error(mini, cmds, CMD_NF);
		return (NULL);
	}
	// printf ("%s\n", temp2);
	return (temp2);
}

// execute non-builtin inputs
void	exec_non_builtins(t_mini *mini, char **cmds)
{
	pid_t	pid;
	char	*exec_path;
	char	**envp;

	exec_path = get_exec_path(mini, cmds);
	if (!exec_path)
		return ;
	pid = fork();
	if (pid == 0) //this code will only run on child process
	{
		envp = ft_llto2darr(mini->envp);// translate updated linked list env to a 2d array
		if (execve(exec_path, cmds, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmds, CMD_NF); //prints error msg for invalid command
			exit(127);
		}
	}
	else
		waitpid(-1, NULL, 0);
	free (exec_path);
	return ;
}

// ./minishell
void	exec_program(t_mini *mini, char **cmds)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid == 0) //this code will only run on child process
	{
		envp = ft_llto2darr(mini->envp);
		if (execve(cmds[0], cmds, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmds, NSFD); //prints error msg for invalid command
			exit(127);
		}
	}
	else
		waitpid(-1, NULL, 0);
}
