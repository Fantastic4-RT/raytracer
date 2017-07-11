/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 18:39:57 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/10 16:34:56 by vhorbach         ###   ########.fr       */
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
