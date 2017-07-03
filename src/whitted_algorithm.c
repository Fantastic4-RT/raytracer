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

t_vec3 reflection_and_refraction(t_vec3 hitcolor, t_ray *ray, t_main *main, int depth, t_thread *th)
{
	t_ray reflectray;
	t_ray refractray;
	t_vec3 reflectcol;
	t_vec3 refractcol;
	double amount;

	reflectray.dir = vec3_norm(reflect_ray(ray->dir, th->obj[main->curr].n));
	reflectray.pos = (vec3_dp(reflectray.dir, th->obj[main->curr].n) < 0) ?
		vec3_add(th->obj[main->curr].hitpoint,
		vec3_mult(th->obj[main->curr].n, 0.0001)) :
		vec3_sub(th->obj[main->curr].hitpoint,
		vec3_mult(th->obj[main->curr].n, 0.0001));
	refractray.dir = vec3_norm(refract_ray(ray->dir, th->obj[main->curr].n,
										   th->obj[main->curr].mat.refract));
	refractray.pos = (vec3_dp(refractray.dir, th->obj[main->curr].n) < 0) ?
		vec3_add(th->obj[main->curr].hitpoint,
		vec3_mult(th->obj[main->curr].n, 0.0001)) :
		vec3_sub(th->obj[main->curr].hitpoint,
		vec3_mult(th->obj[main->curr].n, 0.0001));
//	fresnel(ray->dir, th->obj[main->curr].n, th->obj[main->curr].mat.refract, &amount);
	amount = 1 - th->obj[main->curr].mat.transp;
	reflectcol = cast_ray(th, main, reflectray, ++depth);
	refractcol = cast_ray(th, main, refractray, ++depth);
	hitcolor = vec3_add(vec3_mult(reflectcol, amount), vec3_mult(refractcol, 1 - amount));
	return (hitcolor);
}

t_vec3 reflection(t_vec3 hitcolor, t_ray ray, t_main *main, int depth, t_thread *th)
{
	double	amount;
	t_ray	reflectray;
	t_vec3	prev_col;

	prev_col = main->diff_col;
	fresnel(ray.dir, th->obj[main->curr].n, th->obj[main->curr].mat.refract, &amount);
	reflectray.dir = vec3_norm(reflect_ray(vec3_norm(ray.dir), vec3_norm(th->obj[main->curr].n)));
	reflectray.pos = (vec3_dp(reflectray.dir, th->obj[main->curr].n) > 0) ?
					 vec3_add(th->obj[main->curr].hitpoint, vec3_mult(th->obj[main->curr].n, 0.0001)) :
					 vec3_sub(th->obj[main->curr].hitpoint, vec3_mult(th->obj[main->curr].n, 0.0001));
	hitcolor = vec3_mult(cast_ray(th, main, reflectray, depth + 1),  amount);
	if (vec3_eq(hitcolor, vec3_create(0, 0, 0)) == 1)
		hitcolor = prev_col;
	else
		hitcolor = vec3_add(vec3_mult(prev_col, 0.5),
							vec3_mult(vec3_mult(cast_ray(th, main, reflectray,
							depth + 1),  amount), 0.5));
	return (hitcolor);
}

