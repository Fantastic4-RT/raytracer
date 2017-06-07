/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:11:02 by aradiuk           #+#    #+#             */
/*   Updated: 2017/01/30 12:11:04 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	length_of_n(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	if (n == 0)
		i = 1;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	power(int length)
{
	int pow;

	pow = 1;
	while (length > 1)
	{
		pow = pow * 10;
		length--;
	}
	return (pow);
}

char		*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		length;
	int		check;

	check = n;
	i = 0;
	if (n == -2147483648)
		n = -214748364;
	length = length_of_n(n);
	if (!(result = ft_strnew(length)))
		return (NULL);
	if (n < 0 && length--)
	{
		result[i++] = '-';
		n = n * (-1);
	}
	while (length > 0)
		result[i++] = (n / power(length--)) % 10 + '0';
	if (check == -2147483648)
	{
		result[i++] = '8';
		result[i] = '\0';
	}
	return (result);
}
