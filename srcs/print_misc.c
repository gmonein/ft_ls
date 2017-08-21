/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 03:28:08 by gmonein           #+#    #+#             */
/*   Updated: 2017/08/21 03:31:00 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*buffer_uitoa(unsigned int nbr)
{
	static char		res[12];
	int				i;
	int				j;

	res[11] = '\0';
	i = 10;
	if (nbr == 0)
	{
		res[i] = '0';
		i--;
	}
	while (nbr != 0)
	{
		res[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	j = i + 1;
	while (i != -1)
	{
		res[i] = ' ';
		i--;
	}
	return (&res[j]);
}

char	*get_date(time_t time)
{
	static char	res[64];

	res[0] = ' ';
	ft_strcpy(&res[1], &ctime(&time)[4]);
	res[13] = '\0';
	return (res);
}

int		put_with_indentation(char *dst, char *str, int max)
{
	int		len;
	int		i;

	len = ft_strlen(str);
	i = -1;
	while (++i + len <= max)
		dst[i] = ' ';
	ft_strcpy(&dst[i], str);
	return (max + 1);
}

void	print_right(char *line_buffer, t_node *node)
{
	line_buffer[0] = (S_ISDIR(node->filestat.st_mode)) ? 'd' : '-';
	line_buffer[0] = (S_ISLNK(node->filestat.st_mode)) ? 'l' : line_buffer[0];
	line_buffer[1] = (node->filestat.st_mode & S_IRUSR) ? 'r' : '-';
	line_buffer[2] = (node->filestat.st_mode & S_IWUSR) ? 'w' : '-';
	line_buffer[3] = (node->filestat.st_mode & S_IXUSR) ? 'x' : '-';
	line_buffer[4] = (node->filestat.st_mode & S_IRGRP) ? 'r' : '-';
	line_buffer[5] = (node->filestat.st_mode & S_IWGRP) ? 'w' : '-';
	line_buffer[6] = (node->filestat.st_mode & S_IXGRP) ? 'x' : '-';
	line_buffer[7] = (node->filestat.st_mode & S_IROTH) ? 'r' : '-';
	line_buffer[8] = (node->filestat.st_mode & S_IWOTH) ? 'w' : '-';
	line_buffer[9] = (node->filestat.st_mode & S_IXOTH) ? 'x' : '-';
	line_buffer[10] = ' ';
	line_buffer[11] = '\0';
}
