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
	cone->p1.x = 0;
	cone->p1.y = 0;
	cone->p1.z = 0;
	cone->p2.x = 0;
	cone->p2.y = 0;
	cone->p2.z = 0;
	cone->axis.x = 0;
	cone->axis.y = 0;
	cone->axis.z = 0;
	cone->r1 = 1;
	cone->r2 = 2;
	cone->angle = 45;
	cone->cut = 0;
	cone->mat.color.x = 0;
	cone->mat.color.y = 0;
	cone->mat.color.z = 0;
	cone->mat.diff = 0.5;
	cone->mat.spec = 100;
	cone->mat.reflect = 0;
	return ((void *)cone);
}

void	cone_params(char *str, t_cone *cone, int param)
{
	char	*tmp;
	char	**arr;
	int		color;
	
	if (param == 0)
		cone->cut = ft_atoi(str);
	else if (param == 1)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position1>"));
		arr = ft_strsplit(tmp, ',');
		cone->p1.x = ft_atoi(arr[0]);
		cone->p1.y = ft_atoi(arr[1]);
		cone->p1.z = ft_atoi(arr[2]);
	}
	else if (param == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position2>"));
		arr = ft_strsplit(tmp, ',');
		cone->p2.x = ft_atoi(arr[0]);
		cone->p2.y = ft_atoi(arr[1]);
		cone->p2.z = ft_atoi(arr[2]);
	}
	else if (param == 3)
		cone->r1 = ft_atoi(str);
	else if (param == 4)
		cone->r2 = ft_atoi(str);
	else if (param == 5)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</axis>"));
		arr = ft_strsplit(tmp, ',');
		cone->axis.x = ft_atoi(arr[0]);
		cone->axis.y = ft_atoi(arr[1]);
		cone->axis.z = ft_atoi(arr[2]);
	}
	else if (param == 6)
		cone->angle = ft_atoi(str);
	else if (param == 7)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(tmp, "0123456789abcdef");
		cone->mat.color.x = color >> 16 & 0xFF;
		cone->mat.color.y = color >> 8 & 0xFF;
		cone->mat.color.z = color & 0xFF;
		free(tmp);
	}
	else if (param == 8)
		cone->mat.diff = ft_atoi(str) / 100.;
	else if (param == 9)
		cone->mat.spec = ft_atoi(str);
	else if (param == 10)
		cone->mat.reflect = ft_atoi(str);
	if (param == 1 || param == 2 || param == 5)
	{
		free(arr[0]);
		free(arr[1]);
		free(arr[2]);
		free(arr);
		free(tmp);
	}
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
}

void	add_cone(char *str, t_main *main)
{
	t_cone *c;
	fill_cone_data(str, (t_cone *)main->obj[main->obj_i].data);
	main->obj[main->obj_i].intersect = &intersect_cone;
	main->obj[main->obj_i].normal = &cone_norm;
	c = (t_cone *)main->obj[main->obj_i].data;
	main->obj[main->obj_i].mat = c->mat;
	main->obj[main->obj_i].mattype = get_material_type(c->mat);
}
