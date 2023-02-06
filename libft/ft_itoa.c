/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:44:22 by welim             #+#    #+#             */
/*   Updated: 2022/06/23 22:42:49 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(long nb)
{
	int	res;

	if (nb == 0)
		return (1);
	res = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		res++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	nb;

	len = intlen(n);
	nb = n;
	if (nb == 0 && len == 1)
		return (ft_strdup("0"));
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len--] = 0;
	if (!nb)
		res[len] = '\0';
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	while (nb != 0)
	{
		res[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}
