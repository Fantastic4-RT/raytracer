#include <rt.h>


void init_images(t_main *main)
{
	int w;
	int h;
	main->mlx.menu.main_menu = mlx_xpm_file_to_image(main->mlx.mlx, "menu.xpm", &w, &h);
	main->mlx.menu.data1 = mlx_get_data_addr(main->mlx.menu.main_menu,
	&main->mlx.menu.bpp1, &main->mlx.menu.size_line1, &main->mlx.menu.endian1);

	main->mode.off = 1;
	main->mode.cam_mode = 0;
	main->mode.obj_mode = 0;
	main->mode.obj_index = 0;
}