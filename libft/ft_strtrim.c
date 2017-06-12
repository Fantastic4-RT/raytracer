/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:04:57 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/01 14:44:28 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (*s == '\n' || *s == '\t' || *s == ' ')
		s += 1;
	j = ft_strlen(s);
	while ((s[j - 1] == '\n' || s[j - 1] == '\t' || s[j - 1] == ' ') && j)
		j--;
	new = ft_strnew(j);
	if (!(new))
		return (NULL);
	new[j] = '\0';
	while (j--)
		new[j] = s[j];
	return (new);
}
