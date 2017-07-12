/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_intersections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 17:58:09 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 17:58:11 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		*t = ft_check_min(*t, ft_check_min(s->tt[0], s->tt[1]));
	else
		*t = tmp[0] ? ft_check_min(*t, s->tt[0]) : ft_check_min(*t, s->tt[1]);
	s->hit_obj = *t == s->tt[0] ? 0 : 1;
	return (tmp[0] || tmp[1]);
}

int		intersect_cylind_cut(t_ray r, void *cyl, double *t)
{
	t_abs		solve;
	t_vec3		tmp;
	t_vec3		tmp2;
	t_cyl		*cylind;
	int			retval;

	cylind = (t_cyl*)cyl;
	r.dir = vec3_norm(r.dir);
	cylind->axis = vec3_norm(vec3_sub(cylind->p2, cylind->p1));
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
	solve.b = 2 * (vec3_dp(d, x) - vec3_dp(d, v) * (vec3_dp(x, v) + 2 * p->k));
	solve.c = vec3_dp(x, x) - vec3_dp(x, v) * (vec3_dp(x, v) + 4 * p->k);
	solve.discr = solve.b * solve.b - 4 * solve.a * solve.c;
	return (solve_quadric(solve.discr, t, solve.b, solve.a));
}

void	z_obj_rot(int keycode, t_main *main)
{
	z_object_rotation1(keycode, main);
	z_object_rotation2(keycode, main);
	z_object_rotation3(keycode, main);
	z_object_rotation4(keycode, main);
	z_object_rotation5(keycode, main);
}
