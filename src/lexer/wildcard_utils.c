/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:00:41 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/03/19 00:16:41 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sort the d_names linked list in ascending order
 * 
 * @param names d_names linked list ptr
 */
void	sort_names_list(t_list **names)
{
	t_list	*curr;
	void	*temp;

	curr = *names;
	while (curr->next != NULL)
	{
		if (ft_strcmp((char *)curr->content, (char *)curr->next->content) > 0)
		{
			temp = curr->content;
			curr->content = curr->next->content;
			curr->next->content = temp;
			curr = *names;
		}
		else
			curr = curr->next;
	}
}

/**
 * @brief Get the pattern len,
 * Aka the strlen before * or \0 character.
 * 
 * @param str 
 * @return int 
 */
int	get_pattern_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] != 0 && str[len] != '*')
		len++;
	if (str[len] == 0)
		len++;
	return (len);
}

/**
 * @brief Return the index of matching, -1 for no match
 * 
 * @param wildcard 
 * @param name 
 * @param pattern_len 
 * @return int 
 */
int	name_pattern_match(char *wildcard, char *name, int pattern_len)
{
	int	i;

	i = -1;
	while (name[++i] != 0)
	{
		if (ft_strncmp(wildcard, name + i, pattern_len) == 0)
			return (i);
	}
	return (-1);
}
