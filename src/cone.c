/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:03:56 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/09 17:03:57 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*default_cone(t_cone *cone)
{
	cone->p1 = vec3_create(0, 0, 0);
	cone->p2 = vec3_create(0, 0, 0);
	cone->axis = vec3_create(0, 0, 0);
	cone->r1 = 0.0001;
	cone->r2 = 0.0002;
	cone->angle = 45;
	cone->cut = 0;
	cone->mat.color = vec3_create(0, 0, 0);
	cone->mat.diff = 0.5;
	cone->mat.spec = 100;
	cone->mat.reflect = 0;
	cone->mat.refract = 0;
	cone->mat.transp = 0;
	return ((void *)cone);
}

void	cone_params_2(char *str, t_cone *cone, int param)
{
	char	*tmp;
	int		color;

	cone->r1 = param == 3 ? ft_atof(str) : cone->r1;
	cone->r2 = param == 4 ? ft_atof(str) : cone->r2;
	cone->r1 == cone->r2 ? error(11) : 0;
	cone->angle = param == 6 ? ft_atoi(str) : cone->angle;
	if (param == 7)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(ft_lowercase(tmp), "0123456789abcdef");
		cone->mat.color = vec3_create((color >> 16 & 0xFF) / 255.,
							(color >> 8 & 0xFF) / 255., (color & 0xFF) / 255.);
		free(tmp);
	}
	cone->mat.diff = param == 8 ? ft_atoi(str) / 100. : cone->mat.diff;
	cone->mat.spec = param == 9 ? ft_atoi(str) : cone->mat.spec;
	cone->mat.reflect = param == 10 ? ft_atoi(str) : cone->mat.reflect;
	cone->mat.refract = param == 11 ? ft_atof(str) : cone->mat.refract;
	cone->mat.transp = param == 12 ? ft_atof(str) / 100. : cone->mat.transp;
}

void	cone_params(char *str, t_cone *cone, int param)
{
	char	*tmp;
	char	**arr;

	cone->cut = param == 0 ? ft_atoi(str) : cone->cut;
	if (cone->cut != 1 && cone->cut != 0)
		error(10);
	if (param == 1 || param == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(param == 1 ?
											"</position1>" : "</position2>"));
		arr = ft_strsplit(tmp, ',');
		cone->p1 = param == 1 ? vec3_fill_atoi(arr) : cone->p1;
		cone->p2 = param == 2 ? vec3_fill_atoi(arr) : cone->p2;
		free_arr_tmp(arr, tmp);
	}
	else if (param == 5)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</axis>"));
		arr = ft_strsplit(tmp, ',');
		cone->axis = vec3_fill_atoi(arr);
		free_arr_tmp(arr, tmp);
	}
	else
		cone_params_2(str, cone, param);
}

void	fill_cone_data(char *str, t_cone *cone)
{
	if (ft_strstr(str, "<cut>"))
		cone_params(str + ft_strlen("<cut>"), cone, 0);
	else if (ft_strstr(str, "<position1>"))
		cone_params(str + ft_strlen("<position1>"), cone, 1);
	else if (ft_strstr(str, "<position2>"))
		cone_params(str + ft_strlen("<position2>"), cone, 2);
	else if (ft_strstr(str, "<radius1>"))
		cone_params(str + ft_strlen("<radius1>"), cone, 3);
	else if (ft_strstr(str, "<radius2>"))
		cone_params(str + ft_strlen("<radius2>"), cone, 4);
	else if (ft_strstr(str, "<axis>"))
		cone_params(str + ft_strlen("<axis>"), cone, 5);
	else if (ft_strstr(str, "<angle>"))
		cone_params(str + ft_strlen("<angle>"), cone, 6);
	else if (ft_strstr(str, "<color>"))
		cone_params(str + ft_strlen("<color>"), cone, 7);
	else if (ft_strstr(str, "<diffuse>"))
		cone_params(str + ft_strlen("<diffuse>"), cone, 8);
	else if (ft_strstr(str, "<specular>"))
		cone_params(str + ft_strlen("<specular>"), cone, 9);
	else if (ft_strstr(str, "<reflection>"))
		cone_params(str + ft_strlen("<reflection>"), cone, 10);
	else if (ft_strstr(str, "<refraction>"))
		cone_params(str + ft_strlen("<refraction>"), cone, 11);
}

void	add_cone(char *str, t_main *main)
{
	t_cone *data;

	data = (t_cone *)main->obj[main->obj_i].data;
	fill_cone_data(str, data);
	data->apex = vec3_add(data->p1, vec3_mult(vec3_sub(data->p2, data->p1),
										(data->r1 / (data->r1 - data->r2))));
	if (ft_strstr(str, "<transparency>"))
		cone_params(str + ft_strlen("<transparency>"), data, 12);
	if (((t_cone *)main->obj[main->obj_i].data)->cut == 0)
		main->obj[main->obj_i].intersect = &intersect_cone;
	else
		main->obj[main->obj_i].intersect = &intersect_cone_cut;
	main->obj[main->obj_i].texture = 0;
	if (ft_strstr(str, "<texture>"))
		main->obj[main->obj_i].texture = ft_atoi(str + ft_strlen("<texture>"));
	main->obj[main->obj_i].normal = data->cut == 1 ? &cone_norm_cut :
									&cone_norm;
	main->obj[main->obj_i].tmp_color = data->mat.color;
	main->obj[main->obj_i].mat = data->mat;
	if (data->cut != 0)
		data->axis = vec3_norm(vec3_sub(data->p1, data->p2));
	main->obj[main->obj_i].dir_y = vec3_norm(data->axis);
	main->obj[main->obj_i].dir_x = vec3_norm(vec3_cross(data->axis,
		vec3_add(data->axis, vec3_create(0.01, 0.01, 0.01))));
	main->obj[main->obj_i].mattype = get_material_type(data->mat);
}
