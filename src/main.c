/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 13:33:58 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/07 13:33:59 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		expose(t_main *main)
{
	if (main->mode.start == 1)
	{
		init_images(main);
		generate_textures(main);
		main->mode.start = 0;
		if (main->mode.loaded == 1)
			image(main);
	}
	return (0);
}

void	check_obj_type(char *t)
{
	(int)t == 6 ? error(8) : 0;
	ft_strchr(t, '\"') == 0 ? error(9) : 0;
}

void	error(int param)
{
	param == 0 ? ft_putstr("Wrong number of arguments.\n") : 0;
	param == 1 ? ft_putstr("Wrong file.\n") : 0;
	param == 2 ? ft_putstr("Wrong number of objects.\n") : 0;
	param == 3 ? ft_putstr("Wrong number of lights.\n") : 0;
	param == 4 ? ft_putstr("Scene has no objects.\n") : 0;
	param == 5 ? ft_putstr("Scene has no lights.\n") : 0;
	param == 6 ? ft_putstr("More objects than declared.\n") : 0;
	param == 7 ? ft_putstr("More lights than declared.\n") : 0;
	param == 8 ? ft_putstr("Wrong object tag.\n") : 0;
	param == 9 ? ft_putstr("Wrong object type.\n") : 0;
	param == 10 ? ft_putstr("Wrong coords/axis.\n") : 0;
	exit(0);
}

void	default_values(t_main *main)
{
	main->light = (t_light *)malloc(sizeof(t_light) * main->scene.lights);
	main->obj = (t_obj *)malloc(sizeof(t_obj) * main->scene.objs);
	main->obj_i = 0;
	main->light_i = 0;
	main->flag.cam = 0;
	main->flag.lgh = 0;
	main->flag.obj = 0;
	main->cam.ray.pos = vec3_create(0, 0, 50);
	main->mxs.cam_angle = vec3_create(0, 0, 0);
	main->mxs.dir_angle = vec3_create(0, 0, 0);
	matrices(main);
	main->cam.fov = 45;
	main->cam.start = main->cam.ray.pos;
	main->cam.ray.pos = m_apply(main->mxs.rot_cam, main->cam.ray.pos);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_main	main;

	if (argc != 2)
		error(0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error(1);
	main.uv = 0;
	main.pic = 0;
	main.mode.start = 1;
	main.mode.loaded = 0;
	read_file(fd, &main);
	mlx_initialise(&main);
	return (0);
}
