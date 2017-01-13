/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 14:05:55 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/12 17:21:51 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

#include <stdio.h>
int		main(int argc, char **argv)
{
	char				*par;
	struct l_list		*lst;

	lst = (struct l_list *)malloc(sizeof(struct l_list));
	if (ft_get_arg(argc, argv, &par) == -1)
		return (0);
	ft_get_dir(argc, argv, lst);
	printf("arg = %s\n", par);
	while (lst->next != NULL)
	{
		printf("%s\n", lst->d_name);
		lst = lst->next;
	}
	free(&par);
	return (1);
}
