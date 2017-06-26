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
		main->mode.move_mode = 0;
		main->mode.rot_obj_mode = 0; //(to implement)
		main->mode.text_mode = 0; // to implement
		main->mode.color_mode = 0;
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
		main->mode.dir_mode = 0;
		main->mode.rot_cam_mode = 0;
		main->mode.cam_pos_mode = 0;
	}
}

void print_status(t_main *main)
{
	printf("----------------------------------------------------\n");
	printf("Object mode %d\n"
				   "-Move mode %d\n"
				   "-Object index %d\n"
				   "-Object rotation mode %d\n"
				   "-Texture mode %d\n"
				   "-Texture index %d\n"
				   "-Color mode %d\n"
				   "-Channel %c\n"
			"Camera mode %d\n"
					"-Direction mode %d\n"
				   "-Camera rotation mode %d\n"
				   "Camera position mode %d\n"
				   "Anti-aliasing %d\n",
		   main->mode.obj_mode, main->mode.move_mode,
	main->mode.obj_index, main->mode.rot_obj_mode,
		   main->mode.text_mode, main->mode.text_index,
		   main->mode.color_mode, main->mode.channel,
		   main->mode.cam_mode, main->mode.dir_mode,
		   main->mode.rot_cam_mode, main->mode.cam_pos_mode,
		   main->scene.a_a);
	printf("*******************************************************\n");
}

int 	key_hook(int keycode, t_main *main)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 113)
		outputfile(main);
	else if (keycode == 37 && main->scene.a_a == 0) // L = anti-aliasing mode
	{
		main->scene.a_a= 1;
		image(main);
	}
	else if (keycode == 37 && main->scene.a_a == 1) // L = anti-aliasing mode
	{
		main->scene.a_a= 2;
		image(main);
	}
	else if (keycode == 37 && main->scene.a_a == 2) // L = anti-aliasing mode
	{
		main->scene.a_a= 0;
		image(main);
	}
	change_mode(keycode, main);
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.menu.menu_win,
							main->mlx.menu.main_menu, 0, 0);
	if (main->mode.obj_mode == 1 && main->mode.off == 0)
		switch_obj_mode(keycode, main); // O
//	else if (main->mode.cam_mode == 1 && main->mode.off == 0)
//		switch_cam_mode(keycode, main); // C
	print_status(main);
	return (0);
}