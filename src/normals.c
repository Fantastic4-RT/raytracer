/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 18:39:57 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 18:39:58 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	sphere_norm(void *data, t_vec3 hitpoint)
{
	t_sphere *s;

	s = (t_sphere *)data;
	return (vec3_norm(vec3_sub(hitpoint, s->pos)));
}

t_vec3	plane_norm(void *data, t_vec3 hitpoint)
{
	t_vec3	a;
	t_plane	*p;

	a = hitpoint;
	p = (t_plane *)data;
	return (vec3_norm(p->normal));
}

t_vec3	cone_norm(void *data, t_vec3 hitpoint)
{
	t_vec3	tmp;
	t_cone	*c;
	t_vec3	n;
	double	t;

	c = (t_cone*)data;
	tmp = vec3_sub(hitpoint, c->p1);
	t = vec3_length(tmp) / (vec3_dp(c->axis, vec3_norm(tmp)));
	n = vec3_norm(vec3_sub(hitpoint, vec3_add(c->p1, vec3_mult(c->axis, t))));
	return (n);
}

t_vec3	cylinder_norm(void *data, t_vec3 hitpoint)
{
	t_cyl	*c;
	double	t;

	c = (t_cyl *)data;
	t = vec3_dp(vec3_sub(hitpoint, c->p1), c->axis);
	return (vec3_norm(vec3_sub(hitpoint,
						vec3_add(c->p1, vec3_mult(c->axis, t)))));
}

t_vec3	parab_norm(void *data, t_vec3 hitpoint)
{
	t_parab	*p;
	t_vec3	x;
	t_vec3	n;
	double	m;

	p = (t_parab *)data;
	x = vec3_sub(hitpoint, p->pos);
	m = vec3_dp(x, p->axis);
	n = vec3_sub(x, vec3_mult(p->axis, m + p->k));
	return (vec3_norm(n));
}

t_vec3 torus_norm(void * data, t_vec3 hitpoint)
{
	t_torus *tor = (t_torus *)data;
//	t_vec3 normal;
//
//	normal.x = 4. * hitpoint.x * (sqrt(hitpoint.x) + sqrt(hitpoint.y)
//								  + sqrt(hitpoint.z) - sqrt(tor->r_mjr) - sqrt(tor->r_min));
//	normal.y = 4. * hitpoint.x * (sqrt(hitpoint.x) + sqrt(hitpoint.y)
//								  + sqrt(hitpoint.z) - sqrt(tor->r_mjr) - sqrt(tor->r_min));
//	normal.z = 4. * hitpoint.x * (sqrt(hitpoint.x) + sqrt(hitpoint.y)
//								  + sqrt(hitpoint.z) - sqrt(tor->r_mjr) - sqrt(tor->r_min) + (8 * sqrt(tor->r_min) * hitpoint.z));
	printf("%f %f %f\n", hitpoint.x, hitpoint.y, hitpoint.z);
	t_vec3 a = vec3_sub(hitpoint, tor->pos);
	double y = vec3_dp(a, tor->axis);
	t_vec3 b = vec3_mult(tor->axis, y);
	t_vec3 d = vec3_sub(a, b);
	double c = vec3_dp(d, d);
	double m = 1. / sqrt(c);
	t_vec3 k = vec3_mult(d, m);
	t_vec3 x = vec3_mult(k, tor->r_mjr);
	return (vec3_norm(vec3_sub(a, x)));
//	return (vec3_norm(normal));
}

//t_vec3 torus_norm(void * data, t_vec3 hitpoint)
//{
//	t_torus *tor = (t_torus *) data;
//
//	t_vec3 a = vec3_sub(hitpoint, tor->pos);
//	double y = vec3_dp(a, tor->axis);
//	t_vec3 b = vec3_mult(tor->axis, y);
//	t_vec3 d = vec3_sub(a, b);
//	double c = vec3_dp(d, d);
//	double x = sqrt(c);
//	double dx = 2 * (x - tor->r_mjr);
//	double dy = 2 * y;
//	t_vec3 v1 = vec3_mult(d, ((1 / x) * (dx / 2)));
//	t_vec3 v2 = vec3_mult(a , dy / 2);
//	t_vec3 z = vec3_sub(v1, v2);
//	return (vec3_norm(z));
//}

//t_vec3 torus_norm(void * data, t_vec3 hitpoint)
//{
//	t_torus *tor = (t_torus *)data;
//
//	double k = vec3_dp(vec3_sub(hitpoint, tor->pos), tor->axis);
//	t_vec3 a = vec3_sub(hitpoint, vec3_mult(tor->axis, k));
//	double m = sqrt(pow(tor->r_min, 2) - pow(k, 2));
//	return (vec3_norm(vec3_sub(vec3_sub(hitpoint, a), (vec3_mult(vec3_sub(tor->pos, a), (m / (tor->r_mjr + m)))))));
//}

