#include <rt.h>

void alias_mode(int keycode, t_main *main)
{
	if (keycode == 37 && main->scene.a_a == 0) // L = anti-aliasing mode
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
}

void init_images(t_main *main)
{
	int w;
	int h;

#ifdef TEXT_MODE
	generate_textures(main);
#endif
	main->obj[0].tmp_color = vec3_create(0,0,0);
	main->mlx.menu.main_menu = mlx_xpm_file_to_image(main->mlx.mlx, "menu.xpm", &w, &h);
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
