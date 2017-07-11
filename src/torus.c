/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 12:42:33 by vhorbach          #+#    #+#             */
/*   Updated: 2017/06/22 12:42:35 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*default_torus(t_torus *torus)
{
	torus->pos = vec3_create(0, 0, 0);
	torus->axis = vec3_create(0, 0, 1);
	torus->r_min = 1;
	torus->r_mjr = 4;
	torus->mat.color = vec3_create(0, 0, 0);
	torus->mat.diff = 0.5;
	torus->mat.spec = 100;
	torus->mat.reflect = 0;
	torus->mat.refract = 0;
	return ((void *)torus);
}

void	torus_params2(char *str, t_torus *torus, int param)
{
	torus->r_min = param == 3 ? ft_atoi(str) : torus->r_min;
	torus->r_mjr = param == 4 ? ft_atoi(str) : torus->r_mjr;
	torus->mat.diff = param == 6 ? ft_atoi(str) / 100. : torus->mat.diff;
	torus->mat.spec = param == 7 ? ft_atoi(str) : torus->mat.spec;
	torus->mat.reflect = param == 8 ? ft_atoi(str) : torus->mat.reflect;
	torus->mat.refract = param == 9 ? ft_atoi(str) : torus->mat.refract;
}

void	torus_params(char *str, t_torus *torus, int param)
{
	char	*tmp;
	char	**arr;
	int		color;

	if (param == 1 || param == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(param == 1 ?
													"</position>" : "</axis>"));
		arr = ft_strsplit(tmp, ' ');
		torus->pos = param == 1 ? vec3_fill_atoi(arr) : torus->pos;
		torus->axis = param == 2 ? vec3_fill_atoi(arr) : torus->axis;
		free_arr_tmp(arr, tmp);
	}
	else if (param == 5)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(ft_lowercase(tmp), "0123456789abcdef");
		torus->mat.color = vec3_create((color >> 16 & 0xFF) / 255.,
							(color >> 8 & 0xFF) / 255., (color & 0xFF) / 255.);
		free(tmp);
	}
	else
		torus_params2(str, torus, param);
}

void	fill_torus_data(char *str, t_torus *torus)
{
	if (ft_strstr(str, "<position>"))
		torus_params(str + ft_strlen("<position>"), torus, 1);
	else if (ft_strstr(str, "axis"))
		torus_params(str + ft_strlen("<axis>"), torus, 2);
	else if (ft_strstr(str, "radius_minor"))
		torus_params(str + ft_strlen("<radius_minor>"), torus, 3);
	else if (ft_strstr(str, "radius_major"))
		torus_params(str + ft_strlen("<radius_major>"), torus, 4);
	else if (ft_strstr(str, "<color>"))
		torus_params(str + ft_strlen("<color>"), torus, 5);
	else if (ft_strstr(str, "<diffuse>"))
		torus_params(str + ft_strlen("<diffuse>"), torus, 6);
	else if (ft_strstr(str, "<specular>"))
		torus_params(str + ft_strlen("<specular>"), torus, 7);
	else if (ft_strstr(str, "<reflection>"))
		torus_params(str + ft_strlen("<reflection>"), torus, 8);
	else if (ft_strstr(str, "<refraction>"))
		torus_params(str + ft_strlen("<refraction>"), torus, 9);
}

void	add_torus(char *str, t_main *main)
{
	t_torus *data;

	fill_torus_data(str, (t_torus *)main->obj[main->obj_i].data);
	main->obj[main->obj_i].intersect = &intersect_torus;
	main->obj[main->obj_i].normal = &torus_norm;
	data = (t_torus *)main->obj[main->obj_i].data;
	main->obj[main->obj_i].texture = 0;
	main->obj[main->obj_i].dir_x = vec3_create(1, 0, 0);
	main->obj[main->obj_i].dir_y = vec3_create(0, 1, 0);
	if (ft_strstr(str, "<texture>"))
		main->obj[main->obj_i].texture = ft_atoi(str + ft_strlen("<texture>"));
	main->obj[main->obj_i].mat = data->mat;
	main->obj[main->obj_i].mattype = get_material_type(data->mat);
	main->obj[main->obj_i].tmp_color = data->mat.color;
}
