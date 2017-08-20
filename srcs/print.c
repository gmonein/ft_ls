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
	static char	res[13];
	struct tm	instant;
	int			i;

	instant.tm_sec = time;
	res[0] = ' ';
	res[1] = '\0';
	ft_strcat(res, MONTH[instant.tm_mon]);
	ft_strcat(res, buffer_uitoa(instant.tm_mday + 1) - 1);
	ft_strcat(res, buffer_uitoa(instant.tm_hour) - 1);
	ft_strcat(res, ":");
	ft_strcat(res, buffer_uitoa(instant.tm_min));
	i = -1;
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
}
char	*create_line(t_node *node, t_param *param, int *indentation)
{
	static char		line_buffer[1024];
	int				i;
	struct group	*grp;
	struct passwd	*user;

	grp = getgrgid(node->filestat.st_gid);
	user = getpwuid(node->filestat.st_uid);
	print_right(line_buffer, node);
	ft_strcpy(&line_buffer[11], buffer_uitoa(node->filestat.st_nlink));
	ft_strcat(line_buffer, " ");
	ft_strcat(line_buffer, user->pw_name);
	ft_strcat(line_buffer, " ");
	ft_strcat(line_buffer, grp->gr_name);
	ft_strcat(line_buffer, " ");
	ft_strcat(line_buffer, buffer_uitoa(node->filestat.st_size));
	ft_strcat(line_buffer, get_date(node->filestat.st_mtime));
	ft_strcat(line_buffer, " ");
	ft_strcat(line_buffer, node->name);
	return (line_buffer);
}

void	print_with_info(t_ls_list *begin, t_param *param)
{
	int		line;

	line = 0;
	while (begin->next && (begin = begin->next))
	{
		if (param->show_hide == 1 || is_hide(begin->content) == 0)
		{
			write(1, "\n", line);
			ft_putstr(create_line(begin->content, param, NULL));
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

void	print_dir(t_ls_list *begin, t_param *param)
{
	if (!begin)
		return ;
	sort_list(begin, param);
	if (param->file_info)
		print_with_info(begin, param);
	else if (param->column)
		print_column(begin, param);
	else
		simple_print(begin, param);
}

int		print_param(t_ls_list *lst, t_param *param)
{
	int			line;
	DIR			*dir;

	line = 0;
	while (lst->next && (lst = lst->next))
	{
		errno = 0;
		dir = opendir(lst->content->name);
		if (errno == ENOTDIR)
		{
			write(1, "\n", line);
			if (param->file_info)
				ft_putstr(create_line(lst->content, param, NULL));
			else
				ft_putstr(lst->content->name);
			line |= 1;
		}
		else
			closedir(dir);
	}
	write(1, "\n", line);
	return (line);
}
