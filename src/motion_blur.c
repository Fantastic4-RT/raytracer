/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_blur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alohashc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 11:48:12 by alohashc          #+#    #+#             */
/*   Updated: 2017/07/10 15:42:37 by alohashc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	ft_col_av1(t_vec3 *col)
{
	int		i;
	t_vec3	average;

	i = 0;
	average.x = 0;
	average.y = 0;
	average.z = 0;
	while (i < 20)
	{
		average.x += pow(col[i].x, 2);
		average.y += pow(col[i].y, 2);
		average.z += pow(col[i].z, 2);
		i++;
	}
	average.x = sqrt(average.x / 20);
	average.y = sqrt(average.y / 20);
	average.z = sqrt(average.z / 20);
	return (average);
}

void	ft_check_type_minus(t_thread *th)
{
	int i;

	i = 0;
	while (i < th->main.scene.objs)
	{
		if (ft_strcmp(th->obj[i].type, "sphere") == 0)
			((t_sphere *)th->obj[i].data)->pos.y -= 2;
		if (ft_strcmp(th->obj[i].type, "cylinder") == 0)
			((t_sphere *)th->obj[i].data)->pos.y -= 2;
		if (ft_strcmp(th->obj[i].type, "cone") == 0)
			((t_sphere *)th->obj[i].data)->pos.y -= 2;
		i++;
	}
}

void	ft_check_type(t_thread *th)
{
	int i;

	i = 0;
	while (i < th->main.scene.objs)
	{
		if (ft_strcmp(th->obj[i].type, "sphere") == 0)
			((t_sphere *)th->obj[i].data)->pos.y += 0.1;
		if (ft_strcmp(th->obj[i].type, "cylinder") == 0)
			((t_sphere *)th->obj[i].data)->pos.y += 0.1;
		if (ft_strcmp(th->obj[i].type, "cone") == 0)
			((t_sphere *)th->obj[i].data)->pos.y += 0.1;
		i++;
	}
}

t_vec3	ft_mb(t_thread *th)
{
	t_vec3	col[20];
	t_vec3	color;
	int		i;

	i = 0;
	while (i < 20)
	{
		col[i] = cast_ray(th, &th->main, th->main.cam.ray, 0);
		ft_check_type(th);
		i++;
	}
	ft_check_type_minus(th);
	color = ft_col_av1(col);
	return (color);
}
