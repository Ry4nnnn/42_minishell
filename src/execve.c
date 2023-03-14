/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:26 by welim             #+#    #+#             */
/*   Updated: 2023/03/14 17:53:30 by welim            ###   ########.fr       */
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

/**
 * @brief gets a list executable paths from envp and split it into a 2d array
 * then use access() function to check if input can be found in the list of executable paths
 * when found, this function returns the exec_path for execve() function to execute
 * 
 * @param mini t_mini struct
 * @param cmds input command
**/
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
	return (temp2);
}

int get_exec_argv2(t_mini *mini, t_cmdblock *cmdblock)
{
	int i;
	char **redir;
	// char **res;

	redir = mini->redir;
	while (cmdblock->cmd_argv[i])
	{
		int j = 0;
		while (redir[j])
		{
			i = 0;
			if (ft_strcmp(redir[j], cmdblock->cmd_argv[i]) == 0)
			{
				return (i);
				// res[i + 1] = 0;
				// while (cmdblock->cmd_argv[i])
				// {
				// 	printf ("res[%d]: %s\n", i, res[i]);
				// 	printf ("cmdblock[%d]: %s\n", i, cmdblock->cmd_argv[i]);
				// 	res[i] = cmdblock->cmd_argv[i];
				// 	i--;
				// }
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	**get_exec_argv(t_mini *mini, t_cmdblock *cmdblock)
{
	int size;
	char **res;
	int i = 0;
	int j;

	size  = get_exec_argv2(mini, cmdblock);
	while (size > 0)
	{
		printf ("res[%d]: %s\n", i, res[i]);
		printf ("cmdblock[%d]: %s\n", i, cmdblock->cmd_argv[i]);
		res[i] = cmdblock->cmd_argv[i];
		i++;
		size--;
	}
	res[i] = NULL;
	return (res);
}

// execute non-builtin inputs
int	exec_non_builtins(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*exec_path;
	char	**envp;
	char	**argv;
	// char *test[2];

	// test[0] = "ls" ;
	// test[1] = la
	// test[1] = NULL;
	argv = get_exec_argv(mini, cmdblock);
	cmdblock->need_wait = 1;
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
		if (check_redir_type(mini, cmdblock) == OUT || check_redir_type(mini, cmdblock) == APPEND)
			redir_out(mini, cmdblock); // overwrite the standard output
		if (check_redir_type(mini, cmdblock) == IN)
			redir_in(cmdblock);
		exec_path = get_exec_path(mini, cmdblock->cmd_argv);
		if (!exec_path)
			exit(127);
		if (execve(exec_path, argv, envp) == -1) // if execve fail means (its a invalid command)
		{
			ft_error(mini, cmdblock->cmd_argv, CMD_NF); //prints error msg for invalid command
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

// ./minishell
int	exec_program(t_mini *mini, t_cmdblock *cmdblock)
{
	char	**envp;

	cmdblock->need_wait = 1;
	if (mini->pipes.prep_pipe)
		prepare_pipe(mini);
	cmdblock->pid = fork();
	if (cmdblock->pid == 0) //this code will only run on child process
	{
		signal(SIGINT, SIG_DFL);
		envp = ft_llto2darr(mini->envp, env_to_str);
		if (mini->pipes.do_pipe)
			do_pipe(mini);
		if (access(cmdblock->cmd_argv[0], F_OK) != 0)
		{
			ft_error(mini, cmdblock->cmd_argv, NSFD);
			exit(127);
		}
		if (access(cmdblock->cmd_argv[0], X_OK) != 0)
		{
			ft_error(mini, cmdblock->cmd_argv, PERMISSION_DENIED);
			exit(126);
		}
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
