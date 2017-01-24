/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 19:00:35 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/24 02:36:44 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_memalloc(size_t size)
{
	void	*s;

	if ((s = malloc(size)) == NULL)
		return (NULL);
	ft_bzero(s, size);
	return (s);
}
