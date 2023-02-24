/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:48:01 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:44:20 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unsign_len(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_unsign_len(n);
	num = malloc(sizeof(char) * (len + 1));
	num[len] = '\0';
	if (n == 0)
		num[0] = '0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n /= 10;
		len--;
	}
	return (num);
}

int	ft_putunsign(unsigned int n, t_flags *flags)
{
	char	*nbr;
	int		len;

	nbr = ft_uitoa(n);
	len = 0;
	if (!flags->minus && (flags->dot && flags->precision)
		&& flags->width > flags->precision)
	{
		if ((int)ft_strlen(nbr) > flags->precision)
			len += ft_print_chars(' ', flags->width - (int)ft_strlen(nbr));
		else
			len += ft_print_chars(' ', flags->width - flags->precision);
		flags->width -= len;
	}
	len += ft_print_chars('0', flags->precision - (int)ft_strlen(nbr));
	if (flags->dot)
		flags->c = ' ';
	if ((flags->dot) && !(flags->width))
		flags->width = flags->precision;
	if (flags->dot && (flags->precision < (int)ft_strlen(nbr)) && nbr[0] != '0')
		flags->precision = (int)ft_strlen(nbr);
	len += ft_putnbrstrf(nbr, flags);
	free(nbr);
	return (len);
}
