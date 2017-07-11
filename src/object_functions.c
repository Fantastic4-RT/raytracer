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
		x_object_rotation4(keycode, main);
		image(main);
	}
	else if (keycode == 13 || keycode == 1)
	{
		y_object_rotation1(keycode, main);
		y_object_rotation2(keycode, main);
		y_object_rotation3(keycode, main);
		y_object_rotation4(keycode, main);
		y_object_rotation5(keycode, main);
		image(main);
	}
	else if (keycode == 14 || keycode == 2)
	{
		z_obj_rot(keycode, main);
		image(main);
	}
}

void	image_texture(int keycode, t_main *main)
{
	if (keycode >= 18 && keycode <= 23
		&& main->obj[main->mode.obj_index].texture == 0)
		main->obj[main->mode.obj_index].tmp_color =
				main->obj[main->mode.obj_index].mat.color;
	if (keycode == 18)
		main->obj[main->mode.obj_index].texture = 9;
	else if (keycode == 19)
		main->obj[main->mode.obj_index].texture = 10;
	else if (keycode == 20)
		main->obj[main->mode.obj_index].texture = 11;
	else if (keycode == 21)
		main->obj[main->mode.obj_index].texture = 12;
	else if (keycode == 23)
		main->obj[main->mode.obj_index].texture = 13;
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
		x_object_translation4(keycode, main);
		image(main);
	}
	else if (keycode == 13 || keycode == 1)
	{
		y_object_translation1(keycode, main);
		y_object_translation2(keycode, main);
		y_object_translation3(keycode, main);
		y_object_translation4(keycode, main);
		image(main);
	}
	else if (keycode == 14 || keycode == 2)
	{
		z_object_translation1(keycode, main);
		z_object_translation2(keycode, main);
		z_object_translation3(keycode, main);
		z_object_translation4(keycode, main);
		image(main);
	}
}
