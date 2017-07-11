/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 15:19:10 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 15:19:14 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	x_dirextions_rot(int keycode, t_main *main)
{
	main->obj[main->mode.obj_index].dir_x = keycode == 12 ?
	vec3_norm(m_apply(x_rot(OBJ_ROT * RAD),
	main->obj[main->mode.obj_index].dir_x)) :
	vec3_norm(m_apply(x_rot(-OBJ_ROT * RAD),
	main->obj[main->mode.obj_index].dir_x));
	main->obj[main->mode.obj_index].dir_y = keycode == 12 ?
	vec3_norm(m_apply(x_rot(OBJ_ROT * RAD),
	main->obj[main->mode.obj_index].dir_y)) :
	vec3_norm(m_apply(x_rot(-OBJ_ROT * RAD),
	main->obj[main->mode.obj_index].dir_y));
}

void	x_object_rotation1(int keycode, t_main *main)
{
	t_cone	*data2;

	data2 = (t_cone *)main->obj[main->mode.obj_index].data;
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
	{
		if (data2->cut == 0)
			data2->axis = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD),
			data2->axis) : m_apply(x_rot(-OBJ_ROT * RAD), data2->axis);
		else
		{
			data2->p1 = keycode == 12 ? m_apply(m_mult(m_mult(tr(data2->apex),
				x_rot(OBJ_ROT * RAD)), tr(vec3_invert(data2->apex))), data2->p1)
				: m_apply(m_mult(m_mult(tr(data2->apex), x_rot(-OBJ_ROT * RAD)),
				tr(vec3_invert(data2->apex))), data2->p1);
			data2->p2 = keycode == 12 ? m_apply(m_mult(m_mult(tr(data2->apex),
				x_rot(OBJ_ROT * RAD)), tr(vec3_invert(data2->apex))), data2->p2)
				: m_apply(m_mult(m_mult(tr(data2->apex), x_rot(-OBJ_ROT * RAD)),
				tr(vec3_invert(data2->apex))), data2->p2);
		}
		x_dirextions_rot(keycode, main);
	}
}

void	x_object_rotation2(int keycode, t_main *main)
{
	t_plane		*data1;

	data1 = (t_plane *)main->obj[main->mode.obj_index].data;
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
	{
		data1->normal = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD),
			data1->normal) : m_apply(x_rot(-OBJ_ROT * RAD), data1->normal);
		if (data1->cut != 0)
		{
			data1->pos = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD),
				data1->pos) : m_apply(x_rot(-OBJ_ROT * RAD), data1->pos);
			data1->p2 = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD),
				data1->p2) : m_apply(x_rot(-OBJ_ROT * RAD), data1->p2);
			data1->p3 = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data1->p3)
				: m_apply(x_rot(-OBJ_ROT * RAD), data1->p3);
			data1->p4 = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data1->p4)
				: m_apply(x_rot(-OBJ_ROT * RAD), data1->p4);
			x_dirextions_rot(keycode, main);
		}
	}
}

void	x_object_rotation3(int keycode, t_main *main)
{
	t_cyl		*data1;
	t_sphere	*data2;
	t_parab		*data3;

	data1 = (t_cyl *)main->obj[main->mode.obj_index].data;
	data2 = (t_sphere *)main->obj[main->mode.obj_index].data;
	data3 = (t_parab *)main->obj[main->mode.obj_index].data;
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
	{
		data1->axis = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data1->axis)
			: m_apply(x_rot(-OBJ_ROT * RAD), data1->axis);
		x_dirextions_rot(keycode, main);
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
	{
		data2->p1 = keycode == 12 ? m_apply(m_mult(m_mult(tr(data2->pos),
			x_rot(OBJ_ROT * RAD)), tr(vec3_invert(data2->pos))), data2->p1) :
			m_apply(m_mult(m_mult(tr(data2->pos), x_rot(-OBJ_ROT * RAD)),
			tr(vec3_invert(data2->pos))), data2->p1);
		x_dirextions_rot(keycode, main);
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
		data3->axis = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD), data3->axis)
		: m_apply(x_rot(-OBJ_ROT * RAD), data3->axis);
}

void	x_object_rotation4(int keycode, t_main *main)
{
	t_torus	*data1;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "torus") == 0)
	{
		data1 = (t_torus *)main->obj[main->mode.obj_index].data;
		data1->axis = keycode == 12 ? m_apply(x_rot(OBJ_ROT * RAD),
			data1->axis) : m_apply(x_rot(-OBJ_ROT * RAD), data1->axis);
		x_dirextions_rot(keycode, main);
	}
}
