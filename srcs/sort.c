# include "ft_ls.h"

static void	sort_by_mtime(t_ls_list *begin, t_param *param)
{
	t_ls_list	*lst;
	void		*tmp;

	while (begin->next)
	{
		begin = begin->next;
		lst = begin;
		while (lst->next)
		{
			lst = lst->next;
			if ((begin->content->filestat.st_mtime
						< lst->content->filestat.st_mtime)
				^ param->reverse_sort)
			{
				tmp = lst->content;
				lst->content = begin->content;
				begin->content = tmp;
			}
		}
	}
}

static void	sort_by_name(t_ls_list *begin, t_param *param)
{
	t_ls_list	*lst;
	void		*tmp;

	while (begin->next)
	{
		begin = begin->next;
		lst = begin;
		while (lst->next)
		{
			lst = lst->next;
			if ((ft_strcmp(begin->content->name, lst->content->name) > 0)
				^ param->reverse_sort)
			{
				tmp = lst->content;
				lst->content = begin->content;
				begin->content = tmp;
			}
		}
	}
}

void	sort_list(t_ls_list *begin, t_param *param)
{
	if (param->time_sort)
		sort_by_mtime(begin, param);
	else
		sort_by_name(begin, param);
}
