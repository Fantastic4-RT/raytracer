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

void	ml_d(t_obj *obj1, t_obj *obj2, char *str)
{
	*obj1 = *obj2;
	if (ft_strcmp(str, "sphere") == 0 &&
										(obj1->data = malloc(sizeof(t_sphere))))
		*((t_sphere *)obj1->data) = *((t_sphere *)(obj2->data));
	if (ft_strcmp(str, "plane") == 0 && (obj1->data = malloc(sizeof(t_plane))))
		*((t_plane *)obj1->data) = *((t_plane *)obj2->data);
	if (ft_strcmp(str, "cylinder") == 0 && (obj1->data = malloc(sizeof(t_cyl))))
		*((t_cyl *)obj1->data) = *((t_cyl *)obj2->data);
	if (ft_strcmp(str, "cone") == 0 && (obj1->data = malloc(sizeof(t_cone))))
		*((t_cone *)obj1->data) = *((t_cone *)obj2->data);
	if (ft_strcmp(str, "paraboloid") == 0 &&
										(obj1->data = malloc(sizeof(t_parab))))
		*((t_parab *)obj1->data) = *((t_parab *)obj2->data);
	if (ft_strcmp(str, "torus") == 0 && (obj1->data = malloc(sizeof(t_torus))))
		*((t_torus *)obj1->data) = *((t_torus *)obj2->data);
}

void	pthreading(t_main *main)
{
	pthread_t	threads[THREADS];
	t_thread	data[THREADS];
	int			i[3];

	i[0] = -1;
	i[2] = main->scene.hei / THREADS + 1;
	while (++i[0] < THREADS)
	{
		data[i[0]].obj = (t_obj *)malloc(sizeof(t_obj) * main->scene.objs);
		data[i[0]].light = (t_light *)malloc(sizeof(t_light) *
															main->scene.lights);
		i[1] = -1;
		while (++i[1] < main->scene.objs)
			ml_d(&data[i[0]].obj[i[1]], &main->obj[i[1]], main->obj[i[1]].type);
		i[1] = -1;
		while (++i[1] < main->scene.lights)
			data[i[0]].light[i[1]] = main->light[i[1]];
		data[i[0]].main = *main;
		data[i[0]].start = i[0] * i[2];
		data[i[0]].end = (int)fmin((i[0] + 1) * i[2], main->scene.hei);
		pthread_create(&threads[i[0]], NULL, render, &data[i[0]]);
	}
	i[0] = -1;
	while (++i[0] < THREADS)
		pthread_join(threads[i[0]], NULL);
}

void	outputfile(t_main *main)
{
	FILE					*fp;
	int						i[3];
	static unsigned char	color[3];

	main->pic += 1;
	main->filename = ft_strdup("outXX.ppm");
	main->filename[3] = (char)(main->pic / 10 + 48);
	main->filename[4] = (char)(main->pic % 10 + 48);
	fp = fopen(main->filename, "wb");
	fprintf(fp, "P6\n%d %d\n255\n", main->scene.wid, main->scene.hei);
	i[0] = -1;
	while (++i[0] < main->scene.hei)
	{
		i[1] = -1;
		while (++i[1] < main->scene.wid)
		{
			i[2] = i[1] * main->mlx.bpp / 8 + i[0] * main->mlx.size_line;
			color[2] = main->mlx.ipp[i[2]];
			color[1] = main->mlx.ipp[i[2] + 1];
			color[0] = main->mlx.ipp[i[2] + 2];
			fwrite(color, 1, 3, fp);
		}
	}
	fclose(fp);
	ft_strdel(&main->filename);
}

void	image(t_main *main)
{
	main->mlx.img = mlx_new_image(main->mlx.mlx, main->scene.wid,
															main->scene.hei);
	main->mlx.ipp = mlx_get_data_addr(main->mlx.img, &main->mlx.bpp,
									&main->mlx.size_line, &main->mlx.endian);
	main->cam.ray.pos = main->cam.start;
	matrices(main);
	main->cam.ray.pos = m_apply(main->mxs.rot_cam, main->cam.ray.pos);
	pthreading(main);
	mlx_clear_window(main->mlx.mlx, main->mlx.win);
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.win, main->mlx.img, 0, 0);
	mlx_destroy_image(main->mlx.mlx, main->mlx.img);
}

void	mlx_initialise(t_main *main)
{
	void	*start_page;

	main->mlx.mlx = mlx_init();
	main->mlx.menu.menu_win = mlx_new_window(main->mlx.mlx, 400, 400, "Menu");
	main->mlx.menu.main_menu = mlx_xpm_file_to_image(main->mlx.mlx, "menu.xpm",
									&main->mlx.menu.w, &main->mlx.menu.h);
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
							main->mlx.menu.main_menu, 0, 0);
	main->mlx.win = mlx_new_window(main->mlx.mlx, main->scene.wid,
								main->scene.hei, "Scene");
	start_page = mlx_xpm_file_to_image(main->mlx.mlx, "Loading.xpm",
									&main->mlx.menu.w, &main->mlx.menu.h);
	if (main->mode.start == 1 && main->scene.wid >= 400 &&
			main->scene.hei >= 400)
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.win, start_page,
					main->scene.wid / 2 - 200, main->scene.hei / 2 - 200);
	else
		mlx_string_put(main->mlx.mlx, main->mlx.win, 0, 0, 0x00FF00, "Loading");
	mlx_expose_hook(main->mlx.win, expose, main);
	mlx_hook(main->mlx.win, 2, 3, key_hook, main);
	mlx_hook(main->mlx.win, 17, 1L << 17, cross_exit, main);
	mlx_hook(main->mlx.menu.menu_win, 2, 3, key_hook, main);
	mlx_hook(main->mlx.menu.menu_win, 17, 1L << 17, cross_exit, main);
	mlx_loop(main->mlx.mlx);
}
