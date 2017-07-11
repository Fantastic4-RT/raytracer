/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:59:07 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/10 16:34:39 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		if (t0 > 0 && t1 > 0)
			t0 = fmin(t0, t1);
		else if (t0 < 0 || t1 < 0)
			t0 = fmax(t0, t1);
		if ((t0 > 0.000000001) && (t0 < *t))
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
	tmp = vec3_sub(r.dir, vec3_mult(cone->axis, vec3_dp(cone->axis, r.dir)));
	solve.a = pow(cos(cone->angle * RAD), 2) * vec3_dp(tmp, tmp)
		- pow(sin(cone->angle * RAD), 2) * vec3_dp(cone->axis, r.dir)
		* vec3_dp(cone->axis, r.dir);
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
