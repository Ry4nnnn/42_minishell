/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llto2darr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:44:54 by codespace         #+#    #+#             */
/*   Updated: 2023/03/06 13:41:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_llto2darr(t_list *list, char *(*f)(void *))
{
	int		len;
	int		i;
	char	**arr;

	len = ft_lstsize(list);
	i = -1;
	arr = malloc((len + 1) * sizeof(char *));
	while (++i < len)
	{
		arr[i] = f(list->content);
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
}
