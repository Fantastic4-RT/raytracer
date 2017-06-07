/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:21:13 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/02 13:21:21 by aradiuk          ###   ########.fr       */
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

void		ft_putnbr_fd(int n, int fd)
{
	int count;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
		count = ft_count(n);
		while (count > 0)
		{
			ft_putchar_fd((((n / ft_power(count)) % 10) + '0'), fd);
			count--;
		}
		ft_putchar_fd((n % 10 + '0'), fd);
	}
}
