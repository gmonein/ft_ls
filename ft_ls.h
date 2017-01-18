/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:29:33 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/18 09:34:45 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define VALID_ARG	"lRar"
# define ILL_OPT	"ls: illegal option -- "

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include "libft/includes/libft.h"
# include <time.h>

int				ft_get_arg(int ac, char **av, char **arg);
int				ft_error(int e, char s);
void			print_right(struct stat *filestat);

#endif
