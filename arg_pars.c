/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 14:38:24 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/12 14:39:45 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_get_arg(int ac, char **av, char **arg)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	*arg = ft_strnew(1);
	*arg[0] = '\0';
	while (i <= (ac - 1) && av[i][0] == '-')
	{
		while (av[i][j] && av[i][0] == '-')
		{
			if (ft_strchr(VALID_ARG, av[i][j]) == NULL)
				return (ft_error(1, av[i][j]));
			*arg = ft_stradd(*arg, av[i][j], 1);
			j++;
		}
		j = 1;
		i++;
	}
	return (1);
}

void			ft_get_dir(int ac, char **av, struct l_list *lst)
{
	int		i;

	i = 1;
	while (av[i] && av[i][0] == '-')
		i++;
	if (!av[i])
		lst->d_name = ft_strdup(".");
	while (av[i])
	{
		lst->d_name = ft_strdup(av[i]);
		lst->next = (t_list *)malloc(sizeof(t_list));
		lst = lst->next;
		i++;
	}
	lst->next = NULL;
}
