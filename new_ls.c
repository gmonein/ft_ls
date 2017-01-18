/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:52:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/18 11:19:03 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

typedef struct		l_file
{
	char			*name;
	int				id;
	int				total;
	int				col_one;
	int				col_four;
	int				len_name;
	struct stat		*filestat;
	struct l_file	*dir;
	struct l_file	*next;
	struct l_file	*begin;
}					t_file;

char	*ft_make_path(char *start, char *end)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (start[i])
		i++;
	while (end[j])
		j++;
	path = (char *)malloc(sizeof(char) * (i + j + 2));
	i = -1;
	while (start[++i])
		path[i] = start[i];
	path[i] = '/';
	j = -1;
	while (end[++j])
		path[i + 1 + j] = end[j];
	path[i + 1 + j] = '\0';
	return (path);
}

int					ft_gil(int n)
{
	int		i;

	i = 1;
	while ((n /= 10) != 0)
		i++;
	return (i);
}

struct l_file		*lst_sort_place(struct l_file *lst, char *str, int r)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	while (lst->next != NULL)
	{
		tmp = lst;
		lst = lst->next;
		if (lst->name != NULL && (ft_strcmp(str, lst->name) * r) < 0)
			return (tmp);
	}
	return (tmp->next);
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
	lst->col_one = 1;
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

void	ft_add_dir(struct l_file *lst, char *name, struct stat *filestat, int r)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst->begin, name, r);
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
	if ((lst->col_one = ft_gil(filestat->st_nlink)) > lst->begin->col_one)
		lst->begin->col_one = lst->col_one;
	if ((lst->col_four = ft_gil(filestat->st_size)) > lst->begin->col_four)
		lst->begin->col_four = lst->col_four;
	if ((lst->len_name = ft_strlen(lst->name)) > lst->begin->len_name)
		lst->begin->len_name = lst->len_name;
	lst->begin->total += lst->filestat->st_blocks;
}

void	ft_add_file(struct l_file *lst, char *name, struct stat *filestat, int r)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst->begin, name, r);
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
	if ((lst->col_one = ft_gil(filestat->st_nlink)) > lst->begin->col_one)
		lst->begin->col_one = lst->col_one;
	if ((lst->col_four = ft_gil(filestat->st_size)) > lst->begin->col_four)
		lst->begin->col_four = lst->col_four;
	if ((lst->len_name = ft_strlen(lst->name)) > lst->begin->len_name)
		lst->begin->len_name = lst->len_name;
	lst->begin->total += lst->filestat->st_blocks;
}

int		ft_ls(char *path, struct l_file *lst, struct l_file *begin, int r)
{
	struct dirent	*stc;
	DIR				*fd;
	struct stat		*filestat;

	fd = opendir(path);
	while ((stc = readdir(fd)) != NULL)
	{
		filestat = (struct stat *)malloc(sizeof(struct stat));
		stat(ft_make_path(path, stc->d_name), filestat);
		if (ft_strcmp(".", stc->d_name) != 0
		&& ft_strcmp("..", stc->d_name) != 0 && S_ISDIR(filestat->st_mode))
			ft_add_dir(lst, stc->d_name, filestat, r);
		else
			ft_add_file(lst, stc->d_name, filestat, r);
		if (lst->next)
			lst = lst->next;
	}
	lst = begin;
	while (lst->next != NULL)
	{
		if (lst->id == 1)
			ft_ls(ft_make_path(path, lst->name), lst->dir, lst->dir, r);
		lst = lst->next;
	}
	closedir(fd);
	return (1);
}

