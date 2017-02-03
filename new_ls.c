/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:52:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/02/03 18:31:09 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_first_ls(t_file *av, struct l_file *file, struct l_file *dir, t_arg *sarg)
{
	struct stat		**filestat;

	filestat = (struct stat **)malloc(sizeof(struct stat *) * 2);
	while (av && av->next != NULL)
	{
		filestat[0] = (struct stat *)malloc(sizeof(struct stat));
		filestat[1] = (struct stat *)malloc(sizeof(struct stat));
		if (lstat(av->name, filestat[0]) == -1
		|| stat(av->name, filestat[1]) == -1)
		{
			write(1, "ls: ", 4);
			perror(av->name);
			return (0);
		}
		if (!S_ISDIR(filestat[sarg->ml]->st_mode))
		{
			ft_add_file_ns(file->begin->next, av->name, filestat, sarg);
			//if (file->begin->d_cnt != 0 && (av->name[0] != '.' || sarg->a == 1))
			//	sarg->only_file = 0;
			file->begin->f_cnt++;
		}
		else
		{
			ft_add_dir_ns(dir->begin, av->name, filestat, sarg);
			if (file->begin->d_cnt != 0 && (av->name[0] != '.' || sarg->a == 1))
				sarg->only_file = 0;
			dir->begin->d_cnt++;
		}
		av = av->next;
	}
	filestat[0] = (struct stat *)malloc(sizeof(struct stat));
	filestat[1] = (struct stat *)malloc(sizeof(struct stat));
	if (lstat(av->name, filestat[0]) == -1
	|| stat(av->name, filestat[1]) == -1)
	{
		write(1, "ls: ", 4);
		perror(av->name);
		return (0);
	}
	if (!S_ISDIR(filestat[sarg->ml]->st_mode))
	{
		ft_add_file_ns(file->begin->next, av->name, filestat, sarg);
		file->begin->f_cnt++;
	}
	else
	{
		ft_add_dir_ns(dir->begin, av->name, filestat, sarg);
		dir->begin->d_cnt++;
	}
	return (1);
}

int		ft_ls(char *path, struct l_file *lst, struct l_file *begin, t_arg *sarg)
{
	struct dirent	*stc;
	DIR				*fd;
	struct stat		**filestat;
	char			*tmppath;


	if (path == NULL)
		return (0);
	if (!(fd = opendir(path)))
	{
		if (sarg->single_arg == 0)
		{
			write(1, "\n./", 3);
			write(1, path, ft_strlen(path));
			write(1, ":\n", 2);
		}
		write(1, "ls: ", 4);
		perror(path);
		return (0);
	}
	filestat = (struct stat **)malloc(sizeof(struct stat *) * 2);
	while ((stc = readdir(fd)) != NULL)
	{
		filestat[0] = (struct stat *)malloc(sizeof(struct stat));
		filestat[1] = (struct stat *)malloc(sizeof(struct stat));
		tmppath = ft_make_path(path, stc->d_name);
		lstat(tmppath, filestat[0]);
		stat(tmppath, filestat[1]);
		lst->begin->tmppath = tmppath;
		if (ft_strcmp(".", stc->d_name) != 0
		&& ft_strcmp("..", stc->d_name) != 0 && S_ISDIR(filestat[sarg->ml]->st_mode) && sarg->mr == 1)
		{
			ft_add_dir(lst->begin, stc, filestat, sarg);
			sarg->only_file = 0;
			sarg->single_arg = 0;
		}
		else
			ft_add_file(lst->begin, stc, filestat, sarg);
		lst->begin->path = path;
		if (lst->next)
			lst = lst->next;
	}
	lst = begin;
	ft_print(lst, sarg);
	while (lst != NULL && sarg->mr == 1)
	{
		if (lst->id == 1)
		{
			ft_ls(ft_make_path(path, lst->name), lst->dir, lst->dir, sarg);
		}
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
	struct winsize	size;
	t_file			*tr_file;
	t_file			*tr_dir;
	t_arg			sarg;
	int				dir_pos;

	repeat = 0;
	cnt = 0;
	dir_pos = ft_get_arg(ac, av, &arg);
	sarg.single_arg = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	sarg.r = (ft_strchr(arg, 'r') != NULL ? 1 : -1);
	sarg.a = (ft_strchr(arg, 'a') != NULL ? 1 : 0);
	sarg.l = (ft_strchr(arg, 'l') != NULL ? 1 : 0);
	sarg.t = (ft_strchr(arg, 't') != NULL ? 1 : 0);
	sarg.mc = (ft_strchr(arg, 'C') != NULL && size.ws_col != 0 ? 1 : 0);
	sarg.ml = (ft_strchr(arg, 'L') != NULL ? 1 : 0);
	sarg.mr = (ft_strchr(arg, 'R') != NULL ? 1 : 0);
	sarg.single_folder = 1;
	sarg.only_file = 1;
	lst = ft_init_lst();
	toread = ft_get_dir((ac - dir_pos), &av[dir_pos], &sarg);
/*	printf("single_arg = %d\n", sarg.single_arg);
	while (toread->next != NULL)
	{
		printf("tr = %s\n", toread->name);
		toread = toread->next;
	}
	printf("tr = %s\n", toread->name);
*/	toread = toread->begin;
	tr_file = ft_init_lst();
	tr_dir = ft_init_lst();
	if ((toread->next != NULL && toread->next->next != NULL) || toread->begin->elem > 0)
	{
		tr_file->next = ft_init_lst();
		tr_file->next->begin = tr_file;
		tr_dir->next = ft_init_lst();
		tr_dir->next->begin = tr_dir;
		ft_first_ls(toread->next, tr_file, tr_dir, &sarg);
		sarg.f_total = 1;
		tr_file = tr_file->begin;
		tr_file->p_path = 0;
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
		if (tr_file->begin->f_cnt != 0)
			ft_print(tr_file, &sarg);
		ft_free_tree(tr_file);
	}
	sarg.f_total = 0;
	tr_dir = tr_dir->begin;
	while (tr_dir->next != NULL)
	{
		tr_dir = tr_dir->next;
		if (tr_dir->name && ft_ls(tr_dir->name, lst, lst, &sarg) == 1)
		{
			ft_free_tree(lst->begin);
			lst = ft_init_lst();
//			if (tr_dir->next != NULL && tr_dir->next->name != NULL)
//				write(1, "\n", 1);
		}
	}
	ft_free_tree(toread);
//	ft_free_tree(tr_file);
//	ft_free_tree(tr_dir);
	return (1);
}
