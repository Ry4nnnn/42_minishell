/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:26 by welim             #+#    #+#             */
/*   Updated: 2023/03/23 15:30:24 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Called in a child process, execute the exec_path program.
 * 
 * @param mini 
 * @param cmdblock 
 * @param exec_path 
 * @return int 
 */
int	execute(t_mini *mini, t_cmdblock *cmdblock)
{
	char	**envp;
	int		i;
	char *exec_path;

	i = 0;
	envp = ft_llto2darr(mini->envp, env_to_str);
	signal(SIGINT, SIG_DFL);
	if (mini->pipes.prep_pipe)
		close(mini->pipes.pipe[READ]);
	if (mini->pipes.do_pipe)
		do_pipe(mini);
	exec_path = get_exec_path(mini, cmdblock->cmd_argv);
	if (exec_path == NULL)
		exit (127);
	if (check_redir_type(mini, cmdblock) != 0)
	{
		if (exec_redir(mini, cmdblock) == ERROR)
			exit (258);// errno not working
		if (execve(exec_path, cmdblock->redir_argv, envp) == -1)
		{
			cmd_error(mini, cmdblock->cmd_argv, CMD_NF);
			exit(127);
		}
		exit(0);
	}
	if (execve(exec_path, cmdblock->cmd_argv, envp) == -1)
	{
		cmd_error(mini, cmdblock->cmd_argv, CMD_NF);
		exit(127);
	}
	exit(0);
}

static int	get_program_permission(t_mini *mini, t_cmdblock *cmdblock)
{
	struct stat	file_stat;

	if (stat(cmdblock->cmd_argv[0], &file_stat) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, NSFD);
		return (127);
	}
	if (S_ISDIR(file_stat.st_mode) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, ISDIR);
		return (126);
	}
	else if (access(cmdblock->cmd_argv[0], X_OK) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, PERMISSION_DENIED);
		return (126);
	}
	return (0);
}

/**
 * @brief Execute the program with absolute path specified
 * 
 * From Bash manual, if a command exited by a fatal signal N, Bash will use the exit status N + 128
 * @param mini 
 * @param cmdblock 
 * @return int 
 */
int	exec_program(t_mini *mini, t_cmdblock *cmdblock)
{
	int		errnum;
	char **envp;

	cmdblock->need_wait = 1;
	errnum = get_program_permission(mini, cmdblock);
	if (errnum != 0)
		return (errnum);
	cmdblock->pid = fork();
	if (cmdblock->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		envp = ft_llto2darr(mini->envp, env_to_str);
		if (mini->pipes.do_pipe)
			do_pipe(mini);
		execve(cmdblock->cmd_argv[0], cmdblock->cmd_argv, envp);
	}
	if (mini->pipes.prep_pipe == 0 || cmdblock->was_in_bracket)
		waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
	if (WIFSIGNALED(cmdblock->estatus))
		return (WTERMSIG(cmdblock->estatus) + 128);
	return (WEXITSTATUS(cmdblock->estatus));
}

/**
 * @brief Execute the commands in PATH
 * From Bash manual, if a command exited by a fatal signal N, Bash will use the exit status N + 128
 * 
 * @param mini 
 * @param cmdblock 
 * @return int 
 */
int	exec_commands(t_mini *mini, t_cmdblock *cmdblock)
{
	cmdblock->need_wait = 1;
	get_exec_argv(mini, cmdblock);
	cmdblock->pid = fork();
	if (cmdblock->pid == 0)
		execute(mini, cmdblock);
	if (mini->pipes.prep_pipe == 0 || cmdblock->was_in_bracket)
		waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
	if (WIFSIGNALED(cmdblock->estatus))
		return (WTERMSIG(cmdblock->estatus) + 128);
	return (WEXITSTATUS(cmdblock->estatus));
}

int	executor(t_mini *mini, t_cmdblock *cmdblock)
{
	signal(SIGINT, SIG_IGN);
	if (cmdblock->cmd_argv == NULL || cmdblock->cmd_argv[0] == NULL)
		return (0);
	if (check_builtins(mini, cmdblock->cmd_argv[0]) == 1)
		return (exec_builtins(mini, cmdblock));
	else if (ft_strchr(cmdblock->cmd_argv[0], '/') != NULL)
		return (exec_program(mini, cmdblock));
	else if (get_env(mini, "PATH") == NULL)
	{
		cmd_error(mini, cmdblock->cmd_argv, NSFD);
		return (127);
	}
	else
		return (exec_commands(mini, cmdblock));
	return (0);
}
