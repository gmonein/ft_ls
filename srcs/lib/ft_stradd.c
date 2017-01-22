/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 12:03:34 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/22 08:31:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
