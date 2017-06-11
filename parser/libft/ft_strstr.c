/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:53:10 by atrepyto          #+#    #+#             */
/*   Updated: 2016/11/30 10:11:35 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(to_find);
	if (len == 0 || to_find[i] == '\0')
		return ((char*)str);
	while (str[i])
	{
		while (to_find[j] == str[j + i])
		{
			if (j == len - 1)
				return ((char*)str + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
