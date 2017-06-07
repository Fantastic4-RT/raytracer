/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 14:39:23 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 14:39:28 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	length;
	unsigned int	i;

	i = 0;
	if (s)
	{
		length = ft_strlen(s);
		if ((new = ft_strnew(length)))
		{
			while (i < length)
			{
				new[i] = (*f)(i, s[i]);
				i++;
			}
			return (new);
		}
	}
	return (NULL);
}
