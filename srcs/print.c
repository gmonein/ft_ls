/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 03:27:26 by gmonein           #+#    #+#             */
/*   Updated: 2017/08/21 04:11:41 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*create_line(t_node *node, t_param *param, size_t *indentation)
{
	static char		line_buffer[1024];
	int				i;

	if (!node)
		return (NULL);
	print_right(line_buffer, node);
	i = 10;
	i += put_with_indentation(&line_buffer[i], node->link, indentation[1] + 1);
	i += put_with_indentation(&line_buffer[i], node->usr_name, indentation[2]);
	i += put_with_indentation(&line_buffer[i], node->grp_name,
															indentation[3] + 1);
	i += put_with_indentation(&line_buffer[i], node->size, indentation[4] + 1);
	ft_strcpy(&line_buffer[i], get_date(node->filestat.st_mtime));
	i += 13;
	line_buffer[i] = ' ';
	i++;
	ft_strcpy(&line_buffer[i], node->name);
	i += ft_strlen(&line_buffer[i]);
	if (S_ISLNK(node->filestat.st_mode))
	{
		ft_strcpy(&line_buffer[i], " -> ");
		i += 4;
		readlink(node->path, &line_buffer[i], NAME_MAX);
	}
	return (line_buffer);
}

void	simple_print(t_ls_list *begin, t_param *param, size_t *info)
{
	int		line;

	line = 0;
	while (begin->next && (begin = begin->next))
	{
		if (param->show_hide == 1 || is_hide(begin->content) == 0)
		{
			write(1, "\n", line);
			if (param->file_info)
				ft_putstr(create_line(begin->content, param, info));
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
	simple_print(begin, param, info);
}

void	print_error_dir(t_ls_list *begin, t_param *param)
{
	if (!begin)
		return ;
	while (begin->next && (begin = begin->next))
		if (stat(begin->content->name, &begin->content->filestat))
		{
			ft_putstr_fd("ls: ", 2);
			perror(begin->content->name);
		}
}

int		print_param(t_ls_list *lst, t_param *param)
{
	int			line;
	DIR			*dir;
	size_t		indentation[12];

	if (!lst)
		return (0);
	line = 0;
	print_error_dir(lst, param);
	ft_bzero(indentation, sizeof(indentation));
	while (lst->next && (lst = lst->next))
		if (!(stat(lst->content->name, &lst->content->filestat))
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
