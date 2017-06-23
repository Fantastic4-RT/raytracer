#include <rt.h>



void 	find_pixel_color(t_main *main)
{
	t_vec3 p;
//	double value;

	p.x = fabs(main->obj[main->curr].hitpoint.x);
	p.y = fabs(main->obj[main->curr].hitpoint.y);
	p.z = fabs(main->obj[main->curr].hitpoint.z);
	if (main->mode.text_index - 1 >= 0 && main->mode.text_index <= 3)
	{
//		int color = (int)main->textures[main->mode.text_index - 1].text_arr[z][y][x];
		printf("%d %d %d\n",(int)p.x, (int)p.y, (int)p.z);
		int color = (int)main->textures[0].text_arr[(int)(p.x * 10) % TEXT_SIZE][(int)(p.y * 10) % TEXT_SIZE][(int)(p.z * 10) % TEXT_SIZE];

//		int color = (int)main->textures[main->mode.text_index - 1].text_arr[(int)p.x][(int)p.y][(int)p.z];
		main->obj[main->curr].mat.color =
				vec3_create(((color >> 16) & 0xFF) / 255,
							((color >> 8) & 0xFF) / 255, (color & 0xFF) / 255);
	}
//	else if (main->mode.text_index - 1 == 4)
//	{
//		// just perlin noise ????
//	}
//	else if (main->mode.text_index - 1 == 5)
//	{
//		int color = (int)main->textures[5].text_arr[(int)(p.x * 10) % TEXT_SIZE][(int)(p.y * 10) % TEXT_SIZE][(int)(p.z * 10) % TEXT_SIZE];
//		main->obj[main->curr].mat.color = vec3_create((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
//	}
//	else if ( main->mode.text_index - 1 == 6)
//	{
//		value = smooth_noise(p, main);
//		main->obj[main->curr].mat.color.x = 256 * value;
//		main->obj[main->curr].mat.color.y = 256 * value;
//		main->obj[main->curr].mat.color.z = 256 * value;
//	}
//	else if (main->mode.text_index - 1 == 7)
//	{
//		value = turbulence(p, main, 4);
//		main->obj[main->curr].mat.color.x = value;
//		main->obj[main->curr].mat.color.y = value;
//		main->obj[main->curr].mat.color.z = value * 10;
//	}
}

void generate_textures(t_main *main)
{
	main->textures = (t_text *)malloc(sizeof(t_text) * 10);
	ft_bzero(main->textures, 10);
	sin_stripes(main, 2);
}


void sin_stripes(t_main *main, int w)
{
	int x;
	int y;
	int z;
	int c1 = 0xFF0000;
	int c2 = 0x00FF00;

	main->textures[0].zoom = 2;
//	main->textures[1].zoom = 2;
//	main->textures[2].zoom = 2;
//	main->textures[3].zoom = 2;
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
//				main->textures[1].text_arr[z][y][x] = sin(M_PI * x / w) > 0 ?
//													  c1 : c2;
//				main->textures[2].text_arr[z][y][x] = sin(M_PI * y / w) > 0 ?
//													  c1 : c2;
//				main->textures[3].text_arr[z][y][x] = sin(M_PI * z / w) > 0 ?
//													  c1 : c2;
			}
		}
	}
}
