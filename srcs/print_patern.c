/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_patern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:30:03 by marvin            #+#    #+#             */
/*   Updated: 2017/01/28 08:54:02 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_l(struct l_file *lst, int a, int f_total)
{
	int		tmp;

	tmp = 0;
	if (f_total != 1)
	{
		write(1, "total ", 6);
		ft_putnbr(lst->begin->total);
		write(1, "\n", 1);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (lst->name == NULL)
			break;
		if (a == 1 || (a == 0 && lst->hide == 0))
		{
			write(1, "                  ", lst->begin->col_one - lst->col_one);
			ft_putnbr(lst->filestat->st_nlink);
			write(1, " ", 1);
			write(1, getpwuid(lst->filestat->st_uid)->pw_name, ft_strlen(getpwuid(lst->filestat->st_uid)->pw_name));
			write(1, "  ", 2);
			write(1, getgrgid(lst->filestat->st_gid)->gr_name, ft_strlen(getgrgid(lst->filestat->st_gid)->gr_name));
			if (((tmp = (lst->begin->col_four - lst->col_four)) != -42) && (lst->begin->col_four == 1))
				tmp++;
			write(1, "                  ", tmp);
			ft_putnbr(lst->filestat->st_size);
			write(1, "  ", 1);
		//	print_time(ctime(&lst->filestat->st_mtime));
			write(1, "  ", 1);
			write(1, lst->name, ft_strlen(lst->name));
			write(1, "\n", 1);
		}
	}
}

void			ft_print_total(t_file *lst, t_arg *sarg)
{
	if (lst->begin != NULL && sarg->f_total != 1)
	{
		write(1, "total ", 6);
		ft_putnbr(lst->begin->total);
		write(1, "\n", 1);
	}
}

void			ft_putmultistr(char *a, char *b, char *c, char *d)
{
	if (a != NULL)
		write (1, a, ft_strlen(a));
	if (b != NULL)
		write (1, b, ft_strlen(b));
	if (c != NULL)
		write (1, c, ft_strlen(c));
	if (d != NULL)
		write (1, d, ft_strlen(d));
}

void			print_link(t_file *lst, t_arg *sarg)
{
	int		i;

	i = lst->begin->col_one - lst->col_one;
	if (sarg->a == 1 || lst->hide == 0)
	{
		write(1, "  ", 2);
		write(1, "                                                       ", i);
		ft_putnbr(lst->filestat->st_nlink);
	}
}

void			print_pw(t_file *lst, t_arg *sarg)
{
	int		len;

	if (sarg->a == 1 || lst->hide == 0)
	{
		len = ft_strlen(getpwuid(lst->filestat->st_uid)->pw_name);
		write(1, " ", 1);
		write(1, getpwuid(lst->filestat->st_uid)->pw_name, len);
	}
}

void			print_gr(t_file *lst, t_arg *sarg)
{
	int		len;

	if (sarg->a == 1 || lst->hide == 0)
	{
		len = ft_strlen(getgrgid(lst->filestat->st_gid)->gr_name);
		write(1, "  ", 2);
		write(1, getgrgid(lst->filestat->st_gid)->gr_name, len);
	}
}

void			print_size(t_file *lst, t_arg *sarg)
{
	int		i;

	i = lst->begin->col_four - lst->col_four;
	if (sarg->a == 1 || lst->hide == 0)
	{
		write(1, INF_SPACE, i + 2);
		ft_putnbr(lst->filestat->st_size);
		write(1, " ", 1);
	}
}

void			print_name(t_file *lst, t_arg *sarg)
{
	if (sarg->a == 1 || lst->hide == 0)
	{
		write(1, lst->name, ft_strlen(lst->name));
	}
}

void			new_l(t_file *lst, t_arg *sarg)
{
	ft_print_total(lst, sarg);
	while (lst->next != NULL && lst->next->name != NULL)
	{
		lst = lst->next;
		print_right(lst, sarg);
		print_link(lst, sarg);
		print_pw(lst, sarg);
		print_gr(lst, sarg);
		print_size(lst, sarg);
		print_time(lst, sarg);
		print_name(lst, sarg);
		write(1, "\n", (lst->hide == 0 || sarg->a == 1 ? 1 : 0));
	}
}

void			print_nl_b(t_file *lst, int a)
{
	int					col;
	int					line;
	int					elem;
	struct winsize		size;
	char				**tab;
	int					i;
	int					x;
	int					y;

	elem = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	while (lst->next != NULL)
	{
		if (lst->hide == 0 || a == 1)
			elem++;
		lst = lst->next;
	}
	col = size.ws_col / lst->begin->len_name;
	line = elem / col;
	(elem % col > 0 ? line++ : 1);
	tab = (char **)malloc(sizeof(char *) * (line + 1));
	tab[line] = NULL;
	while (--line != -1)
	{
		tab[line] = (char *)malloc(sizeof(char) * (size.ws_col + 1));
		i = 0;
		while (i <= size.ws_col)
		{
			tab[line][i] = ' ';
			i++;
		}
		tab[line][size.ws_col] = '\0';
	}
	lst = lst->begin->next;
	x = 0;
	y = 0;
	col = size.ws_col / lst->begin->len_name;
	line = elem / col;
	(elem % col > 0 ? line++ : 1);
	while (lst != NULL)
	{
		if (lst->hide == 0 || a == 1)
		{
			i = 0;
			while (lst->name && lst->name[i])
			{
				tab[y][x + i] = lst->name[i];
				i++;
			}
			if (lst->name && y < (line - 1))
				y++;
			else if (lst->name)
			{
				y = 0;
				x += lst->begin->len_name + 1;
			}
		}
		lst = lst->next;
	}
	y = 0;
	while (tab[y])
	{
		write(1, tab[y], ft_strlen(tab[y]));
		write(1, "\n", 1);
		free(tab[y]);
		y++;
	}
	free(tab);
}

void			print_nl(struct l_file *lst, int a)
{
	int					i;
	int					j;
	int					line_len;
	struct winsize		size;

	i = 0;
	line_len = lst->begin->len_name;;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (a == 1 || (a == 0 && lst->hide == 0))
		{
			line_len += lst->begin->len_name;
			write(1, lst->name, lst->len_name);
			j = lst->begin->len_name - lst->len_name + 1;
			while (lst->next != NULL && j--)
				write(1, " ", 1);
			i++;
			if (line_len > size.ws_col)
			{
				line_len = lst->begin->len_name;
				write(1, "\n", 1);
			}
		}
	}
	write(1, "\n", 1);
}

void       ft_print(struct l_file *lst, t_arg *sarg)
{
	static int		first_line = 0;
	static int		does_file = 0;
	t_file			*tmp;

	tmp = lst;
	if (lst->name == NULL && lst->next != NULL)
		lst = lst->next;
	while (lst->name == NULL && lst->next != NULL)
	{
		lst = lst->next;
		tmp = tmp->next;
	}
	lst = tmp;
	if (sarg->a == 1 || (sarg->a == 0 && lst->begin->hide == 0))
	{
		if (sarg->single_arg != 1 || sarg->mr == 1)
		{
			if (first_line != does_file + 1)
				first_line++;
			else
				write(1, "\n", 1);
			if (lst->begin->p_path == 1)
			{
				write(1, lst->begin->path, ft_strlen(lst->begin->path));
				write(1, ":\n", 2);
			}
			else
				does_file = 1;
		}
		if (sarg->l == 1)
		    new_l(lst, sarg);
		if (sarg->l != 1)
			print_nl_b(lst, sarg->a);
		if (lst->begin->p_path == 0)
			write(1, "\n", 1);
	}
}
