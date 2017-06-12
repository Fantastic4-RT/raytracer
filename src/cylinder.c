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

#include "../includes/rt.h"
void	*default_cylinder(t_cyl *cyl)
{
	cyl->p1.x = 0;
	cyl->p1.y = 0;
	cyl->p1.z = 0;
	cyl->p2.x = 0;
	cyl->p2.y = 0;
	cyl->p2.z = 0;
	cyl->axis.x = 0;
	cyl->axis.y = 0;
	cyl->axis.z = 0;
	cyl->rad = 1;
	cyl->cut = 0;
	cyl->mat.color.x = 0;
	cyl->mat.color.y = 0;
	cyl->mat.color.z = 0;
	cyl->mat.diff = 0.5;
	cyl->mat.spec = 100;
	cyl->mat.reflect = 0;
	return ((void *)cyl);
}

void	cyl_params(char *str, t_cyl *cyl, int param)
{
	char	*tmp;
	char	**arr;
	int		color;

	if (param == 0)
		cyl->cut = ft_atoi(str);
	else if (param == 1)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position1>"));
		arr = ft_strsplit(tmp, ',');
		cyl->p1.x = ft_atoi(arr[0]);
		cyl->p1.y = ft_atoi(arr[1]);
		cyl->p1.z = ft_atoi(arr[2]);
	}
	else if (param == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position2>"));
		arr = ft_strsplit(tmp, ',');
		cyl->p2.x = ft_atoi(arr[0]);
		cyl->p2.y = ft_atoi(arr[1]);
		cyl->p2.z = ft_atoi(arr[2]);
	}
	else if (param == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</axis>"));
		arr = ft_strsplit(tmp, ',');
		cyl->axis.x = ft_atoi(arr[0]);
		cyl->axis.y = ft_atoi(arr[1]);
		cyl->axis.z = ft_atoi(arr[2]);
	}
	else if (param == 4)
		cyl->rad = ft_atoi(str);
	else if (param == 5)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(tmp, "0123456789abcdef");
		cyl->mat.color.x = color >> 16 & 0xFF;
		cyl->mat.color.y = color >> 8 & 0xFF;
		cyl->mat.color.z = color & 0xFF;
		free(tmp);
	}
	else if (param == 6)
		cyl->mat.diff = ft_atoi(str) / 100.;
	else if (param == 7)
		cyl->mat.spec = ft_atoi(str);
	else if (param == 8)
		cyl->mat.reflect = ft_atoi(str);
	if (param == 1 || param == 2 || param == 3)
	{
		free(arr[0]);
		free(arr[1]);
		free(arr[2]);
		free(arr);
		free(tmp);
	}
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
}

void	add_cylinder(char *str, t_main *main)
{
	fill_cylinder_data(str, (t_cyl *)main->obj[main->obj_i].data);
}
