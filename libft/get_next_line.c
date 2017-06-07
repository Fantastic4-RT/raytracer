/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 18:53:17 by aradiuk           #+#    #+#             */
/*   Updated: 2017/02/02 13:04:49 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int			get_next_line(const int fd, char **line)
{
	int				ret_val;
	static t_list_g *list;
	t_list_g		*lst_start;

	if (fd == -1 || line == 0)
		return (-1);
	lst_start = list;
	if (list == 0)
	{
		list = malloc(sizeof(t_list_g));
		list->fd = fd;
		list->next = 0;
		list->text.start = 0;
		list->text.end = 0;
		lst_start = list;
	}
	*line = ft_strnew(0);
	list = search_list(fd, list);
	read_buf(line, &list->text, fd, &ret_val);
	list = lst_start;
	return (ret_val);
}

t_list_g	*search_list(int fd, t_list_g *list)
{
	t_list_g *new;

	while (list->next != 0)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	if (list->fd == fd)
		return (list);
	new = malloc(sizeof(t_list_g));
	new->fd = fd;
	new->next = 0;
	new->text.end = 0;
	new->text.start = 0;
	list->next = new;
	return (list->next);
}

void		read_buf(char **line, t_read *text, int fd, int *ret_val)
{
	int		inter;
	char	*line_save;

	*ret_val = 0;
	while (text->start != 0 || (text->end = read(fd, text->buf, BUFF_SIZE)) > 0)
	{
		*ret_val = 1;
		line_save = ft_strdup(*line);
		free(*line);
		if (buf_inter(text, &inter) != -1)
		{
			connect(line, text, inter, line_save);
			break ;
		}
		else
			connect(line, text, -1, line_save);
	}
	if (text->end == -1)
		*ret_val = -1;
}

void		connect(char **line, t_read *text, int inter, char *line_save)
{
	char *temp;

	if (inter != -1)
	{
		temp = ft_strsub(text->buf, (unsigned int)text->start,
			(size_t)(inter - text->start));
		*line = ft_strjoin(line_save, temp);
		text->start = inter + 1;
		if (inter + 1 >= text->end)
			text->start = 0;
	}
	else
	{
		temp = ft_strsub(text->buf, (unsigned int)text->start,
			(size_t)(text->end - text->start));
		*line = ft_strjoin(line_save, temp);
		text->start = 0;
		free(line_save);
	}
	free(temp);
}

int			buf_inter(t_read *text, int *inter)
{
	*inter = text->start;
	while (*inter < text->end)
	{
		if (text->buf[*inter] == '\0' || text->buf[*inter] == '\n')
			return (*inter);
		(*inter)++;
	}
	return (-1);
}
