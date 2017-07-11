/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 18:28:08 by aradiuk           #+#    #+#             */
/*   Updated: 2017/07/10 19:33:07 by alohashc         ###   ########.fr       */
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
	if (th->main.scene.m_b == 1)
		col = ft_mb(th);
	else
		col = cast_ray(th, &th->main, th->main.cam.ray, 0);
	if (th->main.scene.sepia == 1 || th->main.scene.grey == 1)
		col = ft_sepia_grey(th, col);
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

t_vec3	m_apply(t_matrix matrix, t_vec3 vec)
{
	t_vec3	result;

	result.x = matrix.m[0][0] * vec.x + matrix.m[0][1] * vec.y +
			matrix.m[0][2] * vec.z + matrix.m[0][3];
	result.y = matrix.m[1][0] * vec.x + matrix.m[1][1] * vec.y +
			matrix.m[1][2] * vec.z + matrix.m[1][3];
	result.z = matrix.m[2][0] * vec.x + matrix.m[2][1] * vec.y +
			matrix.m[2][2] * vec.z + matrix.m[2][3];
	return (result);
}

void	matrices(t_main *main)
{
	main->mxs.rot_x_cam = x_rot(main->mxs.cam_angle.x);
	main->mxs.rot_y_cam = y_rot(main->mxs.cam_angle.y);
	main->mxs.rot_z_cam = z_rot(main->mxs.cam_angle.z);
	main->mxs.rot_x_dir = x_rot(main->mxs.dir_angle.x);
	main->mxs.rot_y_dir = y_rot(main->mxs.dir_angle.y);
	main->mxs.rot_z_dir = z_rot(main->mxs.dir_angle.z);
	main->mxs.rot_cam = m_mult(m_mult(main->mxs.rot_x_cam, main->mxs.rot_y_cam),
							main->mxs.rot_z_cam);
	main->mxs.rot_dir = m_mult(m_mult(main->mxs.rot_x_dir, main->mxs.rot_y_dir),
							main->mxs.rot_z_dir);
}
