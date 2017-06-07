/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:51:49 by aradiuk           #+#    #+#             */
/*   Updated: 2016/11/30 16:51:58 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	symb;
	size_t	i;
	char	*str;
	size_t	found;

	symb = (char)c;
	i = 0;
	found = 0;
	str = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == symb)
		{
			str = &((char *)s)[i];
			found = 1;
		}
		i++;
	}
	if (symb == '\0')
		str = &((char *)s)[i];
	if (i == ft_strlen(s) && symb != '\0' && found == 0)
		return (NULL);
	else
		return (str);
}
