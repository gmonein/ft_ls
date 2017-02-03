/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_patern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:30:03 by marvin            #+#    #+#             */
/*   Updated: 2017/02/03 17:57:32 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		write(1, "                                         ", (i < 0 ? 0 : i));
		ft_putnbr(lst->filestat[sarg->ml]->st_nlink);
	}
}

void			print_pw(t_file *lst, t_arg *sarg)
{
	int		len;

	if (sarg->a == 1 || lst->hide == 0)
	{
		len = ft_strlen(getpwuid(lst->filestat[sarg->ml]->st_uid)->pw_name);
		write(1, " ", 1);
		write(1, getpwuid(lst->filestat[sarg->ml]->st_uid)->pw_name, len);
	}
}

void			print_gr(t_file *lst, t_arg *sarg)
{
	int		len;

	if (sarg->a == 1 || lst->hide == 0)
	{
		len = ft_strlen(getgrgid(lst->filestat[sarg->ml]->st_gid)->gr_name);
		write(1, "  ", 2);
		write(1, getgrgid(lst->filestat[sarg->ml]->st_gid)->gr_name, len);
	}
}

void			print_size(t_file *lst, t_arg *sarg)
{
	int		i;

	i = lst->begin->col_four - lst->col_four;
	if (sarg->a == 1 || lst->hide == 0)
	{
		write(1, INF_SPACE, i + 2);
		ft_putnbr(lst->filestat[sarg->ml]->st_size);
		write(1, " ", 1);
	}
}

void			print_name(t_file *lst, t_arg *sarg)
{
	if (sarg->a == 1 || lst->hide == 0)
	{
		write(1, lst->name, ft_strlen(lst->name));
		if (sarg->ml == 0 && lst->symb == 1 && sarg->l == 1)
		{
			write(1, " -> ", 4);
			write(1, lst->sl_name, ft_strlen(lst->sl_name));
		}
	}
}

void			print_newline(t_file *lst, t_arg *sarg)
{
	if (sarg->a == 1 || lst->hide == 0)
		write(1, "\n", 1);
}

void			new_l(t_file *lst, t_arg *sarg)
{
	if (lst->begin->f_cnt > 2 || lst->begin->d_cnt > 0)
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
		print_newline(lst, sarg);
	}
	//printf("\n---- %d ----\n", lst->begin->f_cnt + lst->begin->d_cnt - 2);
}

void			print_nl_b(t_file *lst, t_arg *sarg)
{
	while (lst)
	{
		lst = lst->next;
		if (lst && lst->name != NULL)
		{
			print_name(lst, sarg);
			print_newline(lst, sarg);
		}
	}
}

void			print_nl_mc(t_file *lst, t_arg *sarg)
{
	int					col;
	int					line;
	int					elem;
	struct winsize		size;
	char				**tab;
	int					i;
	int					x;
	int					y;
	t_file				*begin;

	begin = lst;
	elem = 0;
	size.ws_col = 0;
	if (sarg->mc == 1)
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	while (lst->next != NULL)
	{
		if ((lst->hide == 0 || sarg->a == 1) && lst->name != NULL)
			elem++;
		lst = lst->next;
	}
	if (sarg->r == -1 && elem != 0)
		elem++;
	if (size.ws_col == 0)
		size.ws_col = lst->begin->len_name;
	col = size.ws_col / lst->begin->len_name;
	line = elem / (col == 0 ? 1 : col);
	(elem % (col == 0 ? 1 : col) > 0 ? line++ : 1);
	tab = (char **)malloc(sizeof(char *) * (line + 1));
	tab[line] = NULL;
	line = (line == 0 ? 1 : line);
	while (--line != -1)
	{
		tab[line] = (char *)malloc(sizeof(char) * (size.ws_col + 1));
		i = 0;
		while (i < size.ws_col)
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
	line = elem / (col == 0 ? 1 : col);
	(elem % (col == 0 ? 1 : col) > 0 ? line++ : 1);
	while (lst != NULL)
	{
		if (lst->hide == 0 || sarg->a == 1)
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
	int		k;
	while (tab[y])
	{
		k = size.ws_col - 1;
		while(tab[y][k] == ' ')
			k--;
		write(1, tab[y], k + 1);
		if (sarg->mc == 0 && tab[y] != NULL && begin->f_cnt > 0)
			write(1, "\n", 1);
		begin->f_cnt--;
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
		}
	}
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
			if (first_line < 2)
				first_line++;
//			else
//				write(1, "\n", 1);
			if (lst->begin->p_path == 1 && first_line != 1)
			{
				write(1, "\n", 1);
				write(1, lst->begin->path, ft_strlen(lst->begin->path));
				write(1, ":\n", 2);
			}
			else
				does_file = 1;
		}
		if (sarg->l == 1)
		    new_l(lst, sarg);
		else if (sarg->l != 1)
			print_nl_b(lst, sarg);
//		if (sarg->only_file != 0 && sarg->mc == 1)
//			write(1, "\n", 1);
	}
}
