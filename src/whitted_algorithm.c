/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitted_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:58:55 by atrepyto          #+#    #+#             */
/*   Updated: 2017/06/14 14:58:59 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	reflect_and_refract(t_vec3 hitcol, t_ray *ray, int depth, t_thread *th)
{
	t_ray	reflectray;
	t_ray	refractray;
	t_vec3	reflectcol;
	t_vec3	refractcol;
	double	amount;

	reflectray.dir = vec3_norm(reflect_ray(ray->dir, th->obj[th->main.curr].n));
	reflectray.pos = (vec3_dp(reflectray.dir, th->obj[th->main.curr].n) > 0) ?
		vec3_add(th->obj[th->main.curr].hitpoint,
		vec3_mult(th->obj[th->main.curr].n, 0.0001)) :
		vec3_sub(th->obj[th->main.curr].hitpoint,
		vec3_mult(th->obj[th->main.curr].n, 0.0001));
	refractray.dir = vec3_norm(refract_ray(ray->dir, th->obj[th->main.curr].n,
										th->obj[th->main.curr].mat.refract));
	refractray.pos = (vec3_dp(refractray.dir, th->obj[th->main.curr].n) > 0) ?
		vec3_add(th->obj[th->main.curr].hitpoint,
		vec3_mult(th->obj[th->main.curr].n, 0.0001)) :
		vec3_sub(th->obj[th->main.curr].hitpoint,
		vec3_mult(th->obj[th->main.curr].n, 0.0001));
	amount = 1 - th->obj[th->main.curr].mat.transp;
	reflectcol = cast_ray(th, &th->main, reflectray, ++depth);
	refractcol = cast_ray(th, &th->main, refractray, ++depth);
	hitcol = vec3_add(vec3_mult(reflectcol, amount), vec3_mult(refractcol,
																1 - amount));
	return (hitcol);
}

t_vec3	reflection(t_vec3 hitcol, t_ray ray, int depth, t_thread *th)
{
	double	amount;
	t_ray	reflectray;
	t_vec3	prev_col;
	t_obj	*obj;

	obj = &th->obj[th->main.curr];
	prev_col = th->main.diff_col;
	fresnel(ray.dir, obj->n, obj->mat.refract, &amount);
	reflectray.dir = vec3_norm(reflect_ray(vec3_norm(ray.dir),
															vec3_norm(obj->n)));
	reflectray.pos = (vec3_dp(reflectray.dir, obj->n) > 0) ?
					vec3_add(obj->hitpoint, vec3_mult(obj->n, 0.0001)) :
					vec3_sub(obj->hitpoint, vec3_mult(obj->n, 0.0001));
	hitcol = vec3_mult(cast_ray(th, &th->main, reflectray, depth + 1), amount);
	if (vec3_eq(hitcol, vec3_create(0, 0, 0)) == 1)
		hitcol = prev_col;
	else
		hitcol = vec3_add(vec3_mult(prev_col, 0.5),
						vec3_mult(vec3_mult(cast_ray(th, &th->main, reflectray,
													depth + 1), amount), 0.5));
	return (hitcol);
}

void	phong_col(t_ray *lray, t_vec3 df_sp[], t_thread *th, t_ray *ray)
{
	ssize_t cur[2];
	int		i;
	double	t[2];
	t_light	l;

	i = -1;
	while (++i < th->main.scene.lights)
	{
		cur[0] = -1;
		l = th->light[i];
		if (!vec3_eq(l.ray.dir, vec3_zero()) && !l.rad)
			l.ray.pos = vec3_add(th->obj[th->main.curr].hitpoint, l.ray.dir);
		lray->dir = vec3_sub(l.ray.pos, th->obj[th->main.curr].hitpoint);
		t[0] = vec3_length(lray->dir);
		t[1] = l.rad ? vec3_length(vec3_sub(l.ray.dir, lray->dir)) : 0;
		lray->dir = vec3_norm(lray->dir);
		cur[1] = trace(*lray, &t[0], &cur[0], th) || t[1] > l.rad;
		df_sp[0] = vec3_add(df_sp[0], vec3_mult(l.color, (1 - cur[1] *
			(th->obj[cur[0]].mattype == 1 ? (1 - th->obj[cur[0]].mat.transp) :
			1)) * fmax(0., vec3_dp(lray->dir, th->obj[th->main.curr].n))));
		df_sp[1] = vec3_add(df_sp[1], vec3_mult(l.color, (1 - cur[1])
				* pow(fmax(0., -vec3_dp(reflect_ray(vec3_invert(lray->dir),
				th->obj[th->main.curr].n), ray->dir)),
				th->obj[th->main.curr].mat.spec)));
	}
}

t_vec3	diffuse(t_vec3 hitcolor, t_ray *ray, t_main *main, t_thread *th)
{
	t_ray	lray;
	t_vec3	df_sp[4];

	df_sp[0] = vec3_zero();
	df_sp[1] = vec3_zero();
	lray.pos = (vec3_dp(ray->dir, th->obj[main->curr].n) < 0) ?
			vec3_add(th->obj[main->curr].hitpoint,
			vec3_mult(th->obj[main->curr].n, 0.00001)) :
			vec3_sub(th->obj[main->curr].hitpoint,
			vec3_mult(th->obj[main->curr].n, 0.00001));
	phong_col(&lray, df_sp, th, ray);
	df_sp[2] = vec3_add(hitcolor, vec3_mult(vec3_comp_dp(df_sp[0],
				th->obj[main->curr].mat.color), th->obj[main->curr].mat.diff));
	df_sp[3].x = fmax(vec3_dp(th->obj[main->curr].n, lray.dir), 0.0);
	if (main->toon == 1)
		toon_effect(df_sp, &hitcolor, main);
	else if (main->toon == 0)
		hitcolor = vec3_add(hitcolor, vec3_add(vec3_mult(vec3_comp_dp(df_sp[0],
				th->obj[main->curr].mat.color), th->obj[main->curr].mat.diff),
													vec3_mult(df_sp[1], SPEC)));
	return (hitcolor);
}

t_vec3	cast_ray(t_thread *th, t_main *main, t_ray ray, int depth)
{
	t_vec3	hitcol;
	t_obj	*obj;
	double	t;

	if (depth > MAXDEPTH)
		return (vec3_zero());
	hitcol = vec3_zero();
	t = 2000000.0;
	if (trace(ray, &t, &main->curr, th))
	{
		obj = &th->obj[main->curr];
		obj->hitpoint = vec3_add(ray.pos, vec3_mult(ray.dir, t));
		obj->n = vec3_norm(obj->normal(obj->data, obj->hitpoint));
		main->diff_col = diffuse(vec3_mult(obj->mat.color, th->main.scene.amb),
																&ray, main, th);
		obj->texture != 0 ? find_pixel_color(th, main) : 0;
		if (obj->mattype == REFLECT_REFRACT)
			hitcol = reflect_and_refract(hitcol, &ray, depth, th);
		else if (obj->mattype == REFLECT)
			hitcol = reflection(hitcol, ray, depth, th);
		else
			hitcol = diffuse(vec3_mult(obj->mat.color, th->main.scene.amb),
							&ray, main, th);
	}
	return (hitcol);
}
