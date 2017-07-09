/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 16:49:51 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 16:49:53 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	color_mode(int keycode, t_main *main)
{
	if (keycode == 107
		&& main->mode.color_mode == 0
		&& main->mode.move_mode == 0
		&& main->mode.rot_obj_mode == 0
		&& main->mode.text_mode == 0)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 200, 135);
		main->mode.color_mode = 1;
	}
	else if (keycode == 107 && main->mode.color_mode == 1)
	{
		main->mode.color_mode = 0;
		main->mode.channel = 0;
	}
	if (main->mode.color_mode == 1)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 200, 135);
		change_color(keycode, main);
	}
}

void	texture_mode(int keycode, t_main *main)
{
	if (keycode == 105
		&& main->mode.text_mode == 0
		&& main->mode.color_mode == 0
		&& main->mode.move_mode == 0
		&& main->mode.rot_obj_mode == 0)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 325, 135);
		main->mode.text_mode = 1;
	}
	else if (keycode == 105 && main->mode.text_mode == 1)
		main->mode.text_mode = 0;
	if (main->mode.text_mode == 1)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 325, 135);
		if (keycode >= 83 && keycode <= 91)
			change_texture(keycode, main);
		else if ((keycode >= 18 && keycode <= 23) || keycode == 92)
			image_texture(keycode, main);
	}
}

void	move_mode(int keycode, t_main *main)
{
	if (keycode == 46
		&& main->mode.move_mode == 0
		&& main->mode.rot_obj_mode == 0
		&& main->mode.text_mode == 0
		&& main->mode.color_mode == 0)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 70, 135);
		main->mode.move_mode = 1;
	}
	else if (keycode == 46 && main->mode.move_mode == 1)
		main->mode.move_mode = 0;
	if (((keycode >= 12 && keycode <= 14) || (keycode >= 0 && keycode <= 2)) &&
		main->mode.color_mode == 0 && main->mode.move_mode == 1)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 70, 135);
		move_objects(keycode, main);
	}
}

void	rotation_mode(int keycode, t_main *main)
{
	if (keycode == 15
		&& main->mode.rot_obj_mode == 0
		&& main->mode.move_mode == 0
		&& main->mode.text_mode == 0
		&& main->mode.color_mode == 0)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 70, 225);
		main->mode.rot_obj_mode = 1;
	}
	else if (keycode == 15 && main->mode.rot_obj_mode == 1)
		main->mode.rot_obj_mode = 0;
	if (main->mode.rot_obj_mode == 1
		&& ((keycode >= 12 && keycode <= 14) || (keycode >= 0 && keycode <= 2)))
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 70, 225);
		rotate_objects(keycode, main);
	}
}

void	switch_obj_mode(int keycode, t_main *main)
{
	char *str;

	mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
							main->mlx.menu.side_arr, 20, 100);
	if (main->mode.color_mode == 0
		&& main->mode.move_mode == 0
		&& main->mode.rot_obj_mode == 0
		&& main->mode.text_mode == 0)
	{
		if (keycode == 123 && main->mode.obj_index > 0)
			main->mode.obj_index--;
		else if (keycode == 124 && main->mode.obj_index < main->obj_i - 1)
			main->mode.obj_index++;
	}
	mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 264, 100,
				0xff0000, main->obj[main->mode.obj_index].type);
	str = ft_itoa(main->mode.obj_index);
	mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 350, 100,
				0xff0000, str);
	ft_strdel(&str);
	color_mode(keycode, main);
	move_mode(keycode, main);
	texture_mode(keycode, main);
	rotation_mode(keycode, main);
}
