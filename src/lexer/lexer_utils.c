/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:58:16 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/08 16:40:26 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expand the string s by inserting the string 'insert' into
 * the position start, and ignore the n characters from the string s.
 * For example: ft_strexpand(&"1234567", "abcde", 2, 3) => "12abcde67"
 * 
 * @param s 
 * @param insert 
 * @param start 
 * @param n 
 */
void	ft_strexpand(char **s, char *insert, int start, int n)
{
	char	*result;
	int		len;
	int		insert_len;
	int		i;

	if (start > (int)ft_strlen(*s) || start < 0 || n < 0)
		return ;
	if (n > (int)ft_strlen(*s + start))
		n = ft_strlen(*s + start);
	insert_len = ft_strlen(insert);
	len = ft_strlen(*s) + insert_len - n;
	result = malloc((len + 1) * sizeof(char));
	result[len] = 0;
	i = -1;
	while (++i < start)
		result[i] = (*s)[i];
	while (++i - start - 1 < insert_len)
		result[i - 1] = insert[i - 1 - start];
	i += n;
	while (++i - 2 - n < len)
		result[i - 2 - n] = (*s)[i - 2 - insert_len];
	free(*s);
	*s = result;
}

/**
 * @brief Ignore the spliter in the string
 * 
 * @param input 
 * @param spliter_type 
 * @return char* 
 */
char	*skip_spliter(char *input, int spliter_type)
{
	if (spliter_type == 0)
		return (input);
	else if (spliter_type == PIPE)
		return (input + 1);
	else if (spliter_type >= AND && spliter_type <= OR)
		return (input + 2);
	return (input);
}

/**
 * @brief Get the spliter type
 * 
 * @param input 
 * @return int 
 */
int	get_spliter_type(char *input)
{
	if (ft_strncmp(input, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(input, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(input, "|", 1) == 0)
		return (PIPE);
	return (INVALID);
}

int	detect_quote_token(char *input, int quote)
{
	int	i;

	i = 0;
	while (input[++i] != 0)
	{
		if (input[i] == quote)
			break ;
	}
	return (i);
}

/**
 * @brief Detect the length of a normal (space separated) token.
 * 
 * @param input 
 * @return int 
 */
int	detect_normal_token(char *input)
{
	int		i;
	char	*special_token;

	special_token = ft_strchr("\1\3", input[0]);
	i = -1;
	while (input[++i] != 0)
	{
		if (input[i] == '\'' || input[i] == '"')
			i += detect_quote_token(input + i, input[i]);
		if (!special_token && ft_strchr("\1\3", input[i]))
		{
			i--;
			break ;
		}
		if ((special_token && !ft_strchr("\1\3", input[i]))
			|| input[i] == ' ' || input[i] == 0)
			break ;
	}
	if (input[i] == 0 || special_token)
		return (i - 1);
	return (i);
}
