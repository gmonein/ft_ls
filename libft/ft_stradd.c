/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 12:03:34 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/12 12:18:18 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd(char *str, char c, int a)
{
	int		len;
	char	*new;

	len = ft_strlen(str) + 1;
	new = (char *)malloc(sizeof(char) * (len + 1));
	new[len--] = '\0';
	new[len--] = c;
	while (len != -1)
	{
		new[len] = str[len];
		len--;
	}
	if (a == 1)
		free(str);
	return (new);
}
