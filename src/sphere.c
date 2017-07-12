/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:15:56 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/09 15:15:57 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*default_sphere(t_sphere *sphere)
{
	sphere->pos = vec3_create(0, 0, 0);
	sphere->tt[0] = 2000000.;
	sphere->tt[1] = 2000000.;
	sphere->rad = 1;
	sphere->cut = 0;
	sphere->hit_obj = -1;
	sphere->mat.color = vec3_create(0, 0, 0);
	sphere->mat.diff = 0.5;
	sphere->mat.spec = 100;
	sphere->mat.reflect = 0;
	sphere->mat.refract = 0;
	sphere->mat.transp = 0;
	return ((void *)sphere);
}

void	sphere_params_2(char *str, t_sphere *sphere, int param)
{
	sphere->rad = param == 2 ? ft_atof(str) : sphere->rad;
	sphere->mat.diff = param == 5 ? ft_atoi(str) / 100. : sphere->mat.diff;
	sphere->mat.spec = param == 6 ? ft_atoi(str) : sphere->mat.spec;
	sphere->mat.reflect = param == 7 ? ft_atoi(str) : sphere->mat.reflect;
	sphere->mat.refract = param == 8 ? ft_atof(str) : sphere->mat.refract;
	sphere->mat.transp = param == 9 ? ft_atof(str) / 100. : sphere->mat.transp;
}

void	sphere_params(char *str, t_sphere *sphere, int param)
{
	char	*tmp;
	char	**arr;
	int		color;

	sphere->cut = param == 0 ? ft_atoi(str) : sphere->cut;
	if (param == 1 || param == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(param == 1 ?
												"</position>" : "</plane>"));
		arr = ft_strsplit(tmp, ' ');
		sphere->pos = param == 1 ? vec3_fill_atoi(arr) : sphere->pos;
		sphere->p1 = param == 3 ? vec3_fill_atoi(arr) : sphere->p1;
		free_arr_tmp(arr, tmp);
	}
	else if (param == 4)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(ft_lowercase(tmp), "0123456789abcdef");
		sphere->mat.color = vec3_create((color >> 16 & 0xFF) / 255.,
							(color >> 8 & 0xFF) / 255., (color & 0xFF) / 255.);
		free(tmp);
	}
	else
		sphere_params_2(str, sphere, param);
}

void	fill_sphere_data(char *str, t_sphere *sphere)
{
	if (ft_strstr(str, "<cut>"))
		sphere_params(str + ft_strlen("<cut>"), sphere, 0);
	else if (ft_strstr(str, "<position>"))
		sphere_params(str + ft_strlen("<position>"), sphere, 1);
	else if (ft_strstr(str, "radius"))
		sphere_params(str + ft_strlen("<radius>"), sphere, 2);
	else if (ft_strstr(str, "<plane>"))
		sphere_params(str + ft_strlen("<plane>"), sphere, 3);
	else if (ft_strstr(str, "<color>"))
		sphere_params(str + ft_strlen("<color>"), sphere, 4);
	else if (ft_strstr(str, "<diffuse>"))
		sphere_params(str + ft_strlen("<diffuse>"), sphere, 5);
	else if (ft_strstr(str, "<specular>"))
		sphere_params(str + ft_strlen("<specular>"), sphere, 6);
	else if (ft_strstr(str, "<reflection>"))
		sphere_params(str + ft_strlen("<reflection>"), sphere, 7);
	else if (ft_strstr(str, "<refraction>"))
		sphere_params(str + ft_strlen("<refraction>"), sphere, 8);
	else if (ft_strstr(str, "<transparency>"))
		sphere_params(str + ft_strlen("<transparency>"), sphere, 9);
}

void	add_sphere(char *str, t_main *main)
{
	t_sphere *data;

	data = (t_sphere *)main->obj[main->obj_i].data;
	fill_sphere_data(str, data);
	if (data->cut == 0)
		main->obj[main->obj_i].intersect = &inter_ray_sphere;
	else
		main->obj[main->obj_i].intersect = &inter_ray_sphere_cut;
	if (data->cut == 0)
		main->obj[main->obj_i].normal = &sphere_norm;
	else
		main->obj[main->obj_i].normal = &sphere_norm_cut;
	main->obj[main->obj_i].dir_x = vec3_create(1, 0, 0);
	main->obj[main->obj_i].dir_y = vec3_create(0, 1, 0);
	main->obj[main->obj_i].texture = 0;
	if (ft_strstr(str, "<texture>"))
		main->obj[main->obj_i].texture = ft_atoi(str + ft_strlen("<texture>"));
	main->obj[main->obj_i].mat = data->mat;
	main->obj[main->obj_i].mattype = get_material_type(data->mat);
	main->obj[main->obj_i].tmp_color = data->mat.color;
	if (vec3_eq(data->pos, data->p1))
		data->p1 = vec3_add(data->p1, vec3_create(0, 0.0001, 0));
}
