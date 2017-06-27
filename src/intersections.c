/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:59:07 by atrepyto          #+#    #+#             */
/*   Updated: 2017/06/14 14:59:11 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//remove these functions for cos2 sin2

double		square_cos(double n)
{
	double res;

	res = (1 + cos(2 * n * RAD)) / 2;
	return (res);
}

double		square_sin(double n)
{
	double res;

	res = (1 - cos(2 * n * RAD)) / 2;
	return (res);
}

double		min_res(t_polynome4 *solve)
{
	double res;
	double	max;

	res = 0.;
	if (solve->x[0] == 0 && solve->x[1] == 0 && solve->x[2] == 0 && solve->x[3] == 0)
		return (0);
	max = fmax(fmax(solve->x[0], solve->x[1]), fmax(solve->x[2], solve->x[3]));
	solve->x[0] = solve->x[0] == 0 ? max : solve->x[0];
	solve->x[1] = solve->x[1] == 0 ? max : solve->x[1];
	solve->x[2] = solve->x[2] == 0 ? max : solve->x[2];
	solve->x[3] = solve->x[3] == 0 ? max : solve->x[3];
	res = fmin(fmin(solve->x[0], solve->x[1]), fmin(solve->x[2], solve->x[3]));
	return (res);
}

int			solve_polynome_4(double *t, t_polynome4 *solve)
{
	int 	retval;
//	double	result;
//	double	x;
	double	t_0;
//	int i = 0;

	solve->x[0] = 0.;
	solve->x[1] = 0.;
	solve->x[2] = 0.;
	solve->x[3] = 0.;
	solve_p4(solve->x, solve->b, solve->c, solve->d, solve->e);
//	x = 0.1;
//	while (x <= 100.)
//	{
//		result = (solve->a * pow(x, 4.)) + (solve->b * pow(x, 3.)) +
//				(solve->c * pow(x, 2.)) + (solve->d * x) + solve->e;
//		printf("%f\n", result);
//		if (result == 0)
//		{
//			solve->x[i] = x;
//			i++;
//		}
//		x = x + 0.1;
//	}
	t_0 = min_res(solve);
	if ((t_0 >= 0.001) && (t_0 < *t))
	{
		*t = t_0;
		retval = 1;
	}
	else
		retval = 0;
//	printf("%f %f %f %f t_0 == %f\n", solve->x[0], solve->x[1], solve->x[2], solve->x[3], t_0);
	return (retval);
}

int			solve_quadric(double discr, double *t, double b, double a)
{
	int		retval;
	double	t0;
	double	t1;

	if (discr < 0)
		retval = 0;
	else
	{
		t0 = (-b + sqrt(discr)) / (2 * a);
		t1 = (-b - sqrt(discr)) / (2 * a);
		if (t0 > t1)
			t0 = t1;
		if ((t0 > 0.001) && (t0 < *t))
		{
			*t = t0;
			retval = 1;
		}
		else
			retval = 0;
	}
	return (retval);
}

int		intersect_plane(t_ray *r, void *p, double *t)
{
	double		denom;
	double		t0;
	double		dp;
	t_vec3	tmp;
	t_plane *plane = (t_plane *)p;

	r->dir = vec3_norm(r->dir);
	plane->normal = vec3_norm(plane->normal);
	denom = vec3_dp(plane->normal, r->dir);
	tmp = vec3_sub(plane->pos, r->pos);
	dp = vec3_dp(tmp, plane->normal);
	t0 = dp / denom;
	if ((denom > 0.000001 || denom < -0.000001)
		&& dp != 0 && t0 >= 0)
	{
		if (t0 < *t)
		{
			*t = t0;
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}

int		intersect_cone(t_ray *r, void *con, double *t)
{
	t_abs		solve;
	t_vec3	delta_p;
	t_vec3	tmp;
	t_vec3	tmp2;
	t_cone *cone = (t_cone*)con;
	r->dir = vec3_norm(r->dir);
	cone->axis = vec3_norm(cone->axis);
	delta_p = vec3_sub(r->pos, cone->p1);
	tmp = vec3_sub(r->dir, vec3_mult(cone->axis, vec3_dp(r->dir, cone->axis)));
	solve.a = square_cos(cone->angle) * vec3_dp(tmp, tmp)
		- square_sin(cone->angle) * vec3_dp(r->dir, cone->axis)
		* vec3_dp(r->dir, cone->axis);
	tmp2 = vec3_sub(delta_p,
	vec3_mult(cone->axis, vec3_dp(delta_p, cone->axis)));
	solve.b = 2 * square_cos(cone->angle) * vec3_dp(tmp, tmp2)
		- 2 * square_sin(cone->angle) * vec3_dp(r->dir, cone->axis)
		* vec3_dp(delta_p, cone->axis);
	solve.c = square_cos(cone->angle) * vec3_dp(tmp2, tmp2)
		- square_sin(cone->angle) * vec3_dp(delta_p, cone->axis)
		* vec3_dp(delta_p, cone->axis);
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

int		intersect_cylind(t_ray *r, void *cyl, double *t)
{
	t_abs		solve;
	t_vec3		tmp;
	t_vec3		tmp2;
	t_vec3		delta_p;
	t_cyl		*cylind;

	cylind = (t_cyl*)cyl;
	r->dir = vec3_norm(r->dir);
	delta_p = vec3_sub(r->pos, cylind->p1);
	cylind->axis= vec3_norm(cylind->axis);
	tmp = vec3_sub(r->dir, vec3_mult(cylind->axis, vec3_dp(r->dir,
														   cylind->axis)));
	solve.a = vec3_dp(tmp, tmp);
	tmp2 = vec3_sub(delta_p, vec3_mult(cylind->axis, vec3_dp(delta_p,
															 cylind->axis)));
	solve.b = 2 * vec3_dp(tmp, tmp2);
	solve.c = vec3_dp(tmp2, tmp2) - cylind->rad * cylind->rad;
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

int		inter_ray_sphere(t_ray *r, void *s, double *t)
{
	t_abs solve;
	t_vec3 dist;
	t_sphere *sphere = (t_sphere *) s;

	r->dir = vec3_norm(r->dir);
	dist = vec3_sub(r->pos, sphere->pos);
	solve.a = vec3_dp(r->dir, r->dir);
	solve.b = 2 * vec3_dp(r->dir, dist);
	solve.c = vec3_dp(dist, dist) - (sphere->rad * sphere->rad);
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

int 	intersect_torus(t_ray *r, void *tor, double *t)
{
	t_polynome4 solve;
	t_vec3 tmp_q;
	double tmp_u;
	double tmp_v;
	double tmp_a;
	double tmp_b;
	double tmp_c;
	double tmp_d;

	t_torus *torus = (t_torus *) tor;
	r->dir = vec3_norm(r->dir);
	tmp_q = vec3_sub(r->pos, torus->pos);
	tmp_u = vec3_dp(torus->axis, tmp_q);
	tmp_v = vec3_dp(torus->axis, r->dir);
	tmp_a = 1 - pow(tmp_v, 2.);
	tmp_b = 2 * (vec3_dp(tmp_q, r->dir) - (tmp_u * tmp_v));
	tmp_c = vec3_dp(tmp_q, tmp_q) - pow(tmp_u, 2.);
	tmp_d = (vec3_dp(tmp_q, tmp_q) + pow(torus->r_mjr, 2.) - pow(torus->r_min, 2.));
	solve.a = 1;
	solve.b = 4 * (vec3_dp(tmp_q, r->dir));
	solve.c = (2 * tmp_d) + (pow(solve.b, 2.) / 4) - (4 * pow(torus->r_mjr, 2.) * tmp_a);
	solve.d = solve.b * tmp_d - (4 * pow(torus->r_mjr, 2.) * tmp_b);
	solve.e = pow(tmp_d, 2.) - (4 * pow(torus->r_mjr, 2.) * tmp_c);
	return(solve_polynome_4(t, &solve));
}