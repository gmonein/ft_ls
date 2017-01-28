/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:45:12 by marvin            #+#    #+#             */
/*   Updated: 2017/01/22 06:45:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_right(t_file *lst, t_arg *sarg)
{
	if (sarg->a == 1 || lst->hide == 0)
	{
		write(1, (S_ISDIR(lst->filestat->st_mode) ? "d" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IRUSR ? "r" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IWUSR ? "w" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IXUSR ? "x" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IRGRP ? "r" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IWGRP ? "w" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IXGRP ? "x" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IROTH ? "r" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IWOTH ? "w" : "-"), 1);
		write(1, (lst->filestat->st_mode & S_IXOTH ? "x" : "-"), 1);
		write(1, "", 1);
	}
}

void			print_time(t_file *lst, t_arg *sarg)
{
	char	**res;

	if (sarg->a == 1 || lst->hide == 0)
	{
		res = ft_strsplit(ctime(&lst->filestat->st_mtime), ' ');
		write(1, res[1], ft_strlen(res[1]));
		write(1, " ", 1);
		write(1, res[2], ft_strlen(res[2]));
		write(1, " ", 1);
		write(1, res[3], 5);
		write(1, " ", 1);
		free(res[0]);
		free(res[1]);
		free(res[2]);
		free(res[3]);
		free(res[4]);
		free(res);
	}
}
