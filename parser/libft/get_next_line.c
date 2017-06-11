/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:17:22 by atrepyto          #+#    #+#             */
/*   Updated: 2017/06/08 12:42:03 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static char	*my_cat(char *str, char *buf)
{
	char		*t;

	t = ft_strdup(str);
	ft_strdel(&str);
	str = ft_strjoin(t, buf);
	ft_strdel(&t);
	return (str);
}

static void	get_line(char *str, char **line, char **tmp, char **buf)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i])
		++i;
	*line = ft_strsub(str, 0, i);
	*tmp = ft_strsub(str, i, ft_strlen(str) - i);
	ft_strdel(buf);
	ft_strdel(&str);
}

int			get_next_line(const int fd, char **line)
{
	static char	*tmp[OPEN_MAX];
	char		*buf;
	char		*str;
	int			ret;

	if (fd < 0 || BUFF_SIZE <= 0 || fd > OPEN_MAX)
		return (-1);
	buf = ft_strnew(BUFF_SIZE);
	str = ft_strnew(0);
	if (tmp[fd] && (str = my_cat(str, tmp[fd] + 1)))
		ft_strdel(&tmp[fd]);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		str = my_cat(str, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret == 0 && (buf[0] == '\0' && str[0] == '\0'))
		return (0);
	get_line(str, line, &tmp[fd], &buf);
	return (1);
}
