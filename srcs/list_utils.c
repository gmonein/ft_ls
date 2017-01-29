/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 00:54:10 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/29 13:14:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_name(char *str, char *name, t_arg *sarg)
{
	if (!name || !str || (ft_strcmp(str, name) * sarg->r) > -1)
		return (1);
	return (0);
}

int		cmp_time(t_file *lst, t_arg *sarg, struct stat *stat)
{
	if (lst->filestat == NULL || ((lst->filestat[sarg->ml]->st_mtime * sarg->r) > (stat->st_mtime * sarg->r)))
		return (1);
	else if (lst->filestat[sarg->ml]->st_mtime == stat->st_mtime)
		return (2);
	return (0);
}

t_file	*lst_sort_place(t_file *lst, char *str, t_arg *sarg, struct stat *stat)
{
	struct l_file	*tmp;
	int				ret_t;

	tmp = lst->begin;
	while (lst->next != NULL)
	{
		tmp = lst;
		lst = lst->next;
		if (sarg->t == 1 && ((ret_t = cmp_time(lst, sarg, stat)) == 1))
			return (tmp);
		if ((sarg->t == 0 || ret_t == 2) && cmp_name(str, lst->name, sarg) == 1)
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
	lst->col_one = 1;
	lst->col_four = 1;
	lst->total = 0;
	lst->p_path = 1;
	lst->f_cnt = 0;
	lst->d_cnt = 0;
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

char	*ft_get_sl_name(t_file *lst)
{
	char	*buf;
	char	*name;
	int		ret;

	buf = (char *)malloc(sizeof(char) * 256);
	name = NULL;
	if ((ret = readlink(lst->begin->tmppath, buf, 256)) != -1)
	{
		buf[ret] = '\0';
		if (name != NULL)
			name = ft_strjoin_free(name, buf, 1, 0);
		else
			name = ft_strdup(buf);
	}
	free(buf);
	return (name);
}

void	ft_add_assign(t_file *lst, char *name, struct stat **filestat, t_arg *sarg)
{
	lst->name = ft_strdup(name);
	lst->filestat = (struct stat **)malloc(sizeof(struct stat *) * 2);
	lst->filestat[0] = filestat[0];
	lst->filestat[1] = filestat[1];
	lst->hide = (name[0] == '.' ? 1 : 0);
	if (lst->begin->tmppath != NULL)
		lst->path = ft_strdup(lst->begin->tmppath);
	else
		lst->path = ft_strdup(name);
	lst->col_one = ft_gil(filestat[sarg->ml]->st_nlink);
	lst->col_four = ft_gil(filestat[sarg->ml]->st_size);
	lst->symb = ((lst->filestat[sarg->ml]->st_mode & S_IFMT) == S_IFLNK ? 1 : 0);
	if (lst->symb == 1)
		lst->sl_name = ft_get_sl_name(lst);
	if ((sarg->a == 1 || lst->hide == 0) && lst->col_one > lst->begin->col_one)
		lst->begin->col_one = lst->col_one;
	if ((sarg->a == 1 || lst->hide == 0) && lst->col_four > lst->begin->col_four)
		lst->begin->col_four = lst->col_four;
	if ((lst->len_name = ft_strlen(lst->name)) > lst->begin->len_name)
		lst->begin->len_name = lst->len_name;
	lst->begin->total += lst->filestat[sarg->ml]->st_blocks;
}

void	ft_add_dir(t_file *lst, struct dirent *stc, struct stat **filestat, t_arg *sarg)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst, stc->d_name, sarg, filestat[sarg->ml]);
	if (lst->next == NULL)
	{
		lst->next = (struct l_file *)malloc(sizeof(struct l_file));
		lst = lst->next;
		lst->next = NULL;
	}
	else
		lst = ft_bet_node(lst);
	lst->begin = tmp;
	lst->dir = ft_init_lst();
	lst->id = 1;
	lst->stc = stc;
	lst->dir->hide = ((stc->d_name[0] == '.' || lst->begin->hide == 1) ? 1 : 0);
	ft_add_assign(lst, stc->d_name, filestat, sarg);
}

void	ft_add_file(t_file *lst, struct dirent *stc, struct stat **filestat, t_arg *sarg)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst->begin, stc->d_name, sarg, filestat[sarg->ml]);
	if (lst->next == NULL)
	{
		lst->next = (struct l_file *)malloc(sizeof(struct l_file));
		lst = lst->next;
		lst->next = NULL;
	}
	else
		lst = ft_bet_node(lst);
	lst->id = 0;
	lst->begin = tmp;
	lst->dir = NULL;
	ft_add_assign(lst, stc->d_name, filestat, sarg);
}

void	ft_add_dir_ns(t_file *lst, char *name, struct stat **filestat, t_arg *sarg)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst, name, sarg, filestat[sarg->ml]);
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
	lst->begin = tmp;
	lst->dir->hide = ((name[0] == '.' || lst->begin->hide == 1) ? 1 : 0);
	ft_add_assign(lst, name, filestat, sarg);
}

void	ft_add_file_ns(t_file *lst, char *name, struct stat **filestat, t_arg *sarg)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst->begin, name, sarg, filestat[sarg->ml]);
	if (lst->next == NULL)
	{
		lst->next = (struct l_file *)malloc(sizeof(struct l_file));
		lst = lst->next;
		lst->next = NULL;
	}
	else
		lst = ft_bet_node(lst);
	lst->id = 0;
	lst->begin = tmp;
	lst->dir = NULL;
	ft_add_assign(lst, name, filestat, sarg);
}
