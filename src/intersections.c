//
// Created by Anastasiia Trepyton on 6/13/17.
//
#include "../includes/rt.h"

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
	t_plane *plane = (t_plane*)p;

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

	r->dir = unit_vector(r->direction);
	con->rotation = unit_vector(con->rotation);
	delta_p = vector_sub(r->origin, con->pos);
	tmp = vector_sub(r->direction, vector_scalar(vector_dot(r->direction, \
	con->rotation), con->rotation));
	solve.a = square_cos(con->radius) * vector_dot(tmp, tmp)\
		- square_sin(con->radius) * vector_dot(r->direction, con->rotation)
		* vector_dot(r->direction, con->rotation);
	tmp2 = vector_sub(delta_p, \
	vector_scalar(vector_dot(delta_p, con->rotation), con->rotation));
	solve.b = 2 * square_cos(con->radius) * vector_dot(tmp, tmp2)
		- 2 * square_sin(con->radius) * vector_dot(r->direction, con->rotation)\
		* vector_dot(delta_p, con->rotation);
	solve.c = square_cos(con->radius) * vector_dot(tmp2, tmp2)
		- square_sin(con->radius) * vector_dot(delta_p, con->rotation)
		* vector_dot(delta_p, con->rotation);
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
	delta_p = vec3_sub(r->pos, cylind->pos);
	cyl->rotation = unit_vector(cyl->rotation);
	tmp = vector_sub(r->direction, vector_scalar(vector_dot(r->direction,
	cyl->rotation), cyl->rotation));
	solve.a = vector_dot(tmp, tmp);
	tmp2 = vector_sub(delta_p, vector_scalar(vector_dot(delta_p,
	cyl->rotation), cyl->rotation));
	solve.b = 2 * vector_dot(tmp, tmp2);
	solve.c = vector_dot(tmp2, tmp2) - cyl->radius * cyl->radius;
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

int		inter_ray_sphere(t_ray *r, void *s, double *t)
{
	t_abs solve;
	t_vec3 dist;
	t_sphere *sphere = (t_sphere *) s;

	r->dir = vec3_norm(r->dir);
	solve.a = vec3_dp(r->dir, r->dir);
	dist = vec3_sub(r->pos, sphere->pos);
	solve.b = 2 * vec3_dp(r->dir, dist);
	solve.c = vec3_dp(dist, dist) - (sphere->rad * sphere->rad);
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}
