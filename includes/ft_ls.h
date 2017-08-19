#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>
# include <unistd.h>
# include <errno.h>

typedef struct dirent t_dirent;
typedef struct stat t_stat;

typedef struct			s_node
{
	char				name[NAME_MAX];
	char				path[PATH_MAX];
	t_stat				filestat;
	t_dirent			file_info;
	struct s_ls_list	*dir;
}						t_node;

typedef struct			s_ls_list
{
	t_node				*content;
	size_t				content_size;
	struct s_ls_list	*next;
	struct s_ls_list	*past;
	struct s_ls_list	*begin;
}						t_ls_list;

typedef struct		s_param
{
	char			time_sort;
	char			reverse_sort;
	char			file_info;
	char			recursive;
	char			show_hide;
	char			**file;
	char			single_dir;
	char			invalide_param;
}					t_param;

typedef struct		s_env
{
	t_param			param;
	t_ls_list		*begin;
}					t_env;

int		get_params(char **gv, int len, t_param *param);
t_ls_list	*read_params(t_param *param);
void	free_lst(t_list *lst);
t_node		get_info(char *file, char *path, t_param *param);
void	sort_list(t_ls_list *begin, t_param *param);
void		multi_puts(char *a, char *b);
int		is_hide(t_node *node);
int		to_open(t_node *node, t_param *param);
int		print_param(t_ls_list *lst, t_param *param);
void	print_dir(t_ls_list *begin, t_param *param);
char		*make_path(char *path, char *name, int to_do);
t_node		get_info(char *file, char *path, t_param *param);
#endif
