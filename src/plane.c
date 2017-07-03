/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 13:26:21 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/09 13:26:22 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*default_plane(t_plane *plane)
{
	plane->pos = vec3_create(0, 0, 0);
	plane->normal = vec3_create(0, 0, 0);
	plane->mat.color = vec3_create(0, 0, 0);
	plane->mat.diff = 0.5;
	plane->mat.spec = 100;
	plane->mat.reflect = 0;
	plane->mat.refract = 0;
	plane->mat.transp = 0;
	plane->p2 = vec3_create(0, 0, 0);
	plane->p3 = vec3_create(0, 0, 0);
	plane->p4 = vec3_create(0, 0, 0);
	plane->rad = 0;
	plane->cut = 0;
	return ((void *)plane);
}

void	plane_params(char *str, t_plane *plane, int param)
{
	char	*tmp;
	char	**arr;
	int		color;

	if (param == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(tmp, "0123456789abcdef");
		plane->mat.color = vec3_create((color >> 16 & 0xFF) / 255.,
				(color >> 8 & 0xFF) / 255., (color & 0xFF) / 255.);
		free(tmp);
	}
	else if (param == 1 || param == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(param == 1 ?
														   "</position>" : "</normal>"));
		arr = ft_strsplit(tmp, ' ');
		plane->pos = param == 1 ? vec3_fill_atoi(arr) : plane->pos;
		plane->normal = param == 2 ? vec3_fill_atoi(arr) : plane->normal;
		free_arr_tmp(arr, tmp);
	}
	plane->mat.diff = param == 4 ? ft_atoi(str) / 100. : plane->mat.diff;
	plane->mat.spec = param == 5 ? ft_atoi(str) : plane->mat.spec;
	plane->mat.reflect = param == 6 ? ft_atoi(str) : plane->mat.reflect;
	plane->mat.refract = param == 7 ? ft_atof(str) : plane->mat.refract;
	plane->mat.transp = param == 8 ? ft_atof(str) / 100. : plane->mat.transp;
}

void	fill_plane_data(char *str, t_plane *plane)
{
	if (ft_strstr(str, "<position>"))
		plane_params(str + ft_strlen("<position>"), plane, 1);
	else if (ft_strstr(str, "<normal>"))
		plane_params(str + ft_strlen("<normal>"), plane, 2);
	else if (ft_strstr(str, "<color>"))
		plane_params(str + ft_strlen("<color>"), plane, 3);
	else if (ft_strstr(str, "<diffuse>"))
		plane_params(str + ft_strlen("<diffuse>"), plane, 4);
	else if (ft_strstr(str, "<specular>"))
		plane_params(str + ft_strlen("<specular>"), plane, 5);
	else if (ft_strstr(str, "<reflection>"))
		plane_params(str + ft_strlen("<reflection>"), plane, 6);
	else if (ft_strstr(str, "<refraction>"))
		plane_params(str + ft_strlen("<refraction>"), plane, 7);
	else if (ft_strstr(str, "<transparency>"))
		plane_params(str + ft_strlen("<transparency>"), plane, 8);
}

//fill obj struct we need
void	add_plane(char *str, t_main *main)
{
	t_plane *data;

	fill_plane_data(str, (t_plane *)main->obj[main->obj_i].data);
	main->obj[main->obj_i].normal = &plane_norm;
	main->obj[main->obj_i].texture = 0;
	data = (t_plane *)main->obj[main->obj_i].data;
//	data->cut = 1;
//	data->p2 = vec3_create(10, -5, -10);
//	data->p3 = vec3_create(9, -2, -10);
//	data->p4 = vec3_create(0, -1, -10);
	main->obj[main->obj_i].mat = data->mat;
	main->obj[main->obj_i].mattype = get_material_type(data->mat);
	if (data->cut == 4)
		main->obj[main->obj_i].intersect = &intersect_mesh;
	else if (data->cut == 3)
		main->obj[main->obj_i].intersect = &intersect_triangle;
	else if (data->rad != 0)
		main->obj[main->obj_i].intersect = &intersect_elips;
	else
		main->obj[main->obj_i].intersect = &intersect_plane;
}
