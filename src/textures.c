/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 13:39:30 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/06 13:39:31 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

double	smooth_noise(t_vec3 p, t_main *main)
{
	t_vec3 f;
	t_vec3 p1;
	t_vec3 p2;
	double value;

	f.x = main->textures[0].zoom == 1 ? 1 : (p.x - (int)p.x);
	f.y = main->textures[0].zoom == 1 ? 1 : (p.y - (int)p.y);
	p1.x = ((int)p.x + TEXT_S) % TEXT_S;
	p1.y = ((int)p.y + TEXT_S) % TEXT_S;
	p2.x = (int)(p1.x + TEXT_S - 1) % TEXT_S;
	p2.y = (int)(p1.y + TEXT_S - 1) % TEXT_S;
	value = 0.0;
	value += f.x * f.y * main->textures[0].text_arr[(int)p1.y][(int)p1.x];
	value += (1 - f.x) * f.y * main->textures[0].text_arr[(int)p1.y][(int)p2.x];
	value += f.x * (1 - f.y) * main->textures[0].text_arr[(int)p2.y][(int)p1.x];
	value += (1 - f.x) * (1 - f.y) *
			main->textures[0].text_arr[(int)p2.y][(int)p2.x];
	return (value);
}

double	turbulence(t_vec3 p, t_main *main, double size)
{
	double value;
	double initial_size;

	value = 0.0;
	initial_size = size;
	while (size >= 1)
	{
		value += smooth_noise(vec3_create(p.x / size, p.y / size, p.z),
						main) * size;
		size /= 2.0;
	}
	return (128.0 * value / initial_size);
}

double	sin_stripes(t_vec3 p, t_thread *th, int w)
{
	int c1;
	int c2;

	c1 = 0xFFFFFF;
	c2 = 0x000000;
	if (th->obj[th->main.curr].texture == 1)
	{
		if (((sin(M_PI * p.x / w) > 0 && sin(M_PI * p.y / w) > 0))
			|| ((sin(M_PI * p.x / w) <= 0 && sin(M_PI * p.y / w) <= 0)))
			return (c1);
		else
			return (c2);
	}
	else if (th->obj[th->main.curr].texture == 2)
		return (sin(M_PI * p.x / w) > 0 ? c1 : c2);
	else
		return (sin(M_PI * p.y / w) > 0 ? c1 : c2);
}

double	wood(t_vec3 p, t_main *main)
{
	t_vec3 color;
	t_vec3 val;
	double distval;
	double sinval;

	val.x = (p.x - TEXT_S / 2) / (double)TEXT_S;
	val.y = (p.y - TEXT_S / 2) / (double)TEXT_S;
	distval = sqrt(val.x * val.x + val.y * val.y) + 0.1 *
		turbulence(vec3_create(p.x, p.y, 0), main, 32.0) / 256.0;
	sinval = 128.0 * fabs(sin(2 * 12.0 * distval * M_PI));
	color = vec3_create((80 + sinval), (30 + sinval), 30);
	return (((int)color.x << 16) | ((int)color.y << 8) | (int)color.z);
}

double	marble(t_vec3 p, t_main *main)
{
	t_vec3 color;
	t_vec3 val;
	double distval;
	double sinval;

	val.x = (p.x - TEXT_S / 2) / (double)TEXT_S;
	val.y = (p.y - TEXT_S / 2) / (double)TEXT_S;
	distval = sqrt(val.x * val.x + val.y * val.y) + 0.5 *
		turbulence(vec3_create(p.x, p.y, 0), main, 32.0) / 256.0;
	sinval = 128.0 * fabs(sin(2 * 12.0 * distval * M_PI));
	color = vec3_create((10 + sinval), (30 + sinval), 30);
	return (((int)color.x << 16) | ((int)color.y << 8) | (int)color.z);
}
