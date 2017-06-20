/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <atrepyto@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:15:07 by atrepyto          #+#    #+#             */
/*   Updated: 2017/06/20 15:42:58 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	nb;
	double	minus;
	double	point;

	nb = 0;
	minus = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == 45)
		minus = -1;
	if (*str == 43 || *str == 45)
		str++;
	point = 1;
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
			point = 10.0f;
		if (*str >= '0' && *str <= '9')
		{
			minus /= point;
			nb = nb * 10.0f + (double)(*str - 48);
		}
		str++;
	}
	return (nb * minus);
}
