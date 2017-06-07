/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 12:19:48 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 12:19:58 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*dst;

	if ((dst = (char *)malloc(size + 1)))
	{
		ft_bzero(dst, size);
		dst[size] = '\0';
		return (dst);
	}
	else
		return (NULL);
}
