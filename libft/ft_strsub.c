/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:10:16 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 15:10:22 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (s)
	{
		if ((new = ft_strnew(len)))
		{
			while (i < len)
			{
				new[i] = s[start + i];
				i++;
			}
			return (new);
		}
	}
	return (NULL);
}
