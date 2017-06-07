/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:38:47 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/02 12:38:51 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_power(int a)
{
	int power;

	power = 1;
	while (a > 0)
	{
		power = power * 10;
		a--;
	}
	return (power);
}

static int	ft_count(int a)
{
	int count;

	count = 0;
	while (a >= 10)
	{
		a = a / 10;
		count++;
	}
	return (count);
}

void		ft_putnbr(int n)
{
	int count;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n == 0)
		ft_putchar('0');
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = -n;
		}
		count = ft_count(n);
		while (count > 0)
		{
			ft_putchar(((n / ft_power(count)) % 10) + '0');
			count--;
		}
		ft_putchar(n % 10 + '0');
	}
}
