/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:11:02 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/14 00:36:07 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	ft_delnode(struct l_list *lst)
{
	struct l_list	*tmp;

	tmp = lst;
	if (lst->next != NULL)
	{
		tmp = lst->next->next;
		if (lst->next->content != NULL)
			free(lst->next->content);
		if (lst->next != NULL)
			free(lst->next);
		lst->next = tmp;
	}
}

struct l_list		*ft_initlist(void)
{
	struct l_list	*lst;

	lst = (struct l_list *)malloc(sizeof(struct l_list));
	lst->next = NULL;
	lst->content = NULL;
	lst->begin = lst;
	return (lst);
}

void			ft_add_node(struct l_list *lst, char *path, struct dirent *sct)
{
	lst->next = (struct l_list *)malloc(sizeof(struct l_list));
	lst->next->begin = lst->begin;
	lst = lst->next;
	lst->content = ft_strjoin(path, "/");
	lst->content = ft_strjoin(lst->content, sct->d_name);
	lst->next = NULL;
}

void			lst_add_file(struct l_file *lst, char *name, struct stat filestat)
{
	struct l_file	*tmp;

	tmp = lst->begin;
	lst->next = (struct l_file *)malloc(sizeof(struct l_file));
	lst = lst->next;
	lst->begin = tmp;
	lst->name = ft_strdup(name);
	lst->next = NULL;
	lst->filestat = filestat;
}

struct l_file			*lst_init_file(void)
{
	struct l_file	*lst;

	lst = (struct l_file *)malloc(sizeof(struct l_file));
	lst->next = NULL;
	lst->begin = lst;
	lst->name = NULL;
	return (lst);
}

void		print_name_lst(struct l_file *lst, int max_len)
{
	int				len;
	int				bm_len;
	struct l_file	*tmp;

	bm_len = max_len;
	while (!lst->name)
		lst = lst->next;
	while (lst != NULL)
	{
		if (ft_strcmp(".", lst->name) != 0 && ft_strcmp("..", lst->name) != 0)
		{
			len = ft_strlen(lst->name);
			write(1, lst->name, len);
			while ((bm_len-- - len) >= 0)
				write(1, " ", 1);
		}
		tmp = lst;
		free(tmp->name);
		lst = lst->next;
		free(tmp);
		bm_len = max_len;
	}
}

int		ft_ls(char *path)
{
	DIR				*fd;
	struct dirent	*stc;
	struct stat		filestat;
	struct l_list	*toread;
	struct l_file	*file;
	char			*fpa;
	int				len;
	int				total;

	len = 0;
	total = 0;
	if (!(fd = opendir(path)))
		exit(1);
	toread = ft_initlist();
	file = lst_init_file();
	while ((stc = readdir(fd)) != NULL)
	{
		fpa = ft_strjoin(path, "/");
		fpa = ft_strjoin(fpa, stc->d_name);
		if (stc->d_name[0] != '.')
		{
			stat(fpa, &filestat);
		if (ft_strcmp(".", stc->d_name) != 0 && ft_strcmp("..", stc->d_name) != 0)
			total += filestat.st_blocks;
			if (S_ISDIR(filestat.st_mode) && ft_strcmp(".", stc->d_name) != 0 && ft_strcmp("..", stc->d_name) != 0)
			{
				ft_add_node(toread, path, stc);
				toread = toread->next;
			}
			if (ft_strlen(stc->d_name) > len)
				len = ft_strlen(stc->d_name);
		}
		lst_add_file(file, stc->d_name, filestat);
		file = file->next;
	}
	while (toread->begin->next != NULL)
	{
		file = file->begin;
		file = file->next;
		if (file->name != NULL)
		{
			print_name_lst(file->begin, len);
			write(1, "\n",1);
		}
		printf("\n%s: \ntotal %d\n", toread->begin->next->content, total);
		ft_ls(toread->begin->next->content);
		ft_delnode(toread->begin);
	}
	closedir(fd);
	return (1);
}

int		main()
{
	ft_ls(".");
	return (0);
}
