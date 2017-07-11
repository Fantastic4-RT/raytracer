/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotations_y.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 15:45:29 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 15:45:40 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	y_dirextions_rot(int keycode, t_main *main)
{
	main->obj[main->mode.obj_index].dir_x = keycode == 13 ?
	vec3_norm(m_apply(y_rot(OBJ_ROT * RAD),
	main->obj[main->mode.obj_index].dir_x)) :
	vec3_norm(m_apply(y_rot(-OBJ_ROT * RAD),
	main->obj[main->mode.obj_index].dir_x));
	main->obj[main->mode.obj_index].dir_y = keycode == 13 ?
	vec3_norm(m_apply(y_rot(OBJ_ROT * RAD),
	main->obj[main->mode.obj_index].dir_y)) :
	vec3_norm(m_apply(y_rot(-OBJ_ROT * RAD),
	main->obj[main->mode.obj_index].dir_y));
}

void	y_object_rotation1(int keycode, t_main *main)
{
	t_cyl	*data;

	data = (t_cyl *)main->obj[main->mode.obj_index].data;
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
	{
		data->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data->axis) :
					m_apply(y_rot(-2 * RAD), data->axis);
		y_dirextions_rot(keycode, main);
	}
}

void	y_object_rotation4(int keycode, t_main *main)
{
	t_cone	*data1;

	data1 = (t_cone *)main->obj[main->mode.obj_index].data;
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
	{
		if (data1->cut == 0)
			data1->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data1->axis)
										: m_apply(y_rot(-2 * RAD), data1->axis);
		else
		{
			data1->p1 = keycode == 13 ? m_apply(m_mult(m_mult(tr(data1->apex),
			y_rot(OBJ_ROT * RAD)), tr(vec3_invert(data1->apex))), data1->p1)
			: m_apply(m_mult(m_mult(tr(data1->apex), y_rot(-OBJ_ROT * RAD)),
			tr(vec3_invert(data1->apex))), data1->p1);
			data1->p2 = keycode == 13 ? m_apply(m_mult(m_mult(tr(data1->apex),
			y_rot(OBJ_ROT * RAD)), tr(vec3_invert(data1->apex))), data1->p2)
			: m_apply(m_mult(m_mult(tr(data1->apex), y_rot(-OBJ_ROT * RAD)),
			tr(vec3_invert(data1->apex))), data1->p2);
		}
		y_dirextions_rot(keycode, main);
	}
}

void	y_object_rotation2(int keycode, t_main *main)
{
	t_plane *data;

	data = (t_plane *)main->obj[main->mode.obj_index].data;
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
	{
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
		y_dirextions_rot(keycode, main);
	}
}

void	y_object_rotation3(int keycode, t_main *main)
{
	t_sphere	*data;
	t_parab		*data1;

	data = (t_sphere *)main->obj[main->mode.obj_index].data;
	data1 = (t_parab *)main->obj[main->mode.obj_index].data;
	if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
	{
		data->p1 = keycode == 13 ? m_apply(m_mult(m_mult(tr(data->pos),
		y_rot(2 * RAD)), tr(vec3_invert(data->pos))), data->p1) :
		m_apply(m_mult(m_mult(tr(data->pos), y_rot(-2 * RAD)),
		tr(vec3_invert(data->pos))), data->p1);
		y_dirextions_rot(keycode, main);
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
		data1->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data1->axis) :
					m_apply(y_rot(-2 * RAD), data1->axis);
}
