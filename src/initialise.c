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

void	malloc_data(t_obj *obj1, t_obj *obj2, char *str)
{
	*obj1 = *obj2;
	if (ft_strcmp(str, "sphere") == 0)
	{
		obj1->data = malloc(sizeof(t_sphere));
		*((t_sphere *)obj1->data) = *((t_sphere *)obj2->data);
	}
	if (ft_strcmp(str, "plane") == 0)
	{
		obj1->data = malloc(sizeof(t_plane));
		*((t_plane *)obj1->data) = *((t_plane *)obj2->data);
	}
	if (ft_strcmp(str, "cylinder") == 0)
	{
		obj1->data = malloc(sizeof(t_cyl));
		*((t_cyl *)obj1->data) = *((t_cyl *)obj2->data);
	}
	if (ft_strcmp(str, "cone") == 0)
	{
		obj1->data = malloc(sizeof(t_cone));
		*((t_cone *)obj1->data) = *((t_cone *)obj2->data);
	}
	if (ft_strcmp(str, "paraboloid") == 0)
	{
		obj1->data = malloc(sizeof(t_parab));
		*((t_parab *)obj1->data) = *((t_parab *)obj2->data);
	}
}

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
			malloc_data(&data[i].obj[j], &main->obj[j], main->obj[j].type);
//			data[i].obj[j].data = malloc(sizeof(t_sphere));
//			*((t_sphere *)data[i].obj[j].data) = *((t_sphere *)(main->obj[j].data));
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

void 	image(t_main *main)
{
	main->mlx.img = mlx_new_image(main->mlx.mlx, main->scene.wid, main->scene.hei);
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

//progress bar loading...........
int expose(t_main *main)
{
	if (main->mode.start == 1)
	{
		init_images(main);
#ifdef TEXT_MODE
		generate_textures(main);
#endif
		main->mode.start = 0;
		if (main->mode.loaded == 1)
			image(main);
	} //menu
	return (0);
}

void	mlx_initialise(t_main *main)
{
	void *start_page;

	main->mlx.mlx = mlx_init();
	main->mlx.menu.menu_win = mlx_new_window(main->mlx.mlx, 400, 400, "Menu"); //menu
	main->mlx.menu.main_menu = mlx_xpm_file_to_image(main->mlx.mlx, "menu.xpm",
									 &main->mlx.menu.w, &main->mlx.menu.h);
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
							main->mlx.menu.main_menu, 0, 0); //menu
	main->mlx.win = mlx_new_window(main->mlx.mlx, main->scene.wid, main->scene.hei, "Scene");
	start_page = mlx_xpm_file_to_image(main->mlx.mlx, "Loading.xpm",
									   &main->mlx.menu.w, &main->mlx.menu.h);
	if (main->mode.start == 1 && main->scene.wid >= 400 && main->scene.hei >= 400)
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.win, start_page,
					main->scene.wid / 2 - 200, main->scene.hei / 2 - 200);
	else
		mlx_string_put(main->mlx.mlx, main->mlx.win, 0, 0, 0x00FF00, "Loading");
	mlx_expose_hook(main->mlx.win, expose, main);
	mlx_hook(main->mlx.win, 2, 3, key_hook, main);
	mlx_hook(main->mlx.win, 17, 1L << 17, cross_exit, main);
	mlx_hook(main->mlx.menu.menu_win, 2, 3, key_hook, main); //menu
	mlx_hook(main->mlx.menu.menu_win, 17, 1L << 17, cross_exit, main); //menu
	mlx_loop(main->mlx.mlx);
}
