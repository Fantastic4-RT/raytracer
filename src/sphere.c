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
	sphere->rad = 1;
	sphere->mat.color = vec3_create(0, 0, 0);
	sphere->mat.diff = 0.5;
	sphere->mat.spec = 100;
	sphere->mat.reflect = 0;
	sphere->mat.refract = 0;
	sphere->mat.transp = 0;
	return ((void *)sphere);
}

void	sphere_params(char *str, t_sphere *sphere, int param)
{
	char	*tmp;
	char	**arr;
	int		color;

	if (param == 1)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position>"));
		arr = ft_strsplit(tmp, ' ');
		sphere->pos = vec3_fill_atoi(arr);
		free_arr_tmp(arr, tmp);
	}
	else if (param == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(tmp, "0123456789abcdef");
		sphere->mat.color = vec3_create((color >> 16 & 0xFF) / 255.,
							(color >> 8 & 0xFF) / 255., (color & 0xFF) / 255.);
		free(tmp);
	}
	sphere->rad = param == 2 ? ft_atoi(str) : sphere->rad;
	sphere->mat.diff = param == 4 ? ft_atoi(str) / 100. : sphere->mat.diff;
	sphere->mat.spec = param == 5 ? ft_atoi(str) : sphere->mat.spec;
	sphere->mat.reflect = param == 6 ? ft_atoi(str) : sphere->mat.reflect;
	sphere->mat.refract = param == 7 ? ft_atof(str) : sphere->mat.refract;
	sphere->mat.transp = param == 8 ? ft_atof(str) / 100. : sphere->mat.transp;
}

void	fill_sphere_data(char *str, t_sphere *sphere)
{
	if (ft_strstr(str, "<position>"))
		sphere_params(str + ft_strlen("<position>"), sphere, 1);
	else if (ft_strstr(str, "radius"))
		sphere_params(str + ft_strlen("<radius>"), sphere, 2);
	else if (ft_strstr(str, "<color>"))
		sphere_params(str + ft_strlen("<color>"), sphere, 3);
	else if (ft_strstr(str, "<diffuse>"))
		sphere_params(str + ft_strlen("<diffuse>"), sphere, 4);
	else if (ft_strstr(str, "<specular>"))
		sphere_params(str + ft_strlen("<specular>"), sphere, 5);
	else if (ft_strstr(str, "<reflection>"))
		sphere_params(str + ft_strlen("<reflection>"), sphere, 6);
	else if (ft_strstr(str, "<refraction>"))
		sphere_params(str + ft_strlen("<refraction>"), sphere, 7);
	else if (ft_strstr(str, "<transparency>"))
		sphere_params(str + ft_strlen("<transparency>"), sphere, 8);
}

//fill obj struct we need

void	add_sphere(char *str, t_main *main)
{
	t_sphere *data;

	fill_sphere_data(str, (t_sphere *)main->obj[main->obj_i].data);
	main->obj[main->obj_i].intersect = &inter_ray_sphere; //pointer to func
	main->obj[main->obj_i].normal = &sphere_norm;
	main->obj[main->obj_i].texture = 0;
	data = (t_sphere *)main->obj[main->obj_i].data;
	main->obj[main->obj_i].mat = data->mat;
	main->obj[main->obj_i].mattype = get_material_type(data->mat);
}
