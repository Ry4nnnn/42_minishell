/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:14 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 21:49:56 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmdblock	*get_new_cmdblock(int spliter_type, int in_bracket)
{
	t_cmdblock	*new_cmdblock;

	new_cmdblock = malloc(sizeof(t_cmdblock));
	if (new_cmdblock == NULL)
		return (NULL);
	new_cmdblock->spliter_type = spliter_type;
	new_cmdblock->in_bracket = in_bracket;
	new_cmdblock->was_in_bracket = 0;
	return (new_cmdblock);
}

t_list	*get_bracket_cmdblock(char *input, int spliter_type)
{
	int			quote;
	int			len;
	t_cmdblock	*new_cmdblock;

	quote = 0;
	len = 1;
	while (input[len] != 0
		&& (quote != 0 || ft_strncmp(input + len, ")", 1) != 0))
	{
		if (quote != 0 && input[len] == quote)
			quote = 0;
		else if (quote == 0 && (input[len] == '\"' || input[len] == '\''))
			quote = input[len];
		len++;
	}
	if (get_new_cmdblock(spliter_type, 1) == NULL)
		return (NULL);
	if (input[len] != ')')
		new_cmdblock->input = ft_strndup(input, len);
	else
		new_cmdblock->input = ft_strndup(input + 1, len - 1);
	return (ft_lstnew((void *)new_cmdblock));
}

t_list	*get_new_cmdblock(char *input, int spliter_type)
{
	int			quote;
	int			len;
	t_cmdblock	*new_cmdblock;

	quote = 0;
	len = 0;
	input = skip_spliter(input, spliter_type);
	while (*input == ' ')
		input++;
	if (ft_strncmp(input, "(", 1) == 0)
		return (get_bracket_cmdblock(input, spliter_type));
	while (input[++len] != 0)
	{
		if (quote == 0 && get_spliter_type(input + len) != INVALID)
			break ;
		if (quote != 0 && input[len] == quote)
			quote = 0;
		else if (quote == 0 && (input[len] == '\"' || input[len] == '\''))
			quote = input[len];
	}
	if (get_new_cmdblock(spliter_type, 0) == NULL)
		return (NULL);
	new_cmdblock->input = ft_strndup(input, len);
	return (ft_lstnew((void *)new_cmdblock));
}

t_list	*split_cmdblocks(char *input, int bracket)
{
	int		i;
	t_list	*cmdblock_list;
	t_list	*new_cmdblock;

	cmdblock_list = get_new_cmdblock(input, BEGINNING);
	((t_cmdblock *)cmdblock_list->content)->was_in_bracket = bracket;
	i = ft_strlen(((t_cmdblock *)cmdblock_list->content)->input) - 1;
	while (input[++i] != 0)
	{
		if (get_spliter_type(input + i) != INVALID)
		{
			new_cmdblock = get_new_cmdblock(input + i,
					get_spliter_type(input + i));
			((t_cmdblock *)new_cmdblock->content)->was_in_bracket = bracket;
			ft_lstadd_back(&cmdblock_list, new_cmdblock);
			i += ft_strlen(((t_cmdblock *)new_cmdblock->content)->input);
		}
	}
	return (cmdblock_list);
}
