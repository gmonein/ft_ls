/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 08:48:39 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/29 09:44:50 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char		*ft_strcat(char *dst, char *src)
{
	int		i;
	int		end_dst;

	i = 0;
	while (dst[i])
		i++;
	end_dst = i;
	while (src[i - end_dst])
	{
		dst[i] = src[i - end_dst];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_free(char *s1, char *s2, int a, int b)
{
	char	*new;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strcpy(new, (char *)s1);
	ft_strcat(new, (char *)s2);
	if (a == 1)
		free(s1);
	if (b == 1)
		free(s2);
	return (new);
}
