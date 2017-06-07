/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:46:37 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 15:46:42 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		len_s1;
	int		len_s2;
	int		i;

	i = -1;
	if (s1 && s2)
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		if ((new = ft_strnew(len_s1 + len_s2)))
		{
			while (i++ < len_s1)
				new[i] = s1[i];
			i = -1;
			while (i++ < len_s2)
				new[i + len_s1] = s2[i];
			return (new);
		}
	}
	return (NULL);
}
