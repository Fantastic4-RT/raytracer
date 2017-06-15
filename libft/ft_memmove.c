/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:36:14 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/01 16:36:35 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;

	d = dst;
	s = (void*)src;
	if (s > d)
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			d[len - i - 1] = s[len - i - 1];
			i++;
		}
	}
	return (d);
}
