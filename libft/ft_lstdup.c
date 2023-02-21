#include "libft.h"

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*new_list = NULL;
	t_list	*last_node = NULL;

	while (lst)
	{
		t_list	*new_node;
		new_node = ft_lstnew(lst->content);
		if (!new_node)
			return (NULL);
		if (!new_list)
		{
			new_list = new_node;
			last_node = new_node;
		}
		else
		{
			last_node->next = new_node;
			last_node = new_node;
		}
		lst = lst->next;
	}
	return (new_list);
}
