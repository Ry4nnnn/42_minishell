/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:52:26 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:43:45 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char format, va_list *args, t_flags *flags)
{
	char	*base1;
	char	*base2;

	base1 = "0123456789abcdef";
	base2 = "0123456789ABCDEF";
	if (format == 'c')
		return (ft_putcharf(va_arg(*args, int), flags));
	else if (format == 's')
		return (ft_putstrf(va_arg(*args, char *), flags));
	else if (format == 'p')
		return (ft_putvoidptr(va_arg(*args, unsigned long long), flags));
	else if (format == 'd')
		return (ft_putnbrf(va_arg(*args, int), flags));
	else if (format == 'i')
		return (ft_putnbrf(va_arg(*args, int), flags));
	else if (format == 'u')
		return (ft_putunsign(va_arg(*args, unsigned int), flags));
	else if (format == 'x')
		return (ft_print_hex(va_arg(*args, int), base1, flags));
	else if (format == 'X')
		return (ft_print_hex(va_arg(*args, int), base2, flags));
	else if (format == '%')
		return (ft_putcharf('%', flags));
	return (0);
}

int	ft_printing(char format, va_list *args, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->zero)
		flags->c = '0';
	len += print_format(format, args, flags);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	int			len;
	t_flags		*flags;

	if (!format)
		return (0);
	va_start(args, format);
	i = -1;
	len = 0;
	flags = malloc(sizeof(t_flags));
	while (++i < (int)ft_strlen((char *)format))
	{
		ft_set_flags(flags);
		if (format[i] == '%')
		{
			ft_get_flags(format, &i, flags);
			len += ft_printing(format[i], &args, flags);
		}
		else
			len += ft_putcharf(format[i], flags);
	}
	va_end(args);
	free(flags);
	return (len);
}
