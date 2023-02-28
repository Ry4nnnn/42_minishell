/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:53:11 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/10 17:09:07 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strdup(char *s1)
{
	char	*temp;
	size_t	len;
	size_t	i;

	if (!s1)
	{
		temp = malloc(1);
		temp[0] = 0;
		return (temp);
	}
	len = ft_strlen((char *)s1);
	temp = malloc((len + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

/* return 1 if the string contains '\n' else 0 */
int	is_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/* read BUFFER by BUFFER and return the final string that contains \n 
 * or encounter EOF.
 */
char	*read_line(int fd, char *buff)
{
	char	*temp;
	int		ret;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ret = 1;
	while (!is_line(buff) && ret)
	{
		ret = read(fd, temp, BUFFER_SIZE);
		if (!ret)
			break ;
		if (ret == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[ret] = 0;
		buff = ft_strcombine(buff, temp);
	}
	free(temp);
	return (buff);
}

/* get the new line and update the static variable buff */
char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*line;
	char		**splitted;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = read_line(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	if (!buff[fd][0])
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	splitted = ft_split_line(buff[fd]);
	line = ft_strdup(splitted[0]);
	free(buff[fd]);
	buff[fd] = ft_strdup(splitted[1]);
	free(splitted[0]);
	if (splitted[1])
		free(splitted[1]);
	free(splitted);
	return (line);
}
