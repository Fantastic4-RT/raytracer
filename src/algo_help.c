//
// Created by Anastasiia Trepyton on 7/3/17.
//
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
	return fmax(low, fmin(high, value));
}

t_vec3 reflect_ray(const t_vec3 i, const t_vec3 n)
{
	return (vec3_sub(i, vec3_mult(n, 2 * (vec3_dp(i, n)))));
}

t_vec3 refract_ray(const t_vec3 i, const t_vec3 n, const double irefract)
{
	double cosi = clamp(-1, 1, vec3_dp(i, n));
	double etai = 1;
	double etat = irefract;
	t_vec3 norm = n;

	if (cosi < 0)
		cosi = -cosi;
	else
	{
		ft_swap_double(&etai, &etat);
		norm = vec3_invert(n);
	}
	double eta = etai / etat;
	double k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? vec3_create(0, 0, 0) : vec3_add(vec3_mult(i, eta),
							vec3_mult(norm, (eta * cosi - sqrt(k)))));
}

void	fresnel(const t_vec3 i, const t_vec3 n, const double ir, double *amount)
{
	double cosi;
	double etai;
	double etat;

	cosi = clamp(-1, 1, vec3_dp(i, n));
	etai = 1;
	etat = ir;
	if (cosi > 0)
		ft_swap_double(&etai, &etat);
	double sint = etai / etat * sqrt(fmax(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		*amount = 1;
	else
	{
		double cost = sqrt(fmax(0.0, 1 - sint * sint));
		cosi = fabs(cosi);
		double rs = ((etai * cost) - (etat * cosi))
					/ ((etai * cost) + (etat * cosi));
		double rp = ((etai * cosi) - (etat * cost))
					/ ((etai * cosi) + (etat * cost));
		*amount = (rs * rs + rp * rp) / 2;
	}
}