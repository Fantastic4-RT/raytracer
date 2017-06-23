#include <rt.h>


void init_images(t_main *main)
{
	int w;
	int h;
	main->mlx.menu.main_menu = mlx_xpm_file_to_image(main->mlx.mlx, "menu.xpm", &w, &h);
//	main->mlx.menu.data1 = mlx_get_data_addr(main->mlx.menu.main_menu,
//	&main->mlx.menu.bpp1, &main->mlx.menu.size_line1, &main->mlx.menu.endian1);
	main->mode.off = 1;
	main->mode.cam_mode = 0;
	main->mode.dir_mode = 0;
	main->mode.rot_cam_mode = 0;
	main->mode.cam_pos_mode = 0;
	main->mode.obj_mode = 0;
	main->mode.obj_index = 0;
	main->mode.color_mode = 0;
	main->mode.channel = 0;
	main->mode.move_mode = 0;
	main->mode.rot_obj_mode = 0;
	main->mode.text_mode = 0;
	main->mode.text_index = 0;
}

//void switch_cam_mode(int keycode, t_main *main)
//{
	//put img indicating the mode in menu

	//cam_rotation (R - QAWSED)

	// cam_direction (D - QAWSED)

	// cam_position (M - QAWSED)
//}