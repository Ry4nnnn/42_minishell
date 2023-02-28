/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2darrlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:41:45 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/19 09:58:21 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_2darrlen(void **arr)
{
	int	len;

	if (arr == NULL)
		return (0);
	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}
