/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:26 by welim             #+#    #+#             */
/*   Updated: 2023/03/28 14:51:00 by welim            ###   ########.fr       */
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
	mini->env = ft_llto2darr(mini->envp, env_to_str);
	signal(SIGINT, SIG_DFL);
	if (mini->pipes.prep_pipe)
		close(mini->pipes.pipe[READ]);
	if (mini->pipes.do_pipe)
		do_pipe(mini);
	mini->exec_path = get_exec_path(mini, cmdblock->cmd_argv);
	if (check_redir_type(mini, cmdblock) != 0)
	{
		if (execve(mini->exec_path, cmdblock->redir_argv, mini->env) == -1)
		{
			cmd_error(mini, cmdblock->cmd_argv, CMD_NF);
			exit(127);
		}
		exit(0);
	}
	if (execve(mini->exec_path, cmdblock->cmd_argv, mini->env) == -1)
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

	cmdblock->need_wait = 1;
	errnum = get_program_permission(mini, cmdblock);
	mini->exec_path = cmdblock->cmd_argv[0];
	if (errnum != 0)
		return (errnum);
	cmdblock->pid = fork();
	if (cmdblock->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (mini->pipes.do_pipe)
			do_pipe(mini);
		execve(mini->exec_path, cmdblock->cmd_argv, mini->env);
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
	
	// char *buff = ft_calloc(1, 222);
	// read(STDIN_FILENO, buff, 222);
	// printf("before execve %s\n", buff);

	cmdblock->pid = fork();
	if (cmdblock->pid == 0)
		execute(mini, cmdblock);
	done_redir(mini);
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
	if (ft_strcmp(cmdblock->cmd_argv[0], ">") == 0 && cmdblock->cmd_argv[1] != NULL) //check if redir exist in input (special)
	{
		if (redir_error(mini, cmdblock) == ERROR)
			return (258);
		cmdblock->file_name = cmdblock->cmd_argv[1];
		redir_out(mini, cmdblock->file_name, OUT);
		done_redir(mini);
		return (0);// if i dont return 0 then it will continue and will show up command not found
	}
	if (ft_strcmp(cmdblock->cmd_argv[0], ">>") == 0 && cmdblock->cmd_argv[1] != NULL) //check if redir exist in input (special)
	{
		if (redir_error(mini, cmdblock) == ERROR)
			return (258);
		cmdblock->file_name = cmdblock->cmd_argv[1];
		redir_out(mini, cmdblock->file_name, APPEND);
		done_redir(mini);
		return (0);// if i dont return 0 then it will continue and will show up command not found
	}
	if (ft_strcmp(cmdblock->cmd_argv[0], "<") == 0 && cmdblock->cmd_argv[1] != NULL) //check if redir exist in input (special)
	{
		if (redir_error(mini, cmdblock) == ERROR)
			return (258);
		cmdblock->file_name = cmdblock->cmd_argv[1];
		redir_in(mini, cmdblock, cmdblock->file_name, IN);
		done_redir(mini);
		return (0);// if i dont return 0 then it will continue and will show up command not found
	}
	if (ft_strcmp(cmdblock->cmd_argv[0], "<<") == 0 && cmdblock->cmd_argv[1] != NULL) //check if redir exist in input (special)
	{
		if (redir_error(mini, cmdblock) == ERROR)
			return (258);
		cmdblock->file_name = cmdblock->cmd_argv[1];
		redir_in(mini, cmdblock, cmdblock->file_name, HEREDOC);
		finish_pipe(mini);
		return (0);// if i dont return 0 then it will continue and will show up command not found
	}
	if (check_redir_type(mini, cmdblock) != 0) // check if redir exist in input
	{
		if (exec_redir(mini, cmdblock) == ERROR)
			return (258);
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
