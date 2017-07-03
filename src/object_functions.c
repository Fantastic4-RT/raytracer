/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 15:55:34 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 15:55:36 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_objects(int keycode, t_main *main)
{
	if (keycode == 12 || keycode == 0)
	{
		x_object_rotation1(keycode, main);
		x_object_rotation2(keycode, main);
		x_object_rotation3(keycode, main);
		image(main);
	}
	else if (keycode == 13 || keycode == 1)
	{
		y_object_rotation1(keycode, main);
		y_object_rotation2(keycode, main);
		y_object_rotation3(keycode, main);
		image(main);
	}
	else if (keycode == 14 || keycode == 2)
	{
		z_object_rotation1(keycode, main);
		z_object_rotation2(keycode, main);
		z_object_rotation3(keycode, main);
		image(main);
	}
}

void	change_texture(int keycode, t_main *main)
{
	if (keycode >= 83 && keycode <= 91
		&& main->obj[main->mode.obj_index].texture == 0)
		main->obj[main->mode.obj_index].tmp_color =
				main->obj[main->mode.obj_index].mat.color;
	if (keycode == 83)
		main->obj[main->mode.obj_index].texture = 1;
	else if (keycode == 84)
		main->obj[main->mode.obj_index].texture = 2;
	else if (keycode == 85)
		main->obj[main->mode.obj_index].texture = 3;
	else if (keycode == 86)
		main->obj[main->mode.obj_index].texture = 4;
	else if (keycode == 87)
		main->obj[main->mode.obj_index].texture = 5;
	else if (keycode == 88)
		main->obj[main->mode.obj_index].texture = 6;
	else if (keycode == 89)
		main->obj[main->mode.obj_index].texture = 7;
	else if (keycode == 91)
		main->obj[main->mode.obj_index].texture = 8;
	else if (keycode == 92)
	{
		main->obj[main->mode.obj_index].texture = 0;
		main->obj[main->mode.obj_index].mat.color =
				main->obj[main->mode.obj_index].tmp_color;
	}
	image(main);
}

int		channels_change(int keycode, t_main *main)
{
	if (keycode == 83)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 150, 180);
		main->mode.channel = 'r';
	}
	else if (keycode == 84)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 150, 193);
		main->mode.channel = 'g';
	}
	else if (keycode == 85)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.side_arr, 150, 206);
		main->mode.channel = 'b';
	}
	main->mode.count = vec3_create(0., 0., 0.);
	return (1);
}

void	change_color(int keycode, t_main *main)
{
	if (channels_change(keycode, main) && (keycode == 69 || keycode == 78))
	{
		if (main->mode.channel == 'r')
			main->mode.count = vec3_create(0.01, 0., 0.);
		else if (main->mode.channel == 'g')
			main->mode.count = vec3_create(0., 0.01, 0.);
		else if (main->mode.channel == 'b')
			main->mode.count = vec3_create(0., 0., 0.01);
		main->obj[main->mode.obj_index].mat.color = keycode == 69 ?
		vec3_add(main->obj[main->mode.obj_index].mat.color, main->mode.count) :
		vec3_sub(main->obj[main->mode.obj_index].mat.color, main->mode.count);
		if (main->obj[main->mode.obj_index].mat.color.x > 255)
			main->obj[main->mode.obj_index].mat.color.x = 0;
		else if (main->obj[main->mode.obj_index].mat.color.x < 0)
			main->obj[main->mode.obj_index].mat.color.x = 255;
		if (main->obj[main->mode.obj_index].mat.color.y > 255)
			main->obj[main->mode.obj_index].mat.color.y = 0;
		else if (main->obj[main->mode.obj_index].mat.color.y < 0)
			main->obj[main->mode.obj_index].mat.color.y = 255;
		if (main->obj[main->mode.obj_index].mat.color.z > 255)
			main->obj[main->mode.obj_index].mat.color.z = 0;
		else if (main->obj[main->mode.obj_index].mat.color.z < 0)
			main->obj[main->mode.obj_index].mat.color.z = 255;
		image(main);
	}
}

void	move_objects(int keycode, t_main *main)
{
	if (keycode == 12 || keycode == 0)
	{
		x_object_translation1(keycode, main);
		x_object_translation2(keycode, main);
		x_object_translation3(keycode, main);
		image(main);
	}
	else if (keycode == 13 || keycode == 1)
	{
		y_object_translation1(keycode, main);
		y_object_translation2(keycode, main);
		y_object_translation3(keycode, main);
		image(main);
	}
	else if (keycode == 14 || keycode == 2)
	{
		z_object_translation1(keycode, main);
		z_object_translation2(keycode, main);
		z_object_translation3(keycode, main);
		image(main);
	}
}
