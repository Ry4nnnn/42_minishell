/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:21:32 by wangxuerui        #+#    #+#             */
/*   Updated: 2023/03/18 14:24:38 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *num)
{
	int	i;

	i = 0;
	if (ft_isdigit(num[0]) == 0 && (num[0] != '-' && num[0] != '+'))
		return (0);
	while (num[++i] != 0)
	{
		if (ft_isdigit(num[i]) == 0)
			return (0);
	}
	return (1);
}
