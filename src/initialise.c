/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:46:58 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/07 14:46:59 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

/*void	scene_initialise(t_main *main)
{
//	main->objs.num_plane = 2;
//	main->objs.num_sph = 2;
//	main->objs.num_cyl = 1;
//	main->objs.num_cone = 1;
	main->scene.lights = 2;
	main->light = (t_light *)malloc(sizeof(t_light) * main->scene.lights);
//	main->objs.plane = (t_plane *)malloc(sizeof(t_plane) * main->objs.num_plane);
//	main->objs.sph = (t_sphere *)malloc(sizeof(t_sphere) * main->objs.num_sph);
//	main->objs.cyl = (t_cyl *)malloc(sizeof(t_cyl) * main->objs.num_cyl);
//	main->objs.cone = (t_cone *)malloc(sizeof(t_cone) * main->objs.num_cone);
	main->cam.ray.pos = vec3_create(0, 0, 50);
	main->light[0].ray.pos = vec3_create(0, 10, 50);
	main->light[0].color = vec3_create(255, 255, 255);
	main->light[1].ray.pos = vec3_create(0, -10, 50);
	main->light[1].color = vec3_create(255, 255, 255);
}*/

void	pthreading(t_main *main)
{
	pthread_t	threads[THREADS];
	t_thread	data[THREADS];
	int 		i;
	int			line_per_th;

	i = 0;
	line_per_th = HEIGHT / THREADS + 1;
	while (i < THREADS)
	{
		data[i].main = *main;
		data[i].start = i * line_per_th;
		data[i].end = (i + 1) * line_per_th;
		data[i].end = data[i].end > HEIGHT ? HEIGHT : data[i].end;
		pthread_create(&threads[i], NULL, render, &data[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(threads[i++], NULL);
}

void	mlx_initialise(t_main *main)
{
	main->mlx.mlx = mlx_init();
	main->mlx.win = mlx_new_window(main->mlx.mlx, WIDTH, HEIGHT, "Scene");
	main->mlx.img = mlx_new_image(main->mlx.mlx, WIDTH, HEIGHT);
	main->mlx.ipp = mlx_get_data_addr(main->mlx.img, &main->mlx.bpp,
									  &main->mlx.size_line, &main->mlx.endian);
	pthreading(main);
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.win, main->mlx.img, 0, 0);
	mlx_destroy_image(main->mlx.mlx, main->mlx.img);
	mlx_hook(main->mlx.win, 2, 3, key_hook, main);
	mlx_hook(main->mlx.win, 17, 1L << 17, cross_exit, main);
	mlx_loop(main->mlx.mlx);
}
