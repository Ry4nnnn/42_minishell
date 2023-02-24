/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrstrf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:01:18 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:44:06 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_fix_nbrstrf(t_flags *flags, int *len, char *str)
{
	int	strlen;

	strlen = (int)ft_strlen(str);
	if (flags->dot && (flags->precision <= flags->width))
		*len += ft_print_chars(flags->c, flags->width - flags->precision);
	else if (flags->dot && !(flags->width))
		*len += ft_print_chars(flags->c, flags->precision - strlen);
	else if (!flags->dot)
		*len += ft_print_chars(flags->c, flags->width - strlen);
}

int	ft_putnull_nbrstrf(t_flags *flags)
{
	ft_putstrf("(null)", flags);
	if (flags->width >= 6)
		return (flags->width);
	if (flags->precision && flags->precision <= 6)
		return (flags->precision);
	return (6);
}

int	ft_putnbrstrf(char *str, t_flags *flags)
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		ft_putnull_nbrstrf(flags);
	if (!flags->minus)
		ft_print_fix_nbrstrf(flags, &len, str);
	while (i < ft_strlen(str))
	{
		if (flags->dot && ((int)i >= flags->precision))
			break ;
		if (str[i] == '%' && str[i + 1] == '%')
			i++;
		write(1, &str[i], 1);
		i++;
		len++;
	}
	if (flags->minus)
		ft_print_fix_nbrstrf(flags, &len, str);
	return (len);
}
