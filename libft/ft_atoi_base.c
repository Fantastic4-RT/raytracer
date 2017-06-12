/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:53:00 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/08 17:43:49 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	base_valid(char *base)
{
	int i;
	int j;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (1);
	while (base[i] != '\0')
	{
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j] || base[i] == '-' || base[j] == '+')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	base_length(char *base)
{
	int i;

	i = 0;
	while (base[i] != '\0')
		i++;
	return (i);
}

int	ret_res(char *str, char *base, int i)
{
	int j;
	int check;
	int res;

	res = 0;
	while (str[i] != '\0')
	{
		j = 0;
		check = 0;
		while (base[j] != '\0')
		{
			if (base[j] == str[i])
			{
				check = 1;
				break ;
			}
			j++;
		}
		if (check == 0)
			return (0);
		res = res * base_length(base) + j;
		i++;
	}
	return (res);
}

int	ft_atoi_base(char *str, char *base)
{
	int i;
	int sign;
	int result;

	sign = 1;
	i = 0;
	if (base_valid(base) == 1)
		return (0);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = ret_res(str, base, i);
	return (result * sign);
}
