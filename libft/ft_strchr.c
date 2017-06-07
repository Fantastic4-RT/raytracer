/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:04:43 by aradiuk           #+#    #+#             */
/*   Updated: 2016/11/30 16:04:44 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	symb;
	size_t	i;

	symb = (char)c;
	i = 0;
	while (s[i] != '\0' && s[i] != symb)
		i++;
	if (i == ft_strlen(s) && symb != '\0')
		return (NULL);
	else
		return (&((char *)s)[i]);
}
