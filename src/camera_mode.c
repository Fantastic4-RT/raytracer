//
// Created by Anastasiia Trepyton on 6/22/17.
//
#include "rt.h"

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

void 	key_hook_cam(int keycode, t_main *main)
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



//void switch_cam_mode(int keycode, t_main *main)
//{
////put img indicating the mode in menu
//
////cam_rotation (R - QAWSED)
//	if(keycode == 15)
//		main->mode.rot_cam_mode = 1;
//// cam_direction (T - QAWSED)
//	else if (keycode == T)
//		main->mode.dir_mode = 1;
//// cam_position (M - QAWSED)
//	else if (keycode == 43)
//		main->mode.cam_pos_mode = 1;
//
//}
