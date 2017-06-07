/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:16:54 by aradiuk           #+#    #+#             */
/*   Updated: 2017/03/22 14:17:34 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 10000

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct		s_read
{
	ssize_t		start;
	ssize_t		end;
	char		buf[BUFF_SIZE];
}					t_read;

typedef struct		s_list_g
{
	int				fd;
	t_read			text;
	struct s_list_g	*next;
}					t_list_g;

int					get_next_line(const int fd, char **line);
void				connect(char **line, t_read *text, int inter,
							char *line_save);
void				read_buf(char **line, t_read *text, int fd, int *ret_val);
int					buf_inter(t_read *text, int *inter);
t_list_g			*search_list(int fd, t_list_g *list);

#endif
