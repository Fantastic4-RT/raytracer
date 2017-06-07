/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:33:36 by aradiuk           #+#    #+#             */
/*   Updated: 2016/11/30 18:33:41 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;
	size_t check;
	size_t start;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		check = 0;
		j = 0;
		start = i;
		while (big[i] == little[j] && i < len && little[j++] && big[i])
		{
			check += 1;
			i++;
		}
		if (check == ft_strlen(little))
			return (&((char *)big)[start]);
		else if (check > 0)
			i = start + 1;
		i++;
	}
	return (0);
}
