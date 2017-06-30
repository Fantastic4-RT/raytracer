#include "rt.h"

void	color_mode(int keycode, t_main *main)
{
	//changing color (F14 123 +-)
	if (keycode == 107
		&& main->mode.color_mode == 0
		&& main->mode.move_mode == 0
		&& main->mode.rot_obj_mode == 0
		&& main->mode.text_mode == 0) // C on
		main->mode.color_mode = 1;
	else if (keycode == 107 && main->mode.color_mode == 1) // C off
	{
		main->mode.color_mode = 0;
		main->mode.channel = 0;
	}
	if (main->mode.color_mode == 1)
		change_color(keycode, main);
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
		main->mode.text_mode = 1;
	else if (keycode == 105 && main->mode.text_mode == 1)
		main->mode.text_mode = 0;
//	printf("texture mode = %d\n", main->mode.text_mode);
	if (main->mode.text_mode == 1)
		change_texture(keycode, main); // IMPLEMENT
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
		main->mode.move_mode = 1;
	else if (keycode == 46 && main->mode.move_mode == 1) // M off
		main->mode.move_mode = 0;
	if (((keycode >= 12 && keycode <=14) || (keycode>=0 && keycode <=2)) &&
		main->mode.color_mode == 0 && main->mode.move_mode == 1)
		move_objects(keycode, main);
}

void 	rotation_mode(int keycode, t_main *main)
{
	// rotate obj (R QAWSED)
	if (keycode == 15
		&& main->mode.rot_obj_mode == 0
		&& main->mode.move_mode == 0
		&& main->mode.text_mode == 0
		&& main->mode.color_mode == 0)
		main->mode.rot_obj_mode = 1;
	else if (keycode == 15 && main->mode.rot_obj_mode == 1)
		main->mode.rot_obj_mode = 0;
	if (main->mode.rot_obj_mode == 1
		&& ((keycode >= 12 && keycode <=14) || (keycode>=0 && keycode <=2)))
		rotate_objects(keycode, main);
}

void switch_obj_mode(int keycode, t_main *main)
{
	//put img indicating the mode in menu
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
	mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 100,  300,
				   0xff0000, main->obj[main->mode.obj_index].type);
	mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 200,  300,
				   0xff0000, ft_itoa(main->mode.obj_index));
	color_mode(keycode, main);
	move_mode(keycode, main);
#ifdef TEXT_MODE
	texture_mode(keycode, main);
#endif
	rotation_mode(keycode, main);
}
