/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 18:28:08 by aradiuk           #+#    #+#             */
/*   Updated: 2017/07/03 18:28:10 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_thread(t_thread *data)
{
	int i;

	i = -1;
	while (++i < data->main.scene.objs)
		free(data->obj[i].data);
	free(data->light);
	free(data->obj);
}

void	one_ray(t_thread *th, double dist, int x, int y)
{
	t_vec3		p;
	t_vec3		col;

	p.x = (2 * (x + 0.5) / th->main.scene.wid - 1) * ASPECT * tan(FOV / 2);
	p.y = (1 - 2 * (y + 0.5) / th->main.scene.hei) * tan(FOV / 2);
	p.z = th->main.cam.start.z - dist;
	th->main.cam.ray.dir = vec3_norm(vec3_sub(p, th->main.cam.start));
	th->main.cam.ray.dir = m_apply(th->main.mxs.rot_cam, th->main.cam.ray.dir);
	th->main.cam.ray.dir = m_apply(th->main.mxs.rot_dir, th->main.cam.ray.dir);
	col = cast_ray(th, &th->main, th->main.cam.ray, 0);
	*((int *)(th->main.mlx.ipp + x * th->main.mlx.bpp / 8 +
			y * th->main.mlx.size_line)) = vec3_to_int(col);
}

void	*render(void *data)
{
	t_thread	*th;
	int			x;
	int			y;
	double		dist;

	th = (t_thread *)data;
	dist = 1. / (2 * tan(FOV / 2.));
	y = th->start - 1;
	while (++y < th->end)
	{
		x = -1;
		while (++x < th->main.scene.wid)
		{
			if (th->main.scene.a_a == 1 || th->main.scene.a_a == 2)
				ft_aa(th, dist, x, y);
			else
				one_ray(th, dist, x, y);
		}
	}
	free_thread((t_thread *)data);
	pthread_exit(data);
}
