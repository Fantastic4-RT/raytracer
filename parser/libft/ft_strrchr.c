/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:20:42 by atrepyto          #+#    #+#             */
/*   Updated: 2016/11/28 17:45:02 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *temp;

	temp = 0;
	while (*s)
	{
		if (*s == (char)c)
			temp = (char*)s;
		s++;
	}
	if ((char)c == '\0' && *s == '\0')
		return ((char*)s);
	return (temp);
}
