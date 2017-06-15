//
// Created by Andrew Radiuk on 6/7/17.
//

#include "rt.h"

void	ipp_fill(t_main *main, int x, int y, int color)
{
	*((int *)(main->mlx.ipp + x * main->mlx.bpp / 8 +
			  y * main->mlx.size_line)) = color;
}

void	*render(void *data)
{
	t_thread	*th;
	t_vec3		p;
	int 		x;
	int 		y;
	double		dist;

	th = (t_thread *)data;
	dist = 1. / (2 * tan(FOV / 2.));
	y = th->start - 1;
	while (++y < th->end)
	{
		x = -1;
		while (++x < WIDTH)
		{
			p.x = (2 * (x + 0.5) / WIDTH - 1) * ASPECT * tan(FOV / 2);
			p.y = (1 - 2 * (y + 0.5) / HEIGHT) * tan(FOV / 2);
			p.z = th->main.cam.ray.pos.z - dist;
			th->main.cam.ray.dir = vec3_norm(vec3_sub(p, th->main.cam.ray.pos));
			ipp_fill(&th->main, x, y, vec3_to_int(cast_ray(&th->main, th->main.cam.ray, 0)));
		}
	}
	pthread_exit(NULL);
}