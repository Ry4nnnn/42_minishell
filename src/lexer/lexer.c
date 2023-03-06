/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:14 by welim             #+#    #+#             */
/*   Updated: 2023/03/06 12:20:50 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// (Bonus) Get the command list based on the priorities and logic
// void	get_commands_list(t_mini *mini)
// {

// }

void	print_list(t_list *list)
{
	while (list != NULL)
	{
		printf("[%s]\n", ((t_token *)list->content)->input);
		printf("spliter: %i\n", ((t_token *)list->content)->spliter_type);
		list = list->next;
	}
}

// ()&|><
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
	else if (ft_strncmp(input, ">>", 2) == 0)
		return (REDIR_OUT_A);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (REDIR_IN_A);
	else if (ft_strncmp(input, ">", 1) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(input, "<", 1) == 0)
		return (REDIR_IN);
	return (INVALID);
}

char	*skip_spliter(char *input, int spliter_type)
{
	if (spliter_type == 0)
		return (input);
	else if (spliter_type >= 1 && spliter_type <= 5)
		return (input + 1);
	else if (spliter_type >= 6 && spliter_type <= 9)
		return (input + 2);
	return (input);
}

t_list	*get_new_token(char *input, int spliter_type)
{
	int	quote;
	int	len;
	t_list	*new_node;
	t_token	*new_token;

	quote = 0;
	len = 0;
	input = skip_spliter(input, spliter_type);
	while (input[len] != 0 && (quote != 0 || )) // while unquoted or while quoted but haven't met another spliter, for brackets is haven't met the closing bracket
	{
		if (quote != 0 && input[len] == quote)
			quote = 0;
		else if (quote == 0 && (input[len] == '\"' || input[len] == '\''))
			quote = input[len];
		len++;
	}
	new_token = malloc(sizeof(t_token));
	new_token->input = ft_strndup(input, len);
	new_token->spliter_type = spliter_type;
	new_node = ft_lstnew((void *)new_token);
	return (new_node);
}

t_list	*split_tokens(char *input)
{
	int	i;
	t_list	*list_tokens;
	t_list	*new_token;

	list_tokens = get_new_token(input, BEGINNING);
	i = ft_strlen(((t_token *)list_tokens->content)->input) - 1;
	while (input[++i] != 0)
	{
		if (ft_incharset(HARD_SPLITERS, input[i]))
		{
			new_token = get_new_token(input + i, get_spliter_type(input + i));
			ft_lstadd_back(&list_tokens, new_token);
			i += ft_strlen(((t_token *)new_token->content)->input);
		}
	}
	return (list_tokens);
}

void	lexer(t_mini *mini)
{
	mini->list_tokens = split_tokens(mini->input);
	print_list(mini->list_tokens);
}
