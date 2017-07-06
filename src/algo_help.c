/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 18:56:43 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/06 13:39:16 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		vec3_to_int(t_vec3 hitcolor)
{
	int res;

	hitcolor = vec3_mult(hitcolor, 255);
	res = ((int)fmin(255, hitcolor.x) << 16) + ((int)fmin(255, hitcolor.y) << 8)
		+ (int)fmin(255, hitcolor.z);
	return (res);
}

double	clamp(const double low, const double high, const double value)
{
	return (fmax(low, fmin(high, value)));
}

t_vec3	reflect_ray(const t_vec3 i, const t_vec3 n)
{
	return (vec3_sub(i, vec3_mult(n, 2 * (vec3_dp(i, n)))));
}

t_vec3	refract_ray(const t_vec3 i, t_vec3 n, double irefract)
{
	double cosi;
	double etai;
	double eta;
	double k;

	cosi = clamp(-1, 1, vec3_dp(i, n));
	etai = 1;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		ft_swap_double(&etai, &irefract);
		n = vec3_invert(n);
	}
	eta = etai / irefract;
	k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? vec3_create(0, 0, 0) : vec3_add(vec3_mult(i, eta),
							vec3_mult(n, (eta * cosi - sqrt(k)))));
}

void	fresnel(const t_vec3 i, const t_vec3 n, double ir, double *amount)
{
	double cosi;
	double etai;
	double sint;
	double cost;
	double r[2];

	cosi = clamp(-1, 1, vec3_dp(i, n));
	etai = 1;
	if (cosi > 0)
		ft_swap_double(&etai, &ir);
	sint = etai / ir * sqrt(fmax(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		*amount = 1;
	else
	{
		cost = sqrt(fmax(0.0, 1 - sint * sint));
		cosi = fabs(cosi);
		r[0] = ((etai * cost) - (ir * cosi))
					/ ((etai * cost) + (ir * cosi));
		r[1] = ((etai * cosi) - (ir * cost))
					/ ((etai * cosi) + (ir * cost));
		*amount = (r[0] * r[0] + r[1] * r[1]) / 2;
	}
}
