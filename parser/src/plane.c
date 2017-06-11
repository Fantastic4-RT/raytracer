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

#include "parser.h"

void	*default_plane(t_plane *plane)
{
	plane->pos.x = 0;
	plane->pos.y = 0;
	plane->pos.z = 0;
	plane->normal.x = 0;
	plane->normal.x = 1;
	plane->normal.x = 0;
	plane->mat.color.x = 0;
	plane->mat.color.y = 0;
	plane->mat.color.z = 0;
	plane->mat.diff = 0.5;
	plane->mat.spec = 100;
	plane->mat.reflect = 0;
	return ((void *)plane);
}

void	plane_params(char *str, t_plane *plane, int param)
{
	char	*tmp;
	char	**arr;
	int		color;

	if (param == 1)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position>"));
		arr = ft_strsplit(tmp, ',');
		plane->pos.x = ft_atoi(arr[0]);
		plane->pos.y = ft_atoi(arr[1]);
		plane->pos.z = ft_atoi(arr[2]);
	}
	else if (param == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</normal>"));
		arr = ft_strsplit(tmp, ',');
		plane->normal.x = ft_atoi(arr[0]);
		plane->normal.y = ft_atoi(arr[1]);
		plane->normal.z = ft_atoi(arr[2]);
	}
	else if (param == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(tmp, "0123456789abcdef");
		plane->mat.color.x = color >> 16 & 0xFF;
		plane->mat.color.y = color >> 8 & 0xFF;
		plane->mat.color.z = color & 0xFF;
		free(tmp);
	}
	else if (param == 4)
		plane->mat.diff = ft_atoi(str) / 100.;
	else if (param == 5)
		plane->mat.spec = ft_atoi(str);
	else if (param == 6)
		plane->mat.reflect = ft_atoi(str);
	if (param == 1 || param == 2)
	{
		free(arr[0]);
		free(arr[1]);
		free(arr[2]);
		free(arr);
		free(tmp);
	}
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
}

void	add_plane(char *str, t_main *main)
{
	fill_plane_data(str, (t_plane *)main->obj[main->obj_i].data);
	//main->obj[main->obj_i].intersect = plane_intersect;
}
