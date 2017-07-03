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

int		intersect_plane(t_ray r, void *p, double *t)
{
	double		denom;
	double		t0;
	double		dp;
	t_vec3		tmp;
	t_plane *plane = (t_plane *)p;

	r.dir = vec3_norm(r.dir);
	plane->normal = vec3_norm(plane->normal);
	denom = vec3_dp(plane->normal, r.dir);
	tmp = vec3_sub(plane->pos, r.pos);
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

int		intersect_cone(t_ray r, void *con, double *t)
{
	t_abs		solve;
	t_vec3	delta_p;
	t_vec3	tmp;
	t_vec3	tmp2;
	t_cone *cone = (t_cone*)con;
	r.dir = vec3_norm(r.dir);
	cone->axis = vec3_norm(cone->axis);
	delta_p = vec3_sub(r.pos, cone->p1);
	tmp = vec3_sub(r.dir, vec3_mult(cone->axis, vec3_dp(r.dir, cone->axis)));
	solve.a = square_cos(cone->angle) * vec3_dp(tmp, tmp)
		- square_sin(cone->angle) * vec3_dp(r.dir, cone->axis)
		* vec3_dp(r.dir, cone->axis);
	tmp2 = vec3_sub(delta_p,
	vec3_mult(cone->axis, vec3_dp(delta_p, cone->axis)));
	solve.b = 2 * square_cos(cone->angle) * vec3_dp(tmp, tmp2)
		- 2 * square_sin(cone->angle) * vec3_dp(r.dir, cone->axis)
		* vec3_dp(delta_p, cone->axis);
	solve.c = square_cos(cone->angle) * vec3_dp(tmp2, tmp2)
		- square_sin(cone->angle) * vec3_dp(delta_p, cone->axis)
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
	cylind->axis= vec3_norm(cylind->axis);
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

int		intersect_cylind_cut(t_ray r, void *cyl, double *t)
{
	t_abs		solve;
	t_vec3		tmp;
	t_vec3		tmp2;
	t_cyl		*cylind;
    int         retval;

	cylind = (t_cyl*)cyl;
	r.dir = vec3_norm(r.dir);
	cylind->axis= vec3_norm(vec3_sub(cylind->p2, cylind->p1));
	tmp = vec3_sub(r.dir, vec3_mult(cylind->axis, vec3_dp(r.dir,
														  cylind->axis)));
	solve.a = vec3_dp(tmp, tmp);
	tmp2 = vec3_sub(vec3_sub(r.pos, cylind->p1), vec3_mult(cylind->axis,
           vec3_dp(vec3_sub(r.pos, cylind->p1), cylind->axis)));
	solve.b = 2 * vec3_dp(tmp, tmp2);
	solve.c = vec3_dp(tmp2, tmp2) - cylind->rad * cylind->rad;
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
    retval = solve_quadric_cut(solve, t, cylind, r);
	return (retval);
}

int		inter_ray_sphere(t_ray r, void *s, double *t)
{
	t_abs solve;
	t_vec3 dist;
	t_sphere *sphere = (t_sphere *)s;

	r.dir = vec3_norm(r.dir);
	dist = vec3_sub(r.pos, sphere->pos);
	solve.a = vec3_dp(r.dir, r.dir);
	solve.b = 2 * vec3_dp(r.dir, dist);
	solve.c = vec3_dp(dist, dist) - (sphere->rad * sphere->rad);
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

int		inter_ray_sphere_cut(t_ray r, void *sphere, double *t)
{
	t_sphere	*s;
	t_plane		plane;
	t_vec3		hp[2];
	int			tmp[2];

	s = (t_sphere *)sphere;
	s->tt[0] = 2000000.0;
	s->tt[1] = 2000000.0;
	plane.pos = s->p1;
	plane.normal = !vec3_eq(s->pos, s->p1) ? vec3_norm(vec3_sub(s->p1, s->pos))
										   : vec3_create(0, 1, 0);
	tmp[0] = inter_ray_sphere(r, sphere, &s->tt[0]);
	tmp[1] = intersect_plane(r, &plane, &s->tt[1]);
	hp[0] = vec3_sub(vec3_add(r.pos, vec3_mult(r.dir, s->tt[0])), plane.pos);
	hp[1] = vec3_sub(vec3_add(r.pos, vec3_mult(r.dir, s->tt[1])), s->pos);
	tmp[0] = vec3_dp(plane.normal, hp[0]) > 0 ? 0 : tmp[0];
	tmp[1] = vec3_dp(hp[1], hp[1]) > s->rad * s->rad ? 0 : tmp[1];
	if (!tmp[0] && !tmp[1])
		return (0);
	if (tmp[0] && tmp[1])
		*t = fmin(s->tt[0], s->tt[1]);
	else
		*t = tmp[0] ? s->tt[0] : s->tt[1];
	s->hit_obj = *t == s->tt[0] ? 0 : 1;
	return (tmp[0] || tmp[1]);
}

int		intersect_parab(t_ray r, void *par, double *t)
{
	t_parab	*p;
	t_abs	solve;
	t_vec3	d;
	t_vec3	v;
	t_vec3	x;

	p = (t_parab *)par;
	d = r.dir;
	v = p->axis;
	x = vec3_sub(r.pos, p->pos);
	solve.a = vec3_dp(d, d) - vec3_dp(d, v) * vec3_dp(d, v);
	solve.b = 2 * (vec3_dp(d,x) - vec3_dp(d, v) * (vec3_dp(x, v) + 2 * p->k));
	solve.c = vec3_dp(x, x) - vec3_dp(x, v) * (vec3_dp(x, v) + 4 * p->k);
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}