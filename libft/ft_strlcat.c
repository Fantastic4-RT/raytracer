/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:09:11 by aradiuk           #+#    #+#             */
/*   Updated: 2016/11/30 15:09:18 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	while (dst[i] != '\0' && i < size)
		i++;
	if (i == size)
		return (size + src_len);
	while (src[j] != '\0' && j < size - i - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + src_len);
}
