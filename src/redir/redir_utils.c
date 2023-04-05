/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:10:02 by welim             #+#    #+#             */
/*   Updated: 2023/04/05 15:19:42 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief goes through the user input in the struct
 * 			finds the first redir in the input
 * 
 * @param mini struct
 * @param cmdblock struct
 * 
 * @return int
 * return 0 if input does not contain any redir
 * return 1 if is > (redir out)
 * return 2 if is >> (append)
 * return 3 if is < (redir in)
 * return 4 if is << (heredoc)
 */
int	check_redir_type(t_mini *mini, t_cmdblock *cmdblock)
{
	char	**redir;
	char	**args;
	int		i;
	int		j;

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
				return (i + 1);
			i++;
		}
		j++;
	}
	return (0);
}

/**
 * @brief goes through the str and search for redir
 * 
 * @param mini struct
 * @param str string
 * 
 * @return int
 * return 0 if true
 * return 1 if false
 */
int	check_for_redir(t_mini *mini, char *str)
{
	int		i;

	i = 0;
	while (mini->redir[i])
	{
		if (ft_strcmp(str, mini->redir[i]) == 0)
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

int	check_is_redir(char *str)
{
	if (ft_strcmp("\3", str) == 0)
		return (1);
	if (ft_strcmp("\3\3", str) == 0)
		return (1);
	if (ft_strcmp("\1", str) == 0)
		return (1);
	if (ft_strcmp("\1\1", str) == 0)
		return (1);
	else
		return (0);
}

void	convert_redir_token(char *orig)
{
	int i;

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
		if (cmdblock->cmd_argv[i][0] == '\3' || cmdblock->cmd_argv[i][0] == '\1')
		{
			if (print_redir_error(mini, cmdblock, i) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
