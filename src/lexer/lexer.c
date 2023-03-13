/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:14 by welim             #+#    #+#             */
/*   Updated: 2023/03/13 14:18:51 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_list(t_list *list)
// {
// 	while (list != NULL)
// 	{
// 		printf("[%s]\n", ((t_cmdblock *)list->content)->input);
// 		printf("spliter: %i\n", ((t_cmdblock *)list->content)->spliter_type);
// 		list = list->next;
// 	}
// }

// ()&|
int	get_spliter_type(char *input)
{
	if (ft_strncmp(input, "(", 1) == 0)
		return (OPEN_BRACKET);
	else if (ft_strncmp(input, ")", 1) == 0)
		return (CLOSE_BRACKET);
	else if (ft_strncmp(input, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(input, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(input, "|", 1) == 0)
		return (PIPE);
	return (INVALID);
}

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

t_list	*get_bracket_cmdblock(char *input, int spliter_type)
{
	int	quote;
	int	len;
	t_list	*new_node;
	t_cmdblock	*new_cmdblock;

	quote = 0;
	len = 0;
	input++;
	while (*input == ' ')
		input++;
	while (input[len] != 0 && 
		(quote != 0 || get_spliter_type(input + len) != CLOSE_BRACKET)) // while unquoted or while quoted but haven't met another spliter, for brackets is haven't met the closing bracket
	{
		if (quote != 0 && input[len] == quote)
			quote = 0;
		else if (quote == 0 && (input[len] == '\"' || input[len] == '\''))
			quote = input[len];
		len++;
	}
	new_cmdblock = malloc(sizeof(t_cmdblock));
	new_cmdblock->input = ft_strndup(input, len);
	new_cmdblock->spliter_type = spliter_type;
	new_cmdblock->in_bracket = 1;
	new_node = ft_lstnew((void *)new_cmdblock);
	return (new_node);
}

t_list	*get_new_cmdblock(char *input, int spliter_type)
{
	int	quote;
	int	len;
	t_list	*new_node;
	t_cmdblock	*new_cmdblock;

	quote = 0;
	len = 0;
	if (spliter_type == OPEN_BRACKET)
		return (get_bracket_cmdblock(input, spliter_type));
	input = skip_spliter(input, spliter_type);
	while (*input == ' ')
		input++;
	while (input[len] != 0) // while unquoted or while quoted but haven't met another spliter, for brackets is haven't met the closing bracket
	{
		if (quote == 0 && get_spliter_type(input + len) == OPEN_BRACKET)
			return (get_bracket_cmdblock(input + len, spliter_type));
		if (quote != 0 && input[len] == quote)
			quote = 0;
		else if (quote == 0 && (input[len] == '\"' || input[len] == '\''))
			quote = input[len];
		len++;
		if (quote == 0 && get_spliter_type(input + len) != INVALID)
			break ;
	}
	new_cmdblock = malloc(sizeof(t_cmdblock));
	new_cmdblock->input = ft_strndup(input, len);
	new_cmdblock->spliter_type = spliter_type;
	new_cmdblock->in_bracket = 0;
	new_node = ft_lstnew((void *)new_cmdblock);
	return (new_node);
}

t_list	*split_cmdblocks(char *input)
{
	int	i;
	t_list	*cmdblock_list;
	t_list	*new_cmdblock;

	cmdblock_list = get_new_cmdblock(input, BEGINNING);
	i = ft_strlen(((t_cmdblock *)cmdblock_list->content)->input) - 1;
	while (input[++i] != 0)
	{
		if (get_spliter_type(input + i) != INVALID && get_spliter_type(input + i) != CLOSE_BRACKET)
		{
			new_cmdblock = get_new_cmdblock(input + i, get_spliter_type(input + i));
			ft_lstadd_back(&cmdblock_list, new_cmdblock);
			i += ft_strlen(((t_cmdblock *)new_cmdblock->content)->input);
		}
	}
	return (cmdblock_list);
}
