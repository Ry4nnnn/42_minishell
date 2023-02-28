/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:08:36 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:50:52 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_fix_nbrf(t_flags *flags, char *nbr, int *len)
{
	if (!flags->minus && (flags->dot && flags->precision)
		&& flags->width > flags->precision)
	{
		if ((int)ft_strlen(nbr) > flags->precision)
			*len += ft_print_chars(' ', flags->width - (int)ft_strlen(nbr));
		else if (nbr[0] == '-')
			*len += ft_print_chars(' ', flags->width - flags->precision - 1);
		else if (nbr[0] != '-')
			*len += ft_print_chars(' ', flags->width - flags->precision);
		flags->width -= *len;
	}
}

void	check_space_plus(t_flags *flags, int *len, int num)
{
	if (num >= 0 && flags->space && ++(*len))
		ft_putchar_fd(' ', 1);
	if (num >= 0 && flags->plus && ++(*len))
		ft_putchar_fd('+', 1);
}

int	ft_putnbrf(int num, t_flags *flags)
{
	char	*nbr;
	int		len;
	int		i;

	nbr = ft_itoa(num);
	len = 0;
	i = 0;
	ft_print_fix_nbrf(flags, nbr, &len);
	if (nbr[0] == '-' && (flags->dot || flags->c == '0') && ++len && ++i)
		ft_putchar_fd('-', 1);
	nbr += i;
	flags->width -= i;
	check_space_plus(flags, &len, num);
	len += ft_print_chars('0', flags->precision - (int)ft_strlen(nbr));
	if (flags->dot)
		flags->c = ' ';
	if ((flags->dot) && !(flags->width))
		flags->width = flags->precision;
	if (flags->dot && (flags->precision < (int)ft_strlen(nbr)) && nbr[0] != '0')
		flags->precision = (int)ft_strlen(nbr);
	len += ft_putnbrstrf(nbr, flags);
	free(nbr - i);
	return (len);
}
