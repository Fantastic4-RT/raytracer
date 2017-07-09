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

void		print_status(t_main *main)
{
	ft_putendl("----------------------------------------------------");
	output("Object mode ", main->mode.obj_mode);
	output("-Move mode ", main->mode.move_mode);
	output("-Object index ", main->mode.obj_index);
	output("-Object rotation mode ", main->mode.rot_obj_mode);
	output("-Texture mode ", main->mode.text_mode);
	output("-Texture index ", main->obj[main->mode.obj_index].texture);
	output("-Color mode ", main->mode.color_mode);
	ft_putstr("-Channel ");
	ft_putchar(main->mode.channel);
	ft_putchar('\n');
	output("Camera mode ", main->mode.cam_mode);
	output("-Direction mode ", main->mode.dir_mode);
	output("-Camera rotation mode ", main->mode.rot_cam_mode);
	output("-Camera position mode ", main->mode.cam_pos_mode);
	output("Anti-aliasing ", main->scene.a_a);
	ft_putendl("*******************************************************");
}
