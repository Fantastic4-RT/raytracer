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

int vec3_to_int(t_vec3 hitcolor)
{
	int res;

	hitcolor = vec3_mult(hitcolor, 255);
	res = ((int)hitcolor.x << 16) + ((int)hitcolor.y << 8) + (int)hitcolor.z;
	return (res);
}

double clamp(const double low, const double high, const double value)
{
	return fmax(low, fmin(high, value));
}

/*
 * Compute reflection direction
 */
t_vec3 reflect_ray(const t_vec3 i, const t_vec3 n)
{
	return (vec3_sub(i, vec3_mult(n, 2 * (vec3_dp(i, n)))));
}

/*
 * Compute refraction direction
 */

t_vec3 refract_ray(const t_vec3 i, const t_vec3 n, const double irefract)
{
	double cosi = clamp(-1, 1, vec3_dp(i, n));
	double etai = 1;
	double etat = irefract;
	t_vec3 norm = n;

	if (cosi < 0)
		cosi = -cosi;
	else
	{
		ft_swap(&etai, &etat);
		norm = vec3_invert(n);
	}
	double eta = etai / etat;
	double k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? vec3_create(0, 0, 0) : vec3_add(vec3_mult(i, eta), vec3_mult(norm, (eta * cosi - sqrt(k)))));
}

/*
 * Compute Fresnel equation
 */

