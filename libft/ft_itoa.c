/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 10:58:42 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/01 20:03:52 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(int value)
{
	int i;

	i = 0;
	if (value < 0)
	{
		i = 1;
		value = -value;
	}
	while (value != 0)
	{
		value = value / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int value)
{
	char	*result;
	int		tval;
	int		i;

	tval = value;
	if (value == -2147483648)
		return (ft_strdup("-2147483648"));
	if (value == 0)
		return (ft_strdup("0"));
	i = ft_nblen(value);
	if (!(result = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (value < 0 && value > -2147483648)
		tval = -tval;
	result[i] = '\0';
	while (tval != 0 && tval <= 2147483647)
	{
		result[--i] = tval % 10 + '0';
		tval = tval / 10;
	}
	if (value < 0 && value > -2147483648)
		result[--i] = '-';
	return (result);
}
