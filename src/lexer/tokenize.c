/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:44 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/04 22:54:04 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the size of the token array for malloc use.
 * 
 * @param input 
 * @return int 
 */
int	get_tokens_size(char *input)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (input[++i] != 0)
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			i += detect_quote_token(input + i, input[i]);
			size++;
		}
		else if (input[i] != ' ')
		{
			i += detect_normal_token(input + i);
			size++;
		}
		if (input[i] == 0)
			break ;
	}
	return (size);
}

static char	*get_quote_token(char *input, int i, int quote)
{
	int	len;

	len = 0;
	while ((input + i)[++len] != quote && (input + i)[len] != 0)
		;
	return (ft_strndup(input + i + 1, len - 1));
}

/**
 * @brief Get the next token.
 * If quote is either ' or ", get the content inside the quotes.
 * Otherwise, get until the next space appeared.
 * During the loop if a quote appeared, change to target the quote.
 * 
 * @param input 
 * @param i 
 * @param quote 
 * @return char* 
 */
char	*get_next_token(char *input, int i, int quote)
{
	int		len;
	int		target;

	len = 0;
	if (quote == '\'' || quote == '"')
		return (get_quote_token(input, i, quote));
	target = ' ';
	while ((input + i)[len] != 0 && (input + i)[len] != target)
	{
		if (target == ' ' && ft_strchr("<>", (input + i)[len]))
		{
			if (len != 0)
				return (ft_strndup((input + i), len));
			while (ft_strchr("<>", (input + i)[len]))
				len++;
			return (ft_strndup((input + i), len));
		}
		if ((input + i)[len] == '\'' || (input + i)[len] == '"')
			target = (input + i)[len];
		len++;
	}
	return (ft_strndup((input + i), len + (target != ' ')));
}

/**
 * @brief Tokenize the command input, works kind of like ft_split
 * 
 * @param mini 
 * @param input 
 * @return char** 
 */
char	**tokenize_cmd(t_mini *mini, char *input)
{
	int		i;
	int		j;
	char	**result;
	int		quote;

	(void)mini;
	i = -1;
	j = -1;
	result = malloc((get_tokens_size(input) + 1) * sizeof(char *));
	while (input[++i] != 0)
	{
		if (input[i] == ' ')
			continue ;
		quote = input[i];
		result[++j] = get_next_token(input, i, quote);
		i += ft_strlen(result[j]);
		if (input[i] != ' ')
			i--;
		if (quote == '\'' || quote == '"')
			i += 2;
		if (input[i] == 0)
			break ;
	}
	result[j + 1] = NULL;
	return (result);
}