void	frensel(const t_vec3 i, const t_vec3 n, const double irefract, double *amount)
{
	double cosi = clamp(-1, 1, vec3_dp(i, n));
	double etai = 1;
	double etat = irefract;
	if (cosi > 0)
		ft_swap(&etai, &etat); //double

	double sint = etai / etat * sqrt(fmax(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		*amount = 1;
	else
	{
		double cost = sqrt(fmax(0.0, 1 - sint * sint));
		cosi = fabs(cosi);
		double rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		double rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*amount = (rs * rs + rp * rp) / 2;
	}
}
/*
 * compute color for different materials
 */
t_vec3 reflection_and_refraction(t_vec3 hitcolor, t_ray *ray, t_main *main, int depth)
{
	t_ray reflectray;
	reflectray.dir = vec3_norm(reflect_ray(ray->dir, main->obj[main->curr].n));
	reflectray.pos = (vec3_dp(reflectray.dir, main->obj[main->curr].n) < 0) ?
					 vec3_add(main->obj[main->curr].hitpoint, vec3_mult(main->obj[main->curr].n, 0.0001)) :
					 vec3_sub(main->obj[main->curr].hitpoint, vec3_mult(main->obj[main->curr].n, 0.0001));
	t_ray refractray;
	refractray.dir = vec3_norm(refract_ray(ray->dir, main->obj[main->curr].n,
										   main->obj[main->curr].mat.refract));
	refractray.pos = (vec3_dp(refractray.dir, main->obj[main->curr].n) < 0) ?
					 vec3_add(main->obj[main->curr].hitpoint, vec3_mult(main->obj[main->curr].n, 0.0001)) :
					 vec3_sub(main->obj[main->curr].hitpoint, vec3_mult(main->obj[main->curr].n, 0.0001));
	t_vec3 reflectcol = cast_ray(main, reflectray, ++depth);
	t_vec3 refractcol = cast_ray(main, refractray, ++depth);
	double amount;
	frensel(ray->dir, main->obj[main->curr].n,
			main->obj[main->curr].mat.refract, &amount);
	hitcolor = vec3_add(vec3_mult(reflectcol, amount), vec3_mult(refractcol, 1 - amount));
	return (hitcolor);
}

t_vec3 reflection(t_vec3 hitcolor, t_ray *ray, t_main *main, int depth)
{
	double amount;
	frensel(ray->dir, main->obj[main->curr].n,
			main->obj[main->curr].mat.refract, &amount);
	t_ray reflectray;

	reflectray.dir = vec3_norm(reflect_ray(ray->dir, main->obj[main->curr].n));
	reflectray.pos = (vec3_dp(reflectray.dir, main->obj[main->curr].n) < 0) ?
					 vec3_add(main->obj[main->curr].hitpoint, vec3_mult(main->obj[main->curr].n, 0.0001)) :
					 vec3_sub(main->obj[main->curr].hitpoint, vec3_mult(main->obj[main->curr].n, 0.0001));
	hitcolor = vec3_mult(cast_ray(main, reflectray, ++depth),  amount);
	return (hitcolor);
}

t_vec3 diffuse(t_vec3 hitcolor, t_ray *ray, t_main *main)
{
	t_ray lightray;
	t_vec3 lightamt = vec3_create(0, 0, 0);
	t_vec3 specularcol = vec3_create(0, 0, 0);
	double	tmp;
	lightray.pos = (vec3_dp(ray->dir, main->obj[main->curr].n) < 0) ?
						  vec3_add(main->obj[main->curr].hitpoint, vec3_mult(main->obj[main->curr].n, 0.0001)) :
						  vec3_sub(main->obj[main->curr].hitpoint, vec3_mult(main->obj[main->curr].n, 0.0001));
	int i;
	i = -1;
	ssize_t curr;
	while (++i < main->scene.lights)
	{
		curr = -1;
		lightray.dir = vec3_sub(main->light[i].ray.pos, main->obj[main->curr].hitpoint);
		double t = sqrt(vec3_dp(lightray.dir, lightray.dir)); //square of the distance to the light
		lightray.dir = vec3_norm(lightray.dir);
		double dp = fmax(0., vec3_dp(lightray.dir, main->obj[main->curr].n));
		int in_shadow = trace(main, lightray, &t, &curr);
		curr = curr == -1 ? 0 : curr;
		lightamt.x += (1 - in_shadow) * main->light[i].color.x * dp;
		lightamt.y += (1 - in_shadow) * main->light[i].color.y * dp;
		lightamt.z += (1 - in_shadow) * main->light[i].color.z * dp;
		t_vec3 reflectray_dir = reflect_ray(vec3_invert(lightray.dir), main->obj[main->curr].n);
		tmp = pow(fmax(0., -vec3_dp(reflectray_dir, ray->dir)), main->obj[curr].mat.spec);
		specularcol.x += tmp * main->light[i].color.x;
		specularcol.y += tmp * main->light[i].color.y;
		specularcol.z += tmp * main->light[i].color.z;
	}
	hitcolor.x += lightamt.x * main->obj[main->curr].mat.color.x * DIFFUSE + specularcol.x * SPECULAR;
	hitcolor.y += lightamt.y * main->obj[main->curr].mat.color.y * DIFFUSE + specularcol.y * SPECULAR;
	hitcolor.z += lightamt.z * main->obj[main->curr].mat.color.z * DIFFUSE + specularcol.z * SPECULAR;
	return (hitcolor);
}

/*
 * trace light
 * check intersection
 * Returns true if the ray intersects an object, false otherwise.
 */
int trace(t_main *main, t_ray ray, double *t, ssize_t *curr)
{
	int i;
	i = -1;
	while (++i < main->scene.objs)
	{
		if (main->obj[i].intersect(&ray, main->obj[i].data, t)) //intersection functions
			*curr = i;
	}
	return (*curr == -1 ? 0 : 1);
}
/*
 * Cast rays recursive algorithm
 */
t_vec3 cast_ray(t_main *main, t_ray ray, int depth)
{
	t_vec3 hitcolor;
	double t;
//	ssize_t curr;

	if (depth > MAXDEPTH)
		return (vec3_create(0, 0, 0)); // returns background color
	hitcolor = vec3_create(0, 0, 0);
	t = 2000000.0;
	main->curr = -1;
	if (trace(main, main->cam.ray, &t, &main->curr))
	{
		main->obj[main->curr].hitpoint = vec3_add(main->cam.ray.pos, vec3_mult(main->cam.ray.dir, t));
		main->obj[main->curr].n = vec3_norm(main->obj[main->curr].normal(main->obj[main->curr].data, main->obj[main->curr].hitpoint));
		/*
		 * three types of material
		 */
		if (main->obj[main->curr].mattype == REFLECT_REFRACT) //transparent
			hitcolor = reflection_and_refraction(hitcolor, &ray, main, depth);
		else if (main->obj[main->curr].mattype == REFLECT) //mirror-like
			hitcolor = reflection(hitcolor, &ray, main, depth);
		else //diffuse
		{
			hitcolor = vec3_create(AMBIENT * main->obj[main->curr].mat.color.x,
								   AMBIENT * main->obj[main->curr].mat.color.y,
								   AMBIENT * main->obj[main->curr].mat.color.z);
			hitcolor = diffuse(hitcolor, &ray, main);
		}
	}
	return(hitcolor);
}
