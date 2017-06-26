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

void	camera_rotation(t_main *main, int param)
{
	if (param == 0)
	{
		main->mxs.cam_angle = vec3_create(0, 0, 0);
		main->mxs.dir_angle = vec3_create(0, 0, 0);
	}
	if (param == 1 || param == -1)
		main->mxs.cam_angle.x += param * ROT_ANGLE;
	if (param == 2 || param == -2)
		main->mxs.cam_angle.y += param / 2. * ROT_ANGLE;
	if (param == 3 || param == -3)
		main->mxs.cam_angle.z += param / 3. * ROT_ANGLE;
	if (param == 4 || param == -4)
		main->mxs.dir_angle.x += param / 4. * ROT_ANGLE;
	if (param == 5 || param == -5)
		main->mxs.dir_angle.y += param / 5. * ROT_ANGLE;
	if (param == 6 || param == -6)
		main->mxs.dir_angle.z += param / 6. * ROT_ANGLE;
	image(main);
}

int 	key_hook_cam(int keycode, t_main *main)
{
	if (keycode == 83)
		camera_rotation(main, -1);
	if (keycode == 85)
		camera_rotation(main, 1);
	if (keycode == 86)
		camera_rotation(main, -2);
	if (keycode == 88)
		camera_rotation(main, 2);
	if (keycode == 89)
		camera_rotation(main, 3);
	if (keycode == 92)
		camera_rotation(main, -3);
	if (keycode == 1)
		camera_rotation(main, -4);
	if (keycode == 13)
		camera_rotation(main, 4);
	if (keycode == 0)
		camera_rotation(main, -5);
	if (keycode == 2)
		camera_rotation(main, 5);
	keycode == 12 ? camera_rotation(main, 6) : 0;
	keycode == 14 ? camera_rotation(main, -6) : 0;
	keycode == 87 ? camera_rotation(main, 0) : 0;
	keycode == 53 ? exit(0) : 0;
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