t_vec3 diffuse(t_vec3 hitcolor, t_ray *ray, t_main *main, t_thread *th)
{
	t_ray lightray;
	t_vec3 lightamt = vec3_create(0, 0, 0);
	t_vec3 specularcol = vec3_create(0, 0, 0);
	double	tmp;
	double	amount;
	int i;

	fresnel(ray->dir, th->obj[main->curr].n, th->obj[main->curr].mat.refract, &amount);
	lightray.pos = (vec3_dp(ray->dir, th->obj[main->curr].n) < 0) ?
					vec3_add(th->obj[main->curr].hitpoint, vec3_mult(th->obj[main->curr].n, 0.00001)) :
					vec3_sub(th->obj[main->curr].hitpoint, vec3_mult(th->obj[main->curr].n, 0.00001));
	i = -1;
	ssize_t curr;
	while (++i < main->scene.lights)
	{
		curr = -1;
		lightray.dir = vec3_sub(th->light[i].ray.pos, th->obj[main->curr].hitpoint);
		double t = sqrt(vec3_dp(lightray.dir, lightray.dir)); //square of the distance to the light
		lightray.dir = vec3_norm(lightray.dir);
		double dp = fmax(0., vec3_dp(lightray.dir, th->obj[main->curr].n));
		int in_shadow = trace(lightray, &t, &curr, th);
		lightamt.x += (1 - in_shadow * (th->obj[curr].mattype == 1 ? th->obj[curr].mat.transp : 1)) * th->light[i].color.x * dp;
		lightamt.y += (1 - in_shadow * (th->obj[curr].mattype == 1 ? th->obj[curr].mat.transp : 1)) * th->light[i].color.y * dp;
		lightamt.z += (1 - in_shadow * (th->obj[curr].mattype == 1 ? th->obj[curr].mat.transp : 1)) * th->light[i].color.z * dp;
		t_vec3 reflectray_dir = reflect_ray(vec3_invert(lightray.dir), th->obj[main->curr].n);
		tmp = pow(fmax(0., -vec3_dp(reflectray_dir, ray->dir)), th->obj[main->curr].mat.spec);
		specularcol.x += tmp * th->light[i].color.x;
		specularcol.y += tmp * th->light[i].color.y;
		specularcol.z += tmp * th->light[i].color.z;
	}
	hitcolor.x += lightamt.x * th->obj[main->curr].mat.color.x * th->obj[main->curr].mat.diff + specularcol.x * SPECULAR;
	hitcolor.y += lightamt.y * th->obj[main->curr].mat.color.y * th->obj[main->curr].mat.diff + specularcol.y * SPECULAR;
	hitcolor.z += lightamt.z * th->obj[main->curr].mat.color.z * th->obj[main->curr].mat.diff + specularcol.z * SPECULAR;
	return (hitcolor);
}

int trace(t_ray ray, double *t, ssize_t *curr, t_thread *th)
{
	int i;

	i = -1;
	while (++i < th->main.scene.objs)
	{
		if (th->obj[i].intersect(ray, th->obj[i].data, t)) //intersection functions
			*curr = i;
	}
	return (*curr == -1 ? 0 : 1);
}

t_vec3 cast_ray(t_thread *th, t_main *main, t_ray ray, int depth)
{
	t_vec3    hitcolor;
	double t;

	if (depth > MAXDEPTH)
		return (vec3_create(0., 0., 0.)); // returns background color
	hitcolor = vec3_create(0., 0., 0.);
	t = 2000000.0;
	main->curr = -1;
	if (trace(ray, &t, &main->curr, th))
	{
		th->obj[main->curr].hitpoint = vec3_add(ray.pos, vec3_mult(ray.dir, t));
		th->obj[main->curr].n = vec3_norm(th->obj[main->curr].normal(
				th->obj[main->curr].data, th->obj[main->curr].hitpoint));
		main->diff_col = diffuse(vec3_mult(vec3_create(
				th->obj[main->curr].mat.color.x, th->obj[main->curr].mat.color.y,
				th->obj[main->curr].mat.color.z), th->main.scene.amb), &ray, main, th);

		if (main->obj[main->curr].texture != 0 )
			find_pixel_color(th, main);

		if (th->obj[main->curr].mattype == REFLECT_REFRACT) //transparent
			hitcolor = reflection_and_refraction(hitcolor, &ray, main, depth, th);
		else if (th->obj[main->curr].mattype == REFLECT) //mirror-like
			hitcolor = reflection(hitcolor, ray, main, depth, th);
		else
		{
			hitcolor = vec3_mult(vec3_create(th->obj[main->curr].mat.color.x,
			th->obj[main->curr].mat.color.y, th->obj[main->curr].mat.color.z),
															th->main.scene.amb);
			hitcolor = diffuse(hitcolor, &ray, main, th);
		}
	}
	return(hitcolor);
}
