/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_blur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alohashc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 11:48:12 by alohashc          #+#    #+#             */
/*   Updated: 2017/07/07 11:48:16 by alohashc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_col_av1(t_vec3 *col)
{
    int		res;
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
    res = vec3_to_int(average);
    return (res);
}

//void    ft_sphere_data(t_thread *th, int index)
//{
//    t_sphere *sph;
//
//    sph = (t_sphere *)th->main.obj[index].data;
//    sph->pos.x += 20;
//}

//void    ft_check_type(t_thread *th, int index)
//{
//    if (ft_strcmp(th->main.obj[index].type, "sphere") == 0)
//        ft_sphere_data(th, index);
//}

void    ft_check_axis_minus(t_thread *th)
{
    if (((t_sphere *)th->obj[0].data)->motion_x == 1)
        ((t_sphere *) th->obj[0].data)->pos.x -= 2;
    if (((t_sphere *)th->obj[0].data)->motion_y == 1)
        ((t_sphere *) th->obj[0].data)->pos.y -= 2;
    if (((t_sphere *)th->obj[0].data)->motion_z == 1)
        ((t_sphere *) th->obj[0].data)->pos.z -= 2;
}

void    ft_check_axis(t_thread *th)
{
    if (((t_sphere *)th->obj[0].data)->motion_x == 1)
        ((t_sphere *)th->obj[0].data)->pos.x += 0.1;
    if (((t_sphere *)th->obj[0].data)->motion_y == 1)
        ((t_sphere *) th->obj[0].data)->pos.y += 0.1;
    if (((t_sphere *)th->obj[0].data)->motion_z == 1)
        ((t_sphere *) th->obj[0].data)->pos.z += 0.1;
}

void	ft_mb(t_thread *th, double dist, int x, int y)
{
    t_vec3 col[20];
    int     i;

    i = 0;
    th->main.scene.a_a = 1;
    while (i < 20)
    {
        col[i] = ft_aa(th, dist, x, y);
        ft_check_axis(th);
        i++;
    }
    ft_check_axis_minus(th);
    *((int *) (th->main.mlx.ipp + x * th->main.mlx.bpp / 8 +
               y * th->main.mlx.size_line)) = ft_col_av1(col);
}
