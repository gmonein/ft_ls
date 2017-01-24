/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:52:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/24 16:56:19 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls(char *path, struct l_file *lst, struct l_file *begin, t_arg *sarg)
{
	struct dirent	*stc;
	DIR				*fd;
	struct stat		*filestat;
	char			*tmppath;

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
			ft_add_dir(lst, stc->d_name, filestat, sarg);
		else
			ft_add_file(lst, stc->d_name, filestat, sarg);
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
	while (toread->next != NULL)
	{
		toread = toread->next;
		if (ft_ls(toread->name, lst, lst, &sarg) == 1)
		{
//			ft_print_mr(lst, &sarg, repeat);
			ft_free_tree(lst->begin);
			lst = ft_init_lst();
			if (toread->next != NULL)
				write(1, "\n", 1);
		}
	}
	ft_free_tree(toread);
	return (0);
}