void			print_right(struct stat *filestat)
{
	write(1, (S_ISDIR(filestat->st_mode) ? "d" : "-"), 1);
	write(1, (filestat->st_mode & S_IRUSR ? "r" : "-"), 1);
	write(1, (filestat->st_mode & S_IWUSR ? "w" : "-"), 1);
	write(1, (filestat->st_mode & S_IXUSR ? "x" : "-"), 1);
	write(1, (filestat->st_mode & S_IRGRP ? "r" : "-"), 1);
	write(1, (filestat->st_mode & S_IWGRP ? "w" : "-"), 1);
	write(1, (filestat->st_mode & S_IXGRP ? "x" : "-"), 1);
	write(1, (filestat->st_mode & S_IROTH ? "r" : "-"), 1);
	write(1, (filestat->st_mode & S_IWOTH ? "w" : "-"), 1);
	write(1, (filestat->st_mode & S_IXOTH ? "x" : "-"), 1);
	write(1, "  ", 2);
}

void			print_time(char *str)
{
	char	**res;

	res = ft_strsplit(str, ' ');
	write(1, res[1], ft_strlen(res[1]));
	write(1, " ", 1);
	write(1, res[2], ft_strlen(res[2]));
	write(1, " ", 1);
	write(1, res[3], 5);
}

void			print_l(struct l_file *lst, int a)
{
	write(1, "total ", 6);
	ft_putnbr(lst->begin->total);
	write(1, "\n", 1);
	while (lst != NULL)
	{
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
		lst = lst->next;
	}
}

void			print_nl(struct l_file *lst, int a)
{
	int		i;
	int		j;

	i = 0;
	while (lst != NULL)
	{
		if (a == 1 || (a == 0 && lst->name[0] != '.'))
		{
			write(1, lst->name, lst->len_name);
			j = lst->begin->len_name - lst->len_name + 2;
			while (lst->next != NULL && j--)
				write(1, " ", 1);
			i++;
			if (i % 5 == 0)
				write(1, "\n", 1);
		}
		lst = lst->next;
	}
	if (i % 5 != 0)
		write(1, "\n", 1);
}

int					ft_error(int e, char s)
{
	if (e == 1)
	{
		write(1, ILL_OPT, ft_strlen(ILL_OPT));
		write(1, &s, 1);
		write(1, "\n", 1);
	}
	return (-1);
}

int					ft_get_arg(int ac, char **av, char **arg)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	*arg = ft_strnew(1);
	*arg[0] = '\0';
	while (i <= (ac - 1) && av[i][0] == '-')
	{
		while (av[i][j] && av[i][0] == '-')
		{
			if (ft_strchr(VALID_ARG, av[i][j]) == NULL)
				return (ft_error(1, av[i][j]));
			*arg = ft_stradd(*arg, av[i][j], 1);
			j++;
		}
		j = 1;
		i++;
	}
	return (1);
}

struct l_file		*ft_get_dir(int ac, char **av)
{
	int				i;
	struct l_file	*lst;
	struct l_file	*tmp;

	i = 1;
	lst = ft_init_lst();
	tmp = lst;
	while (av[i] && av[i][0] == '-')
		i++;
	if (!av[i])
		lst->name = ft_strdup(".");
	while (av[i])
	{
		lst->next = ft_init_lst();
		lst = lst->next;
		lst->name = ft_strdup(av[i]);
		i++;
	}
	lst->next = NULL;
	return (tmp);
}

int		main(int ac, char **av)
{
	struct l_file	*lst;
	struct l_file	*toread;
	long long		cnt;
	int				tmp;
	char			*arg;
	int				a;
	int				r;

	cnt = 0;
	lst = ft_init_lst();
	ft_get_arg(ac, av, &arg);
	toread = ft_get_dir(ac, av);
	r = (ft_strchr(arg, 'r') != NULL ? -1 : 1);
	a = (ft_strchr(arg, 'a') != NULL ? 1 : 0);
	if (toread->next == NULL)
	{
		ft_ls(toread->name, lst, lst, r);
		(ft_strchr(arg, 'l') != NULL ? print_l(lst, a) : print_nl(lst, a));
	}
	else while (toread != NULL)
	{
		toread = toread->next;
		write(1, toread->name, ft_strlen(toread->name));
		write(1, ":\n", 2);
		ft_ls(toread->name, lst, lst, r);
		(ft_strchr(arg, 'l') != NULL ? print_l(lst, a) : print_nl(lst, a));
	}
	return (0);
}
