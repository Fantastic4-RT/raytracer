//
// Created by Andrew Radiuk on 6/7/17.
//

#include "rt.h"

int		cross_exit(void *a)
{
	if (a)
		exit(0);
	return (0);
}

void 	change_mode(int keycode, t_main *main)
{
	if (keycode == 31 &&  main->mode.obj_mode == 0) // it is obj mode
	{
		main->mode.obj_mode = 1;
		main->mode.cam_mode = 0;
		main->mode.off = 0;
		main->mode.obj_index = 0;
	}
	else if (keycode == 31 &&  main->mode.obj_mode == 1) // turns off obj mode
	{
		main->mode.obj_mode = 0;
		main->mode.off = 1;
	}
	else if (keycode == 8 && main->mode.cam_mode == 0) // it is camera mode
	{
		main->mode.obj_mode = 0;
		main->mode.cam_mode = 1;
		main->mode.off = 0;
	}
	else if (keycode == 8 && main->mode.cam_mode == 1) // turns off camera mode
	{
		main->mode.cam_mode = 0;
		main->mode.off = 1;
	}
//	printf("obj mode %d\n", main->mode.obj_mode);
}

int 	key_hook(int keycode, t_main *main)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 113)
		outputfile(main);
	change_mode(keycode, main);
	if (main->mode.obj_mode == 1)
	{
		//put img indicating the mode in menu
		if (keycode == 123 && main->mode.obj_index > 0)
			main->mode.obj_index--;
		else if (keycode == 124 && main->mode.obj_index < main->obj_i - 1)
			main->mode.obj_index++;
		mlx_clear_window(main->mlx.mlx, main->mlx.menu.menu_win);
		mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
								main->mlx.menu.main_menu, 0, 0);
		mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 100,  300,
					   0xff0000, main->obj[main->mode.obj_index].type);
		mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 200,  300,
					   0xff0000, ft_itoa(main->mode.obj_index));

	}
	return (0);
}