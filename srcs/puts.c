/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 03:17:46 by gmonein           #+#    #+#             */
/*   Updated: 2017/08/21 04:14:37 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	multi_puts(char *a, char *b)
{
	if (a)
		ft_putstr(a);
	if (b)
		ft_putstr(b);
}

void	triple_puts(char *a, char *b, char *c)
{
	if (a)
		ft_putstr(a);
	if (b)
		ft_putstr(b);
	if (c)
		ft_putstr(c);
}

void	quad_puts(char *a, char *b, char *c, char *d)
{
	if (a)
		ft_putstr(a);
	if (b)
		ft_putstr(b);
	if (c)
		ft_putstr(c);
	if (d)
		ft_putstr(d);
}
