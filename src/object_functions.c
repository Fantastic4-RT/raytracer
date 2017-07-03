//
// Created by Anastasiia Trepyton on 6/23/17.
//
#include "rt.h"

void rotate_objects(int keycode, t_main *main)
{
	if (keycode == 12 || keycode == 0)
	{// x
		if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
		{
			t_cyl *data = (t_cyl *)main->obj[main->mode.obj_index].data;
			data->axis = keycode == 12 ? m_apply(x_rot(2 * RAD), data->axis) :
						 m_apply(x_rot(-2 * RAD), data->axis);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
		{
			t_cone *data = (t_cone *)main->obj[main->mode.obj_index].data;
			data->axis = keycode == 12 ? m_apply(x_rot(2 * RAD), data->axis) :
						 m_apply(x_rot(-2 * RAD), data->axis);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
		{
			t_plane *data = (t_plane *)main->obj[main->mode.obj_index].data;
			data->normal = keycode == 12 ? m_apply(x_rot(2 * RAD), data->normal)
						: m_apply(x_rot(-2 * RAD), data->normal);
			data->pos = keycode == 12 ? m_apply(x_rot(2 * RAD), data->pos)
									  : m_apply(x_rot(-2 * RAD), data->pos);
			data->p2 = keycode == 12 ? m_apply(x_rot(2 * RAD), data->p2)
									 : m_apply(x_rot(-2 * RAD), data->p2);
			data->p3 = keycode == 12 ? m_apply(x_rot(2 * RAD), data->p3)
									 : m_apply(x_rot(-2 * RAD), data->p3);
			data->p4 = keycode == 12 ? m_apply(x_rot(2 * RAD), data->p4)
									 : m_apply(x_rot(-2 * RAD), data->p4);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
		{
			t_sphere *data = (t_sphere *)main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 12 ? m_apply(m_mult(m_mult(tr(data->pos),
					x_rot(2 * RAD)), tr(vec3_invert(data->pos))), data->p1) :
						m_apply(m_mult(m_mult(tr(data->pos) ,x_rot(-2 * RAD)),
						   				tr(vec3_invert(data->pos))), data->p1);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
		{
			t_parab *data = (t_parab *)main->obj[main->mode.obj_index].data;
			data->axis = keycode == 12 ? m_apply(x_rot(2 * RAD), data->axis) :
										m_apply(x_rot(-2 * RAD), data->axis);
		}
	}
	if (keycode == 13 || keycode == 1)
	{// y
		if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
		{
			t_cyl *data = (t_cyl *) main->obj[main->mode.obj_index].data;
			data->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data->axis) :
						 m_apply(y_rot(-2 * RAD), data->axis);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
		{
			t_cone *data = (t_cone *) main->obj[main->mode.obj_index].data;
			data->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data->axis) :
						 m_apply(y_rot(-2 * RAD), data->axis);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
		{
			t_plane *data = (t_plane *) main->obj[main->mode.obj_index].data;
			data->normal = keycode == 13 ? m_apply(y_rot(2 * RAD), data->normal) :
						   m_apply(y_rot(-2 * RAD), data->normal);
			data->pos = keycode == 13 ? m_apply(y_rot(2 * RAD), data->pos)
									  : m_apply(y_rot(-2 * RAD), data->pos);
			data->p2 = keycode == 13 ? m_apply(y_rot(2 * RAD), data->p2)
									 : m_apply(y_rot(-2 * RAD), data->p2);
			data->p3 = keycode == 13 ? m_apply(y_rot(2 * RAD), data->p3)
									 : m_apply(y_rot(-2 * RAD), data->p3);
			data->p4 = keycode == 13 ? m_apply(y_rot(2 * RAD), data->p4)
									 : m_apply(y_rot(-2 * RAD), data->p4);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
		{
			t_sphere *data = (t_sphere *) main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 13 ? m_apply(m_mult(m_mult(tr(data->pos),
					y_rot(2 * RAD)), tr(vec3_invert(data->pos))), data->p1) :
					   m_apply(m_mult(m_mult(tr(data->pos) ,y_rot(-2 * RAD)),
									  tr(vec3_invert(data->pos))), data->p1);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
		{
			t_parab *data = (t_parab *)main->obj[main->mode.obj_index].data;
			data->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data->axis) :
						 				m_apply(y_rot(-2 * RAD), data->axis);
		}
	}
	if (keycode == 14 || keycode == 2)
	{// z
		if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
		{
			t_cyl *data = (t_cyl *) main->obj[main->mode.obj_index].data;
			data->axis = keycode == 14 ? m_apply(z_rot(2 * RAD), data->axis) :
						 m_apply(z_rot(-2 * RAD), data->axis);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
		{
			t_cone *data = (t_cone *) main->obj[main->mode.obj_index].data;
			data->axis = keycode == 14 ? m_apply(z_rot(2 * RAD), data->axis) :
						 m_apply(z_rot(-2 * RAD), data->axis);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
		{
			t_plane *data = (t_plane *) main->obj[main->mode.obj_index].data;
			data->normal = keycode == 14 ? m_apply(z_rot(2 * RAD), data->normal) :
						   m_apply(z_rot(-2 * RAD), data->normal);
			data->pos = keycode == 14 ? m_apply(z_rot(2 * RAD), data->pos)
									  : m_apply(z_rot(-2 * RAD), data->pos);
			data->p2 = keycode == 14 ? m_apply(z_rot(2 * RAD), data->p2)
									 : m_apply(z_rot(-2 * RAD), data->p2);
			data->p3 = keycode == 14 ? m_apply(z_rot(2 * RAD), data->p3)
									 : m_apply(z_rot(-2 * RAD), data->p3);
			data->p4 = keycode == 14 ? m_apply(z_rot(2 * RAD), data->p4)
									 : m_apply(z_rot(-2 * RAD), data->p4);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
		{
			t_sphere *data = (t_sphere *) main->obj[main->mode.obj_index].data;
			data->p1 = keycode == 14 ? m_apply(m_mult(m_mult(tr(data->pos),
					z_rot(2 * RAD)), tr(vec3_invert(data->pos))), data->p1) :
					   m_apply(m_mult(m_mult(tr(data->pos), z_rot(-2 * RAD)),
									  tr(vec3_invert(data->pos))), data->p1);
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
		{
			t_parab *data = (t_parab *)main->obj[main->mode.obj_index].data;
			data->axis = keycode == 14 ? m_apply(z_rot(2 * RAD), data->axis) :
						 				m_apply(z_rot(-2 * RAD), data->axis);
		}
	}
	image(main);
}

#ifdef TEXT_MODE
void change_texture(int keycode, t_main *main)
{
	if (keycode >= 83 && keycode <= 91 && main->mode.text_index == 0)
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
			data->p1 = keycode == 12 ?
						vec3_add(data->p1, vec3_create(1, 0, 0)) :
						vec3_sub(data->p1, vec3_create(1, 0, 0));
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
			if (!vec3_eq(data->p2, vec3_create(0, 0, 0)) && !vec3_eq(data->p3, vec3_create(0, 0, 0)))
			{
				data->p2 = keycode == 12 ?
							vec3_add(data->p2, vec3_create(1, 0, 0)) :
							vec3_sub(data->p2, vec3_create(1, 0, 0));
				data->p3 = keycode == 12 ?
							vec3_add(data->p3, vec3_create(1, 0, 0)) :
							vec3_sub(data->p3, vec3_create(1, 0, 0));
				data->p4 = keycode == 12 ?
						   vec3_add(data->p4, vec3_create(1, 0, 0)) :
						   vec3_sub(data->p4, vec3_create(1, 0, 0));
			}

		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
		{
			t_parab *data = (t_parab *)main->obj[main->mode.obj_index].data;
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
			data->p1 = keycode == 13 ?
						vec3_add(data->p1, vec3_create(0, 1, 0)) :
						vec3_sub(data->p1, vec3_create(0, 1, 0));
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
			if (!vec3_eq(data->p2, vec3_create(0, 0, 0)) && !vec3_eq(data->p3, vec3_create(0, 0, 0)))
			{
				data->p2 = keycode == 13 ?
						   vec3_add(data->p2, vec3_create(0, 1, 0)) :
						   vec3_sub(data->p2, vec3_create(0, 1, 0));
				data->p3 = keycode == 13 ?
						   vec3_add(data->p3, vec3_create(0, 1, 0)) :
						   vec3_sub(data->p3, vec3_create(0, 1, 0));
				data->p4 = keycode == 13 ?
						   vec3_add(data->p4, vec3_create(0, 1, 0)) :
						   vec3_sub(data->p4, vec3_create(0, 1, 0));
			}
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
		{
			t_parab *data = (t_parab *)main->obj[main->mode.obj_index].data;
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
			data->p1 = keycode == 14 ?
						vec3_add(data->p1, vec3_create(0, 0, 1)) :
						vec3_sub(data->p1, vec3_create(0, 0, 1));
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
			if (!vec3_eq(data->p2, vec3_create(0, 0, 0)) && !vec3_eq(data->p3, vec3_create(0, 0, 0)))
			{
				data->p2 = keycode == 14 ?
						   vec3_add(data->p2, vec3_create(0, 0, 1)) :
						   vec3_sub(data->p2, vec3_create(0, 0, 1));
				data->p3 = keycode == 14 ?
						   vec3_add(data->p3, vec3_create(0, 0, 1)) :
						   vec3_sub(data->p3, vec3_create(0, 0, 1));
				data->p4 = keycode == 14 ?
						   vec3_add(data->p4, vec3_create(0, 0, 1)) :
						   vec3_sub(data->p4, vec3_create(0, 0, 1));
			}
		}
		else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
		{
			t_parab *data = (t_parab *)main->obj[main->mode.obj_index].data;
			data->pos = keycode == 14 ?
						vec3_add(data->pos, vec3_create(0, 0, 1)) :
						vec3_sub(data->pos, vec3_create(0, 0, 1));
		}
		image(main);
	}
}

