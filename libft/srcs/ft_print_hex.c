/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:58:31 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:50:05 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa_base(unsigned int num, char *base)
{
	int					count;
	unsigned int		tmp;
	char				*res;
	unsigned int		base_length;

	base_length = ft_strlen(base);
	count = 1;
	tmp = num;
	while (tmp >= base_length && (tmp / base_length) && ++count)
		tmp /= base_length;
	tmp = num;
	res = (malloc(sizeof(char) * (count + 1)));
	res[count] = '\0';
	while (tmp >= base_length)
	{
		--count;
		res[count] = base[tmp % base_length];
		tmp /= base_length;
	}
	res[--count] = base[tmp % base_length];
	return (res);
}

void	ft_hexhash(t_flags *flags, unsigned int num, int *len, char *base)
{
	if (flags->hash && num)
	{
		*len += 2;
		if (base[10] == 'a')
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
	}
}

int	ft_print_hex(unsigned int num, char *base, t_flags *flags)
{
	char	*nbr;
	int		len;

	nbr = ft_uitoa_base(num, base);
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
	ft_hexhash(flags, num, &len, base);
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
