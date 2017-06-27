//
// Created by Anastasiia Trepyton on 6/23/17.
//
#include "rt.h"

//void rotate_objects(int keycode, t_main *main)
//{
//
//}

#ifdef TEXT_MODE
void change_texture(int keycode, t_main *main)
{
	if (keycode >= 83 && keycode <= 90 && main->mode.text_index == 0)
		main->obj[main->curr].tmp_color = main->obj[main->curr].mat.color;
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
		main->mode.text_index = 7; // smooth noise
	else if (keycode == 91)
		main->mode.text_index = 8; // turbulence
	else if (keycode == 92)
	{
		main->mode.text_index = 0;
		main->obj[main->mode.obj_index].mat.color = main->obj[main->mode.obj_index].tmp_color;
	}
	image(main);
}
#endif

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
		if (main->obj[main->mode.obj_index].mat.color.x > 255)
			main->obj[main->mode.obj_index].mat.color.x = 0;
		else if (main->obj[main->mode.obj_index].mat.color.x < 0)
			main->obj[main->mode.obj_index].mat.color.x = 255;
		if (main->obj[main->mode.obj_index].mat.color.y > 255)
			main->obj[main->mode.obj_index].mat.color.y = 0;
		else if (main->obj[main->mode.obj_index].mat.color.y < 0)
			main->obj[main->mode.obj_index].mat.color.y = 255;
		if (main->obj[main->mode.obj_index].mat.color.z > 255)
			main->obj[main->mode.obj_index].mat.color.z = 0;
		else if (main->obj[main->mode.obj_index].mat.color.z < 0)
			main->obj[main->mode.obj_index].mat.color.z = 255;

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

