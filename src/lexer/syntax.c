/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:08:58 by codespace         #+#    #+#             */
/*   Updated: 2023/03/18 15:37:02 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief trim the leading and tailing spaces from the input
 * 
 * @param input 
 * @return char* 
 */
char	*trim_input(char *input)
{
	char	*result;

	result = ft_strtrim(input, " ");
	free(input);
	return (result);
}

/**
 * @brief Find the unexpected token in the brackets syntax error string.
 * Token string will be freed in the syntax_error() function.
 * 
 * @param input 
 * @return char* 
 */
static char	*find_unexpected_token(char *input)
{
	int	i;

	if (input[0] == ')')
		return (ft_strdup(")"));
	input++;
	while (*input == ' ')
		input++;
	i = -1;
	while (input[++i] != 0)
	{
		if (input[i] == ' ' || input[i] == '(' || input[i] == ')')
			break ;
	}
	if (i == 0)
		return (ft_strdup("newline"));
	return (ft_strndup(input, i));
}

/**
 * @brief
 * Types of checking:
 * 1. If there is a bracket unquoted
 * 		Before in split cmdblocks all () for priorities are trimed,
 * 		a unquoted bracket here means there is unpaired or illegal brackets.
 * 2. If there is unclosed quote
 * 
 * @param mini 
 * @param cmdblock 
 * @return int 
 */
int	check_cmdblock_syntax(t_mini *mini, t_cmdblock *cmdblock)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (cmdblock->input[++i] != 0)
	{
		if (quote == 0
			&& (cmdblock->input[i] == '(' || cmdblock->input[i] == ')'))
		{
			return (syntax_error(mini, UNEXPECTED_TOKEN,
					find_unexpected_token(cmdblock->input + i)));
		}
		else if (quote == 0
			&& (cmdblock->input[i] == '\'' || cmdblock->input[i] == '"'))
			quote = cmdblock->input[i];
		else if (quote != 0 && cmdblock->input[i] == quote)
			quote = 0;
	}
	if (quote != 0)
		return (syntax_error(mini, UNCLOSED_QUOTE, NULL));
	return (1);
}

/**
 * @brief Check if the syntax of all cmdblocks are correct
 * 
 * @param mini 
 * @param cmdblocks_list 
 * @return int 
 */
int	check_syntax(t_mini *mini, t_list *cmdblocks_list)
{
	t_cmdblock	*cmdblock;

	while (cmdblocks_list != NULL)
	{
		cmdblock = (t_cmdblock *)cmdblocks_list->content;
		if (check_cmdblock_syntax(mini, cmdblock) == 0)
			return (0);
		cmdblocks_list = cmdblocks_list->next;
	}
	return (1);
}
