# include <stdio.h>
# include "ft_ls.h"

void	*because_of_norm(char *path)
{
	if (errno != ENOTDIR)
	{
		ft_putstr_fd("ls: cannot open directory '", 2);
		ft_putstr_fd(path, 2);
		perror("'");
	}
	return (NULL);
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
	if (!directory)
		return (because_of_norm(path));
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

int		ls(char *path, t_param *param, int line)
{
	t_ls_list	*dir;
	t_ls_list	*tmp;

	dir = read_directory(path, NULL, param);
	if (!dir)
		return (0);
	if (line)
		ft_putstr("\n");
	if ((param->single_dir != 1 || param->recursive == 1) && (errno != ENOTDIR))
		multi_puts(path, "/:\n");
	sort_list(dir, param);
	print_dir(dir, param);
	tmp = dir;
	if (param->recursive)
		while (tmp->next)
		{
			tmp = tmp->next;
			if (S_ISDIR(tmp->content->filestat.st_mode))
				if (to_open(tmp->content, param))
					ls(tmp->content->path, param, 1);
		}
	free_lst((void *)dir);
	return (1);
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
