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
}

int 	key_hook(int keycode, t_main *main)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 113)
		outputfile(main);
	change_mode(keycode, main);
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
							main->mlx.menu.main_menu, 0, 0);
	if (main->mode.obj_mode == 1 && main->mode.off == 0)
		switch_obj_mode(keycode, main); // O
//	else if (main->mode.cam_mode == 1 && main->mode.off == 0)
//		switch_cam_mode(keycode, main); // C
	return (0);
}