/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_patern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:30:03 by marvin            #+#    #+#             */
/*   Updated: 2017/01/22 06:30:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_l(struct l_file *lst, int a)
{
	write(1, "total ", 6);
	ft_putnbr(lst->begin->total);
	write(1, "\n", 1);
	while (lst->next != NULL)
	{
	lst = lst->next;
		if (a == 1 || (a == 0 && lst->name[0] != '.'))
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

void			print_nl(struct l_file *lst, int a)
{
	int		i;
	int		j;

	i = 0;
	while (lst->next != NULL)
	{
	lst = lst->next;
		if (a == 1 || (a == 0 && lst->name[0] != '.'))
		{
			write(1, lst->name, lst->len_name);
//			j = lst->begin->len_name - lst->len_name + 2;
//			while (lst->next != NULL && j--)
//				write(1, " ", 1);
//
//			i++;
//			if (i % 5 == 0)
				write(1, "\n", 1);
		}
	}
//	if (i % 5 != 0)
//		write(1, "\n", 1);
}

void        ft_print(struct l_file *lst, t_arg *srag)
{
    if (sarg->l == 1)
        print_l(lst, sarg->a);
    if (sarg->l != 1)
        print_nl(lst, sarg->a);
}