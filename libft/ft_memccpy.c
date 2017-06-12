/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:36:00 by atrepyto          #+#    #+#             */
/*   Updated: 2016/11/30 12:30:13 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	char *dst;
	char *src;

	dst = d;
	src = (void*)s;
	while (n != 0)
	{
		if ((*dst++ = *src++) == c)
			return (dst);
		n--;
	}
	return (0);
}
