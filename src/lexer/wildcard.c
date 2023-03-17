/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:41:46 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/03/17 19:18:18 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pattern_match(char *wildcard, char *name)
{
	int	pattern_len;
	int	wc_len;
	int	i;
	int	match_len;

	i = -1;
	wc_len = ft_strlen(wildcard);
	while (++i < wc_len)
	{
		pattern_len = get_pattern_len(wildcard + i);
		if (pattern_len == 0)
			continue ;
		match_len = name_pattern_match(wildcard + i, name, pattern_len);
		if (match_len == -1 || (i == 0 && match_len != 0))
			return (0);
		i += pattern_len;
		name += match_len + pattern_len;
	}
	return (1);
}

t_list	*get_cwd_names(void)
{
	int		buf[2];

	pipe(buf);
	store_names(buf);
	return (get_names_list(buf));
}

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

void	wildcard(t_mini *mini, char **pinput, char **ptoken, int i)
{
	char	*expanded;
	t_list	*names;

	names = get_cwd_names();
	expanded = get_wildcard_expanded(mini, names, *ptoken);
	ft_lstclear(&names, free);
	if (expanded == NULL)
		return ;
	ft_strexpand(pinput, expanded, i, ft_strlen(*ptoken));
	free(*ptoken);
	*ptoken = expanded;
}
