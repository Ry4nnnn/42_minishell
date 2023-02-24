/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:22:17 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/13 16:50:52 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*list;

	if (!lst)
		return ;
	if (*lst != NULL)
	{
		list = ft_lstlast(*lst);
		list->next = new_node;
	}
	else
		*lst = new_node;
}
