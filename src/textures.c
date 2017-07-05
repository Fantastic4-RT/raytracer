#include <rt.h>

void	perlin_noise(t_main *main, float zoom)
{
	int x;
	int y;

	main->textures[4].zoom = (int)zoom;
		y = 0;
		while (y < TEXT_SIZE)
		{
			x = 0;
			while (x < TEXT_SIZE)
			{
				main->textures[4].text_arr[y][x] = (rand() % 32768) / 32768.0;
				x++;
			}
			y++;
		}
}

double	smooth_noise(t_vec3 p, t_main *main)
{
	t_vec3 f;
	t_vec3 p1;
	t_vec3 p2;
	double value;

	f.x = main->textures[4].zoom == 1 ? 1 : (p.x - (int)p.x);
	f.y = main->textures[4].zoom == 1 ? 1 : (p.y - (int)p.y);
	p1.x = ((int)p.x + TEXT_SIZE) % TEXT_SIZE;
	p1.y = ((int)p.y + TEXT_SIZE) % TEXT_SIZE;
	p2.x = (int)(p1.x + TEXT_SIZE - 1) % TEXT_SIZE;
	p2.y = (int)(p1.y + TEXT_SIZE - 1) % TEXT_SIZE;
	value = 0.0;
	value += f.x * f.y * main->textures[4].text_arr[(int)p1.y][(int)p1.x];
	value += (1 - f.x) * f.y * main->textures[4].text_arr[(int)p1.y][(int)p2.x];
	value += f.x * (1 - f.y) * main->textures[4].text_arr[(int)p2.y][(int)p1.x];
	value += (1 - f.x) * (1 - f.y) *
			main->textures[4].text_arr[(int)p2.y][(int)p2.x];
	return (value);
}

double	turbulence(t_vec3 p, t_main * main,  double size)
{
	double value;
	double initial_size;

	value = 0.0;
	initial_size = size;
	while(size >= 1)
	{
		value += smooth_noise(vec3_create(p.x / size, p.y / size, p.z),
						main) * size;
		size /= 2.0;
	}
	return(128.0 * value / initial_size);
}

//void sin_stripes(t_main *main, int w)
//{
//	int x;
//	int y;
//	int z;
//	int c1 = 0xFF0000;
//	int c2 = 0x00FF00;
//
//	main->textures[0].zoom = 2;
//	main->textures[1].zoom = 2;
//	main->textures[2].zoom = 2;
//	main->textures[3].zoom = 2;
//	z = -1;
//	while (++z < TEXT_SIZE)
//	{
//		y = -1;
//		while (++y < TEXT_SIZE)
//		{
//			x = -1;
//			while (++x < TEXT_SIZE)
//			{
//				if (((sin(M_PI * y / w) > 0 && sin(M_PI * z / w) > 0))
//					|| ((sin(M_PI * y / w) <= 0 && sin(M_PI * z / w) <= 0)))
//					main->textures[0].text_arr[z][y][x] = c1;
//				else
//					main->textures[0].text_arr[z][y][x] = c2;
//				main->textures[1].text_arr[z][y][x] = sin(M_PI * x / w) > 0 ?
//													  c1 : c2;
//				main->textures[2].text_arr[z][y][x] = sin(M_PI * y / w) > 0 ?
//													  c1 : c2;
//				main->textures[3].text_arr[z][y][x] = sin(M_PI * z / w) > 0 ?
//													  c1 : c2;
//			}
//		}
//	}
//}
//
void wood(t_main *main)
{
	t_vec3 color;
	t_vec3 i;
	t_vec3 val;
	double distval;
	double sinval;

	i.y = -1;
	while (++i.y < TEXT_SIZE)
	{
		i.x = -1;
		while (++i.x < TEXT_SIZE)
		{
			val.x = (i.x - TEXT_SIZE / 2) / (double)TEXT_SIZE;
			val.y = (i.y - TEXT_SIZE / 2) / (double)TEXT_SIZE;
			distval = sqrt(val.x * val.x + val.y * val.y) + 0.1 *
				turbulence(vec3_create(i.x, i.y, 0), main, 32.0) / 256.0;
			sinval = 128.0 * fabs(sin(2 * 12.0 * distval * M_PI));
			color = vec3_create((80 + sinval), (30 + sinval), 30);
			main->textures[5].text_arr[(int)i.y][(int)i.x] = vec3_to_int(color);
		}
	}
}


void 	find_pixel_color(t_thread *th, t_main *main)
{
	t_vec3 p;
	double v;

	main->mode.text_index = main->obj[main->curr].texture;
	p.x = asin(th->obj[main->curr].n.x) / M_PI + 0.5;
	p.y = asin(th->obj[main->curr].n.y) / M_PI + 0.5;
	p.z = 0;
	if (main->mode.text_index - 1 >= 0 && main->mode.text_index - 1 <= 3)
	{
		int color = (int) main->textures[main->mode.text_index -
		1].text_arr[(int) (p.y * 10)  % TEXT_SIZE][(int) (p.x * 10)  % TEXT_SIZE];
		th->obj[main->curr].mat.color =
		vec3_create(((color >> 16) & 0xFF) / 255.0,
		((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0);
	}
	if (main->mode.text_index - 1 == 4)
	{
		double color = main->textures[0].
				text_arr[(int) (p.y * TEXT_SIZE) % TEXT_SIZE][(int) (p.x * TEXT_SIZE) % TEXT_SIZE];
		th->obj[main->curr].mat.color = vec3_create(color, color, color);
	}
	else if (main->mode.text_index - 1 == 5)
	{
		int color = (int) main->textures[1].text_arr[(int) (p.y * TEXT_SIZE) % TEXT_SIZE][(int) (p.x * TEXT_SIZE) % TEXT_SIZE];
		th->obj[main->curr].mat.color = vec3_create(
				((color >> 16) & 0xFF) / 255.0,
				((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0);
	}
	if (main->mode.text_index - 1 == 6)
	{
		v = smooth_noise(vec3_create((int) (p.x * TEXT_SIZE) % TEXT_SIZE /
		8.0, (int) (p.y * TEXT_SIZE) % TEXT_SIZE / 8.0, p.z ), main);
		th->obj[main->mode.obj_index].mat.color = vec3_create(v, v, v);
	}
	else if (main->mode.text_index - 1 == 7)
	{
		v = turbulence(vec3_create((int) (p.x * TEXT_SIZE) % TEXT_SIZE,
		(int) (p.y * TEXT_SIZE) % TEXT_SIZE, p.z ), main, 32) / 255;
		th->obj[main->mode.obj_index].mat.color = vec3_create(v, v, v);
	}
}

void generate_textures(t_main *main)
{
	main->textures = (t_text *)malloc(sizeof(t_text) * 10);
	ft_bzero(main->textures, 10);
	perlin_noise(main, 2);
	wood(main);
//	sin_stripes(main, 2);
}
