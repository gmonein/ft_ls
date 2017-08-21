/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 03:21:34 by gmonein           #+#    #+#             */
/*   Updated: 2017/08/21 04:14:01 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		to_open(t_node *node, t_param *param)
{
	if (!node)
		return (0);
	if (node->name[0] == '.'
	&& ((node->name[1] == '\0' || node->name[1] == '.')
		|| param->show_hide == 0))
		return (0);
	return (1);
}

int		is_hide(t_node *node)
{
	if (!node)
		return (0);
	if (node->name[0] == '.')
		return (1);
	return (0);
}

void	free_lst(t_list *lst)
{
	if (!lst)
		return ;
	if (lst->next != NULL)
		free_lst(lst->next);
	if (lst != NULL)
	{
		if (lst->content != NULL)
			free(lst->content);
		free(lst);
	}
}
