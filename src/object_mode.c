#include "rt.h"

void	color_mode(int keycode, t_main *main)
{
	//changing color (F14 123 +-)
	if (keycode == 107
		&& main->mode.color_mode == 0
		&& main->mode.move_mode == 0
		&& main->mode.rot_obj_mode == 0
		&& main->mode.text_mode == 0) // C on
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 200, 135);
		main->mode.color_mode = 1;
	}
	else if (keycode == 107 && main->mode.color_mode == 1) // C off
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
#ifdef TEXT_MODE
void 	texture_mode(int keycode, t_main *main)
{
	//change texture
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
		change_texture(keycode, main);
	}
}
#endif

void 	move_mode(int keycode, t_main *main)
{
	// move obj (M QAWSED)
	if (keycode == 46
		&& main->mode.move_mode == 0
		&& main->mode.rot_obj_mode == 0
		&& main->mode.text_mode == 0
		&& main->mode.color_mode == 0) // M on
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 70, 135);
		main->mode.move_mode = 1;
	}
	else if (keycode == 46 && main->mode.move_mode == 1) // M off
		main->mode.move_mode = 0;
	if (((keycode >= 12 && keycode <=14) || (keycode>=0 && keycode <=2)) &&
		main->mode.color_mode == 0 && main->mode.move_mode == 1)
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 70, 135);
		move_objects(keycode, main);
	}
}

void 	rotation_mode(int keycode, t_main *main)
{
	// rotate obj (R QAWSED)
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
		&& ((keycode >= 12 && keycode <=14) || (keycode>=0 && keycode <=2)))
	{
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.vert_arr, 70, 225);
		rotate_objects(keycode, main);
	}
}

void switch_obj_mode(int keycode, t_main *main)
{
	//put img indicating the mode in menu
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
							main->mlx.menu.side_arr, 20, 100);
	//selecting object (arrows)
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
	mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 264,  100,
				   0xff0000, main->obj[main->mode.obj_index].type);
	mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 350,  100,
				   0xff0000, ft_itoa(main->mode.obj_index));
	color_mode(keycode, main);
	move_mode(keycode, main);
#ifdef TEXT_MODE
	texture_mode(keycode, main);
#endif
	rotation_mode(keycode, main);
}
