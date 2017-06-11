/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:57:25 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/01 16:38:52 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;
	size_t slen;

	i = 0;
	j = 0;
	slen = ft_strlen(to_find);
	if (to_find == '\0' || slen == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		while (to_find[j] == str[j + i] && j + i < len)
		{
			if (j == slen - 1)
				return ((char*)str + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
