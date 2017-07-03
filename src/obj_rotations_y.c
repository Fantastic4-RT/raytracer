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

void	y_object_rotation1(int keycode, t_main *main)
{
	t_cyl	*data;
	t_cone	*data1;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
	{
		data = (t_cyl *)main->obj[main->mode.obj_index].data;
		data->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data->axis) :
					m_apply(y_rot(-2 * RAD), data->axis);
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
	{
		data1 = (t_cone *)main->obj[main->mode.obj_index].data;
		if (data1->cut == 0)
			data1->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data1->axis)
					: m_apply(y_rot(-2 * RAD), data1->axis);
		else
		{
			data1->p1 = keycode == 13 ? m_apply(y_rot(2 * RAD), data1->p1) :
					m_apply(y_rot(-2 * RAD), data1->p1);
			data1->p2 = keycode == 13 ? m_apply(y_rot(2 * RAD), data1->p2) :
					m_apply(y_rot(-2 * RAD), data1->p2);
		}
	}
}

void	y_object_rotation2(int keycode, t_main *main)
{
	t_plane *data;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
	{
		data = (t_plane *)main->obj[main->mode.obj_index].data;
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
}

void	y_object_rotation3(int keycode, t_main *main)
{
	t_sphere	*data;
	t_parab		*data1;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
	{
		data = (t_sphere *)main->obj[main->mode.obj_index].data;
		data->p1 = keycode == 13 ? m_apply(m_mult(m_mult(tr(data->pos),
		y_rot(2 * RAD)), tr(vec3_invert(data->pos))), data->p1) :
		m_apply(m_mult(m_mult(tr(data->pos), y_rot(-2 * RAD)),
		tr(vec3_invert(data->pos))), data->p1);
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
	{
		data1 = (t_parab *)main->obj[main->mode.obj_index].data;
		data1->axis = keycode == 13 ? m_apply(y_rot(2 * RAD), data1->axis) :
					m_apply(y_rot(-2 * RAD), data1->axis);
	}
}