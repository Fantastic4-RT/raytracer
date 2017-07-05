#include "rt.h"

void find_img_cd(t_thread *th, t_main *main)
{
	int i;
	t_vec3 p;
	int color;
	int index;

	index = main->mode.text_index - 9;
	p.x = (int)(((asin(th->obj[main->curr].n.x) + main->uv * RAD) / M_PI + 0.5)
			* 128) % 64;
	p.y = (int)(((asin(th->obj[main->curr].n.y)  + main->uv* RAD) / M_PI + 0.5)
			* 128) % 64;
	p.z = 0;
	i = (int)(p.x * main->img[index].bpp / 8 + p.y * main->img[index].sl);
	color = (main->img[index].data[i + 2] << 16) + (main->img[index].data[i + 1]
			<< 8) + main->img[index].data[i];
	th->obj[main->mode.obj_index].mat.color = int_to_vec3(color);
}

void find_disturb_cd(t_thread *th, t_main *main, t_vec3 p)
{
	double v;
	double color;

	if (main->mode.text_index - 1 >= 0 && main->mode.text_index - 1 <= 2)
	{
		color = sin_stripes(p, main, 2);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	else if (main->mode.text_index - 1 == 4 || main->mode.text_index - 1 == 5)
	{
		color = main->mode.text_index - 1 == 4 ? wood(p, main) : marble(p, main);
		th->obj[main->curr].mat.color = int_to_vec3((int)color);
	}
	else if (main->mode.text_index - 1 == 3)
	{
		color = main->textures[0].text_arr[(int)p.y][(int)p.x];
		th->obj[main->curr].mat.color = vec3_create(color, color, color);
	}
	else if (main->mode.text_index - 1 == 6 || main->mode.text_index - 1 == 7)
	{
		v = main->mode.text_index - 1 == 6 ?
		smooth_noise(vec3_create((p.x / 8.0), (p.y / 8.0), p.z), main) :
		turbulence(vec3_create((int) (p.x), (int) (p.y), p.z), main, 32) / 255;
		th->obj[main->mode.obj_index].mat.color = vec3_create(v, v, v);
	}
}

void 	find_pixel_color(t_thread *th, t_main *main)
{
	t_vec3 p;

	main->mode.text_index = main->obj[main->curr].texture;
	if (main->mode.text_index >= 9)
		find_img_cd(th, main);
	else
	{
		p.x = (int)(((asin(th->obj[main->curr].n.x) + main->uv * RAD) /
					 M_PI + 0.5) * TEXT_S) % TEXT_S;
		p.y = (int)(((asin(th->obj[main->curr].n.y)  + main->uv* RAD) /
					 M_PI + 0.5) * TEXT_S) % TEXT_S;
		p.z = 0;
		find_disturb_cd(th, main, p);
	}
}
