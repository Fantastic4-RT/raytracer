/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:07:51 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 15:07:58 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
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
