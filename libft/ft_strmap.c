/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 14:05:23 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 14:05:28 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	int		length;

	if (s)
	{
		length = ft_strlen(s);
		if ((new = ft_strnew(length)))
		{
			while (length > 0)
			{
				new[length - 1] = (*f)(s[length - 1]);
				length--;
			}
			return (new);
		}
	}
	return (NULL);
}
