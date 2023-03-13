/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:26 by welim             #+#    #+#             */
/*   Updated: 2023/03/13 18:24:02 by welim            ###   ########.fr       */
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
int	exec_non_builtins(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*exec_path;
	char	**envp;

	printf("execve run\n");
	exec_path = get_exec_path(mini, cmdblock->cmd_argv);
	if (!exec_path)
		return (127);
	if (mini->pipes.prep_pipe)
		prepare_pipe(mini);
	cmdblock->pid = fork();
	if (cmdblock->pid == 0) //this code will only run on child process
	{
		signal(SIGINT, SIG_DFL);
		envp = ft_llto2darr(mini->envp, env_to_str);// translate updated linked list env to a 2d array
		if (mini->pipes.prep_pipe)
			close(mini->pipes.pipe[READ]);
		if (mini->pipes.do_pipe)
			do_pipe(mini);
		if (execve(exec_path, cmdblock->cmd_argv, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmdblock->cmd_argv, CMD_NF); //prints error msg for invalid command
			exit(127);
		}
		exit(0);
	}
	if (mini->pipes.prep_pipe == 0)
		waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
	free (exec_path);
	if (mini->pipes.do_pipe || mini->pipes.prep_pipe)
		finish_pipe(mini);
	if (WIFSIGNALED(cmdblock->estatus))
		return (WTERMSIG(cmdblock->estatus) + 128); // From Bash manual, if a command exited by a fatal signal N, Bash will use the exit status N + 128
	return (WEXITSTATUS(cmdblock->estatus));
}

// ./minishell
int	exec_program(t_mini *mini, t_cmdblock *cmdblock)
{
	char	**envp;

	if (mini->pipes.prep_pipe)
		prepare_pipe(mini);
	cmdblock->pid = fork();
	if (cmdblock->pid == 0) //this code will only run on child process
	{
		signal(SIGINT, SIG_DFL);
		envp = ft_llto2darr(mini->envp, env_to_str);
		if (mini->pipes.do_pipe)
			do_pipe(mini);
		if (execve(cmdblock->cmd_argv[0], cmdblock->cmd_argv, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmdblock->cmd_argv, PERMISSION_DENIED); //prints error msg for invalid command
			exit(127);
		}
		exit(0);
	}
	if (mini->pipes.prep_pipe == 0)
		waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
	if (mini->pipes.do_pipe || mini->pipes.prep_pipe)
		finish_pipe(mini);
	if (WIFSIGNALED(cmdblock->estatus))
		return (WTERMSIG(cmdblock->estatus) + 128); // From Bash manual, if a command exited by a fatal signal N, Bash will use the exit status N + 128
	return (WEXITSTATUS(cmdblock->estatus));
}
