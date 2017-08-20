# include "ft_ls.h"

char	*buffer_uitoa(unsigned int nbr)
{
	static  char	res[12];
	int				i;
	int				j;

	res[11] = '\0';
	i = 10;
	if (nbr == 0)
	{
		res[i] = '0';
		i--;
	}
	while (nbr != 0)
	{
		res[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	j = i + 1;
	while (i != -1)
	{
		res[i] = ' ';
		i--;
	}
	return (&res[j]);
}

char	*get_date(time_t time)
{
	static char	res[64];

	res[0] = ' ';
	ft_strcpy(&res[1], &ctime(&time)[4]);
	res[13] = '\0';
	return (res);
}

void	print_right(char *line_buffer, t_node *node)
{
	line_buffer[0] = (S_ISDIR(node->filestat.st_mode)) ? 'd' : '-';
	line_buffer[1] = (node->filestat.st_mode & S_IRUSR) ? 'r' : '-';
	line_buffer[2] = (node->filestat.st_mode & S_IWUSR) ? 'w' : '-';
	line_buffer[3] = (node->filestat.st_mode & S_IXUSR) ? 'x' : '-';
	line_buffer[4] = (node->filestat.st_mode & S_IRGRP) ? 'r' : '-';
	line_buffer[5] = (node->filestat.st_mode & S_IWGRP) ? 'w' : '-';
	line_buffer[6] = (node->filestat.st_mode & S_IXGRP) ? 'x' : '-';
	line_buffer[7] = (node->filestat.st_mode & S_IROTH) ? 'r' : '-';
	line_buffer[8] = (node->filestat.st_mode & S_IWOTH) ? 'w' : '-';
	line_buffer[9] = (node->filestat.st_mode & S_IXOTH) ? 'x' : '-';
	line_buffer[10] = ' ';
	line_buffer[11] = '\0';
}

int		put_with_indentation(char *dst, char *str, int max)
{
	int		len;
	int		i;

	len = ft_strlen(str);
	i = -1;
	while (++i + len <= max)
		dst[i] = ' ';
	ft_strcpy(&dst[i], str);
	return (max + 1);
}

char	*create_line(t_node *node, t_param *param, size_t *indentation)
{
	static char		line_buffer[1024];
	int				i;

	if (!node)
		return (NULL);
	print_right(line_buffer, node);
	ft_strlen(line_buffer);
	i = 10;
	i += put_with_indentation(&line_buffer[i], node->link, indentation[1] + 1);
	i += put_with_indentation(&line_buffer[i], node->usr_name, indentation[2]);
	i += put_with_indentation(&line_buffer[i], node->grp_name, indentation[3] + 1);
	i += put_with_indentation(&line_buffer[i], node->size, indentation[4] + 1);
	ft_strcat(line_buffer, get_date(node->filestat.st_mtime));
	ft_strcat(line_buffer, " ");
	ft_strcat(line_buffer, node->name);
	return (line_buffer);
}

void	print_with_info(t_ls_list *begin, t_param *param, size_t *info)
{
	int		line;

	line = 0;
	while (begin->next && (begin = begin->next))
	{
		if (param->show_hide == 1 || is_hide(begin->content) == 0)
		{
			write(1, "\n", line);
			ft_putstr(create_line(begin->content, param, info));
			line |= 1;
		}
	}
	ft_putstr("\n");
}

void	print_column(t_ls_list *begin, t_param *param)
{
	return ;
}
void	simple_print(t_ls_list *begin, t_param *param)
{
	int		line;

	line = 0;
	while (begin->next && (begin = begin->next))
	{
		if (param->show_hide == 1 || is_hide(begin->content) == 0)
		{
			write(1, "\n", line);
			if (param->file_info)
				ft_putstr(create_line(begin->content, param, NULL));
			else
				ft_putstr(begin->content->name);
			line |= 1;
		}
	}
	ft_putstr("\n");
}

void	print_dir(t_ls_list *begin, t_param *param, size_t *info)
{
	if (!begin)
		return ;
	sort_list(begin, param);
	if (param->file_info)
		print_with_info(begin, param, info);
	else if (param->column)
		print_column(begin, param);
	else
		simple_print(begin, param);
}

int		print_param(t_ls_list *lst, t_param *param)
{
	int			line;
	DIR			*dir;
	int			ret;
	t_ls_list	*begin;
	size_t		indentation[12];

	line = 0;
	begin = lst;
	while (begin->next && (begin = begin->next))
		if (stat(begin->content->name, &begin->content->filestat))
		{
			ft_putstr_fd("ls: ", 2);
			perror(begin->content->name);
		}
	ft_bzero(indentation, sizeof(indentation));
	while (lst->next && (lst = lst->next))
		if (!(ret = stat(lst->content->name, &lst->content->filestat))
				&& !S_ISDIR(lst->content->filestat.st_mode))
		{
			write(1, "\n", line);
			if (param->file_info)
			{
				get_file_info(indentation, lst->content, param);
				ft_putstr(create_line(lst->content, param, indentation));
			}
			else
				ft_putstr(lst->content->name);
			line |= 1;
		}
	write(1, "\n", line);
	return (line);
}
