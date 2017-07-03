//
// Created by Anastasiia Trepyton on 7/3/17.
//

#include "rt.h"

void	x_object_rotation1(int keycode, t_main *main)
{
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
	{
		t_cyl *data = (t_cyl *)main->obj[main->mode.obj_index].data;
		data->axis = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data->axis) :
		m_apply(x_rot(-OBJ_ROT * RAD), data->axis);
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
	{
		t_cone *data = (t_cone *) main->obj[main->mode.obj_index].data;
		if (data->cut == 0)
			data->axis = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD),
			data->axis) : m_apply(x_rot(-OBJ_ROT * RAD), data->axis);
		else
		{
			data->p1 = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data->p1) :
			m_apply(x_rot(-OBJ_ROT * RAD), data->p1);
			data->p2 = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data->p2) :
			m_apply(x_rot(-OBJ_ROT * RAD), data->p2);
		}
	}

}

void	x_object_rotation2(int keycode, t_main *main)
{
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
	{
		t_plane *data = (t_plane *)main->obj[main->mode.obj_index].data;
		data->normal = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD),
			data->normal) : m_apply(x_rot(-OBJ_ROT * RAD), data->normal);
		data->pos = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data->pos)
								  : m_apply(x_rot(-OBJ_ROT * RAD), data->pos);
		data->p2 = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data->p2)
								 : m_apply(x_rot(-OBJ_ROT * RAD), data->p2);
		data->p3 = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data->p3)
								 : m_apply(x_rot(-OBJ_ROT * RAD), data->p3);
		data->p4 = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data->p4)
								 : m_apply(x_rot(-OBJ_ROT * RAD), data->p4);
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
	{
		t_sphere *data = (t_sphere *)main->obj[main->mode.obj_index].data;
		data->p1 = keycode == 12 ? m_apply(m_mult(m_mult(tr(data->pos),
		x_rot(OBJ_ROT * RAD)), tr(vec3_invert(data->pos))), data->p1) :
		m_apply(m_mult(m_mult(tr(data->pos) ,x_rot(-OBJ_ROT * RAD)),
		tr(vec3_invert(data->pos))), data->p1);
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
	{
		t_parab *data = (t_parab *)main->obj[main->mode.obj_index].data;
		data->axis = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data->axis) :
		m_apply(x_rot(-OBJ_ROT * RAD), data->axis);
	}
}