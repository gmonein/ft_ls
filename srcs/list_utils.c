/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:25:16 by marvin            #+#    #+#             */
/*   Updated: 2017/01/27 05:48:39 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct l_file		*lst_sort_place(struct l_file *lst, char *str, t_arg *sarg, struct stat *filestat)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	while (lst->next != NULL)
	{
		tmp = lst;
		lst = lst->next;
		if (sarg->t == 0 && lst->name != NULL && (ft_strcmp(str, lst->name) * sarg->r) > -1)
			return (tmp);
		if (sarg->t == 1 && (lst->filestat == NULL || ((lst->filestat->st_mtime * sarg->r) > (filestat->st_mtime * sarg->r))))
			return (tmp);
	}
	return (tmp->next);
}

void		ft_dupe_lst(t_file *src, t_file *lst)
{
	lst->name = src->name;
	lst->dir = src->dir;
	lst->filestat = src->filestat;
	lst->len_name = src->len_name;
	lst->id = src->id;
	lst->isp = src->isp;
	lst->hide = src->hide;
	lst->col_one = src->col_one;
	lst->col_four = src->col_four;;
	lst->total = src->total;
}

struct l_file		*ft_init_lst(void)
{
	struct l_file	*lst;

	lst = (struct l_file *)malloc(sizeof(struct l_file));
	lst->name = NULL;
	lst->next = NULL;
	lst->dir = NULL;
	lst->filestat = NULL;
	lst->len_name = 1;
	lst->id = 0;
	lst->isp = 0;
	lst->hide = 0;
	lst->col_one = 0;
	lst->col_four = 1;
	lst->total = 0;
	lst->begin = lst;
	return (lst);
}


struct l_file		*ft_bet_node(struct l_file *lst)
{
	struct l_file		*tmp;
	struct l_file		*begin;

	tmp = NULL;
	if (lst->next)
		tmp = lst->next;
	lst->next = NULL;
	begin = lst->begin;
	lst->next = ft_init_lst();
	lst = lst->next;
	lst->begin = begin;
	lst->next = tmp;
	return (lst);
}

void	ft_add_dir(struct l_file *lst, char *name, struct stat *filestat, t_arg *arg)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst, name, arg, filestat);
	if (lst->next == NULL)
	{
		lst->next = (struct l_file *)malloc(sizeof(struct l_file));
		lst = lst->next;
		lst->next = NULL;
	}
	else
		lst = ft_bet_node(lst);
	lst->dir = ft_init_lst();
	lst->id = 1;
	lst->name = ft_strdup(name);
	lst->begin = tmp;
	lst->filestat = filestat;
	lst->hide = (name[0] == '.' ? 1 : 0);
	lst->dir->hide = ((name[0] == '.' || lst->begin->hide == 1) ? 1 : 0);
	if ((lst->col_one = ft_gil(filestat->st_nlink)) > lst->begin->col_one && ((arg->a == 0 && ft_strcmp(lst->name, ".") != 0 && ft_strcmp(lst->name, "..") != 0) || arg->a == 1))
		lst->begin->col_one = lst->col_one;
	if ((lst->col_four = ft_gil(filestat->st_size)) > lst->begin->col_four)
		lst->begin->col_four = lst->col_four;
	if ((lst->len_name = ft_strlen(lst->name)) > lst->begin->len_name)
		lst->begin->len_name = lst->len_name;
	lst->begin->total += lst->filestat->st_blocks;
}

void	ft_add_file(struct l_file *lst, char *name, struct stat *filestat, t_arg *arg)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst->begin, name, arg, filestat);
	if (lst->next == NULL)
	{
		lst->next = (struct l_file *)malloc(sizeof(struct l_file));
		lst = lst->next;
		lst->next = NULL;
	}
	else
		lst = ft_bet_node(lst);
	lst->id = 0;
	lst->name = ft_strdup(name);
	lst->begin = tmp;
	lst->dir = NULL;
	lst->filestat = filestat;
	lst->hide = (name[0] == '.' ? 1 : 0);
	if ((lst->col_one = ft_gil(filestat->st_nlink)) > lst->begin->col_one && ((arg->a == 0 && ft_strcmp(lst->name, ".") != 0 && ft_strcmp(lst->name, "..") != 0) || arg->a == 1))
		lst->begin->col_one = lst->col_one;
	if ((lst->col_four = ft_gil(filestat->st_size)) > lst->begin->col_four)
		lst->begin->col_four = lst->col_four;
	if ((lst->len_name = ft_strlen(lst->name)) > lst->begin->len_name)
		lst->begin->len_name = lst->len_name;
	lst->begin->total += lst->filestat->st_blocks;
}
