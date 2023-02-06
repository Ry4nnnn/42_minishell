/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:46:30 by welim             #+#    #+#             */
/*   Updated: 2022/04/18 15:46:31 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*curr;

	if (!lst)
		return ;
	curr = *lst;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		del(temp->content);
		free(temp);
	}
	*lst = curr;
}
