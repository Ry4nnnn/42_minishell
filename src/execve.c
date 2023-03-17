/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:26 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 14:51:05 by wangxuerui       ###   ########.fr       */
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
		cmd_error(mini, cmds, CMD_NF);
		ft_free2darr((void *)path); // free 2d array
		return (NULL);
	}
	ft_free2darr((void *)path); // free 2d array
	return (temp2);
}

static int	get_exec_argv_sz(t_mini *mini, t_cmdblock *cmdblock)
{
	char **cmd_argv = cmdblock->cmd_argv;
	char **redir = mini->redir;
	int i = 0;
	int j;

	while (cmd_argv[i])
	{
		j = 0;
		while (redir[j])
		{
			// printf ("comparing argv: %s, redir: %s \n", cmd_argv[i], redir[j]);
			if (ft_strcmp(cmd_argv[i], redir[j]) == 0)
			{
				// printf ("HEREcmd_argv: %s\n", cmd_argv[i]);
				// printf ("HEREredir: %s\n", redir[j]);
				return (i) ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

//get the input in 2d array and check if theres a redir
//and remove the args after the redir including the redir
void get_exec_argv(t_mini *mini, t_cmdblock *cmdblock)
{
	int i = get_exec_argv_sz(mini, cmdblock);
	char **cmd_argv = cmdblock->cmd_argv;
	char **res;
	int j;
	int k;

	k = 0;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	while (i--)
	{
		j = 0;
		// printf("K:%d\n", k);
		res[k] = malloc(sizeof(char) * (ft_strlen(cmdblock->cmd_argv[k]) + 1));
		while (cmd_argv[k][j])
		{
			res[k][j] = cmd_argv[k][j];
			j++;
		}
		res[k][j] = '\0';
		k++;
	}
	res[k] = NULL;
	cmdblock->redir_argv = res;
	// free
}

// execute non-builtin inputs
int	exec_non_builtins(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*exec_path;
	char	**envp;

	cmdblock->need_wait = 1;
	if (mini->pipes.prep_pipe)
		prepare_pipe(mini);
	get_exec_argv(mini, cmdblock); // cmdblock->redir_argv
	cmdblock->pid = fork();
	if (cmdblock->pid == 0) //this code will only run on child process
	{
		signal(SIGINT, SIG_DFL);
		envp = ft_llto2darr(mini->envp, env_to_str);// convert linked list env to a 2d array
		if (mini->pipes.prep_pipe)
			close(mini->pipes.pipe[READ]);
		if (mini->pipes.do_pipe)
			do_pipe(mini);
		exec_path = get_exec_path(mini, cmdblock->cmd_argv);
		if (!exec_path)
			exit(127);
		if (check_redir_type(mini, cmdblock) != 0) // checking if input has a redir type
		{
			call_redir(mini, cmdblock);
			if (execve(exec_path, cmdblock->redir_argv, envp) == -1) // if execve fail means (its a invalid command)
			{
				cmd_error(mini, cmdblock->cmd_argv, CMD_NF); //prints error msg for invalid command
				exit(127);
			}
			exit(0);
		}
		if (execve(exec_path, cmdblock->cmd_argv, envp) == -1) // if execve fail means (its a invalid command)
		{
			cmd_error(mini, cmdblock->cmd_argv, CMD_NF); //prints error msg for invalid command
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
			cmd_error(mini, cmdblock->cmd_argv, NSFD);
			exit(127);
		}
		if (access(cmdblock->cmd_argv[0], X_OK) != 0)
		{
			cmd_error(mini, cmdblock->cmd_argv, PERMISSION_DENIED);
			exit(126);
		}
		if (execve(cmdblock->cmd_argv[0], cmdblock->cmd_argv, envp) == -1) // if execve fail means (its a invalid command)
		{
			cmd_error(mini, cmdblock->cmd_argv, PERMISSION_DENIED); //prints error msg for invalid command
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
