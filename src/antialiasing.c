/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alohashc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 11:46:52 by alohashc          #+#    #+#             */
/*   Updated: 2017/07/10 19:37:12 by alohashc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	vec3_comp_dp(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x * v2.x;
	res.y = v1.y * v2.y;
	res.z = v1.z * v2.z;
	return (res);
}

int		trace(t_ray ray, double *t, ssize_t *curr, t_thread *th)
{
	int i;

	i = -1;
	*curr = -1;
	ray.dir = vec3_norm(ray.dir);
	while (++i < th->main.scene.objs)
	{
		if (th->obj[i].intersect(ray, th->obj[i].data, t))
			*curr = i;
	}
	return (*curr == -1 ? 0 : 1);
}

t_vec3	ft_tracer_aa(t_thread *th, t_vec3 p)
{
	t_vec3		col;

	th->main.cam.ray.dir = vec3_norm(vec3_sub(p, th->main.cam.ray.pos));
	col = cast_ray(th, &th->main, th->main.cam.ray, 0);
	return (col);
}

int		ft_col_av(t_thread *th, t_vec3 *col)
{
	int		res;
	int		i;
	t_vec3	average;

	i = 0;
	average.x = 0;
	average.y = 0;
	average.z = 0;
	while (i < (th->main.scene.a_a == 1 ? 4 : 16))
	{
		average.x += pow(col[i].x, 2);
		average.y += pow(col[i].y, 2);
		average.z += pow(col[i].z, 2);
		i++;
	}
	average.x = sqrt(average.x / (th->main.scene.a_a == 1 ? 4 : 16));
	average.y = sqrt(average.y / (th->main.scene.a_a == 1 ? 4 : 16));
	average.z = sqrt(average.z / (th->main.scene.a_a == 1 ? 4 : 16));
	if (th->main.scene.m_b == 1)
		average = ft_mb(th);
	res = vec3_to_int(average);
	return (res);
}

void	ft_aa(t_thread *th, double dist, int x, int y)
{
	t_vec3	sub_ray;
	int		i;
	double	n_x;
	double	n_y;
	t_vec3	*col;

	i = 0;
	n_y = th->main.scene.a_a == 1 ? 0.25 : 0.2;
	col = (t_vec3*)malloc(sizeof(t_vec3) * (th->main.scene.a_a == 1 ? 4 : 16));
	while (n_y < 1)
	{
		n_x = th->main.scene.a_a == 1 ? 0.25 : 0.2;
		while (n_x < 1)
		{
			sub_ray.x = (2 * (x + n_x) / WIDTH - 1) * ASPECT * tan(FOV / 2);
			sub_ray.y = (1 - 2 * (y + n_y) / HEIGHT) * tan(FOV / 2);
			sub_ray.z = th->main.cam.ray.pos.z - dist;
			col[i++] = ft_tracer_aa(th, sub_ray);
			n_x += 1. / (th->main.scene.a_a == 1 ? 2. : 5.);
		}
		n_y += 1. / (th->main.scene.a_a == 1 ? 2. : 5.);
	}
	*((int *)(th->main.mlx.ipp + x * th->main.mlx.bpp / 8 +
				y * th->main.mlx.size_line)) = ft_col_av(th, col);
	free(col);
}
