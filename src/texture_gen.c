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
	main->textures = (t_text *)malloc(sizeof(t_text) * 6);
	ft_bzero(main->textures, 1);
	perlin_noise(main, 2);
//	wood(main);
	main->img = (t_img *)malloc(sizeof(t_img) * 5);
	ft_bzero(main->img, 5);
	main->img[0].img = mlx_xpm_file_to_image(main->mlx.mlx,
		"textures/Brick.xpm", &main->img[0].w, &main->img[0].h);
	main->img[0].data = mlx_get_data_addr(main->img[0].img, &main->img[0].bpp,
		&main->img[0].sl, &main->img[0].endian);
	main->img[1].img = mlx_xpm_file_to_image(main->mlx.mlx,
		"textures/RedStone.xpm", &main->img[1].w, &main->img[1].h);
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
		"textures/Stone.xpm", &main->img[4].w, &main->img[4].h);
	main->img[4].data = mlx_get_data_addr(main->img[4].img, &main->img[4].bpp,
		&main->img[4].sl, &main->img[4].endian);
}
