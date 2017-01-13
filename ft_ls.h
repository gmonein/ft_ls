/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:29:33 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/13 21:42:13 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define VALID_ARG	"lRartufgd"
# define ILL_OPT	"ls: illegal option -- "

# include "libft/includes/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
#include <sys/stat.h>


typedef struct		l_list
{
	char			*content;
	struct l_list	*next;
	struct l_list	*begin;
}					t_list;

typedef struct		l_file
{
	char			*name;
	struct stat		filestat;
	struct l_file	*next;
	struct l_file	*begin;

}					t_file;

int					ft_get_arg(int ac, char **av, char **arg);
void			ft_get_dir(int ac, char **av, struct l_list *lst);
int					ft_error(int e, char s);
void			ch_see(struct stat *filestat);
void			print_right(struct stat *filestat);

#endif
