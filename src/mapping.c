/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 13:39:23 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/06 13:39:24 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	find_img_cd(t_thread *th, t_main *main)
{
	int		i;
	int		color;
	int		index;
	t_vec3	p;

	index = th->obj[main->curr].texture - 9;
	p.x = (int)(th->obj[main->curr].uv.x * th->main.img[index].w)
		% th->main.img[index].w;
	p.y = (int)(th->obj[main->curr].uv.y * th->main.img[index].h)
		% th->main.img[index].h;
	i = (int)(p.x * th->main.img[index].bpp / 8 + p.y * th->main.img[index].sl);
	color = (th->main.img[index].data[i + 2] << 16) +
		(th->main.img[index].data[i + 1] << 8) + th->main.img[index].data[i];
	th->obj[main->curr].mat.color = int_to_vec3(color);
}

void	find_disturb_cd2(t_thread *th, t_main *main, t_vec3 p)
{
	int		text;
	double	v;
	double	color;

	text = th->obj[main->curr].texture;
	if (text - 1 == 3)
	{
		p.x = (int)((p.x) * TEXT_S) % TEXT_S;
		p.y = (int)((p.y) * TEXT_S) % TEXT_S;
		color = th->main.textures[0].text_arr[(int)p.y][(int)p.x];
		th->obj[main->curr].mat.color = vec3_create(color, color, color);
	}
	else if (text - 1 == 6 || text - 1 == 7)
	{
		p.x *= 32;
		p.y *= 32;
		v = text - 1 == 6 ?
		smooth_noise(vec3_create((p.x / 8.0), (p.y / 8.0), p.z), &th->main) :
		turbulence(vec3_create((int)(p.x), (int)(p.y), p.z), &th->main, 32)
		/ 255;
		th->obj[main->curr].mat.color = vec3_create(v, v, v);
	}
}

void	find_disturb_cd(t_thread *th, t_main *main, t_vec3 p)
{
	double	color;
	int		text;

	text = th->obj[main->curr].texture;
	if (text - 1 >= 0 && text - 1 <= 2)
	{
		color = sin_stripes(p, th, 2);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	else if (text - 1 == 4 || text - 1 == 5)
	{
		color = text - 1 == 4 ? wood(p, &th->main) : marble(p, &th->main);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	else
		find_disturb_cd2(th, main, p);
}

void	get_uv_coordinates(t_thread *th, t_main *main)
{
	if (!ft_strcmp(th->obj[main->curr].type, "sphere") ||
			!ft_strcmp(th->obj[main->curr].type, "torus"))
		sphere_uv(th, main);
	else if (ft_strcmp(th->obj[main->curr].type, "plane") == 0)
		plane_uv(th, main);
	else if (ft_strcmp(th->obj[main->curr].type, "cone") == 0)
		cone_uv(th, main);
	else if (ft_strcmp(th->obj[main->curr].type, "cylinder") == 0)
		cylinder_uv(th, main);
	else
	{
		th->obj[main->curr].uv = vec3_zero();
		th->obj[main->curr].uv.x = (th->obj[main->curr].hitpoint.x
									+ main->scene.wid / 2);
		th->obj[main->curr].uv.y = (th->obj[main->curr].hitpoint.y
									+ main->scene.hei / 2);
	}
}

void	find_pixel_color(t_thread *th, t_main *main)
{
	if (th->main.obj[main->curr].texture >= 9)
	{
		get_uv_coordinates(th, main);
		find_img_cd(th, main);
	}
	else
	{
		th->obj[main->curr].uv.x = (th->obj[main->curr].hitpoint.x
							+ main->scene.wid / 2);
		th->obj[main->curr].uv.y = (th->obj[main->curr].hitpoint.y
							+ main->scene.hei / 2);
		find_disturb_cd(th, main, th->obj[main->curr].uv);
	}
}
