#include "libft.h"

/* If a node fails, its mapped content has no owner yet and must be released. */
static t_list	*ft_map_node(void *content, void *(*f)(void *),
		void (*del)(void *))
{
	void	*mapped;
	t_list	*node;

	mapped = f(content);
	node = ft_lstnew(mapped);
	if (node == NULL)
		del(mapped);
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*tail;
	t_list	*node;

	if (f == NULL || del == NULL)
		return (NULL);
	result = NULL;
	tail = NULL;
	while (lst != NULL)
	{
		node = ft_map_node(lst->content, f, del);
		if (node == NULL)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		if (result == NULL)
			result = node;
		else
			tail->next = node;
		tail = node;
		lst = lst->next;
	}
	return (result);
}
