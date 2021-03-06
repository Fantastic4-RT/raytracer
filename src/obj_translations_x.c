/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_translations_x.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 16:06:30 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 16:06:34 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	x_object_translation1(int keycode, t_main *main)
{
	t_sphere	*data;
	t_cone		*data1;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
	{
		data = (t_sphere *)main->obj[main->mode.obj_index].data;
		data->pos = keycode == 12 ?
				vec3_add(data->pos, vec3_create(1, 0, 0)) :
				vec3_sub(data->pos, vec3_create(1, 0, 0));
		data->p1 = keycode == 12 ?
				vec3_add(data->p1, vec3_create(1, 0, 0)) :
				vec3_sub(data->p1, vec3_create(1, 0, 0));
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
	{
		data1 = (t_cone *)main->obj[main->mode.obj_index].data;
		data1->p1 = keycode == 12 ?
				vec3_add(data1->p1, vec3_create(1, 0, 0)) :
				vec3_sub(data1->p1, vec3_create(1, 0, 0));
		data1->p2 = keycode == 12 ?
				vec3_add(data1->p2, vec3_create(1, 0, 0)) :
				vec3_sub(data1->p2, vec3_create(1, 0, 0));
	}
}

void	x_object_translation2(int keycode, t_main *main)
{
	t_cyl	*data;
	t_parab	*data1;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
	{
		data = (t_cyl *)main->obj[main->mode.obj_index].data;
		data->p1 = keycode == 12 ?
				vec3_add(data->p1, vec3_create(1, 0, 0)) :
				vec3_sub(data->p1, vec3_create(1, 0, 0));
		data->p2 = keycode == 12 ?
				vec3_add(data->p2, vec3_create(1, 0, 0)) :
				vec3_sub(data->p2, vec3_create(1, 0, 0));
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
	{
		data1 = (t_parab *)main->obj[main->mode.obj_index].data;
		data1->pos = keycode == 12 ?
					vec3_add(data1->pos, vec3_create(1, 0, 0)) :
					vec3_sub(data1->pos, vec3_create(1, 0, 0));
	}
}

void	x_object_translation3(int keycode, t_main *main)
{
	t_plane *data;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
	{
		data = (t_plane *)main->obj[main->mode.obj_index].data;
		data->pos = keycode == 12 ?
					vec3_add(data->pos, vec3_create(1, 0, 0)) :
					vec3_sub(data->pos, vec3_create(1, 0, 0));
		if (data->cut != 0)
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
}

void	x_object_translation4(int keycode, t_main *main)
{
	t_torus	*data;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "torus") == 0)
	{
		data = (t_torus *)main->obj[main->mode.obj_index].data;
		data->pos = keycode == 12 ?
					vec3_add(data->pos, vec3_create(1, 0, 0)) :
					vec3_sub(data->pos, vec3_create(1, 0, 0));
	}
}
