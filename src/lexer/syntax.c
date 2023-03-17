/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:08:58 by codespace         #+#    #+#             */
/*   Updated: 2023/03/17 12:49:15 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_input(char *input)
{
	char	*result;

	result = ft_strtrim(input, " ");
	free(input);
	return (result);
}

char	*find_unexpected_token(char *input)
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

int	check_cmdblock_syntax(t_mini *mini, t_cmdblock *cmdblock)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (cmdblock->input[++i] != 0)
	{
		if (quote == 0 && (cmdblock->input[i] == '(' || cmdblock->input[i] == ')'))
		{
			syntax_error(mini, UNEXPECTED_TOKEN, find_unexpected_token(cmdblock->input + i));
			g_errno = 258;
			return (0);
		}
		else if (quote == 0 && (cmdblock->input[i] == '\'' || cmdblock->input[i] == '"'))
			quote = cmdblock->input[i];
		else if (quote != 0 && cmdblock->input[i] == quote)
			quote = 0;
	}
	if (quote != 0)
	{
		syntax_error(mini, UNCLOSED_QUOTE, NULL);
		return (0);
	}
	return (1);
	
}

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