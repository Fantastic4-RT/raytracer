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

void change_color(int keycode, t_main *main)
{
	t_vec3 count;

	if (keycode == 83) // change r channel
		main->mode.channel = 'r';
	else if (keycode == 84) // change g channel
		main->mode.channel = 'g';
	else if (keycode == 85) // change  channel
		main->mode.channel = 'b';
	if ((keycode == 69 || keycode == 78))
	{
		count = vec3_create(0., 0., 0.);
		if (main->mode.channel == 'r')
			count = vec3_create(0.1, 0., 0.);
		else if (main->mode.channel == 'g')
			count = vec3_create(0., 0.1, 0.);
		else if (main->mode.channel == 'b')
			count = vec3_create(0., 0., 0.1);
		main->obj[main->mode.obj_index].mat.color = keycode == 69 ?
				vec3_add(main->obj[main->mode.obj_index].mat.color, count) :
				vec3_sub(main->obj[main->mode.obj_index].mat.color, count);
		image(main);
	}
}

void move_objects(int keycode, t_main *main)
{
	if (keycode == 12 || keycode == 0) // x
	{
		if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
		{
			t_sphere *data = (t_sphere *) main->obj[main->mode.obj_index].data;
			data->pos = keycode == 12 ?
					vec3_add(data->pos, vec3_create(1, 0, 0)) :
					vec3_sub(data->pos, vec3_create(1, 0, 0));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
		{
			t_cone *data = (t_cone *) main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 12 ?
					   vec3_add(data->p1, vec3_create(1, 0, 0)) :
					   vec3_sub(data->p1, vec3_create(1, 0, 0));
			data->p2 = keycode == 12 ?
					   vec3_add(data->p2, vec3_create(1, 0, 0)) :
					   vec3_sub(data->p2, vec3_create(1, 0, 0));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
		{
			t_cyl *data = (t_cyl *) main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 12 ?
					   vec3_add(data->p1, vec3_create(1, 0, 0)) :
					   vec3_sub(data->p1, vec3_create(1, 0, 0));
			data->p2 = keycode == 12 ?
					   vec3_add(data->p2, vec3_create(1, 0, 0)) :
					   vec3_sub(data->p2, vec3_create(1, 0, 0));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
		{
			t_plane *data = (t_plane *) main->obj[main->mode.obj_index].data;
			data->pos = keycode == 12 ?
						vec3_add(data->pos, vec3_create(1, 0, 0)) :
						vec3_sub(data->pos, vec3_create(1, 0, 0));
		}
		image(main);
	}
	else if (keycode == 13 || keycode == 1) // y
	{
		if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
		{
			t_sphere *data = (t_sphere *) main->obj[main->mode.obj_index].data;
			data->pos = keycode == 13 ?
						vec3_add(data->pos, vec3_create(0, 1, 0)) :
						vec3_sub(data->pos, vec3_create(0, 1, 0));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
		{
			t_cone *data = (t_cone *) main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 13 ?
					vec3_add(data->p1, vec3_create(0, 1, 0)) :
					vec3_sub(data->p1, vec3_create(0, 1, 0));
			data->p2 = keycode == 13 ?
				   vec3_add(data->p2, vec3_create(0, 1, 0)) :
				   vec3_sub(data->p2, vec3_create(0, 1, 0));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
		{
			t_cyl *data = (t_cyl *) main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 13 ?
					   vec3_add(data->p1, vec3_create(0, 1, 0)) :
					   vec3_sub(data->p1, vec3_create(0, 1, 0));
			data->p2 = keycode == 13 ?
					   vec3_add(data->p2, vec3_create(0, 1, 0)) :
					   vec3_sub(data->p2, vec3_create(0, 1, 0));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
		{
			t_plane *data = (t_plane *) main->obj[main->mode.obj_index].data;
			data->pos = keycode == 13 ?
				   vec3_add(data->pos, vec3_create(0, 1, 0)) :
				   vec3_sub(data->pos, vec3_create(0, 1, 0));
		}
		image(main);
	}
	else if (keycode == 14 || keycode == 2) // z
	{
		if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
		{
			t_sphere *data = (t_sphere *) main->obj[main->mode.obj_index].data;
			data->pos = keycode == 14 ?
						vec3_add(data->pos, vec3_create(0, 0, 1)) :
						vec3_sub(data->pos, vec3_create(0, 0, 1));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
		{
			t_cone *data = (t_cone *) main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 14 ?
					   vec3_add(data->p1, vec3_create(0, 0, 1)) :
					   vec3_sub(data->p1, vec3_create(0, 0, 1));
			data->p2 = keycode == 14 ?
					   vec3_add(data->p2, vec3_create(0, 0, 1)) :
					   vec3_sub(data->p2, vec3_create(0, 0, 1));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
		{
			t_cyl *data = (t_cyl *) main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 14 ?
					   vec3_add(data->p1, vec3_create(0, 0, 1)) :
					   vec3_sub(data->p1, vec3_create(0, 0, 1));
			data->p2 = keycode == 14 ?
					   vec3_add(data->p2, vec3_create(0, 0, 1)) :
					   vec3_sub(data->p2, vec3_create(0, 0, 1));
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
		{
			t_plane *data = (t_plane *) main->obj[main->mode.obj_index].data;
			data->pos = keycode == 14 ?
						vec3_add(data->pos, vec3_create(0, 0, 1)) :
						vec3_sub(data->pos, vec3_create(0, 0, 1));
		}
		image(main);
	}
}

void rotate_objects(int keycode, t_main *main)
{

}

void switch_obj_mode(int keycode, t_main *main)
{
	//put img indicating the mode in menu
	//selecting object (arrows)
	if (keycode == 123 && main->mode.obj_index > 0)
		main->mode.obj_index--;
	else if (keycode == 124 && main->mode.obj_index < main->obj_i - 1)
		main->mode.obj_index++;
	mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 100,  300,
				   0xff0000, main->obj[main->mode.obj_index].type);
	mlx_string_put(main->mlx.mlx, main->mlx.menu.menu_win, 200,  300,
				   0xff0000, ft_itoa(main->mode.obj_index));
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
	//change texture
	if (keycode == 105
		&& main->mode.text_mode == 0
		&& main->mode.color_mode == 0
		&& main->mode.move_mode == 0
		&& main->mode.rot_obj_mode == 0)
		main->mode.text_mode = 1;
	else if (keycode == 105 && main->mode.text_mode == 1)
		main->mode.text_mode = 0;
//	if (main->mode.text_mode == 1)
//	{
//		change_texture(keycode, main); // IMPLEMENT
//	}
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

//void switch_cam_mode(int keycode, t_main *main)
//{
	//put img indicating the mode in menu

	//cam_rotation (R - QAWSED)

	// cam_direction (D - QAWSED)

	// cam_position (M - QAWSED)
//}