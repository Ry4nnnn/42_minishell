/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoidptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:51:09 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:44:27 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa_base(unsigned long long num, char *base)
{
	int					count;
	unsigned long long	tmp;
	char				*res;
	unsigned int		base_length;

	base_length = ft_strlen(base);
	count = 3;
	tmp = num;
	while (tmp >= base_length && (tmp / base_length) && ++count)
		tmp /= base_length;
	tmp = num;
	res = (malloc(sizeof(char) * (count + 1)));
	res[count] = '\0';
	res[0] = '0';
	res[1] = 'x';
	while (tmp >= base_length)
	{
		--count;
		res[count] = base[tmp % base_length];
		tmp /= base_length;
	}
	res[--count] = base[tmp % base_length];
	return (res);
}

int	ft_putvoidptr(unsigned long long ptr, t_flags *flags)
{
	char	*nbr;
	int		len;

	nbr = ft_ulltoa_base(ptr, "0123456789abcdef");
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
