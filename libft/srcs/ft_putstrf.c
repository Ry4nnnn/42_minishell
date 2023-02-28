/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:07:58 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:44:13 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnull(t_flags *flags)
{
	ft_putstrf("(null)", flags);
	if (flags->width >= 6)
		return (flags->width);
	if (flags->precision && flags->precision <= 6)
		return (flags->precision);
	return (6);
}

void	ft_print_fix(t_flags *flags, int *len, char *str)
{
	if (flags->dot && (flags->precision <= flags->width))
		*len += ft_print_chars(flags->c, flags->width - flags->precision);
	else
		*len += ft_print_chars(flags->c, flags->width - (int)ft_strlen(str));
}

int	ft_putstrf(char *str, t_flags *flags)
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		return (ft_putnull(flags));
	if (!flags->minus)
		ft_print_fix(flags, &len, str);
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
		ft_print_fix(flags, &len, str);
	return (len);
}
