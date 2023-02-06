/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:47:38 by welim             #+#    #+#             */
/*   Updated: 2022/04/18 15:48:24 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	if (!lst || !f)
		return (0);
	new = NULL;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		if (!new)
			new = temp;
		else
			ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	temp->next = 0;
	return (new);
}

// #include <stdio.h>
// void * addOne(void * p)
// {
// 	void * r = malloc(sizeof(int));
// 	*(int*)r = *(int*)p + 1;
// 	return (r);
// }

// int main()
// {
// 	// int	tab = {0, 1, 2, 3};

// 	int	*tab;
// 	tab = malloc(sizeof(int) * 4);
// 	tab[0] = 0;
// 	tab[1] = 1;
// 	tab[2] = 2;
// 	tab[3] = 3;
// 	printf("tab[0] %d \n", tab[0]);
// 	t_list * l =  ft_lstnew(tab);

// 	for (int i = 1; i < 4; ++i)
// 		ft_lstadd_back(&l, ft_lstnew(tab + i));

// 	t_list * mapped = ft_lstmap(l, addOne, free);
// 	t_list	*iter = l;
// 	while(iter){
// 		printf("%d\n", *(int*)iter->content);
// 		iter = iter->next;
// 	}
// 	printf("\n");
// 	iter = mapped;
// 	while(iter){
// 		printf("%d\n", *(int*)iter->content);
// 		iter = iter->next;
// 	}
// }