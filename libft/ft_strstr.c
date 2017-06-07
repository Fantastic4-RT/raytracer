/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:37:40 by aradiuk           #+#    #+#             */
/*   Updated: 2016/11/30 17:37:47 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;
	int check;
	int length;

	i = 0;
	length = ft_strlen(little);
	if (length == 0)
		return ((char *)big);
	while (big[i] != '\0')
	{
		check = 0;
		j = 0;
		while (big[i + j] == little[j] &&
				big[i + j] != '\0' && little[j] != '\0')
		{
			check += 1;
			j++;
		}
		if (check == length)
			return (&((char *)big)[i]);
		i++;
	}
	return (0);
}
