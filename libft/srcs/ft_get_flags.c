/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:42:45 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:43:17 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_flags(t_flags *flags)
{
	flags->zero = 0;
	flags->minus = 0;
	flags->dot = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->c = ' ';
}

int	in_formats(char c)
{
	char	*formats;
	int		i;

	formats = "cspdiuxX%";
	i = -1;
	while (formats[++i])
		if (c == formats[i])
			return (1);
	return (0);
}

int	ft_get_width(const char *format, int *i)
{
	int	width;

	width = ft_atoi(format + *i);
	while (ft_isdigit(format[*i]))
		(*i)++;
	return (width);
}

int	ft_get_prec(const char *format, int *i)
{
	int	prec;

	(*i)++;
	prec = ft_atoi(format + *i);
	while (ft_isdigit(format[*i]))
		(*i)++;
	return (prec);
}

void	ft_get_flags(const char *format, int *i, t_flags *flags)
{
	(*i)++;
	while (format[*i] && !in_formats(format[*i]))
	{
		if (ft_isdigit(format[*i]) && format[*i] != '0')
		{
			flags->width = ft_get_width(format, i);
			continue ;
		}
		if (format[*i] == '0')
			flags->zero = 1;
		else if (format[*i] == '-')
			flags->minus = 1;
		else if (format[*i] == '.' && ++(flags->dot))
		{
			flags->precision = ft_get_prec(format, i);
			continue ;
		}
		else if (format[*i] == '#')
			flags->hash = 1;
		else if (format[*i] == ' ')
			flags->space = 1;
		else if (format[*i] == '+')
			flags->plus = 1;
		(*i)++;
	}
}
