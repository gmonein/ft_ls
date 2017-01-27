/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_patern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:30:03 by marvin            #+#    #+#             */
/*   Updated: 2017/01/28 00:31:29 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_l(struct l_file *lst, int a, int f_total)
{
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
			print_right(lst->filestat);
			write(1, "                  ", lst->begin->col_one - lst->col_one);
			ft_putnbr(lst->filestat->st_nlink);
			write(1, " ", 1);
			write(1, getpwuid(lst->filestat->st_uid)->pw_name, ft_strlen(getpwuid(lst->filestat->st_uid)->pw_name));
			write(1, "  ", 2);
			write(1, getgrgid(lst->filestat->st_gid)->gr_name, ft_strlen(getgrgid(lst->filestat->st_gid)->gr_name));
			write(1, "                  ", lst->begin->col_four - lst->col_four + 2);
			ft_putnbr(lst->filestat->st_size);
			write(1, "  ", 1);
			print_time(ctime(&lst->filestat->st_mtime));
			write(1, "  ", 1);
			write(1, lst->name, ft_strlen(lst->name));
			write(1, "\n", 1);
		}
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
			if (y < (line - 1))
				y++;
			else
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
			if (first_line != 2)
				first_line++;
			else
				write(1, "\n", 1);
			if (lst->begin->p_path == 1)
			{
				write(1, lst->begin->path, ft_strlen(lst->begin->path));
				write(1, ":\n", 2);
			}
		}
		if (sarg->l == 1)
		    print_l(lst, sarg->a, sarg->f_total);
		if (sarg->l != 1)
			print_nl_b(lst, sarg->a);
		if (lst->begin->p_path == 0)
			write(1, "\n", 1);
	}
}
