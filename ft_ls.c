/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:11:02 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/13 20:01:14 by gmonein          ###   ########.fr       */
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

int		ft_ls(char *path)
{
	DIR				*fd;
	struct dirent	*stc;
	struct stat		filestat;
	struct l_list	*toread;
	char			*fpa;

	if (!(fd = opendir(path)))
	{
		printf("foire");
		exit(1);
	}
	toread = ft_initlist();
	while ((stc = readdir(fd)) != NULL)
	{
		fpa = ft_strjoin(path, "/");
		fpa = ft_strjoin(fpa, stc->d_name);
		if (stc->d_name[0] == '.')
		{
	//		write(1, path, ft_strlen(path));
	//		write(1, ":\n", 2);
		}
		else
		{
			stat(fpa, &filestat);
			if (S_ISDIR(filestat.st_mode))
			{
				ft_add_node(toread, path, stc);
				toread = toread->next;
			}
			write(1, stc->d_name, ft_strlen(stc->d_name));
			write(1, " ", 1);
//			print_right(&filestat);
//			write (1, "\n", 1);
		}
	}
	while (toread->begin->next != NULL)
	{
		printf("\n\n%s: \n", toread->begin->next->content);
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
