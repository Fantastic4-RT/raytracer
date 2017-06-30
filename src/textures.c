#include <rt.h>

#ifdef TEXT_MODE
void perlin_noise(t_main *main, float zoom)
{
	int x;
	int y;
	int z;
	main->textures[4].zoom = (int)zoom;
	z = -1;
	while (++z < TEXT_SIZE)
	{
		y = -1;
		while (++y < TEXT_SIZE)
		{
			x = -1;
			while (++x < TEXT_SIZE)
			{
				main->textures[4].text_arr[z][y][x] =
						(rand() % 32768) / 32768.0;
			}
		}
	}
}

double smooth_noise(t_vec3 p, t_main *main)
{

	double fractx = main->textures[4].zoom == 1 ? 1 : (p.x - (int)p.x);
	double fracty = main->textures[4].zoom == 1 ? 1 : (p.y - (int)p.y);
	double fractz = main->textures[4].zoom == 1 ? 1 : (p.z - (int)p.z);
	int x1 = ((int)p.x + TEXT_SIZE) % TEXT_SIZE;
	int y1 = ((int)p.y + TEXT_SIZE) % TEXT_SIZE;
	int z1 = ((int)p.z + TEXT_SIZE) % TEXT_SIZE;

	int x2 = (x1 + TEXT_SIZE - 1) % TEXT_SIZE;
	int y2 = (y1 + TEXT_SIZE - 1) % TEXT_SIZE;
	int z2 = (z1 + TEXT_SIZE - 1) % TEXT_SIZE;
	double value = 0.0;
	value += fractx * fracty * fractz * main->textures[4].text_arr[z1][y1][x1];
	value += fractx * (1 - fracty) * fractz * main->textures[4].text_arr[z1][y2][x1];
	value += (1 - fractx) * fracty * fractz * main->textures[4].text_arr[z1][y1][x2];
	value += (1 - fractx) * (1 - fracty) * fractz * main->textures[4].text_arr[z1][y2][x2];
	value += fractx * fracty * (1 - fractz) * main->textures[4].text_arr[z2][y1][x1];
	value += fractx * (1 - fracty) * (1 - fractz) * main->textures[4].text_arr[z2][y2][x1];
	value += (1 - fractx) * fracty * (1 - fractz) * main->textures[4].text_arr[z2][y1][x2];
	value += (1 - fractx) * (1 - fracty) * (1 - fractz) * main->textures[4].text_arr[z2][y2][x2];
	return value;
}

double turbulence(t_vec3 p, t_main * main,  double size)
{
	double value = 0.0;
	double initial_size = size;

	t_vec3 tmp;
	while(size >= 1)
	{
		tmp.x = p.x;
		tmp.y = p.y;
		tmp.z = p.z;
		tmp.x /= size;
		tmp.y /= size;
		tmp.z /= size;
		value += smooth_noise(p, main) * size;
		size /= 2.0;
	}
	return(128.0 * value / initial_size);
}

void sin_stripes(t_main *main, int w)
{
	int x;
	int y;
	int z;
	int c1 = 0xFF0000;
	int c2 = 0x00FF00;

	main->textures[0].zoom = 2;
	main->textures[1].zoom = 2;
	main->textures[2].zoom = 2;
	main->textures[3].zoom = 2;
	z = -1;
	while (++z < TEXT_SIZE)
	{
		y = -1;
		while (++y < TEXT_SIZE)
		{
			x = -1;
			while (++x < TEXT_SIZE)
			{
				if (((sin(M_PI * y / w) > 0 && sin(M_PI * z / w) > 0))
					|| ((sin(M_PI * y / w) <= 0 && sin(M_PI * z / w) <= 0)))
					main->textures[0].text_arr[z][y][x] = c1;
				else
					main->textures[0].text_arr[z][y][x] = c2;
				main->textures[1].text_arr[z][y][x] = sin(M_PI * x / w) > 0 ?
													  c1 : c2;
				main->textures[2].text_arr[z][y][x] = sin(M_PI * y / w) > 0 ?
													  c1 : c2;
				main->textures[3].text_arr[z][y][x] = sin(M_PI * z / w) > 0 ?
													  c1 : c2;
			}
		}
	}
}

void wood(t_main *main)
{
	double rings = 24.0;
	double twist = 0.1;
	double turb_size = 32;
	t_vec3 color;
	int x;
	int y;
	int z;

	z = -1;
	while (++z < TEXT_SIZE)
	{
		y = -1;
		while (++y < TEXT_SIZE)
		{
			x = -1;
			while (++x < TEXT_SIZE)
			{
				double xval = (x - TEXT_SIZE) / (double)TEXT_SIZE;
				double yval = (y - TEXT_SIZE) / (double)TEXT_SIZE;
				double zval = (z - TEXT_SIZE) / (double)TEXT_SIZE;
				double distval = sqrt(xval * xval + yval * yval + zval * zval) +
								 twist * turbulence(vec3_create(x, y, z), main, turb_size) / 256.0;

				double sinval = 128.0 * fabs(sin(2 * rings * distval * M_PI));
				color.x = (80 + sinval);
				color.y = (30 + sinval);
				color.z = 30;
				main->textures[5].text_arr[x][y][z] = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
			}
		}
	}
}


void 	find_pixel_color(t_thread *th, t_main *main)
{
	t_vec3 p;
	double value;

	p.x = th->obj[main->curr].hitpoint.x;
	p.y = th->obj[main->curr].hitpoint.y;
	p.z = th->obj[main->curr].hitpoint.z;
	if (main->mode.text_index - 1 >= 0 && main->mode.text_index - 1 <= 3)
	{
		int color = (int) main->textures[main->mode.text_index -
										 1].text_arr[(int) p.z][(int) p.y][(int) p.x];
		th->obj[main->curr].mat.color =
				vec3_create(((color >> 16) & 0xFF) / 255.0,
							((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0);
	}
	else if (main->mode.text_index - 1 == 4)
	{
		double color = main->textures[4].text_arr[(int) p.z][(int) p.y][(int) p.x];
		th->obj[main->curr].mat.color = vec3_create(color, color, color);
	}
	else if (main->mode.text_index - 1 == 5)
	{
		int color = (int) main->textures[5].text_arr[(int) p.z][(int) p.y][(int) p.x];
		th->obj[main->curr].mat.color = vec3_create(
				((color >> 16) & 0xFF) / 255.0,
				((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0);
	}
	if (main->mode.text_index - 1 == 6)
	{
		value = smooth_noise(p, main);
		th->obj[main->mode.obj_index].mat.color.x = value;
		th->obj[main->mode.obj_index].mat.color.y = value;
		th->obj[main->mode.obj_index].mat.color.z = value;
	}
	else if (main->mode.text_index - 1 == 7)
	{
		value = turbulence(p, main, 4) / 255;
		th->obj[main->mode.obj_index].mat.color.x = value;
		th->obj[main->mode.obj_index].mat.color.y = value;
		th->obj[main->mode.obj_index].mat.color.z = value;
	}
}


void generate_textures(t_main *main)
{
	main->textures = (t_text *)malloc(sizeof(t_text) * 10);
	ft_bzero(main->textures, 10);
	perlin_noise(main, 2);
	sin_stripes(main, 2);
	wood(main);
}
#endif