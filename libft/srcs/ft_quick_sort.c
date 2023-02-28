/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:57:36 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/09 21:55:50 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	partition(int *nums, int start, int end)
{
	int	pivot;
	int	i;
	int	j;

	pivot = nums[end];
	i = start;
	j = start - 1;
	while (++j < end)
	{
		if (nums[j] <= pivot)
		{
			ft_swap(&nums[j], &nums[i]);
			i++;
		}
	}
	ft_swap(&nums[i], &nums[end]);
	return (i);
}

void	ft_quick_sort(int *nums, int start, int end)
{
	int	pivot;

	if (start >= end)
		return ;
	pivot = partition(nums, start, end);
	ft_quick_sort(nums, start, pivot - 1);
	ft_quick_sort(nums, pivot + 1, end);
}
