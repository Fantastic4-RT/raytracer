/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:37:03 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/01 15:55:18 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *mem;

	mem = (char *)malloc(sizeof(char) * (size + 1));
	if (!(mem))
		return (NULL);
	ft_bzero(mem, size + 1);
	return (mem);
}
