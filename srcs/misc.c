# include "ft_ls.h"

void	free_lst(t_list *lst)
{
	if (lst->next != NULL)
		free_lst(lst->next);
	if (lst != NULL)
	{
		if (lst->content != NULL)
			free(lst->content);
		free(lst);
	}
}
