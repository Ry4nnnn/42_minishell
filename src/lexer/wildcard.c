/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:41:46 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/03/17 16:00:56 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_pattern_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] != 0 && str[len] != '*')
		len++;
	if (str[len] == 0)
		len++;
	return (len);
}

int	pattern_match(char *wildcard, char *name)
{
	int	len;
	int	wc_len;
	int	i;
	int	j;

	i = -1;
	wc_len = ft_strlen(wildcard);
	while (++i < wc_len)
	{
		len = get_pattern_len(wildcard + i);
		if (len == 0)
			continue ;
		j = -1;
		while (name[++j] != 0)
		{
			if (i == 0 && j != 0)
				return (0);
			if (ft_strncmp(wildcard + i, name + j, len) == 0)
				break ;
		}
		if (name[j] == 0)
			return (0);
		i += len;
		name += j + len;
	}
	return (1);
}

t_list	*get_cwd_names(void)
{
	t_list	*names = NULL;
	pid_t	getter;
	char	*cmd_argv[2];
	int		buf[2];
	char	*temp;

	cmd_argv[0] = "/bin/ls";
	cmd_argv[1] = NULL;
	pipe(buf);
	getter = fork();
	if (getter == 0)
	{
		dup2(buf[WRITE], STDOUT_FILENO);
		close(buf[READ]);
		if (execve("/bin/ls", cmd_argv, NULL) != 0)
			exit(EXIT_FAILURE);
	}
	waitpid(getter, NULL, 0);
	close(buf[WRITE]);
	temp = get_next_line(buf[READ]);
	while (temp != NULL)
	{
		temp[ft_strlen(temp) - 1] = 0;
		ft_lstadd_back(&names, ft_lstnew((void *)temp));	
		temp = get_next_line(buf[READ]);
	}
	close(buf[READ]);
	return (names);
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