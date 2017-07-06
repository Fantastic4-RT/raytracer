/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 18:41:15 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 18:41:16 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	sphere_norm_cut(void *data, t_vec3 hitpoint)
{
	t_sphere *s;

	s = (t_sphere *)data;
	if (s->hit_obj == 0)
		return (vec3_norm(vec3_sub(hitpoint, s->pos)));
	else
		return (vec3_norm(vec3_sub(s->p1, s->pos)));
}

t_vec3	cone_norm_cut(void *data, t_vec3 hitpoint)
{
	t_cone	*c;
	t_vec3	n;
	double	t;

	c = (t_cone *)data;
	if (c->cone_hit == 1)
	{
		t = vec3_length(vec3_sub(hitpoint, c->apex)) /
			(vec3_dp(c->axis, vec3_norm(vec3_sub(hitpoint, c->apex))));
		n = vec3_norm(vec3_sub(hitpoint,
							vec3_add(c->apex, vec3_mult(c->axis, t))));
		return (n);
	}
	else if (c->cone_hit == 3)
		return (vec3_norm(c->axis));
	else
		return (vec3_norm(vec3_invert(c->axis)));
}

t_vec3	cylinder_norm_cut(void *data, t_vec3 hitpoint)
{
	t_cyl *c;

	c = (t_cyl *)data;
	if (c->t_final != c->t_top_cap && c->t_final != c->t_low_cap)
		return (cylinder_norm(data, hitpoint));
	else if (c->t_low_cap == c->t_final)
		return (vec3_norm(vec3_invert(c->axis)));
	else
		return (vec3_norm(c->axis));
}
