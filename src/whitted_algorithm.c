//
// Created by Anastasiia Trepyton on 6/12/17.
//

#include "../includes/rt.h"

inline double clamp(const double lo, const double hi, const double v)
{ return fmax(lo, fmin(hi, v)); }

/*
 * Compute reflection direction
 */
t_vec3 reflect_ray(const t_vec3 i, const t_vec3 n)
{
	return (vec3_sub(i, vec3_mult(n, 2 * (vec3_dp(i, n)))));
}

/*
 * Compute refraction direction
 */

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
		ft_swap(&etai, &etat);
		norm = vec3_invert(n);
	}
	double eta = etai / etat;
	double k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? 0 : vec3_add(vec3_mult(i, eta), vec3_mult(norm, (eta * cosi - sqrt(k)))));
}

/*
 * Compute Fresnel equation
 */

void	frensel(const t_vec3 i, const t_vec3 n, const double irefract, double *amount)
{
	double cosi = clamp(-1, 1, vec3_dp(i, n));
	double etai = 1;
	double etat = irefract;
	if (cosi > 0)
		ft_swap(&etai, &etat);

	double sint = etai / etat * sqrt(fmax(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		*amount = 1;
	else
	{
		double cost = sqrt(fmax(0.0, 1 - sint * sint));
		cosi = fabs(cosi);
		double rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		double rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*amount = (rs * rs + rp * rp) / 2;
	}
}

/*
 * Cast rays recursive algorithm
 */

int cast_ray(t_main *main, int depth)
{

}