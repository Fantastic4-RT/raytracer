/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 16:20:00 by aradiuk           #+#    #+#             */
/*   Updated: 2016/11/29 16:20:02 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	symb;
	size_t			i;
	unsigned char	*locate;

	symb = (unsigned char)c;
	i = 0;
	locate = (unsigned char *)s;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == symb)
			return (locate + i);
		i++;
	}
	return (NULL);
}
