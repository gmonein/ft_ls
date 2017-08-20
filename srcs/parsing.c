# include "ft_ls.h"

static int		print_error(char *str, char invalid_param)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\'", 1);
	write(2, &invalid_param, 1);
	write(2, "\'", 1);
	write(2, "\n", 1);
	return (-1);
}

static int	translate_param(t_param *param, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 'a')
			param->show_hide = 1;
		else if (str[i] == 'r')
			param->reverse_sort = 1;
		else if (str[i] == 'R')
			param->recursive = 1;
		else if (str[i] == 'l')
			param->file_info = 1;
		else if (str[i] == 't')
			param->time_sort = 1;
		else if (param->invalide_param)
			return (0);
		else
		{
			param->invalide_param = str[i];
			return (0);
		}
	}
	return (1);
}

t_ls_list	*read_params(t_param *param)
{
	t_ls_list		*begin;
	t_ls_list		*lst;
	int				i;
	t_node			buf;

	begin = (void *)ft_lstnew(NULL, 0);
	lst = begin;
	i = -1;
	if (param->file)
		while (param->file[++i])
		{
			buf = get_info(param->file[i], NULL, param);
			lst->next = (void *)ft_lstnew(&buf, sizeof(t_node));
			lst = lst->next;
			param->single_dir = (i < 1 ? 1 : 0);
		}
	else if (!param->file)
	{
		buf = get_info(".", NULL, param);
		lst->next = (void *)ft_lstnew(&buf, sizeof(t_node));
		param->single_dir = 1;
	}
	return (begin);
}

int		get_params(char **gv, int len, t_param *param)
{
	int			i;

	ft_bzero(param, sizeof(t_param));
	i = -1;
	while (++i < len)
	{
		if (gv[i][0] != '-')
			break ;
		if (gv[i][0] == '-' && gv[i][1] == '-')
		{
			i++;
			break ;
		}
		if (!translate_param(param, &gv[i][1]))
		{
			print_error("invalid option -- ", param->invalide_param);
			return (-1);
		}
	}
	if (i != len)
		param->file = &gv[i];
	else
		param->file = NULL;
	return (1);
}
