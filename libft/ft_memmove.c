/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:29:20 by aradiuk           #+#    #+#             */
/*   Updated: 2016/11/29 14:29:22 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (src < dst)
	{
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((const char *)src)[len - 1];
			len--;
		}
	}
	else
		while (i < len)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
	return (dst);
}
