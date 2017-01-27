/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:52:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/27 06:47:18 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_first_ls(t_file *av, struct l_file *file, struct l_file *dir, t_arg *sarg)
{
	struct stat		*filestat;

	while (av->next != NULL)
	{
		filestat = (struct stat *)malloc(sizeof(struct stat));
		stat(av->name, filestat);
		if (!S_ISDIR(filestat->st_mode))
			ft_add_file(file->begin->next, av->name, filestat, sarg);
		else
			ft_add_dir(dir->begin, av->name, filestat, sarg);
		av = av->next;
	}
	return (1);
}

int		ft_ls(char *path, struct l_file *lst, struct l_file *begin, t_arg *sarg)
{
	struct dirent	*stc;
	DIR				*fd;
	struct stat		*filestat;
	char			*tmppath;


	if (path == NULL)
		return (0);
	if (!(fd = opendir(path)))
	{
//		write(1, "ls: ", 4);
//		perror(path);
		return (0);
	}
	while ((stc = readdir(fd)) != NULL)
	{
		filestat = (struct stat *)malloc(sizeof(struct stat));
		tmppath = ft_make_path(path, stc->d_name);
		stat(tmppath, filestat);
		if (ft_strcmp(".", stc->d_name) != 0
		&& ft_strcmp("..", stc->d_name) != 0 && S_ISDIR(filestat->st_mode))
			ft_add_dir(lst->begin, stc->d_name, filestat, sarg);
		else
			ft_add_file(lst->begin, stc->d_name, filestat, sarg);
		lst->path = tmppath;
		lst->begin->path = path;
		if (lst->next)
			lst = lst->next;
	}
	lst = begin;
	ft_print(lst, sarg);
	while (lst != NULL && sarg->mr == 1)
	{
		if (lst->id == 1)
			ft_ls(ft_make_path(path, lst->name), lst->dir, lst->dir, sarg);
		lst = lst->next;
	}
	closedir(fd);
	return (1);
}

int		main(int ac, char **av)
{
	struct l_file	*lst;
	struct l_file	*toread;
	long long		cnt;
	char			*arg;
	int				repeat;
	t_file			*tr_file;
	t_file			*tr_dir;
	t_arg			sarg;

	repeat = 0;
	cnt = 0;
	ft_get_arg(ac, av, &arg);
	sarg.single_arg = 0;
	sarg.r = (ft_strchr(arg, 'r') != NULL ? 1 : -1);
	sarg.a = (ft_strchr(arg, 'a') != NULL ? 1 : 0);
	sarg.l = (ft_strchr(arg, 'l') != NULL ? 1 : 0);
	sarg.mr = (ft_strchr(arg, 'R') != NULL ? 1 : 0);
	sarg.t = (ft_strchr(arg, 't') != NULL ? 1 : 0);
	lst = ft_init_lst();
	toread = ft_get_dir(ac, av, &sarg);
	tr_file = ft_init_lst();
	tr_dir = ft_init_lst();
	if (toread->next->next != NULL)
	{
		tr_file->next = ft_init_lst();
		tr_file->next->begin = tr_file;
		tr_dir->next = ft_init_lst();
		tr_dir->next->begin = tr_dir;
		ft_first_ls(toread->next, tr_file, tr_dir, &sarg);
		sarg.f_total = 1;
		tr_file = tr_file->begin;
		tr_dir = tr_dir->begin;
/*		while (tr_file->next != NULL)
		{
			printf("name = %s\n", tr_file->name);
			tr_file = tr_file->next;
		}
		printf("name = %s\n", tr_file->name);
		while (tr_dir->next != NULL)
		{
			printf("dir = %s\n", tr_dir->name);
			tr_dir = tr_dir->next;
		}
		printf("dir = %s\n", tr_dir->name);
*/		tr_file = tr_file->begin;
		ft_print(tr_file, &sarg);
		ft_free_tree(tr_file);
	}
	sarg.f_total = 0;
	tr_dir = tr_dir->begin;
	while (tr_dir->next != NULL)
	{
		tr_dir = tr_dir->next;
		if (ft_ls(tr_dir->name, lst, lst, &sarg) == 1)
		{
			ft_free_tree(lst->begin);
			lst = ft_init_lst();
			if (tr_dir->next != NULL && tr_dir->next->name != NULL)
				write(1, "\n", 1);
		}
	}
	ft_free_tree(toread);
	return (0);
}
