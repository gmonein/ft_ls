/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 08:19:36 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/07 16:41:43 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
