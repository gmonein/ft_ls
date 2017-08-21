# include "ft_ls.h"

void	*because_of_norm(char *path)
{
	if (errno != ENOTDIR)
	{
		ft_putstr_fd("ls: ", 2);
		perror(path);
	}
	return (NULL);
}

void		get_file_info(size_t *info, t_node *node, t_param *param)
{
	struct group	*grp;
	struct passwd	*user;

	grp = getgrgid(node->filestat.st_gid);
	user = getpwuid(node->filestat.st_uid);
	if (!S_ISLNK(node->filestat.st_mode) || param->show_hide == 1)
		info[0] += node->filestat.st_blocks;
	ft_strcpy(node->usr_name, user->pw_name);
	ft_strcpy(node->grp_name, grp->gr_name);
	ft_strcpy(node->size, buffer_uitoa(node->filestat.st_size));
	ft_strcpy(node->link, buffer_uitoa(node->filestat.st_nlink));
	if (param->show_hide == 1 || is_hide(node) == 0)
	if (info[1] < ft_strlen(node->link))
		info[1] = ft_strlen(node->link);
	if (info[2] < ft_strlen(user->pw_name))
		info[2] = ft_strlen(user->pw_name);
	if (info[3] < ft_strlen(grp->gr_name))
		info[3] = ft_strlen(grp->gr_name);
	if (info[4] < ft_strlen(node->size))
		info[4] = ft_strlen(node->size);
}

t_ls_list	*read_directory(char *path, char *name, t_param *param, size_t *info)
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
	bzero(info, sizeof(size_t) * 12);
	while ((file = readdir(directory)))
	{
		node = get_info(file->d_name, make_path(path, name, 0), param);
		get_file_info(info, &node, param);
		tmp->next = (void *)ft_lstnew(&node, sizeof(t_node));
		tmp = tmp->next;
	}
	closedir(directory);
	return (res);
}

void	triple_puts(char *a, char *b, char*c)
{
	ft_putstr(a);
	ft_putstr(b);
	ft_putstr(c);
}

void	quad_puts(char *a, char *b, char *c, char *d)
{
	ft_putstr(a);
	ft_putstr(b);
	ft_putstr(c);
	ft_putstr(d);
}

int		ls(char *path, t_param *param, int line)
{
	t_ls_list	*dir;
	t_ls_list	*tmp;
	size_t		info[12];

	write(1, "\n", line);
	if (param->single_dir != 1)
		triple_puts(path, ":", "\n");
	param->single_dir = 0;
	dir = read_directory(path, NULL, param, info);
	if (!dir)
		return (0);
	sort_list(dir, param);
	if (param->file_info)
		triple_puts("total ", buffer_uitoa(info[0]), "\n");
	print_dir(dir, param, info);
	tmp = dir;
	if (param->recursive)
		while (tmp->next)
		{
			tmp = tmp->next;
			if ((tmp->content->filestat.st_mode & S_IFMT) == S_IFDIR)
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
		return (1);
	lst = read_params(&env.param);
	sort_list(lst, &env.param);
	begin = lst;
	tab = print_param(lst, &env.param);
	while (lst->next)
	{
		lst = lst->next;
		if (!lstat(lst->content->name, &lst->content->filestat)
				&& S_ISDIR(lst->content->filestat.st_mode))
		{
			write(1, "\n", (tab > 0 ? 1 : 0));
			tab += ls(lst->content->name, &env.param, 0);
		}
	}
	free_lst((void *)begin);
	return (0);
}
