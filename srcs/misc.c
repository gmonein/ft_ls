/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:46:35 by marvin            #+#    #+#             */
/*   Updated: 2017/01/22 06:46:35 by marvin           ###   ########.fr       */
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
	}
	return (-1);
}

void	ft_free_tree(struct l_file *lst)
{
	if (lst->next)
	{
		if (lst->dir != NULL)
			ft_free_tree(lst->dir);
		ft_free_tree(lst->next);
	}
	if (lst->filestat)
		free(lst->filestat);
	if (lst->name)
		free(lst->name);
	free(lst);
}
