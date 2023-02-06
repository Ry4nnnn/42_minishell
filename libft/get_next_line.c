/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:24:31 by welim             #+#    #+#             */
/*   Updated: 2022/06/22 22:55:44 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_read(int fd, char **buff, int *bytes)
{
	int	res;

	res = read(fd, *buff, BUFFER_SIZE);
	*bytes = res;
	return (res);
}

static void	ft_free(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

static char	*get_newline(char **str)
{
	size_t	i;
	char	*temp;
	char	*res;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i])
	{
		res = ft_substr(*str, 0, i + 1);
		temp = ft_strdup(*str + i + 1);
		ft_free(str);
		if (temp[0] != '\0')
			*str = temp;
		else
			ft_free(&temp);
	}
	else
	{
		res = ft_strdup(*str);
		ft_free(str);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	int			bytes;
	char		*buff;
	char		*temp;
	static char	*res;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (ft_read(fd, &buff, &bytes) > 0)
	{
		buff[bytes] = 0;
		if (!res)
			res = ft_strdup("");
		temp = ft_strjoin(res, buff);
		ft_free(&res);
		res = temp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	ft_free(&buff);
	if (bytes < 0 || (bytes == 0 && !res))
		return (0);
	return (get_newline(&res));
}
