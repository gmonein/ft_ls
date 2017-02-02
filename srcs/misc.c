/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:46:35 by marvin            #+#    #+#             */
/*   Updated: 2017/02/02 19:25:14 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

int					ft_gil(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int					ft_error(int e, char s)
{
	if (e == 1)
	{
		write(1, ILL_OPT, ft_strlen(ILL_OPT));
		write(1, &s, 1);
		write(1, "\n", 1);
		write(1, USAGE, ft_strlen(USAGE));
		write(1, "\n", 1);
	}
	return (-1);
}

void	ft_free(void *f)
{
	if (f)
		free(f);
}

void	ft_free_tree(struct l_file *lst)
{
	if (lst)
	{
		if (lst->next)
		{
			if (lst->dir != NULL)
				ft_free_tree(lst->dir);
			ft_free_tree(lst->next);
		}
		if (lst->filestat)
		{
			ft_free(lst->filestat[0]);
			ft_free(lst->filestat[1]);
		}
		ft_free(lst->name);
		ft_free(lst->path);
		free(lst);
	}
}
