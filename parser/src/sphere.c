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

#include "parser.h"

void	*default_sphere(t_sphere *sphere)
{
	sphere->pos.x = 0;
	sphere->pos.y = 0;
	sphere->pos.z = 0;
	sphere->rad = 1;
	sphere->mat.color.x = 0;
	sphere->mat.color.y = 0;
	sphere->mat.color.z = 0;
	sphere->mat.diff = 0.5;
	sphere->mat.spec = 100;
	sphere->mat.reflect = 0;
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
		arr = ft_strsplit(tmp, ',');
		sphere->pos.x = ft_atoi(arr[0]);
		sphere->pos.y = ft_atoi(arr[1]);
		sphere->pos.z = ft_atoi(arr[2]);
	}
	else if (param == 2)
		sphere->rad = ft_atoi(str);
	else if (param == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(tmp, "0123456789abcdef");
		sphere->mat.color.x = color >> 16 & 0xFF;
		sphere->mat.color.y = color >> 8 & 0xFF;
		sphere->mat.color.z = color & 0xFF;
		free(tmp);
	}
	else if (param == 4)
		sphere->mat.diff = ft_atoi(str) / 100.;
	else if (param == 5)
		sphere->mat.spec = ft_atoi(str);
	else if (param == 6)
		sphere->mat.reflect = ft_atoi(str);
	if (param == 1)
	{
		free(arr[0]);
		free(arr[1]);
		free(arr[2]);
		free(arr);
		free(tmp);
	}
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
}

void	add_sphere(char *str, t_main *main)
{
	fill_sphere_data(str, (t_sphere *)main->obj[main->obj_i].data);
	//main->obj[main->obj_i].intersect = sphere_intersect;
}
