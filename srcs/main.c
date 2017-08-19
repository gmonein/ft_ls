# include <stdio.h>
# include "ft_ls.h"

char		*make_path(char *path, char *name, int to_do)
{
	static char	path_buffer[NAME_MAX + PATH_MAX];
	int		len;

	if (to_do == 1)
		return (path_buffer);
	len = ft_strlen(path);
	ft_strcpy(path_buffer, path);
	if (path && path[len - 1] != '/' && to_do != 2)
	{
		path_buffer[len] = '/';
		len++;
		path_buffer[len] = '\0';
	}
	if (name)
		ft_strcpy(&path_buffer[len], name);
	return (path_buffer);
}

t_node		get_info(char *file, char *path, t_param *param)
{
	t_node		res;
	int			ret;
	static char	error_buffer[NAME_MAX + PATH_MAX];

	ft_bzero(&res, sizeof(res));
	if (file)
		ft_strcpy(res.name, file);
	else
		ft_strcpy(res.name, path);
	if (path)
		ft_strcpy(res.path, make_path(path, file, 0));
	else
		ft_strcpy(res.path, make_path("./", NULL, 0));
	ret = stat(make_path(NULL, NULL, 1), &res.filestat);
	if (ret)
	{
		bzero(error_buffer, sizeof(error_buffer));
		ft_strcat(error_buffer, "ls: ");
		ft_strcat(error_buffer, file);
		perror(error_buffer);
	}
	res.dir = NULL;
	return (res);
}

void		multi_puts(char *a, char *b)
{
	write(1, a, ft_strlen(a) - 1);
	ft_putstr(b);
}

t_ls_list	*read_directory(char *path, char *name, t_param *param)
{
	DIR				*directory;
	t_ls_list		*res;
	t_ls_list		*tmp;
	t_dirent		*file;
	t_node			node;

	errno = 0;
	directory = opendir(make_path(path, name, 0));
	if ((param->single_dir != 1 || param->recursive == 1) && (errno != ENOTDIR))
		multi_puts(make_path(NULL, NULL, 1), ":\n");
	if (!directory)
	{
		if (errno != ENOTDIR)
		perror("");
		return (NULL);
	}
	res = (void *)ft_lstnew(NULL, 0);
	tmp = res;
	while ((file = readdir(directory)))
	{
		node = get_info(file->d_name, make_path(path, name, 0), param);
		node.file_info = *file;
		tmp->next = (void *)ft_lstnew(&node, sizeof(t_node));
		tmp = tmp->next;
	}
	closedir(directory);
	return (res);
}

int		to_open(t_node *node, t_param *param)
{
	if (node->name[0] == '.'
	&& ((node->name[1] == '\0' || node->name[1] == '.')
		|| param->show_hide == 0))
		return (0);
	return (1);
}

int		is_hide(t_node *node)
{
	if (node->name[0] == '.')
		return (1);
	return (0);
}

void	print_dir(t_ls_list *begin, t_param *param)
{
	if (!begin)
		return ;
	sort_list(begin, param);
	while (begin->next)
	{
		begin = begin->next;
		if (param->show_hide == 1 || is_hide(begin->content) == 0)
		{
			ft_putstr(begin->content->name);
			ft_putstr("\t");
		}
	}
	ft_putstr("\n");
}

int		ls(char *path, t_param *param, int line)
{
	t_ls_list	*dir;
	t_ls_list	*tmp;

	dir = read_directory(path, NULL, param);
	if (!dir)
		return (0);
	sort_list(dir, param);
	print_dir(dir, param);
	tmp = dir;
	if (param->recursive)
		while (tmp->next)
		{
			tmp = tmp->next;
			if (S_ISDIR(tmp->content->filestat.st_mode))
				if (to_open(tmp->content, param))
				{
					ls(tmp->content->path, param, 1);
				}
		}
	free_lst((void *)dir);
	return (1);
}

int		print_param(t_ls_list *lst, t_param *param)
{
	int		tab;
	DIR			*dir;

	tab = 0;
	while (lst->next)
	{
		lst = lst->next;
		errno = 0;
		dir = opendir(lst->content->name);
		if (errno == ENOTDIR)
		{
			if (tab != 0)
				ft_putstr("\t");
			ft_putstr(lst->content->name);
			tab++;
		}
		else
			closedir(dir);
	}
	return (tab ? 1 : 0);
}

int		main(int argc, char **argv)
{
	t_env		env;
	int			tab;
	t_ls_list	*lst;
	t_ls_list	*begin;

	if (get_params(&argv[1], argc - 1, &env.param) == -1)
		return (0);
	lst = read_params(&env.param);
	sort_list(lst, &env.param);
	begin = lst;
	tab = print_param(lst, &env.param);
	while (lst->next)
	{
		lst = lst->next;
		tab += ls(lst->content->name, &env.param, tab);
	}
	free_lst((void *)begin);
	return (1);
}
