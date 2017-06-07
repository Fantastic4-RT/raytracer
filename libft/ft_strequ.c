/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 14:50:40 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 14:50:47 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		while (s1[i] != '\0' || s2[i] != '\0')
		{
			if (((char *)s1)[i] != ((char *)s2)[i])
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}
