/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:52:51 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/16 20:46:20 by gmonein          ###   ########.fr       */
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
# include "libft/includes/libft.h"

typedef struct		l_file
{
	char			*name;
	int				id;
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

struct l_file		*ft_init_lst(void)
{
	struct l_file	*lst;

	lst = (struct l_file *)malloc(sizeof(struct l_file));
	lst->name = NULL;
	lst->next = NULL;
	lst->dir = NULL;
	lst->id = 0;
	lst->begin = lst;
	return (lst);
}

void	ft_add_dir(struct l_file *lst, char *name)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	lst->next = (struct l_file *)malloc(sizeof(struct l_file));
	lst = lst->next;
	lst->dir = ft_init_lst();
	lst->id = 1;
	lst->name = ft_strdup(name);
	lst->begin = tmp;
	lst->next = NULL;
}

void	ft_add_file(struct l_file *lst, char *name)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	lst->next = (struct l_file *)malloc(sizeof(struct l_file));
	lst = lst->next;
	lst->id = 0;
	lst->name = ft_strdup(name);
	lst->begin = tmp;
	lst->dir = NULL;
	lst->next = NULL;
}

int		ft_ls(char *path, struct l_file *lst, struct l_file *begin)
{
	struct dirent	*stc;
	struct stat		filestat;
	DIR				*fd;

	fd = opendir(path);
	while ((stc = readdir(fd)) != NULL)
	{
		stat(ft_make_path(path, stc->d_name), &filestat);
		if (ft_strcmp(".", stc->d_name) != 0
		&& ft_strcmp("..", stc->d_name) != 0 && S_ISDIR(filestat.st_mode))
			ft_add_dir(lst, stc->d_name);
		else
			ft_add_file(lst, stc->d_name);
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

int		main()
{
	struct l_file	*lst;

	lst = ft_init_lst();
	ft_ls(".", lst, lst);
	return (0);
}
