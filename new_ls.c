/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:52:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/18 05:00:25 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
#include <sys/stat.h>
# include <stdio.h>
#include <pwd.h>
#include <grp.h>
# include "libft/includes/libft.h"
#include <time.h>

typedef struct		l_file
{
	char			*name;
	int				id;
	int				total;
	int				col_one;
	int				col_four;
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

struct l_file		*lst_sort_place(struct l_file *lst, char *str)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	while (lst->next != NULL)
	{
		tmp = lst;
		lst = lst->next;
		if (lst->name != NULL && ft_strcmp(str, lst->name) < 0)
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

void	ft_add_dir(struct l_file *lst, char *name, struct stat *filestat)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst->begin, name);
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
	lst->begin->total += lst->filestat->st_blocks;
}

void	ft_add_file(struct l_file *lst, char *name, struct stat *filestat)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	if (lst->begin->next != NULL)
		lst = lst_sort_place(lst->begin, name);
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
	lst->begin->total += lst->filestat->st_blocks;
}

int		ft_ls(char *path, struct l_file *lst, struct l_file *begin)
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
			ft_add_dir(lst, stc->d_name, filestat);
		else
			ft_add_file(lst, stc->d_name, filestat);
		if (lst->next)
			lst = lst->next;
	}
	lst = begin;
	while (lst->next != NULL)
	{
		if (lst->id == 1)
			ft_ls(ft_make_path(path, lst->name), lst->dir, lst->dir);
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

int		main()
{
	struct l_file	*lst;
	long long		cnt;
	int				tmp;

	cnt = 0;
	lst = ft_init_lst();
	ft_ls(".", lst, lst);
	printf("total %d\n", lst->total);
	lst = lst->next;
	while (lst != NULL)
	{
		print_right(lst->filestat);
		write(1, "                  ", lst->begin->col_one - lst->col_one);
		ft_putnbr(lst->filestat->st_nlink);
		write(1, " ", 1);
		write(1, getpwuid(lst->filestat->st_uid)->pw_name, ft_strlen(getpwuid(lst->filestat->st_uid)->pw_name));
		write(1, "  ", 2);
		write(1, getgrgid(lst->filestat->st_gid)->gr_name, ft_strlen(getgrgid(lst->filestat->st_gid)->gr_name));
		write(1, "  ", 2);
		write(1, "                  ", lst->begin->col_four - lst->col_four);
		ft_putnbr(lst->filestat->st_size);
		write(1, "  ", 1);
		print_time(ctime(&lst->filestat->st_mtime));
		write(1, "  ", 1);
		write(1, lst->name, ft_strlen(lst->name));
		write(1, "\n", 1);
		lst = lst->next;
	}
	return (0);
}
