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

void find_img_cd(t_thread *th, t_main *main)
{
	int i;
	t_vec3 p;
	int color;
	int index;

	index = th->obj[main->curr].texture - 9;
//	p.x = (int)(((asin(th->obj[main->curr].n.x) /*+ main->uv * RAD*/) / M_PI + 0.5)
//			* 128) % 64;
//	p.y = (int)(((asin(th->obj[main->curr].n.y) /* + main->uv* RAD*/) / M_PI + 0.5)
//			* 128) % 64;
	p.x = (int)(((th->obj[main->curr].hitpoint.x + main->scene.wid/2) -
			(int)(th->obj[main->curr].hitpoint.x + main->scene.wid/2))
				* th->main.img[index].w) % th->main.img[index].w;
	p.y = (int)(((th->obj[main->curr].hitpoint.y + main->scene.hei/2) -
			(int)(th->obj[main->curr].hitpoint.y + main->scene.hei/2))
				* th->main.img[index].h) % th->main.img[index].h;
	p.z = 0;
	i = (int)(p.x * th->main.img[index].bpp / 8 + p.y * th->main.img[index].sl);
	color = (th->main.img[index].data[i + 2] << 16) + (th->main.img[index].data[i + 1]
			<< 8) + th->main.img[index].data[i];
	th->obj[main->curr].mat.color = int_to_vec3(color);
}

void find_disturb_cd(t_thread *th, t_main *main, t_vec3 p)
{
	double v;
	double color;
	int text;

	text = th->obj[main->curr].texture;
	if (text - 1 >= 0 && text - 1 <= 2)
	{
		color = sin_stripes(p, th, 2);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	else if (text - 1 == 4 || text - 1 == 5)
	{
			p.x *= 10;
			p.y *= 10;
		color = text - 1 == 4 ? wood(p, &th->main) : marble(p, &th->main);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	else if (text - 1 == 3)
	{
			p.x = (int)(p.x * TEXT_S) % TEXT_S;
			p.y = (int)(p.y * TEXT_S) % TEXT_S;
		color = th->main.textures[0].text_arr[(int)p.y][(int)p.x];
		th->obj[main->curr].mat.color = vec3_create(color, color, color);
	}
	else if (text - 1 == 6 || text - 1 == 7)
	{
			p.x *= 32;
			p.y *= 32;
		v = text - 1 == 6 ?
		smooth_noise(vec3_create((p.x / 8.0), (p.y / 8.0), p.z), &th->main) :
		turbulence(vec3_create((int) (p.x), (int) (p.y), p.z), &th->main, 32) / 255;
		th->obj[main->curr].mat.color = vec3_create(v, v, v);
	}
}

void 	find_pixel_color(t_thread *th, t_main *main)
{
	t_vec3 p;

	if (th->main.obj[main->curr].texture>= 9)
		find_img_cd(th, main);
	else
	{
		p.z = 0;
//			p.x = (int)(((asin(th->obj[main->curr].n.x) + main->uv * RAD) /
//					 M_PI + 0.5) * TEXT_S) % TEXT_S;
//			p.y = (int)(((asin(th->obj[main->curr].n.y)  + main->uv* RAD) /
//					 M_PI + 0.5) * TEXT_S) % TEXT_S;
		p.x = (th->obj[main->curr].hitpoint.x + main->scene.wid / 2);
		p.y = (th->obj[main->curr].hitpoint.y + main->scene.hei / 2);
		find_disturb_cd(th, main, p);
	}
}
