/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:20:44 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/05 19:25:53 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;
	t_list	*head;

	if (!lst)
		return (NULL);
	head = ft_lstnew((*f)(lst->content));
	if (!head)
		return (NULL);
	(void)(*del);
	temp = head;
	temp2 = lst->next;
	while (temp2)
	{
		temp->next = ft_lstnew((*f)(temp2->content));
		temp = temp->next;
		if (!temp)
			return (NULL);
		temp2 = temp2->next;
	}
	return (head);
}
