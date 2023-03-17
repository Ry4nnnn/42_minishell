/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:00:41 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/03/17 19:18:42 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_names(int *buf)
{
	char	*cmd_argv[2];
	pid_t	getter;

	cmd_argv[0] = "/bin/ls";
	cmd_argv[1] = NULL;
	getter = fork();
	if (getter == 0)
	{
		dup2(buf[WRITE], STDOUT_FILENO);
		close(buf[READ]);
		if (execve("/bin/ls", cmd_argv, NULL) != 0)
			exit(EXIT_FAILURE);
	}
	waitpid(getter, NULL, 0);
}

t_list	*get_names_list(int *buf)
{
	t_list	*names_list;
	char	*name;

	names_list = NULL;
	close(buf[WRITE]);
	name = get_next_line(buf[READ]);
	while (name != NULL)
	{
		name[ft_strlen(name) - 1] = 0;
		ft_lstadd_back(&names_list, ft_lstnew((void *)name));
		name = get_next_line(buf[READ]);
	}
	close(buf[READ]);
	return (names_list);
}

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
