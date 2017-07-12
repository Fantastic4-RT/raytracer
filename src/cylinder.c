/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:46:49 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/09 15:46:50 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*default_cylinder(t_cyl *cyl)
{
	cyl->p1 = vec3_create(0, 0, 0);
	cyl->p2 = vec3_create(0, 0, 0);
	cyl->axis = vec3_create(0, 0, 0);
	cyl->rad = 1;
	cyl->cut = 0;
	cyl->mat.color = vec3_create(0, 0, 0);
	cyl->mat.diff = 0.5;
	cyl->mat.spec = 100;
	cyl->mat.reflect = 0;
	cyl->mat.refract = 0;
	cyl->mat.transp = 0;
	return ((void *)cyl);
}

void	cyl_params_2(char *str, t_cyl *cyl, int param)
{
	char	*tmp;
	int		color;

	if (param == 5)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(ft_lowercase(tmp), "0123456789abcdef");
		cyl->mat.color = vec3_create((color >> 16 & 0xFF) / 255.,
						(color >> 8 & 0xFF) / 255., (color & 0xFF) / 255.);
		free(tmp);
	}
	cyl->mat.diff = param == 6 ? ft_atoi(str) / 100. : cyl->mat.diff;
	cyl->mat.spec = param == 7 ? ft_atoi(str) : cyl->mat.spec;
	cyl->mat.reflect = param == 8 ? ft_atoi(str) : cyl->mat.reflect;
	cyl->mat.refract = param == 9 ? ft_atof(str) : cyl->mat.refract;
	cyl->mat.transp = param == 10 ? ft_atof(str) / 100. : cyl->mat.transp;
}

void	cyl_params(char *str, t_cyl *cyl, int param)
{
	char	*tmp;
	char	**arr;

	cyl->cut = param == 0 ? ft_atoi(str) : cyl->cut;
	cyl->rad = param == 4 ? ft_atof(str) : cyl->rad;
	if (param == 1 || param == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(param == 1 ?
											"</position1>" : "</position2>"));
		arr = ft_strsplit(tmp, ' ');
		cyl->p1 = param == 1 ? vec3_fill_atoi(arr) : cyl->p1;
		cyl->p2 = param == 2 ? vec3_fill_atoi(arr) : cyl->p2;
		free_arr_tmp(arr, tmp);
	}
	else if (param == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</axis>"));
		arr = ft_strsplit(tmp, ' ');
		cyl->axis = vec3_fill_atoi(arr);
		free_arr_tmp(arr, tmp);
	}
	else
		cyl_params_2(str, cyl, param);
}

void	fill_cylinder_data(char *str, t_cyl *cyl)
{
	if (ft_strstr(str, "<cut>"))
		cyl_params(str + ft_strlen("<cut>"), cyl, 0);
	else if (ft_strstr(str, "<position1>"))
		cyl_params(str + ft_strlen("<position1>"), cyl, 1);
	else if (ft_strstr(str, "<position2>"))
		cyl_params(str + ft_strlen("<position2>"), cyl, 2);
	else if (ft_strstr(str, "<axis>"))
		cyl_params(str + ft_strlen("<axis>"), cyl, 3);
	else if (ft_strstr(str, "<radius>"))
		cyl_params(str + ft_strlen("<radius>"), cyl, 4);
	else if (ft_strstr(str, "<color>"))
		cyl_params(str + ft_strlen("<color>"), cyl, 5);
	else if (ft_strstr(str, "<diffuse>"))
		cyl_params(str + ft_strlen("<diffuse>"), cyl, 6);
	else if (ft_strstr(str, "<specular>"))
		cyl_params(str + ft_strlen("<specular>"), cyl, 7);
	else if (ft_strstr(str, "<reflection>"))
		cyl_params(str + ft_strlen("<reflection>"), cyl, 8);
	else if (ft_strstr(str, "<refraction>"))
		cyl_params(str + ft_strlen("<refraction>"), cyl, 9);
	else if (ft_strstr(str, "<transparency>"))
		cyl_params(str + ft_strlen("<transparency>"), cyl, 10);
}

void	add_cylinder(char *str, t_main *main)
{
	t_cyl	*data;

	data = (t_cyl *)main->obj[main->obj_i].data;
	fill_cylinder_data(str, data);
	if (data->cut == 0)
		main->obj[main->obj_i].intersect = &intersect_cylind;
	else
		main->obj[main->obj_i].intersect = &intersect_cylind_cut;
	if (data->cut == 0)
		main->obj[main->obj_i].normal = &cylinder_norm;
	else
		main->obj[main->obj_i].normal = &cylinder_norm_cut;
	if (data->cut != 0)
		data->axis = vec3_norm(vec3_sub(data->p1, data->p2));
	main->obj[main->obj_i].dir_y = vec3_norm(data->axis);
	main->obj[main->obj_i].dir_x = vec3_norm(vec3_cross(data->axis,
				vec3_add(data->axis, vec3_create(0.01, 0.01, 0.01))));
	main->obj[main->obj_i].texture = 0;
	main->obj[main->obj_i].tmp_color = data->mat.color;
	if (ft_strstr(str, "<texture>"))
		main->obj[main->obj_i].texture = ft_atoi(str + ft_strlen("<texture>"));
	main->obj[main->obj_i].mat = data->mat;
	main->obj[main->obj_i].mattype = get_material_type(data->mat);
}
