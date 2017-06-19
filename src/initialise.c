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

#include <memory.h>
#include "rt.h"

void	pthreading(t_main *main)
{
	pthread_t	threads[THREADS];
	t_thread	data[THREADS];
	int 		i;
	int			j;
	int			line_per_th;

	i = -1;
	line_per_th = HEIGHT / THREADS + 1;
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
		data[i].end = data[i].end > HEIGHT ? HEIGHT : data[i].end;
		pthread_create(&threads[i], NULL, render, &data[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
}


void	mlx_initialise(t_main *main, double a)
{
	clock_t begin1 = clock();
	main->mlx.mlx = mlx_init();
	main->mlx.win = mlx_new_window(main->mlx.mlx, WIDTH, HEIGHT, "Scene");
	main->mlx.img = mlx_new_image(main->mlx.mlx, WIDTH, HEIGHT);
	main->mlx.ipp = mlx_get_data_addr(main->mlx.img, &main->mlx.bpp,
									  &main->mlx.size_line, &main->mlx.endian);
	pthreading(main);
	outputfile(main);
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.win, main->mlx.img, 0, 0);
	mlx_destroy_image(main->mlx.mlx, main->mlx.img);
	mlx_hook(main->mlx.win, 2, 3, key_hook, main);
	mlx_hook(main->mlx.win, 17, 1L << 17, cross_exit, main);
	clock_t end1 = clock();
	double b = (double)(end1 - begin1) / CLOCKS_PER_SEC;
	printf("rendering: %f\n", b);
	printf("read vs render: %f\n", a / b * 100);
	mlx_loop(main->mlx.mlx);
}
