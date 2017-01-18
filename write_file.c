/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:22:43 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/18 02:01:56 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



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
