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

void	ft_add_dir(struct l_file *lst, char *name)
{
	if (lst->dir != NULL)
	{
		lst->next = (struct l_file *)malloc(sizeof(struct l_file));
		lst->next->begin = lst->begin;
		lst = lst->next;
	}
	lst->dir = (struct l_file *)malloc(sizeof(struct l_file));
	lst->next = NULL;
	lst->name = ft_strdup(name);
}

void	ft_add_file(struct l_file *lst, char *name)
{
	if (lst->name != NULL)
	{
		lst->next = (struct l_file *)malloc(sizeof(struct l_file));
		lst->next->begin = lst->begin;
		lst = lst->next;
	}
	lst->next = NULL;
	lst->name = ft_strdup(name);
}

int		ft_ls(char *path, struct l_file *lst)
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
		printf("%s\n", stc->d_name);
	}
	lst = lst->begin;
	while (lst->next != NULL)
	{
		if (lst->dir != NULL)
			ft_ls(ft_make_path(path, lst->name), lst->dir);
		lst = lst->next;
	}
	return (1);
}

int		main()
{
	struct l_file	*lst;

	lst = (struct l_file *)malloc(sizeof(struct l_file));
	lst->next = NULL;
	lst->begin = lst;
	lst->dir = NULL;
	ft_ls(".", lst);
	return (0);
}
