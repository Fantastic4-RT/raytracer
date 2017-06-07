/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 18:33:30 by aradiuk           #+#    #+#             */
/*   Updated: 2016/11/29 18:33:32 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(s1);
	if ((dst = (char *)malloc(sizeof(char) * (length + 1))))
	{
		while (i < length)
		{
			dst[i] = s1[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}
