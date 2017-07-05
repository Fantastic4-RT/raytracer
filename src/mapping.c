//
// Created by Anastasiia Trepyton on 7/5/17.
//

#include "rt.h"

void 	find_pixel_color(t_thread *th, t_main *main)
{
	t_vec3 p;
	double v;
	double color;

	main->mode.text_index = main->obj[main->curr].texture;
	//spherical -- good
	p.x = (int)(((asin(th->obj[main->curr].n.x) + main->uv * RAD) / M_PI + 0.5) * TEXT_S) % TEXT_S;
	p.y = (int)(((asin(th->obj[main->curr].n.y)  + main->uv* RAD) / M_PI + 0.5) * TEXT_S) % TEXT_S;
	p.z = 0;

	if (main->mode.text_index - 1 >= 0 && main->mode.text_index - 1 <= 2)
	{
		color = sin_stripes(p, main, 2);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	if (main->mode.text_index - 1 == 3)
	{
		color = main->textures[0].text_arr[(int)p.y][(int)p.x];
		th->obj[main->curr].mat.color = vec3_create(color, color, color);
	}
	if (main->mode.text_index - 1 == 4)
	{
		color = wood(p, main);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	else if (main->mode.text_index - 1 == 5)
	{
		color = marble(p, main);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	if (main->mode.text_index - 1 == 6)
	{
		v = smooth_noise(vec3_create((p.x / 8.0), (p.y / 8.0), p.z ), main);
		th->obj[main->mode.obj_index].mat.color = vec3_create(v, v, v);
	}
	p.x = (int)(((asin(th->obj[main->curr].n.x) + main->uv * RAD) / M_PI + 0.5) * 128) % 64;
	p.y = (int)(((asin(th->obj[main->curr].n.y)  + main->uv* RAD) / M_PI + 0.5) * 128) % 64;
	if (main->mode.text_index - 1 == 7)
	{
		int i;
		i = (int)(p.x * main->img[0].bpp / 8 + p.y * main->img[0].sl);
		color = (main->img[0].data[i + 2] << 16) + (main->img[0].data[i + 1] << 8) + main->img[0].data[i];
		th->obj[main->mode.obj_index].mat.color = int_to_vec3((int)color);
//		v = turbulence(vec3_create((int) (p.x), (int) (p.y), p.z ), main, 32) / 255;
//		th->obj[main->mode.obj_index].mat.color = vec3_create(v, v, v);
	}
}
