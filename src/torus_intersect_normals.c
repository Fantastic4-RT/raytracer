/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_intersect_normals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:32:44 by vhorbach          #+#    #+#             */
/*   Updated: 2017/07/10 16:36:53 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		fmin_custom(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	else if (a < 0)
		return (b);
	else if (b < 0)
		return (a);
	return (fmin(a, b));
}

double		min_res(t_polynome4 *solve)
{
	double	res;
	double	a;
	double	b;

	if (solve->x[0] <= 0 && solve->x[1] <= 0 && solve->x[2] <= 0 &&
		solve->x[3] <= 0)
		return (0);
	a = fmin_custom(solve->x[0], solve->x[1]);
	b = fmin_custom(solve->x[2], solve->x[3]);
	res = fmin_custom(a, b);
	return (res);
}

int			solve_polynome_4(double *t, t_polynome4 *solve)
{
	int		retval;
	double	t_0;

	solve->x[0] = 0.;
	solve->x[1] = 0.;
	solve->x[2] = 0.;
	solve->x[3] = 0.;
	solve->poly[4] = solve->a;
	solve->poly[3] = solve->b;
	solve->poly[2] = solve->c;
	solve->poly[1] = solve->d;
	solve->poly[0] = solve->e;
	solve_real_poly_1(4, solve->poly, solve->x, solve);
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

t_vec3		torus_norm(void *data, t_vec3 hitpoint)
{
	t_torus *tor;

	tor = (t_torus *)data;
	tor->norm.a = vec3_sub(hitpoint, tor->pos);
	tor->norm.y = vec3_dp(tor->norm.a, tor->axis);
	tor->norm.b = vec3_mult(tor->axis, tor->norm.y);
	tor->norm.d = vec3_sub(tor->norm.a, tor->norm.b);
	tor->norm.c = vec3_dp(tor->norm.d, tor->norm.d);
	tor->norm.m = 1. / sqrt(tor->norm.c);
	tor->norm.k = vec3_mult(tor->norm.d, tor->norm.m);
	tor->norm.x = vec3_mult(tor->norm.k, tor->r_mjr);
	return (vec3_norm(vec3_sub(tor->norm.a, tor->norm.x)));
}

int			intersect_torus(t_ray r, void *tor, double *t)
{
	t_polynome4		solve;
	t_vec3			tmp_q;
	t_torus			*torus;

	torus = (t_torus *)tor;
	r.dir = vec3_norm(r.dir);
	tmp_q = vec3_sub(r.pos, torus->pos);
	torus->intersect.tmp_u = vec3_dp(torus->axis, tmp_q);
	torus->intersect.tmp_v = vec3_dp(torus->axis, r.dir);
	torus->intersect.tmp_a = 1 - pow(torus->intersect.tmp_v, 2.);
	torus->intersect.tmp_b = 2 * (vec3_dp(tmp_q, r.dir) -
			(torus->intersect.tmp_u * torus->intersect.tmp_v));
	torus->intersect.tmp_c = vec3_dp(tmp_q, tmp_q) -
					pow(torus->intersect.tmp_u, 2.);
	torus->intersect.tmp_d = vec3_dp(tmp_q, tmp_q) + pow(torus->r_mjr, 2.)
						- pow(torus->r_min, 2.);
	solve.a = 1;
	solve.b = 4 * (vec3_dp(tmp_q, r.dir));
	solve.c = (2 * torus->intersect.tmp_d) + (pow(solve.b, 2.) / 4)
		- (4 * pow(torus->r_mjr, 2.) * torus->intersect.tmp_a);
	solve.d = solve.b * torus->intersect.tmp_d - (4 * pow(torus->r_mjr, 2.) *
											torus->intersect.tmp_b);
	solve.e = pow(torus->intersect.tmp_d, 2.) - (4 * pow(torus->r_mjr, 2.) *
											torus->intersect.tmp_c);
	return (solve_polynome_4(t, &solve));
}
