/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:26 by welim             #+#    #+#             */
/*   Updated: 2023/04/06 21:45:08 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Called in a child process, execute the exec_path program.
 * 
 * @param mini 
 * @param cmdblock 
 * @return int 
 */
int	execute(t_mini *mini, t_cmdblock *cmdblock)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	mini->env = ft_llto2darr(mini->envp, env_to_str);
	if (mini->pipes.prep_pipe)
		close(mini->pipes.pipe[READ]);
	if (mini->pipes.do_pipe)
		do_pipe(mini);
	if (execve(mini->exec_path, cmdblock->cmd_argv, mini->env) == -1)
	{
		cmd_error(mini, cmdblock->cmd_argv, CMD_NF);
		exit(127);
	}
	exit(0);
}

/**
 * @brief Execute the program with absolute path specified
 * 
 * From Bash manual, if a command exited by a fatal signal N
 * Bash will use the exit status N + 128
 * @param mini 
 * @param cmdblock 
 * @return int 
 */
int	exec_program(t_mini *mini, t_cmdblock *cmdblock)
{
	int		errnum;

	errnum = get_program_permission(mini, cmdblock);
	if (errnum != 0)
		return (errnum);
	if (cmdblock->cmd_argv == NULL || cmdblock->cmd_argv[0] == NULL)
		return (0);
	mini->exec_path = cmdblock->cmd_argv[0];
	if (!mini->exec_path)
		return (127);
	cmdblock->need_wait = 1;
	cmdblock->pid = fork();
	if (cmdblock->pid == 0)
		execute(mini, cmdblock);
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
	if (mini->pipes.prep_pipe == 0)
		waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
	if (WIFSIGNALED(cmdblock->estatus))
		return (WTERMSIG(cmdblock->estatus) + 128);
	return (WEXITSTATUS(cmdblock->estatus));
}

/**
 * @brief Execute the commands in PATH
 * From Bash manual, if a command exited by a fatal signal N
 * Bash will use the exit status N + 128
 * 
 * @param mini 
 * @param cmdblock 
 * @return int 
 */
int	exec_commands(t_mini *mini, t_cmdblock *cmdblock)
{
	if (cmdblock->cmd_argv == NULL || cmdblock->cmd_argv[0] == NULL)
		return (0);
	mini->exec_path = get_exec_path(mini, cmdblock->cmd_argv);
	if (!mini->exec_path)
		return (127);
	cmdblock->need_wait = 1;
	cmdblock->pid = fork();
	if (cmdblock->pid == 0)
		execute(mini, cmdblock);
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
	free (mini->exec_path);
	done_redir(mini, 0);
	if (mini->pipes.prep_pipe == 0)
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
	if (redir_error(mini, cmdblock) == ERROR)
		return (258);
	if (check_redir_type(mini, cmdblock) != 0)
	{
		if (exec_redir(mini, cmdblock) == -1)
			return (0);
		get_exec_argv(mini, cmdblock);
	}
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
