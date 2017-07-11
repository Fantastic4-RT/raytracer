/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 17:31:35 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 17:31:41 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		cross_exit(void *a)
{
	if (a)
		exit(0);
	return (0);
}

void	cam_hook(t_main *main)
{
	if (main->mode.cam_mode == 0)
	{
		main->mode.obj_mode = 0;
		main->mode.cam_mode = 1;
		main->mode.off = 0;
	}
	else if (main->mode.cam_mode == 1)
	{
		main->mode.cam_mode = 0;
		main->mode.off = 1;
		main->mode.dir_mode = 0;
		main->mode.rot_cam_mode = 0;
		main->mode.cam_pos_mode = 0;
	}
}

void	change_mode(int keycode, t_main *main)
{
	if (keycode == 31 && main->mode.obj_mode == 0)
	{
		main->mode.obj_mode = 1;
		main->mode.cam_mode = 0;
		main->mode.off = 0;
		main->mode.obj_index = 0;
	}
	else if (keycode == 31 && main->mode.obj_mode == 1)
	{
		main->mode.obj_mode = 0;
		main->mode.off = 1;
		main->mode.move_mode = 0;
		main->mode.rot_obj_mode = 0;
		main->mode.text_mode = 0;
		main->mode.color_mode = 0;
	}
	if (keycode == 8)
		cam_hook(main);
}

void	output(char *str, int nb)
{
	ft_putstr(str);
	ft_putnbr(nb);
	ft_putchar('\n');
}

int		key_hook(int keycode, t_main *main)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 113)
		outputfile(main);
	if (main->mode.loaded == 1)
	{
		alias_mode(keycode, main);
		change_mode(keycode, main);
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.main_menu, 0, 0);
		if (main->mode.obj_mode == 1 && main->mode.off == 0)
			switch_obj_mode(keycode, main);
		else if (main->mode.cam_mode == 1 && main->mode.off == 0)
			switch_cam_mode(keycode, main);
		print_status(main);
	}
	return (0);
}
