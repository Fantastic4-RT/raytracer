/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envinronment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 17:06:18 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 17:06:20 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		alias_mode(int keycode, t_main *main)
{
	if (keycode == 37 && main->scene.a_a == 0)
	{
		main->scene.a_a = 1;
		image(main);
	}
	else if (keycode == 37 && main->scene.a_a == 1)
	{
		main->scene.a_a = 2;
		image(main);
	}
	else if (keycode == 37 && main->scene.a_a == 2)
	{
		main->scene.a_a = 0;
		image(main);
	}
}

void		init_images(t_main *main)
{
	main->mlx.menu.side_arr = mlx_xpm_file_to_image(main->mlx.mlx,
		"side_arrow.xpm", &main->mlx.menu.w, &main->mlx.menu.h);
	main->mlx.menu.vert_arr = mlx_xpm_file_to_image(main->mlx.mlx,
		"down_arrow.xpm", &main->mlx.menu.w, &main->mlx.menu.h);
	main->obj[0].tmp_color = vec3_create(0, 0, 0);
	main->mode.off = 1;
	main->mode.cam_mode = 0;
	main->mode.dir_mode = 0;
	main->mode.rot_cam_mode = 0;
	main->mode.cam_pos_mode = 0;
	main->mode.obj_mode = 0;
	main->mode.obj_index = 0;
	main->mode.color_mode = 0;
	main->mode.channel = 0;
	main->mode.move_mode = 0;
	main->mode.rot_obj_mode = 0;
	main->mode.text_mode = 0;
	main->mode.text_index = 0;
	main->mode.loaded = 1;
	main->mode.count = vec3_create(0., 0., 0.);
}

t_mattype	get_material_type(t_material mat)
{
	if (mat.refract != 0 && mat.reflect != 0)
		return (REFLECT_REFRACT);
	else if (mat.refract == 0 && mat.reflect != 0)
		return (REFLECT);
	else
		return (LAMBERT);
}
