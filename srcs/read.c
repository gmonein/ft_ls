/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 03:23:06 by gmonein           #+#    #+#             */
/*   Updated: 2017/08/21 03:23:54 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*make_path(char *path, char *name, int to_do)
{
	static char	path_buffer[NAME_MAX + PATH_MAX];
	int			len;

	if (to_do == 1)
		return (path_buffer);
	len = ft_strlen(path);
	ft_strcpy(path_buffer, path);
	if (path && path[len - 1] != '/' && to_do != 2)
	{
		path_buffer[len] = '/';
		len++;
		path_buffer[len] = '\0';
	}
	if (name)
		ft_strcpy(&path_buffer[len], name);
	return (path_buffer);
}

t_node		get_info(char *file, char *path, t_param *param)
{
	t_node		res;
	int			ret;
	static char	error_buffer[NAME_MAX + PATH_MAX];

	ft_bzero(&res, sizeof(res));
	if (file)
		ft_strcpy(res.name, file);
	else
		ft_strcpy(res.name, path);
	if (path)
		ft_strcpy(res.path, make_path(path, file, 0));
	else
		ft_strcpy(res.path, make_path("./", NULL, 0));
	ret = lstat(make_path(NULL, NULL, 1), &res.filestat);
	if (ret)
	{
		bzero(error_buffer, sizeof(error_buffer));
		ft_strcat(error_buffer, "ls: ");
		ft_strcat(error_buffer, file);
		perror(error_buffer);
	}
	res.dir = NULL;
	if (param->file_info)
		return (res);
	return (res);
}
