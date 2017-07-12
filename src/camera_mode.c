/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 19:01:39 by atrepyto          #+#    #+#             */
/*   Updated: 2017/06/30 19:01:42 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	camera_rotation(int keycode, t_main *main)
{
	if (keycode == 15 && main->mode.rot_cam_mode == 0
		&& main->mode.dir_mode == 0 && main->mode.cam_pos_mode == 0)
	{
		main->mode.rot_cam_mode = 1;
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 2, 373);
	}
	else if (keycode == 15 && main->mode.rot_cam_mode == 1)
		main->mode.rot_cam_mode = 0;
	if (main->mode.rot_cam_mode == 1 && ((keycode >= 12 && keycode <= 14)
		|| (keycode >= 0 && keycode <= 2)))
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 2, 373);
		if (keycode == 12 || keycode == 0)
			main->mxs.cam_angle.x += keycode == 12 ? ROT_ANGLE : -ROT_ANGLE;
		else if (keycode == 13 || keycode == 1)
			main->mxs.cam_angle.y += keycode == 13 ? ROT_ANGLE : -ROT_ANGLE;
		else if (keycode == 14 || keycode == 2)
			main->mxs.cam_angle.z += keycode == 14 ? ROT_ANGLE : -ROT_ANGLE;
		image(main);
	}
}

void	camera_direction(int keycode, t_main *main)
{
	if (keycode == 17 && main->mode.rot_cam_mode == 0
		&& main->mode.dir_mode == 0 && main->mode.cam_pos_mode == 0)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 2, 353);
		main->mode.dir_mode = 1;
	}
	else if (keycode == 17 && main->mode.dir_mode == 1)
		main->mode.dir_mode = 0;
	if (main->mode.dir_mode == 1 &&
		((keycode >= 12 && keycode <= 14) || (keycode >= 0 && keycode <= 2)))
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 2, 353);
		if (keycode == 12 || keycode == 0)
			main->mxs.dir_angle.x += keycode == 12 ? ROT_ANGLE : -ROT_ANGLE;
		else if (keycode == 13 || keycode == 1)
			main->mxs.dir_angle.y += keycode == 13 ? ROT_ANGLE : -ROT_ANGLE;
		else if (keycode == 14 || keycode == 2)
			main->mxs.dir_angle.z += keycode == 14 ? ROT_ANGLE : -ROT_ANGLE;
		image(main);
	}
}

void	camera_position(int keycode, t_main *main)
{
	if (keycode == 46 && main->mode.rot_cam_mode == 0
		&& main->mode.dir_mode == 0 && main->mode.cam_pos_mode == 0)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 2, 335);
		main->mode.cam_pos_mode = 1;
	}
	else if (keycode == 46 && main->mode.cam_pos_mode == 1)
		main->mode.cam_pos_mode = 0;
	if (main->mode.cam_pos_mode == 1 && ((keycode >= 12 && keycode <= 14)
				|| (keycode >= 0 && keycode <= 2)))
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 2, 335);
		if (keycode == 12 || keycode == 0)
			main->cam.start.x += keycode == 12 ? 1 / (double)main->scene.wid :
				-1 / (double)main->scene.wid;
		else if (keycode == 13 || keycode == 1)
			main->cam.start.y += keycode == 13 ? 1 / (double)main->scene.hei :
				-1 / (double)main->scene.wid;
		else if (keycode == 14 || keycode == 2)
			main->cam.start.z += keycode == 14 ? 1 : -1;
		image(main);
	}
}

void	switch_cam_mode(int keycode, t_main *main)
{
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
							main->mlx.menu.side_arr, 90, 300);
	camera_rotation(keycode, main);
	camera_direction(keycode, main);
	camera_position(keycode, main);
}

void	last_check(char *str, t_main *main)
{
	if (ft_strstr(str, "/scene") == 0)
		error(12);
	main->obj_i == main->scene.objs ? 0 : error(2);
	main->light_i == main->scene.lights ? 0 : error(3);
}