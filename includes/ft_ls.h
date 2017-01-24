/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:29:33 by gmonein           #+#    #+#             */
/*   Updated: 2017/01/24 03:26:38 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define VALID_ARG	"lRart"
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
# include <time.h>

typedef struct		l_file
{
	char			*name;
	char			*path;
	int				id;
	int				total;
	int				col_one;
	int				col_four;
	int				len_name;
	struct stat		*filestat;
	struct l_file	*dir;
	struct l_file	*next;
	struct l_file	*begin;
}					t_file;

typedef struct		s_arg
{
	int			a;
	int			l;
	int			r;
	int			mr;
	int			t;
}					t_arg;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				**ft_strsplit(char const *s, char c);
char				*ft_strnew(size_t size);
int					ft_error(int e, char s);
size_t				ft_strlen(const char *s);
char				*ft_strdup(char *src);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strchr(const char *str, int c);
char				*ft_stradd(char *str, char c, int a);
void				ft_putnbr(int n);
struct l_file		*lst_sort_place(t_file *lst, char *str, t_arg *sarg, struct stat *filestat);
struct l_file		*ft_init_lst(void);
struct l_file		*ft_bet_node(struct l_file *lst);
void				ft_add_dir(struct l_file *lst, char *name, struct stat *filestat, t_arg *arg);
void				ft_add_file(struct l_file *lst, char *name, struct stat *filestat, t_arg *arg);
char				*ft_make_path(char *start, char *end);
int					ft_gil(int n);
void				ft_free_tree(struct l_file *lst);
void      			ft_print(struct l_file *lst, t_arg *srag);
void				print_nl(struct l_file *lst, int a);
void				print_l(struct l_file *lst, int a);
void				print_right(struct stat *filestat);
void				print_time(char *str);
int					ft_get_arg(int ac, char **av, char **arg);
struct l_file		*ft_get_dir(int ac, char **av, t_arg *sarg);

#endif
