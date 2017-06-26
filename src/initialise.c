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

#include "rt.h"

void	pthreading(t_main *main)
{
	pthread_t	threads[THREADS];
	t_thread	data[THREADS];
	int 		i;
	int			j;
	int			line_per_th;

	i = -1;
	line_per_th = main->scene.hei / THREADS + 1;
	while (++i < THREADS)
	{
		data[i].obj = (t_obj *)malloc(sizeof(t_obj) * main->scene.objs);
		data[i].light = (t_light *)malloc(sizeof(t_light) * main->scene.lights);
		j = -1;
		while (++j < main->scene.objs)
			data[i].obj[j] = main->obj[j];
		j = -1;
		while (++j < main->scene.lights)
			data[i].light[j] = main->light[j];
		data[i].main = *main;
		data[i].start = i * line_per_th;
		data[i].end = (i + 1) * line_per_th;
		data[i].end = data[i].end > main->scene.hei ? main->scene.hei : data[i].end;
		pthread_create(&threads[i], NULL, render, &data[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
}

void outputfile(t_main *main)
{
	FILE *fp;
	int i;
	int j;
	int	index;
	static unsigned char color[3];

	fp  = fopen("out5.ppm", "wb");
	fprintf(fp, "P6\n%d %d\n255\n", main->scene.wid, main->scene.hei);
	i = -1;
	while (++i < main->scene.hei)
	{
		j = -1;
		while (++j < main->scene.wid)
		{
			index = j * main->mlx.bpp / 8 + i * main->mlx.size_line;
			color[2] = main->mlx.ipp[index];
			color[1] = main->mlx.ipp[index + 1];
			color[0] = main->mlx.ipp[index + 2];
			fwrite(color, 1, 3, fp);
		}
	}
	fclose(fp);
}

void 	image(t_main *main)
{
	main->mlx.img = mlx_new_image(main->mlx.mlx, main->scene.wid, main->scene.hei);
	main->mlx.ipp = mlx_get_data_addr(main->mlx.img, &main->mlx.bpp,
									  &main->mlx.size_line, &main->mlx.endian);
	pthreading(main);
//	outputfile(main);

	mlx_put_image_to_window(main->mlx.mlx, main->mlx.win, main->mlx.img, 0, 0);
	mlx_destroy_image(main->mlx.mlx, main->mlx.img);
}

void	mlx_initialise(t_main *main)
{
	main->mlx.mlx = mlx_init();
	main->mlx.win = mlx_new_window(main->mlx.mlx, main->scene.wid, main->scene.hei, "Scene");
	main->mlx.menu.menu_win = mlx_new_window(main->mlx.mlx, 400, 400, "Menu"); //menu
	init_images(main); //menu
	image(main);
	mlx_hook(main->mlx.win, 2, 3, key_hook, main);
	mlx_hook(main->mlx.win, 17, 1L << 17, cross_exit, main);
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
							main->mlx.menu.main_menu, 0, 0); //menu
	mlx_hook(main->mlx.menu.menu_win, 2, 3, key_hook, main); //menu
	mlx_hook(main->mlx.menu.menu_win, 17, 1L << 17, cross_exit, main); //menu
	mlx_loop(main->mlx.mlx);
}
