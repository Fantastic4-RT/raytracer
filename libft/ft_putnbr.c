/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:02:02 by atrepyto          #+#    #+#             */
/*   Updated: 2016/11/29 13:02:04 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	int exception;

	exception = 0;
	if (nb == -2147483648)
	{
		nb = nb / 10;
		exception = -1;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10 && nb <= 2147483647)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	if (nb >= 0 && nb <= 9)
	{
		nb = nb + '0';
		write(1, &nb, 1);
	}
	if (exception < 0)
		write(1, "8", 1);
}
