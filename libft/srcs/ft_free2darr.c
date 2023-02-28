/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2darr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:57:09 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/19 09:57:48 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free2darr(void **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}
