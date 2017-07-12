/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 15:32:03 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/06 15:32:06 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	toon_effect(t_vec3 df_sp[], t_vec3 *hitcolor, t_main *main)
{
	if (df_sp[3].x > 0.95 && main->toon == 1)
		*hitcolor = df_sp[2];
	else if (df_sp[3].x > 0.5 && df_sp[2].x < 0.95 && main->toon == 1)
		*hitcolor = vec3_mult(df_sp[2], 0.7);
	else if (df_sp[3].x > 0.2 && df_sp[3].x < 0.5 && main->toon == 1)
		*hitcolor = vec3_mult(df_sp[2], 0.2);
	else if (df_sp[3].x < 0.2 && main->toon == 1)
		*hitcolor = vec3_mult(df_sp[2], 0.05);
}

t_vec3	int_to_vec3(int color)
{
	return (vec3_create(((color >> 16) & 0xFF) / 255.0,
						((color >> 8) & 0xFF) / 255.0, (color & 0xFF) / 255.0));
}

void	perlin_noise(t_main *main, float zoom)
{
	int x;
	int y;

	main->textures[0].zoom = (int)zoom;
	y = 0;
	while (y < TEXT_S)
	{
		x = 0;
		while (x < TEXT_S)
		{
			main->textures[0].text_arr[y][x] = (rand() % 32768) / 32768.0;
			x++;
		}
		y++;
	}
}

void	generate_textures(t_main *main)
{
	perlin_noise(main, 2);
	main->img[0].img = mlx_xpm_file_to_image(main->mlx.mlx,
		"textures/Brick.xpm", &main->img[0].w, &main->img[0].h);
	main->img[0].data = mlx_get_data_addr(main->img[0].img, &main->img[0].bpp,
		&main->img[0].sl, &main->img[0].endian);
	main->img[1].img = mlx_xpm_file_to_image(main->mlx.mlx,
		"textures/Azurite.xpm", &main->img[1].w, &main->img[1].h);
	main->img[1].data = mlx_get_data_addr(main->img[1].img, &main->img[1].bpp,
		&main->img[1].sl, &main->img[1].endian);
	main->img[2].img = mlx_xpm_file_to_image(main->mlx.mlx, "textures/Sky.xpm",
		&main->img[2].w, &main->img[2].h);
	main->img[2].data = mlx_get_data_addr(main->img[2].img, &main->img[2].bpp,
		&main->img[2].sl, &main->img[2].endian);
	main->img[3].img = mlx_xpm_file_to_image(main->mlx.mlx,
		"textures/Grass.xpm", &main->img[3].w, &main->img[3].h);
	main->img[3].data = mlx_get_data_addr(main->img[3].img, &main->img[3].bpp,
		&main->img[3].sl, &main->img[3].endian);
	main->img[4].img = mlx_xpm_file_to_image(main->mlx.mlx,
		"textures/Beryllium.xpm", &main->img[4].w, &main->img[4].h);
	main->img[4].data = mlx_get_data_addr(main->img[4].img, &main->img[4].bpp,
		&main->img[4].sl, &main->img[4].endian);
}

void	change_texture(int keycode, t_main *main)
{
	if (keycode >= 83 && keycode <= 91
		&& main->obj[main->mode.obj_index].texture == 0)
		main->obj[main->mode.obj_index].tmp_color =
				main->obj[main->mode.obj_index].mat.color;
	if (keycode == 83)
		main->obj[main->mode.obj_index].texture = 1;
	else if (keycode == 84)
		main->obj[main->mode.obj_index].texture = 2;
	else if (keycode == 85)
		main->obj[main->mode.obj_index].texture = 3;
	else if (keycode == 86)
		main->obj[main->mode.obj_index].texture = 4;
	else if (keycode == 87)
		main->obj[main->mode.obj_index].texture = 5;
	else if (keycode == 88)
		main->obj[main->mode.obj_index].texture = 6;
	else if (keycode == 89)
		main->obj[main->mode.obj_index].texture = 7;
	else if (keycode == 91)
		main->obj[main->mode.obj_index].texture = 8;
	image(main);
}
