/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 06:25:51 by welim             #+#    #+#             */
/*   Updated: 2023/03/13 18:21:15 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** @brief Find the redir type
* return 0 if input does not contain any redir
* return 1 if contain >
* return 2 if contain >>
* return 3 if contain <
* return 4 if contain <<
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
				cmdblock->file_name = args[j + 1];
				return (i + 1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

// void	set_io(int fd, int std_file_no)
// {
// 	dup2(fd, std_file_no);
// 	close(fd);
// }


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

void	redir_in(t_cmdblock *cmdblock)
{
	int  fd;

	fd = open(cmdblock->file_name, O_CREAT | O_WRONLY, 0644);
	printf ("%s\n", cmdblock->file_name);
	if (fd == -1)
	{
		printf ("Error!\n");
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

void	redir_out(t_cmdblock *cmdblock)
{
	int fd;

	fd = open(cmdblock->file_name, O_RDONLY);
	printf ("%s\n", cmdblock->file_name);
	if (fd == -1)
	{
		printf ("Error!\n");
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int exec_redir(t_mini *mini, t_cmdblock *cmdblock)
{
	int type;

	type = check_redir_type(mini, cmdblock);
	// file = find_file_name(cmdblock);
	if (type == 1 || type == 2)// ">"
	{
		//redir_in
		printf("redir_in\n");
		redir_in(cmdblock);
	}
	if (type == 3 || type == 4) // "<"
	{
		//redir out
		printf("redir_out\n");
		redir_out(cmdblock);
	}
	return (0);
}