# include "ft_ls.h"

void	print_dir(t_ls_list *begin, t_param *param)
{
	int		line;

	line = 0;
	if (!begin)
		return ;
	sort_list(begin, param);
	while (begin->next)
	{
		begin = begin->next;
		if (param->show_hide == 1 || is_hide(begin->content) == 0)
		{
			if (line)
				ft_putstr("\n");
			ft_putstr(begin->content->name);
			line++;
		}
	}
	ft_putstr("\n");
}

int		print_param(t_ls_list *lst, t_param *param)
{
	int		tab;
	DIR			*dir;

	tab = 0;
	while (lst->next)
	{
		lst = lst->next;
		errno = 0;
		dir = opendir(lst->content->name);
		if (errno == ENOTDIR)
		{
			if (tab != 0)
				ft_putstr("\n");
			ft_putstr(lst->content->name);
			tab++;
		}
		else
			closedir(dir);
	}
	if (tab)
		ft_putstr("\n");
	return (tab ? 1 : 0);
}
