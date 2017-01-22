/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 21:27:31 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/22 08:31:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	while (src[i])
		i++;
	dst = (char*)malloc(sizeof(char) * (i + 1));
	if (dst == NULL)
		return (0);
	while (j < i)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
