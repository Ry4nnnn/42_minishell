/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:41:46 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/04/08 15:36:37 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * First get the length of the pattern string, e.g. "123*" => 3
 * Then check if the name matches this pattern,
 * a special case is that if the pattern is in the beginning of the wildcard,
 * the name must match the pattern in the index of 0,
 * other patterns can just loop through the name and find, so it allows
 * some extra characters.
 * 
 * @param wildcard 
 * @param name 
 * @return int 1 for true 0 for false
 */
int	pattern_match(char *wildcard, char *name)
{
	int	pattern_len;
	int	wc_len;
	int	i;
	int	match_index;

	i = -1;
	wc_len = ft_strlen(wildcard);
	while (++i < wc_len)
	{
		pattern_len = get_pattern_len(wildcard + i);
		if (pattern_len == 0)
			continue ;
		match_index = name_pattern_match(wildcard + i, name, pattern_len);
		if (match_index == -1 || (i == 0 && match_index != 0))
			return (0);
		i += pattern_len;
		name += match_index + pattern_len;
	}
	return (1);
}

/**
 * @brief Get all the d_names in the current working directory
 * 
 * @return t_list* names linked list
 */
t_list	*get_cwd_names(void)
{
	DIR				*dir;
	t_list			*names;
	struct dirent	*dir_info;

	names = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	dir_info = readdir(dir);
	while (dir_info != NULL)
	{
		if (dir_info->d_name[0] != '.')
			ft_lstadd_back(&names, ft_lstnew(ft_strdup(dir_info->d_name)));
		dir_info = readdir(dir);
	}
	closedir(dir);
	sort_names_list(&names);
	return (names);
}

/**
 * @brief Get the wildcard expanded string for the pattern
 * Check if the pattern matches a name in the names list,
 * join the names with space in between and return.
 * 
 * @param mini 
 * @param names 
 * @param wildcard 
 * @return char* 
 */
char	*get_wildcard_expanded(t_mini *mini, t_list *names, char *wildcard)
{
	char	*expanded;

	(void)mini;
	expanded = NULL;
	while (names != NULL)
	{
		if (pattern_match(wildcard, (char *)names->content))
		{
			expanded = ft_strjoin_free(expanded, " ");
			expanded = ft_strjoin_free(expanded, (char *)names->content);
		}
		names = names->next;
	}
	return (expanded);
}

/**
 * @brief Expand the * wildcards in the input string.
 * First get the file and directory names in the current working directory,
 * Then get the expanded string by the function get_wildcard_expanded,
 * Then expand the input string if there is indeed something to expand.
 * 
 * @param mini 
 * @param pinput input string ptr
 * @param ptoken token string ptr
 * @param i 
 */
int	wildcard(t_mini *mini, char **pinput, char **ptoken, int i)
{
	char	*expanded;
	t_list	*names;

	names = get_cwd_names();
	expanded = get_wildcard_expanded(mini, names, *ptoken);
	ft_lstclear(&names, free);
	if (expanded == NULL)
		return (0);
	ft_strexpand(pinput, expanded, i, ft_strlen(*ptoken));
	free(*ptoken);
	*ptoken = expanded;
	return (1);
}
