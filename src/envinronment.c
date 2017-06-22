#include <rt.h>


void 	find_pixel_color(t_main *main)
{
	t_vec3 p;
	double value;

	p.x = fabs(main->obj[main->curr].hitpoint.x);
	p.y = fabs(main->obj[main->curr].hitpoint.y);
	p.z = fabs(main->obj[main->curr].hitpoint.z);
	if (main->mode.text_index - 1 >= 0 && main->mode.text_index <= 3)
	{
		int color = (int)main->textures[main->mode.text_index - 1].text_arr[(int)p.z][(int)p.y][(int)p.x];
		main->obj[main->curr].mat.color = vec3_create((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
	}
//	else if (main->mode.text_index - 1 == 4)
//	{
//		// just perlin noise ????
//	}
	else if (main->mode.text_index - 1 == 5)
	{
		int color = (int)main->textures[5].text_arr[(int)(p.x * 10) % TEXT_SIZE][(int)(p.y * 10) % TEXT_SIZE][(int)(p.z * 10) % TEXT_SIZE];
		main->obj[main->curr].mat.color = vec3_create((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
	}
	else if ( main->mode.text_index - 1 == 6)
	{
		value = smooth_noise(p, main);
		main->obj[main->curr].mat.color.x = 256 * value;
		main->obj[main->curr].mat.color.y = 256 * value;
		main->obj[main->curr].mat.color.z = 256 * value;
	}
	else if (main->mode.text_index - 1 == 7)
	{
		value = turbulence(p, main, 4);
		main->obj[main->curr].mat.color.x = value;
		main->obj[main->curr].mat.color.y = value;
		main->obj[main->curr].mat.color.z = value * 10;
	}
}

void generate_textures(t_main *main)
{
	sin_stripes(main, 2);
	perlin_noise(main, 2);
	wood(main);
}

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
	generate_textures(main);
}

void change_texture(int keycode, t_main *main)
{
	if (keycode == 83)
		main->mode.text_index = 1; // checkerboard
	else if (keycode == 84)
		main->mode.text_index = 2; //vert stripes
	else if (keycode == 85)
		main->mode.text_index = 3; // hor stripes
	else if (keycode == 86)
		main->mode.text_index = 4; // round stripes
	else if (keycode == 87)
		main->mode.text_index = 5; // noise
	else if (keycode == 88)
		main->mode.text_index = 6; // wood
	else if (keycode == 89)
		main->mode.text_index = 7; // smoth noise
	else if (keycode == 90)
		main->mode.text_index = 8; // turbulence
	else if (keycode == 91)
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

//void rotate_objects(int keycode, t_main *main)
//{
//	if (keycode == 12 || keycode == 0) // x
//	{
//		if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
//		{}
//		image(main);
//	}
//	else if (keycode == 13 || keycode == 1)
//	{
//		if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
//		{}
//		image(main);
//	}
//	else if (keycode == 14 || keycode == 2)
//	{
//		if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
//		{}
//		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
//		{}
//		image(main);
//	}
//}



