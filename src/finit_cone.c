/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finit_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 17:08:04 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 17:08:06 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	ft_sepia_grey(t_thread *th, t_vec3 col)
{
	double grey;

	col = vec3_mult(col, 255);
	grey = col.x * 0.3 + col.y * 0.59 + col.z * 0.11;
	if (th->main.scene.sepia == 1)
	{
		col.x = grey > 206 ? 255 : grey + 49;
		col.y = grey < 14 ? 0 : grey - 14;
		col.z = grey < 56 ? 0 : grey - 56;
	}
	if (th->main.scene.grey == 1 && th->main.scene.sepia != 1)
	{
		col.x = grey;
		col.y = grey;
		col.z = grey;
	}
	col = vec3_mult(col, 1. / 255);
	return (col);
}

double	ft_check_min(double t1, double t2)
{
	double temp;

	temp = 0;
	if (t1 != 0 && t2 != 0)
		temp = fmin(t1, t2);
	else if (t1 != 0 || t2 != 0)
		temp = fmax(t1, t2);
	return (temp);
}

void	check_inters(t_ray r, t_cone *cone, double tt[], int tmp[])
{
	t_cone	cn;
	t_plane	plane;

	tt[0] = tt[3];
	tt[1] = tt[3];
	tt[2] = tt[3];
	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 0;
	cone->apex = vec3_add(cone->p1, vec3_mult(vec3_sub(cone->p2, cone->p1),
										(cone->r1 / (cone->r1 - cone->r2))));
	cone->axis = vec3_norm(vec3_sub(cone->p2, cone->p1));
	cone->angle = atan((cone->r1 - cone->r2) / vec3_length(vec3_sub(cone->p2,
													cone->p1))) * 180 / M_PI;
	cn.p1 = cone->apex;
	cn.axis = cone->axis;
	cn.angle = cone->angle;
	plane.pos = cone->p1;
	plane.normal = cone->axis;
	tmp[0] = intersect_cone(r, &cn, &tt[0]);
	tmp[1] = intersect_plane(r, &plane, &tt[1]);
	plane.pos = cone->p2;
	tmp[2] = intersect_plane(r, &plane, &tt[2]);
}

void	check_tt(double *t, double tt[], int tmp[])
{
	if (tmp[0] && tmp[1] && tmp[2])
		*t = ft_check_min(*t, ft_check_min(tt[0], ft_check_min(tt[1], tt[2])));
	else if (tmp[0] && tmp[1])
		*t = ft_check_min(*t, ft_check_min(tt[0], tt[1]));
	else if (tmp[0] && tmp[2])
		*t = ft_check_min(*t, ft_check_min(tt[0], tt[2]));
	else if (tmp[1] && tmp[2])
		*t = ft_check_min(*t, ft_check_min(tt[1], tt[2]));
	else if (tmp[0])
		*t = tt[0];
	else if (tmp[1])
		*t = tt[1];
	else if (tmp[2])
		*t = tt[2];
}

int		intersect_cone_cut(t_ray r, void *s, double *t)
{
	t_cone	*cone;
	t_vec3	hp[3];
	int		tmp[3];
	double	tt[4];

	tt[3] = *t;
	cone = (t_cone *)s;
	check_inters(r, cone, tt, tmp);
	if (!tmp[0])
		return (0);
	hp[0] = vec3_add(r.pos, vec3_mult(r.dir, tt[0]));
	hp[1] = vec3_sub(vec3_add(r.pos, vec3_mult(r.dir, tt[1])), cone->p1);
	hp[2] = vec3_sub(vec3_add(r.pos, vec3_mult(r.dir, tt[2])), cone->p2);
	if (vec3_dp(cone->axis, vec3_sub(hp[0], cone->p1)) < 0 ||
							vec3_dp(cone->axis, vec3_sub(hp[0], cone->p2)) > 0)
		tmp[0] = 0;
	tmp[1] = vec3_dp(hp[1], hp[1]) > cone->r1 * cone->r1 ? 0 : tmp[1];
	tmp[2] = vec3_dp(hp[2], hp[2]) > cone->r2 * cone->r2 ? 0 : tmp[2];
	if (!tmp[0] && !tmp[1] && !tmp[2])
		return (0);
	check_tt(t, tt, tmp);
	cone->cone_hit = *t == tt[0] ? 1 : 0;
	if (*t != tt[0])
		cone->cone_hit = *t == tt[1] ? 2 : 3;
	return (tmp[0] || tmp[1] || tmp[2]);
}
