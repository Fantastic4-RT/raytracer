//
// Created by Anastasiia Trepyton on 6/8/17.
//


#include "includes/rt.h"

void perlin_noise(t_env *e, int i,float zoom)
{
	int x;
	int y;
	int z;
	e->scene.text[0].zoom = zoom;
	z = -1;
	while (++z < TEXT_SIZE)
	{
		y = -1;
		while (++y < TEXT_SIZE)
		{
			x = -1;
			while (++x < TEXT_SIZE)
			{
				e->scene.text[i].text_arr[z][y][x] =
						(rand() % 32768) / 32768.0;
			}
		}
	}
}

double smooth_noise(t_vector p, t_env *e, int i)
{
	double fractx = e->scene.text[i].zoom == 1 ? 1 : p.x - (int)p.x;
	double fracty = e->scene.text[i].zoom == 1 ? 1 : p.y - (int)p.y;
	double fractz = e->scene.text[i].zoom == 1 ? 1 : p.z - (int)p.z;

	int x1 = ((int)p.x + TEXT_SIZE) % TEXT_SIZE;
	int y1 = ((int)p.y + TEXT_SIZE) % TEXT_SIZE;
	int z1 = ((int)p.z + TEXT_SIZE) % TEXT_SIZE;

	int x2 = (x1 + TEXT_SIZE - 1) % TEXT_SIZE;
	int y2 = (y1 + TEXT_SIZE - 1) % TEXT_SIZE;
	int z2 = (z1 + TEXT_SIZE - 1) % TEXT_SIZE;

	double value = 0.0;
	value += fractx * fracty * fractz * e->scene.text[i].text_arr[z1][y1][x1];
	value += fractx * (1 - fracty) * fractz * e->scene.text[i].text_arr[z1][y2][x1];
	value += (1 - fractx) * fracty * fractz * e->scene.text[i].text_arr[z1][y1][x2];
	value += (1 - fractx) * (1 - fracty) * fractz * e->scene.text[i].text_arr[z1][y2][x2];
	value += fractx * fracty * (1 - fractz) * e->scene.text[i].text_arr[z2][y1][x1];
	value += fractx * (1 - fracty) * (1 - fractz) * e->scene.text[i].text_arr[z2][y2][x1];
	value += (1 - fractx) * fracty * (1 - fractz) * e->scene.text[i].text_arr[z2][y1][x2];
	value += (1 - fractx) * (1 - fracty) * (1 - fractz) * e->scene.text[i].text_arr[z2][y2][x2];
	return value;
}

double turbulence(t_vector p, t_env *e, double size)
{
	double value = 0.0;
	double initialSize = size;

	t_vector tmp;
	while(size >= 1)
	{
		tmp.x = p.x;
		tmp.y = p.y;
		tmp.z = p.z;
		tmp.x /= size;
		tmp.y /= size;
		tmp.z /= size;
		value += smooth_noise(tmp, e, 0) * size;
		size /= 2.0;
	}
	return(128.0 * value / initialSize);
}

void sin_stripes(t_env *e, int i, int w)
{
	int x;
	int y;
	int z;
	int c1 = 0xFF0000;
	int c2 = 0x00FF00;
	double t;
	e->scene.text[i].zoom = 2;
	z = -1;
	while (++z < TEXT_SIZE)
	{
		y = -1;
		while (++y < TEXT_SIZE)
		{
			x = -1;
			while (++x < TEXT_SIZE)
			{
				/*
				 * checkerboard
				 */
			if (((sin(M_PI * y / w) > 0 && sin(M_PI * z / w) > 0)) || ((sin(M_PI * y / w) <= 0 && sin(M_PI * z / w) <= 0)))
				e->scene.text[i].text_arr[z][y][x] = c1;
			else
				e->scene.text[i].text_arr[z][y][x] = c2;
				/*
				 * round stripe
				 */
//			if (sin(M_PI * x / w) > 0)
//				e->scene.text[i].text_arr[z][y][x] = c1;
//			else
//				e->scene.text[i].text_arr[z][y][x] = c2;
				/*
				* vertical stripe
				*/
//			if (sin(M_PI * y / w) > 0)
//				e->scene.text[i].text_arr[z][y][x] = c1;
//			else
//				e->scene.text[i].text_arr[z][y][x] = c2;
//			}
				/*
				* horisontal stripe
				*/
//			if (sin(M_PI * z / w) > 0)
//				e->scene.text[i].text_arr[z][y][x] = c1;
//			else
//				e->scene.text[i].text_arr[z][y][x] = c2;
			}
		}
	}
}


void wood(int i, t_env *e)
{
	perlin_noise(e, 0, 2);
	double rings = 24.0;
	double twist = 0.1;
	double turb_size = 32;
	t_vector color;
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
				twist * turbulence(vector_save(x, y, z), e, turb_size) / 256.0;

				double sinval = 128.0 * fabs(sin(2 * rings * distval * M_PI));
				color.x = 80 + sinval;
				color.y = 30 + sinval;
				color.z = 30;
				e->scene.text[i].text_arr[x][y][z] = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
			}
		}
	}
}

void generate_textures(t_env *e)
{
//	e->scene.text = (t_text *)malloc(sizeof(t_text) * 10);
//	perlin_noise(e, 0, 2);
//	sin_stripes(e, 1, 2);
//	wood(2, e);

	printf("start\n");
	e->scene.img[0].i = mlx_xpm_file_to_image(e->mlx, "Grass.xpm",
												&e->scene.img[0].w, &e->scene.img[0].h);
	printf("middle\n");
	e->scene.img[0].data = mlx_get_data_addr(e->scene.img[0].i, &e->scene.img[0].bpp,
											 &e->scene.img[0].sl, &e->scene.img[0].endian);
	printf("end\n");
}

void texture(t_env *e, int curr, int i)
{
	t_vector p;
/*
 * noise
 */
	p.x = fabs(e->scene.point.x);
	p.y = fabs(e->scene.point.y);
	p.z = fabs(e->scene.point.z);
	double value;
//	value = smooth_noise(p, e, i);
//	e->scene.obs[curr].color.x = 256 * value;
//	e->scene.obs[curr].color.y = 256 * value;
//	e->scene.obs[curr].color.z = 256 * value;
//	value = turbulence(p, e, 4);
//	e->scene.obs[curr].color.x = value;
//	e->scene.obs[curr].color.y = value;
//	e->scene.obs[curr].color.z = value * 10;
/*
 * stripes
 */
////	x = abs((int)e->scene.point.x) % TEXT_SIZE;
////	y = abs((int)e->scene.point.y) % TEXT_SIZE;
//	int color = (int)e->scene.text[1].text_arr[(int)p.z][(int)p.y][(int)p.x];
//	e->scene.obs[curr].color.x = (color >> 16) & 0xFF;
//	e->scene.obs[curr].color.y = (color >> 8) & 0xFF;
//	e->scene.obs[curr].color.z = color & 0xFF;
/*
 * wood (does not work properly);
 */
	int color = (int)e->scene.text[2].text_arr[(int)(p.x * 10) % TEXT_SIZE][(int)(p.y * 10) % TEXT_SIZE][(int)(p.z * 10) % TEXT_SIZE];
	e->scene.obs[curr].color.x = (color >> 16) & 0xFF;
	e->scene.obs[curr].color.y = (color >> 8) & 0xFF;
	e->scene.obs[curr].color.z = color & 0xFF;
}

