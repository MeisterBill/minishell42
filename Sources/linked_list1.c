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
