/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:44 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/18 17:04:31 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Detect the length of a normal (space separated) token.
 * 
 * @param input 
 * @return int 
 */
static int	detect_normal_token(char *input)
{
	int	i;

	i = -1;
	while (input[++i] != 0)
	{
		if (input[i] != ' ')
			break ;
	}
	if (input[i] == 0)
		return (i - 1);
	return (i);
}

/**
 * @brief Detect the length of a quote token
 * 
 * @param input 
 * @param quote 
 * @return int 
 */
static int	detect_quote_token(char *input, int quote)
{
	int	i;

	i = -1;
	while (input[++i] != 0)
	{
		if (input[i] == quote)
			break ;
	}
	return (i);
}

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
	size = 1;
	while (input[++i] != 0)
	{
		if (input[i] == ' ')
		{
			i += detect_normal_token(input + i);
			size++;
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			i += detect_quote_token(input + i, input[i]);
			size++;
		}
		if (input[i] == 0)
			break ;
	}
	return (size);
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
	char	*result;

	len = 0;
	if (quote == '\'' || quote == '"')
	{
		while ((input + i)[++len] != quote && (input + i)[len] != 0)
			;
		result = ft_strndup(input + i + 1, len - 1);
		return (result);
	}
	target = ' ';
	while ((input + i)[len] != 0 && (input + i)[len] != target)
	{
		if ((input + i)[len] == '"' || (input + i)[len] == '\'')
			target = (input + i)[len];
		len++;
	}
	result = ft_strndup((input + i), len + (target != ' '));
	return (result);
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
	int		quote;
	char	**result;

	(void)mini;
	i = -1;
	j = -1;
	result = malloc((get_tokens_size(input) + 1) * sizeof(char *));
	while (input[++i] != 0)
	{
		while (input[i] == ' ')
			i++;
		quote = input[i];
		result[++j] = get_next_token(input, i, quote);
		i += ft_strlen(result[j]);
		if (quote == '\'' || quote == '"')
			i += 2;
		if (input[i] == 0)
			break ;
	}
	result[j + 1] = NULL;
	return (result);
}
