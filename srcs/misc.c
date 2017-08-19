# include "ft_ls.h"

int		to_open(t_node *node, t_param *param)
{
	if (node->name[0] == '.'
	&& ((node->name[1] == '\0' || node->name[1] == '.')
		|| param->show_hide == 0))
		return (0);
	return (1);
}

int		is_hide(t_node *node)
{
	if (node->name[0] == '.')
		return (1);
	return (0);
}

void		multi_puts(char *a, char *b)
{
	write(1, a, ft_strlen(a));
	ft_putstr(b);
}

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
