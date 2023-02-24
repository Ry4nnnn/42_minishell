/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:15:59 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 19:51:07 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_chars(char c, int rep)
{
	int	len;

	len = 0;
	while (rep > 0)
	{
		ft_putchar_fd(c, 1);
		len++;
		rep--;
	}
	return (len);
}
