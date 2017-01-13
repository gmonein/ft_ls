/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:22:43 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/13 20:00:21 by gmonein          ###   ########.fr       */
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
}


/*
#include<stdio.h>

int			main()
{
	DIR		*fd;
	struct stat filestat;
	int i = 0;
	struct dirent *dir;

	dir = (struct dirent *)malloc(sizeof(struct dirent));
	fd = opendir(".");
	while ((dir = readdir(fd)) > 0)
	{
		printf("%s :\t\t", dir->d_name);
		print_right(&filestat);
		if ((stat(dir->d_name, &filestat)) < 0)
			return (0);
		i += filestat.st_blocks;
		printf("%lld\n", filestat.st_blocks);
	}
	printf("total : %d", i);
	free(dir);
	return (0);
}

*/
