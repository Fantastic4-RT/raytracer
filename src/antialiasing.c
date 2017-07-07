/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alohashc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 11:46:52 by alohashc          #+#    #+#             */
/*   Updated: 2017/07/07 11:47:04 by alohashc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	ft_tracer_aa(t_thread *th, t_vec3 p)
{
	t_vec3		col;

	th->main.cam.ray.dir = vec3_norm(vec3_sub(p, th->main.cam.ray.pos));
	col = cast_ray(th, &th->main, th->main.cam.ray, 0);
	return (col);
}

t_vec3		ft_col_av(t_thread *th, t_vec3 *col)
{
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
	return (average);
}

t_vec3	ft_aa(t_thread *th, double dist, int x, int y)
{
	t_vec3	sub_ray;
	int		i;
	double	n_x;
	double	n_y;
	t_vec3	*col;
    t_vec3  color;

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
    color = ft_col_av(th, col);
    free(col);
    return (color);
}
