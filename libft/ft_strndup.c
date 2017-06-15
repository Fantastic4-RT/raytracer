/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 10:46:34 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/06 10:59:13 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s;
	char	*new;
	size_t	i;

	i = 0;
	s = (char *)s1;
	while (s1[i] && i < n)
		i++;
	new = (char *)malloc(sizeof(char) * i + 1);
	if (!new)
		return (0);
	new[i] = '\0';
	while (s[--i])
		new[i] = s[i];
	return (new);
}
