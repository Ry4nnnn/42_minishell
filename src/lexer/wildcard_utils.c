/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:00:41 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/03/18 15:59:23 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Use a pipe to store the names
 * 
 * @param buf 
 */
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

/**
 * @brief Get the file and directory names in the current working directory
 * 
 * @param buf 
 * @return t_list* 
 */
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
