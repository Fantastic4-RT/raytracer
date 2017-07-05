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

double		min_res(t_polynome4 *solve)
{
	double	res;
	double	max;

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
	double	t_0;

	solve->x[0] = 0.;
	solve->x[1] = 0.;
	solve->x[2] = 0.;
	solve->x[3] = 0.;
	solve_p4(solve->x, solve->b, solve->c, solve->d, solve->e);
	t_0 = min_res(solve);
	if ((t_0 >= 0.0000001) && (t_0 < *t))
	{
		*t = t_0;
		retval = 1;
	}
	else
		retval = 0;
	return (retval);
}

int		solve_quadric(double discr, double *t, double b, double a)
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

int		intersect_plane(t_ray r, void *p, double *t)
{
	double		denom;
	double		t0;
	double		dp;
	t_plane		*plane;

	plane = (t_plane *)p;
	r.dir = vec3_norm(r.dir);
	plane->normal = vec3_norm(plane->normal);
	denom = vec3_dp(plane->normal, r.dir);
	dp = vec3_dp(vec3_sub(plane->pos, r.pos), plane->normal);
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

int		intersect_cone(t_ray r, void *con, double *t)
{
	t_abs		solve;
	t_vec3		delta_p;
	t_vec3		tmp;
	t_vec3		tmp2;
	t_cone		*cone;

	cone = (t_cone*)con;
	r.dir = vec3_norm(r.dir);
	cone->axis = vec3_norm(cone->axis);
	delta_p = vec3_sub(r.pos, cone->p1);
	tmp = vec3_sub(r.dir, vec3_mult(cone->axis, vec3_dp(r.dir, cone->axis)));
	solve.a = pow(cos(cone->angle * RAD), 2) * vec3_dp(tmp, tmp)
		- pow(sin(cone->angle * RAD), 2) * vec3_dp(r.dir, cone->axis)
		* vec3_dp(r.dir, cone->axis);
	tmp2 = vec3_sub(delta_p,
	vec3_mult(cone->axis, vec3_dp(delta_p, cone->axis)));
	solve.b = 2 * pow(cos(cone->angle * RAD), 2) * vec3_dp(tmp, tmp2)
		- 2 * pow(sin(cone->angle * RAD), 2) * vec3_dp(r.dir, cone->axis)
		* vec3_dp(delta_p, cone->axis);
	solve.c = pow(cos(cone->angle * RAD), 2) * vec3_dp(tmp2, tmp2)
		- pow(sin(cone->angle * RAD), 2) * vec3_dp(delta_p, cone->axis)
		* vec3_dp(delta_p, cone->axis);
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

int		intersect_cylind(t_ray r, void *cyl, double *t)
{
	t_abs		solve;
	t_vec3		tmp;
	t_vec3		tmp2;
	t_vec3		delta_p;
	t_cyl		*cylind;

	cylind = (t_cyl*)cyl;
	r.dir = vec3_norm(r.dir);
	delta_p = vec3_sub(r.pos, cylind->p1);
	cylind->axis = vec3_norm(cylind->axis);
	tmp = vec3_sub(r.dir, vec3_mult(cylind->axis, vec3_dp(r.dir,
														cylind->axis)));
	solve.a = vec3_dp(tmp, tmp);
	tmp2 = vec3_sub(delta_p, vec3_mult(cylind->axis, vec3_dp(delta_p,
														cylind->axis)));
	solve.b = 2 * vec3_dp(tmp, tmp2);
	solve.c = vec3_dp(tmp2, tmp2) - cylind->rad * cylind->rad;
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

int		inter_ray_sphere(t_ray r, void *s, double *t)
{
	t_abs		solve;
	t_vec3		dist;
	t_sphere	*sphere;

	sphere = (t_sphere *)s;
	r.dir = vec3_norm(r.dir);
	dist = vec3_sub(r.pos, sphere->pos);
	solve.a = vec3_dp(r.dir, r.dir);
	solve.b = 2 * vec3_dp(r.dir, dist);
	solve.c = vec3_dp(dist, dist) - (sphere->rad * sphere->rad);
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

//int 	intersect_torus(t_ray r, void *tor, double *t)
//{
//	t_polynome4 solve;
//	t_torus *torus = (t_torus *) tor;
//
//	t_vec3 tmp_q = vec3_sub(r.pos, torus->pos);
//	double tmp_u = vec3_dp(torus->axis, tmp_q);
//	double tmp_v = vec3_dp(torus->axis, r.dir);
//	double tmp_a = 1 - pow(tmp_v, 2.);
//	double tmp_b = 2 * (vec3_dp(tmp_q, r.dir) - (tmp_u * tmp_v));
//	double tmp_c = vec3_dp(tmp_q, tmp_q) - pow(tmp_u, 2.);
//	double p = tmp_a + pow(tmp_v, 2.);
//	double q = tmp_b + 2 * tmp_v;
//	double rad = tmp_c + pow(tmp_u, 2.) + pow(torus->r_mjr, 2.) - pow(torus->r_min / 2, 2.);
//	solve.a = 1;
//	solve.b = (2 * p * q) / pow(p, 2.);
//	solve.c = ((2 * p * rad) + pow(q, 2.) - (4 * pow(torus->r_mjr, 2.) * tmp_a)) / pow(p, 2.);
//	solve.d = ((2 * q * rad) - (4 * pow(torus->r_mjr, 2.) * tmp_b)) / pow(p, 2.);
//	solve.e = pow(rad, 2.) - (4 * pow(torus->r_mjr, 2.) * tmp_c) / pow(p, 2.);
//	return (solve_polynome_4(t, &solve));
//}

//int 	intersect_torus(t_ray r, void *tor, double *t)
//{
//	t_polynome4 solve;
//	t_torus *torus = (t_torus *) tor;
//	t_vec3 x = vec3_sub(r.pos, torus->pos);
//	double m = vec3_dp(r.dir, r.dir);
//	double n = vec3_dp(r.dir, x);
//	double o = vec3_dp(x, x);
//	double p = vec3_dp(r.dir, torus->axis);
//	double q = vec3_dp(x, torus->axis);
//
//	solve.a = 1;
//	solve.b = (4 * m * n) / pow(m, 2.);
//	solve.c = ((4 * pow(m, 2.)) + (2 * m * o) - (2 * (pow(torus->r_mjr, 2.) + pow(torus->r_min, 2.)) * m) +
//			(4 * pow(torus->r_mjr, 2.) * pow(p, 2.)))/ pow(m, 2.);
//	solve.d = ((4 * n * o) - (4 * (pow(torus->r_mjr, 2.) + pow(torus->r_min, 2.)) *
//								  n) + (8 * pow(torus->r_mjr, 2.) * p * q)) / pow(m, 2.);
//	solve.e = (pow(o, 2.) - (2 * (pow(torus->r_mjr, 2.) + pow(torus->r_min, 2.)) * o) +
//			(4 * pow(torus->r_mjr, 2.) * pow(q, 2.)) + pow((pow(torus->r_mjr, 2.) - pow(torus->r_min, 2.)), 2.))/ pow(m, 2.);
//	return (solve_polynome_4(t, &solve));
//}

int 	intersect_torus(t_ray r, void *tor, double *t)
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
	r.dir = vec3_norm(r.dir);
	tmp_q = vec3_sub(r.pos, torus->pos);
	tmp_u = vec3_dp(torus->axis, tmp_q);
	tmp_v = vec3_dp(torus->axis, r.dir);
	tmp_a = 1 - pow(tmp_v, 2.);
	tmp_b = 2 * (vec3_dp(tmp_q, r.dir) - (tmp_u * tmp_v));
	tmp_c = vec3_dp(tmp_q, tmp_q) - pow(tmp_u, 2.);
	tmp_d = vec3_dp(tmp_q, tmp_q) + pow(torus->r_mjr, 2.) - pow(torus->r_min, 2.);
	solve.a = 1;
	solve.b = 4 * (vec3_dp(tmp_q, r.dir));
	solve.c = (2 * tmp_d) + (pow(solve.b, 2.) / 4) - (4 * pow(torus->r_mjr, 2.) * tmp_a);
	solve.d = solve.b * tmp_d - (4 * pow(torus->r_mjr, 2.) * tmp_b);
	solve.e = pow(tmp_d, 2.) - (4 * pow(torus->r_mjr, 2.) * tmp_c);
	return (solve_polynome_4(t, &solve));
}

