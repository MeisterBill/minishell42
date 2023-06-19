#include "../Includes/minishell.h"

t_list	*ft_listlast(t_list *list)
{
	t_list	*last;

	if (!list)
		return (NULL);
	while (list)
	{
		if (!list->next)
			last = list;
		list = list->next;
	}
	return (last);
}

void	ft_listadd_back(t_list **list, t_list *new_elem)
{
	t_list	*start;

	start = *list;
	if (*list)
	{
		while (start->next)
			start = start->next;
		start->next = new_elem;
	}
	else
		*list = new_elem;
}

t_list	*ft_listnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
