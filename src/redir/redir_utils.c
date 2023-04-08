/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:10:02 by welim             #+#    #+#             */
/*   Updated: 2023/04/08 16:39:41 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	convert_redir_token(char *orig)
{
	int		i;

	i = -1;
	while (orig[++i] != 0)
		orig[i] += 59;
}

/**
 * @brief printf error msg accordingly for redirections
 * 
 * @param mini struct
 * @param cmdblock struct
 * @param i
 * 
 * @return int
 * returns 0 if theres no error
 */
static int	print_redir_error(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	char	*err_token;

	if (!check_is_redir(cmdblock->cmd_argv[i]))
	{
		err_token = ft_strndup(cmdblock->cmd_argv[i], 1);
		convert_redir_token(err_token);
		syntax_error(mini, UNEXPECTED_TOKEN, err_token);
		return (ERROR);
	}
	if (cmdblock->cmd_argv[i + 1]
		&& check_is_redir(cmdblock->cmd_argv[i + 1]))
	{
		err_token = ft_strndup(cmdblock->cmd_argv[i + 1],
				ft_strlen(cmdblock->cmd_argv[i + 1]));
		convert_redir_token(err_token);
		syntax_error(mini, UNEXPECTED_TOKEN, err_token);
		return (ERROR);
	}
	if (cmdblock->cmd_argv[i + 1] == NULL)
	{
		err_token = ft_strdup("newline");
		syntax_error(mini, UNEXPECTED_TOKEN, err_token);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief goes through the input in the struct
 * 			checks if input ends with a redirection
 * 			checks if there a redirection after a redirction
 * 			and prints the error msg accordingly
 * 
 * @param mini struct
 * @param cmdblock struct
 * 
 * @return int
 * returns 0 if theres no error
 */
int	redir_error(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;

	i = 0;
	while (cmdblock->cmd_argv[i])
	{
		if (cmdblock->cmd_argv[i][0] == '\3'
			|| cmdblock->cmd_argv[i][0] == '\1')
		{
			if (print_redir_error(mini, cmdblock, i) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
