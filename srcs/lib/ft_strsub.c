/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 08:19:36 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/24 02:37:07 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*dst;

	if (s == NULL)
		return (NULL);
	dst = ft_strnew(len + 1);
	i = 0;
	if (dst == NULL)
		return (NULL);
	while (i < len + start)
	{
		if (i >= start)
			dst[i - start] = s[i];
		i++;
	}
	return (dst);
}
