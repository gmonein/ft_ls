/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:52:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/22 07:41:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		g_err(char *beg, char *path, char *end, (*f)(char *str), fd)
{
	write(1, )
}

int		ft_ls(char *path, struct l_file *lst, struct l_file *begin, t_arg *arg)
{
	struct dirent	*stc;
	DIR				*fd;
	struct stat		*filestat;
	char			*tmppath;

	if (!(fd = opendir(path)))
	{
		write(1, "ls: ", 4);
		perror(path);
		return (0);
	}
	while ((stc = readdir(fd)) != NULL)
	{
		filestat = (struct stat *)malloc(sizeof(struct stat));
		tmppath = ft_make_path(path, stc->d_name);
		stat(tmppath, filestat);
		if (ft_strcmp(".", stc->d_name) != 0
		&& ft_strcmp("..", stc->d_name) != 0 && S_ISDIR(filestat->st_mode))
			ft_add_dir(lst, stc->d_name, filestat, arg);
		else
			ft_add_file(lst, stc->d_name, filestat, arg);
		if (sarg->r == 1)
			ft_print(lst, sarg);
		lst->path = tmppath;
		lst->begin->path = path;
		if (lst->next)
			lst = lst->next;
	}
	lst = begin;
	while (lst->next != NULL && arg->mr == 1)
	{
		if (lst->id == 1)
			ft_ls(ft_make_path(path, lst->name), lst->dir, lst->dir, arg);
		lst = lst->next;
	}
	closedir(fd);
	return (1);
}

void	ft_print_mr(struct l_file *lst, t_arg *sarg, int repeat)
{
	struct l_file	*toread;
	struct l_file	*tmpt;
	struct l_file	*tmpl;

	tmpl = lst;
	toread = ft_init_lst();
	tmpt = toread;
	while (lst && lst->next != NULL)
	{
		if (sarg->mr == 1 && lst->id == 1 && (sarg->a == 1 || (sarg->a == 0 && lst->name[0] != '.')))
		{
			toread->next = ft_init_lst();
			toread->name = ft_strdup(lst->begin->path);
			toread = toread->next;
			toread->dir = lst->dir;
		}
		lst = lst->next;
	}
	toread = tmpt;
	if (repeat != 0)
	{
		write(1, tmpl->path, ft_strlen(tmpl->path));
		write(1, ":\n", 2);
	}
	(sarg->l == 1 ? print_l(tmpl, sarg->a) : print_nl(tmpl, sarg->a));
	if (toread->next != NULL)
		write(1, "\n", 1);
	while (toread->next != NULL)
	{
		toread = toread->next;
		ft_print_mr(toread->dir, sarg, 1);
	}
}

int		main(int ac, char **av)
{
	struct l_file	*lst;
	struct l_file	*toread;
	long long		cnt;
	int				tmp;
	char			*arg;
	int				repeat;
	t_arg			sarg;

	repeat = 0;
	cnt = 0;
	ft_get_arg(ac, av, &arg);
	sarg.r = (ft_strchr(arg, 'r') != NULL ? 1 : -1);
	sarg.a = (ft_strchr(arg, 'a') != NULL ? 1 : 0);
	sarg.l = (ft_strchr(arg, 'l') != NULL ? 1 : 0);
	sarg.mr = (ft_strchr(arg, 'R') != NULL ? 1 : 0);
	sarg.t = (ft_strchr(arg, 't') != NULL ? 1 : 0);
	lst = ft_init_lst();
	toread = ft_get_dir(ac, av, &sarg);
	while (toread->next != NULL)
	{
		toread = toread->next;
		if (ft_ls(toread->name, lst, lst, &sarg) == 1)
		{
			ft_print_mr(lst, &sarg, repeat);
			ft_free_tree(lst->begin);
			lst = ft_init_lst();
			if (toread->next != NULL)
				write(1, "\n", 1);
		}
		else
			repeat = 1;
	}
	ft_free_tree(toread);
	return (0);
}
