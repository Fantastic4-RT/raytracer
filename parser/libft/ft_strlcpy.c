/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:41:41 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/05 18:28:48 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char	*s;
	size_t	i;
	size_t	len;

	if (!dst || !src)
		return (0);
	s = (char*)src;
	len = ft_strlen(s);
	i = 0;
	while (i < size - 1 && dst[i] && s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
