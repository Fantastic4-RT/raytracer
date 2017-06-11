/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:06:57 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/05 18:28:02 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*d;
	char	*s;
	size_t	i;
	size_t	j;
	size_t	dlen;

	d = dst;
	s = (char*)src;
	dlen = ft_strlen(dst);
	if (size <= dlen)
		return (size + ft_strlen(src));
	i = 0;
	while (d[i])
		i++;
	j = 0;
	while (s[j] && j < size - i - 1)
	{
		d[dlen] = s[j];
		dlen++;
		j++;
	}
	d[dlen] = '\0';
	return (dlen + (ft_strlen(s) - j));
}
