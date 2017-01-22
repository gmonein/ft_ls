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
	free(res[0]);
	free(res[1]);
	free(res[2]);
	free(res[3]);
	free(res[4]);
	free(res);
}