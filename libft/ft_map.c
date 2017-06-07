/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:25:11 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/03 17:25:23 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		*ft_map(int *tab, int length, int (*f)(int))
{
	int i;
	int *new;

	new = (int*)malloc(sizeof(*new) * length);
	i = 0;
	while (i < length)
	{
		new[i] = f(tab[i]);
		i++;
	}
	return (new);
}
