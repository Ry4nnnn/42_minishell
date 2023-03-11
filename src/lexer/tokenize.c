/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:44 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/11 16:53:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tokens_size(char *input)
{
	int	quote;
	int	i;
	int	size;

	quote = 0;
	i = -1;
	size = 1;
	while (input[++i] != 0)
	{
		if (quote == 0 && input[i] == ' ')
		{
			while (input[i] == ' ' && input[i] != 0)
				i++;
			if (input[i] != 0 && input[i] != '\'' && input[i] != '"')
				size++;
			else
				i--;
		}
		else if (quote == 0 && (input[i] == '\'' || input[i] == '"'))
		{
			quote = input[i];
			while (input[++i] != 0 && input[i] != quote)
				i++;
			quote = 0;
			size++;
		}
		if (input[i] == 0)
			break ;
	}
	return (size);
}

char	*get_next_token(char *input, int *i, int quote)
{
	int	len;
	int	target;
	char	*result;

	len = 0;
	if (quote == '\'' || quote == '"')
	{
		while ((input + *i)[++len] != quote && (input + *i)[len] != 0)
			;
		result = ft_strndup(input + *i + 1, len - 1);
		*i += len;
		return (result); 
	}
	target = ' ';
	while ((input + *i)[len] != 0 && (input + *i)[len] != target)
	{
		if ((input + *i)[len] == '"' || (input + *i)[len] == '\'')
			target = (input + *i)[len];
		len++;
	}
	result = ft_strndup((input + *i), len + (target != ' '));
	*i += len;
	return (result);
}

char	**tokenize_cmd(t_mini *mini, char *input)
{
	int	size;
	int	i;
	int	j;
	char	**result;

	(void)mini;
	size = get_tokens_size(input);
	i = -1;
	j = -1;
	result = malloc((size + 1) * sizeof(char *));
	while (input[++i] != 0)
	{
		result[++j] = get_next_token(input, &i, input[i]);
		printf("token%i: %s\n", j, result[j]);
		if (input[i] == 0)
			break ;
	}
	result[j + 1] = NULL;
	return (result);
}