/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:14 by welim             #+#    #+#             */
/*   Updated: 2023/04/06 21:30:58 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new cmdblock, by passing in the spliter type,
 * If the function is called from get_bracket_cmdblock function,
 * the in_bracket argument will be 1 instead of 0 as in get_new_cmdblock.
 * 
 * @param spliter_type 
 * @param in_bracket 
 * @return t_cmdblock* 
 */
static t_cmdblock	*create_new_cmdblock(int spliter_type, int in_bracket)
{
	t_cmdblock	*new_cmdblock;

	new_cmdblock = malloc(sizeof(t_cmdblock));
	if (new_cmdblock == NULL)
		return (NULL);
	new_cmdblock->spliter_type = spliter_type;
	new_cmdblock->in_bracket = in_bracket;
	new_cmdblock->need_wait = 0;
	new_cmdblock->cmd_argv = NULL;
	return (new_cmdblock);
}

/**
 * @brief Works similar to get_new_cmdblock, but the loop ends when hitting ')'
 * And when the end is not ')', it means there is a dangling bracket,
 * later the handler will trigger syntax error.
 * 
 * @param input 
 * @param spliter_type 
 * @return t_list* 
 */
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
	new_cmdblock = create_new_cmdblock(spliter_type, 1);
	if (new_cmdblock == NULL)
		return (NULL);
	if (input[len] != ')')
		new_cmdblock->input = ft_strndup(input, len);
	else
		new_cmdblock->input = ft_strndup(input + 1, len - 1);
	return (ft_lstnew((void *)new_cmdblock));
}

/**
 * @brief Get the new cmdblock from the current position of input string.
 * First skip the spliter characters, for example if the spliter is &&,
 * skip the 2 characters and directly go into the content.
 * After this, ignore leading the spaces.
 * If the first character after leading spaces is '(', get the cmdblock
 * using the get_bracket_cmdblock() instead.
 * The quote variable is used to track if now the string is quoted or not,
 * and meanwhile track the type of quote by the value itself.
 * Loop through the input string, until hitting another spliter while unquoted.
 * Then create the new cmdblock and pass in the spliter type for later use.
 * 
 * @param input 
 * @param spliter_type 
 * @return t_list* 
 */
t_list	*get_new_cmdblock(char *input, int spliter_type)
{
	int			quote;
	int			len;
	t_cmdblock	*new_cmdblock;

	quote = 0;
	len = -1;
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
	new_cmdblock = create_new_cmdblock(spliter_type, 0);
	if (new_cmdblock == NULL)
		return (NULL);
	new_cmdblock->input = ft_strndup(input, len);
	return (ft_lstnew((void *)new_cmdblock));
}

/**
 * @brief Split command blocks by spliters &&, || and |, into a linked list.
 * First get the special cmdblock BEGINNING,
 * and then loop through the input string,
 * when meet a spliter, get the cmdblock by the function get_new_cmdblock().
 * After getting the cmdblock, add_back to the linked list,
 * and jump the index i to the end of the cmdblock.
 * 
 * @param input 
 * @param bracket 
 * @return t_list* 
 */
t_list	*split_cmdblocks(char *input, int bracket)
{
	int		i;
	t_list	*cmdblock_list;
	t_list	*new_cmdblock;
	int		quote;

	(void) bracket;
	quote = 0;
	cmdblock_list = get_new_cmdblock(input, BEGINNING);
	i = ft_strlen(((t_cmdblock *)cmdblock_list->content)->input) - 1;
	while (input[++i] != 0)
	{
		if (quote == 0 && (input[i] == '\'' || input[i] == '"'))
			quote = input[i++];
		if (quote && input[i] != quote)
			continue ;
		if (get_spliter_type(input + i) != INVALID)
		{
			new_cmdblock = get_new_cmdblock(input + i,
					get_spliter_type(input + i));
			ft_lstadd_back(&cmdblock_list, new_cmdblock);
			i += ft_strlen(((t_cmdblock *)new_cmdblock->content)->input);
		}
	}
	return (cmdblock_list);
}
