/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 12:23:21 by aradiuk           #+#    #+#             */
/*   Updated: 2017/07/02 12:23:29 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*default_parab(t_parab *parab)
{
	parab->pos = vec3_create(0, 0, 0);
	parab->axis = vec3_create(0, 0, 0);
	parab->k = 0;
	parab->mat.color = vec3_create(0, 0, 0);
	parab->mat.diff = 0.5;
	parab->mat.spec = 100;
	parab->mat.reflect = 0;
	parab->mat.refract = 0;
	parab->mat.transp = 0;
	return ((void *)parab);
}

void	parab_params_2(char *str, t_parab *parab, int param)
{
	parab->mat.diff = param == 5 ? ft_atoi(str) / 100. : parab->mat.diff;
	parab->mat.spec = param == 6 ? ft_atoi(str) : parab->mat.spec;
	parab->mat.reflect = param == 7 ? ft_atoi(str) : parab->mat.reflect;
	parab->mat.refract = param == 8 ? ft_atof(str) : parab->mat.refract;
	parab->mat.transp = param == 9 ? ft_atof(str) / 100. : parab->mat.transp;
}

void	parab_params(char *str, t_parab *parab, int param)
{
	char	*tmp;
	char	**arr;
	int		color;

	parab->k = param == 3 ? ft_atoi(str) : parab->k;
	if (param == 1 || param == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(param == 1 ?
												"</position1>" : "</axis>"));
		arr = ft_strsplit(tmp, ',');
		parab->pos = param == 1 ? vec3_fill_atoi(arr) : parab->pos;
		parab->axis = param == 2 ? vec3_fill_atoi(arr) : parab->axis;
		free_arr_tmp(arr, tmp);
	}
	else if (param == 4)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(ft_lowercase(tmp), "0123456789abcdef");
		parab->mat.color = vec3_create((color >> 16 & 0xFF) / 255.,
							(color >> 8 & 0xFF) / 255., (color & 0xFF) / 255.);
		free(tmp);
	}
	else
		parab_params_2(str, parab, param);
}

void	fill_parab_data(char *str, t_parab *parab)
{
	if (ft_strstr(str, "<position>"))
		parab_params(str + ft_strlen("<position>"), parab, 1);
	else if (ft_strstr(str, "<axis>"))
		parab_params(str + ft_strlen("<axis>"), parab, 2);
	else if (ft_strstr(str, "<kernel>"))
		parab_params(str + ft_strlen("<kernel>"), parab, 3);
	else if (ft_strstr(str, "<color>"))
		parab_params(str + ft_strlen("<color>"), parab, 4);
	else if (ft_strstr(str, "<diffuse>"))
		parab_params(str + ft_strlen("<diffuse>"), parab, 5);
	else if (ft_strstr(str, "<specular>"))
		parab_params(str + ft_strlen("<specular>"), parab, 6);
	else if (ft_strstr(str, "<reflection>"))
		parab_params(str + ft_strlen("<reflection>"), parab, 7);
	else if (ft_strstr(str, "<refraction>"))
		parab_params(str + ft_strlen("<refraction>"), parab, 8);
	else if (ft_strstr(str, "<transparency>"))
		parab_params(str + ft_strlen("<transparency>"), parab, 9);
}

void	add_paraboloid(char *str, t_main *main)
{
	t_parab *data;

	fill_parab_data(str, (t_parab *)main->obj[main->obj_i].data);
	main->obj[main->obj_i].intersect = &intersect_parab;
	main->obj[main->obj_i].normal = &parab_norm;
	data = (t_parab *)main->obj[main->obj_i].data;
	main->obj[main->obj_i].texture = 0;
	main->obj[main->obj_i].tmp_color = data->mat.color;
	if (ft_strstr(str, "<texture>"))
		main->obj[main->obj_i].texture = ft_atoi(str + ft_strlen("<texture>"));
	main->obj[main->obj_i].mat = data->mat;
	main->obj[main->obj_i].mattype = get_material_type(data->mat);
}
