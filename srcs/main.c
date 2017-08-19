# include <stdio.h>
# include "ft_ls.h"

t_node		get_info(char *file, char *path, t_param *param)
{
	t_node		res;
	int			ret;
	static char	error_buffer[NAME_MAX + PATH_MAX];

	ft_bzero(&res, sizeof(res));
	ret = stat(file, &res.filestat);
	if (ret)
	{
		bzero(error_buffer, sizeof(error_buffer));
		ft_strcat(error_buffer, "ls: ");
		ft_strcat(error_buffer, file);
		perror(error_buffer);
	}
	if (file)
		ft_strcpy(res.name, file);
	if (path)
		ft_strcpy(res.path, path);
	res.dir = NULL;
	return (res);
}

void	sort_by_ctime(t_ls_list *begin, t_param *param)
{
	t_ls_list	*lst;
	void		*tmp;

	while (begin->next)
	{
		begin = begin->next;
		lst = begin;
		while (lst->next)
		{
			lst = lst->next;
			if ((begin->content->filestat.st_ctime
						< lst->content->filestat.st_ctime)
				^ param->reverse_sort)
			{
				tmp = lst->content;
				lst->content = begin->content;
				begin->content = tmp;
			}
		}
	}
}
void	sort_by_name(t_ls_list *begin, t_param *param)
{
	t_ls_list	*lst;
	void		*tmp;

	while (begin->next)
	{
		begin = begin->next;
		lst = begin;
		while (lst->next)
		{
			lst = lst->next;
			if ((ft_strcmp(begin->content->name, lst->content->name) > 0)
				^ param->reverse_sort)
			{
				tmp = lst->content;
				lst->content = begin->content;
				begin->content = tmp;
			}
		}
	}
}

int		main(int argc, char **argv)
{
	t_env		env;
	int			ret;
	t_ls_list	*lst;
	t_ls_list	*begin;

	if (get_params(&argv[1], argc - 1, &env.param) == -1)
		return (0);
	lst = read_params(&env.param);
	if (env.param.time_sort)
		sort_by_ctime(lst, &env.param);
	else
		sort_by_name(lst, &env.param);
	begin = lst;
	while (lst->next)
	{
		lst = lst->next;
		printf("%s\n", lst->content->name);
	}
	free_lst((void *)begin);
	return (1);
}
