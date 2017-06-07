/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:30:32 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 16:30:36 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new;
	size_t	i;
	size_t	length;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	length = ft_strlen(s);
	while ((s[length - 1] == ' ' || s[length - 1] == '\n' ||
						s[length - 1] == '\t') && length)
		length--;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && length)
		i++;
	if (!(new = ft_strnew(length - i)))
		return (NULL);
	while (j + i < length)
	{
		new[j] = s[i + j];
		j++;
	}
	return (new);
}
