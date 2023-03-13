/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:08:58 by codespace         #+#    #+#             */
/*   Updated: 2023/03/13 11:42:58 by codespace        ###   ########.fr       */
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

int	check_syntax(t_mini *mini)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (mini->input[++i] != 0)
	{
		if (quote == 0 && (mini->input[i] == '(' || mini->input[i] == ')'))
		{
			syntax_error(mini, UNEXPECTED_TOKEN, find_unexpected_token(mini->input + i));
			g_errno = 258;
			return (0);
		}
		else if (quote == 0 && (mini->input[i] == '\'' || mini->input[i] == '"'))
			quote = mini->input[i];
		else if (quote != 0 && mini->input[i] == quote)
			quote = 0;
	}
	if (quote != 0)
	{
		syntax_error(mini, UNCLOSED_QUOTE, NULL);
		return (0);
	}
	return (1);
}