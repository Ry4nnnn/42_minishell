/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 06:25:51 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 23:52:17 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** @brief Find the redir type
* return 0 if input does not contain any redir
* return 1 if contain >
* return 2 if contain >> (append)
* return 3 if contain <
* return 4 if contain << (heredoc)
**/
int	check_redir_type(t_mini *mini, t_cmdblock *cmdblock)
{
	char **redir;
	int i;
	int j;
	char **args;

	i = 0;
	j = 0;
	args = cmdblock->cmd_argv;
	redir = mini->redir;
	if (args == NULL)
		return (0);
	while (args[j] != NULL)
	{
		i = 0;
		while (redir[i] != 0)
		{
			if (ft_strcmp(redir[i], args[j]) == 0)
			{
				cmdblock->file_name = args[j + 1]; // for now hardcoded
				return (i + 1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

// char *find_file_name(t_cmdblock *cmdblock)
// {
// 	char **args;
// 	int i = 0;
	
// 	args = cmdblock->cmd_argv;
// 	while (args[i])
// 	{
// 		printf ("%s\n", args[i]);
// 		i++;
// 	}
// 	return (args);
// }

void	handle_io(int fd, int std_file_no)
{
	dup2(fd, std_file_no);
	close(fd);
}

void	redir_out(t_mini *mini, t_cmdblock *cmdblock)
{
	pid_t  fd;
	int flag;

	printf ("redirOUT!\n");
	if (check_redir_type(mini, cmdblock) == OUT)
		flag = O_CREAT | O_TRUNC | O_WRONLY;
	if (check_redir_type(mini, cmdblock) == APPEND)
		flag = O_CREAT | O_APPEND | O_WRONLY;
	fd = open(cmdblock->file_name, flag, 0644);
	printf ("file->name: %s\n", cmdblock->file_name);
	if (fd < 0)
	{
		handle_io(fd, STDOUT_FILENO);
		printf ("ErrorOUT!\n");
	}
	handle_io(fd, STDOUT_FILENO);
}

void	redir_in(t_cmdblock *cmdblock)
{
	pid_t fd;

	fd = open(cmdblock->file_name, O_RDONLY);
	printf ("redirIN!\n");
	printf ("file->name: %s\n", cmdblock->file_name);
	if (fd < 0)
	{
		handle_io(fd, STDIN_FILENO);
		printf ("ErrorIN!\n");
	}
	handle_io(fd, STDIN_FILENO);
}

void	done_redir(t_mini *mini)
{
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	if (mini->pipes.do_pipe)
		dup2(mini->pipes.pipe[READ], STDIN_FILENO);
	else
		dup2(mini->pipes.saved_stdin, STDIN_FILENO);
}

void	call_redir(t_mini *mini, t_cmdblock *cmdblock)
{
	// if ()
	if (check_redir_type(mini, cmdblock) == OUT || check_redir_type(mini, cmdblock) == APPEND)
		redir_out(mini, cmdblock); // overwrite the standard output
	if (check_redir_type(mini, cmdblock) == IN)
		redir_in(cmdblock);
}