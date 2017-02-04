/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 06:28:27 by marvin            #+#    #+#             */
/*   Updated: 2017/02/03 19:23:47 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
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
			if (ft_strchr(VALID_ARG, av[i][j]) == NULL
			&& ((av[i][1] != '-') || (av[i][1] == '-' && av[i][2] != '\0')))
				return (ft_error(1, av[i][j]));
			else if (av[i][1] == '-' && av[i][2] != '\0')
				return (i + 1);
			*arg = ft_stradd(*arg, av[i][j], 1);
			j++;
		}
		j = 1;
		i++;
	}
	return (i - 1);
}

struct l_file		*ft_get_dir(int ac, char **av, t_arg *sarg)
{
	int				i;
	int				r;
	struct l_file	*lst;
	struct l_file	*tmp;

	i = 1;
	lst = ft_init_lst();
	tmp = lst;
	r = ac - 1;
	sarg->single_arg = (ac - i > 1 ? 0 : 1);
	lst->begin->elem = 0;
	if (ac - i == 0 || ac == 1)
	{
		lst->begin->elem = 1;
		lst->next = ft_init_lst();
		lst->next->begin = lst->begin;
		lst = lst->next;
		lst->name = ft_strdup(".");
	}
	else
		while (av[r] && r > (i - 1))
		{
			lst->begin->elem++;
			lst->next = ft_init_lst();
			lst->next->begin = lst->begin;
			lst = lst->next;
			lst->name = ft_strdup(av[r]);
			r--;
		}
	lst->next = NULL;
	return (tmp);
}*/

void		nodir(t_file *lst)
{
	lst->begin->elem = 1;
	lst->next = ft_init_lst();
	lst->next->begin = lst->begin;
	lst = lst->next;
	lst->name = ft_strdup(".");
}

t_file		*pars(int ac, char **av, t_arg *sarg, char **arg)
{
	int		i;
	int		j;
	t_file	*lst;

	i = 0;
	while (av[i] && av[i][0] == '-' && !(av[i][0] == '-' && av[i][1] == '-'))
	{
		j = 1;
		while (av[i][j])
		{
			if (ft_strchr(VALID_ARG, av[i][j]) == NULL && ft_error(1, av[i][j]) == -1)
				return NULL;
			*arg = ft_stradd(*arg, av[i][j], 1);
			j++;
		}
		i++;
	}
	i++;
	lst = ft_init_lst();
	sarg->single_arg = (ac - (i + 1) > 0 ? 0 : 1);
	if (!av[i])
		nodir(lst);
	while (av[i])
	{
		lst->begin->elem++;
		lst->next = ft_init_lst();
		lst->next->begin = lst->begin;
		lst = lst->next;
		lst->name = ft_strdup(av[i]);
		i++;
	}
	return (lst->begin);
}
