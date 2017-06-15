/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:36:44 by atrepyto          #+#    #+#             */
/*   Updated: 2016/11/30 11:35:08 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *str;

	str = (unsigned char*)s;
	while (n != 0)
	{
		if (*str++ == (unsigned char)c)
			return ((void*)str - 1);
		n--;
	}
	return (0);
}
