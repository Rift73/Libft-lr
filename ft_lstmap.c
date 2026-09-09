#include "libft.h"

/* If a node fails, its mapped content has no owner yet and must be released. */
static t_list	*ft_map_node(void *content, void *(*f)(void *),
		void (*del)(void *))
{
	void	*mapped_content;
	t_list	*new_node;

	mapped_content = f(content);
	new_node = ft_lstnew(mapped_content);
	if (new_node == NULL)
		del(mapped_content);
	return (new_node);
}

/*
** Build a separate list without changing the original links. new_tail lets
** each append connect directly to the previous node. If construction fails,
** the helper frees the unattached content; this loop frees earlier nodes.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_tail;
	t_list	*new_node;

	if (f == NULL || del == NULL)
		return (NULL);
	new_head = NULL;
	new_tail = NULL;
	while (lst != NULL)
	{
		new_node = ft_map_node(lst->content, f, del);
		if (new_node == NULL)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		if (new_head == NULL)
			new_head = new_node;
		else
			new_tail->next = new_node;
		new_tail = new_node;
		lst = lst->next;
	}
	return (new_head);
}
